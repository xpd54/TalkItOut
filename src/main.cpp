#include "../include/crow.h"
#include "./common/constant.hpp"
#include "./entity/user.h"
#include "./router/chat_activity.h"
#include "./router/health.h"
#include "./router/room_builder.h"
#include "./router/signin.h"
#include "./router/signup.h"
#include "connection/mongo.h"
#include <bsoncxx/json.hpp>
#include <iostream>
int main(int argc, char *argv[]) {
    // The mongocxx::instance constructor initialize the driver:
    // it must be created before using the driver and
    // must remain alive for as long as the driver is in use.
    mongocxx::instance inst{};
    mongo_connection::Mongo mongo;
    mongo.connect();

    bsoncxx::oid user_oid("65b8a3c8ba8543035303da82");
    bsoncxx::oid chat_room_oid("65b8a3c8ba8543035303da82");
    bsoncxx::types::b_oid user_id;
    user_id.value = user_oid;
    bsoncxx::types::b_oid chat_room_id;
    chat_room_id.value = chat_room_oid;
    bsoncxx::stdx::optional<bsoncxx::types::b_array> messages = mongo.get_all_messages_for_room(chat_room_id);
    if (messages) {
        bsoncxx::types::b_array messages_value = messages.value();
        std::string array_json = bsoncxx::to_json(messages_value);
        std::cout << "Array JSON: " << array_json << "\n";
    } else if (messages == bsoncxx::stdx::nullopt) {
        std::cout << "failed to find"
                  << "\n";
    }

    const int32_t count = mongo.add_message_to_room("Hello C++", user_id, chat_room_id);
    crow::SimpleApp app;

    route::Health health;
    /*Capture of lambdas is by reference avoid copy of object*/
    CROW_ROUTE(app, "/health")
    ([&health, &mongo]() { return health.health_check(mongo); });

    route::Signup signup_module;
    CROW_ROUTE(app, "/signup").methods(crow::HTTPMethod::Post)([&signup_module, &mongo](const crow::request &req) {
        crow::json::rvalue body = crow::json::load(req.body);
        chat_box::User user(body[request_key::user_name].s(), body[request_key::password].s());
        return signup_module.sign_up(mongo, user);
    });

    route::Signin signin_module;
    CROW_ROUTE(app, "/signin").methods(crow::HTTPMethod::POST)([&signin_module, &mongo](const crow::request &req) {
        crow::json::rvalue body = crow::json::load(req.body);
        chat_box::User user(body[request_key::user_name].s(), body[request_key::password].s());
        return signin_module.sing_in(mongo, user);
    });
    route::Room room_builder_module;
    CROW_ROUTE(app, "/create_room")
        .methods(crow::HTTPMethod::POST)([&room_builder_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            return room_builder_module.create_a_room(mongo, body[request_key::chat_room_name].s(),
                                                     body[request_key::user_id].s());
        });
    CROW_ROUTE(app, "/join_room")
        .methods(crow::HTTPMethod::POST)([&room_builder_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            return room_builder_module.join_a_room(mongo, body[request_key::chat_room_id].s(),
                                                   body[request_key::user_id].s());
        });
    route::Chat chat_activity_module;
    CROW_ROUTE(app, "/send_message")
        .methods(crow::HTTPMethod::POST)([&chat_activity_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            return chat_activity_module.send_message_to_room(mongo, body[request_key::message_payload].s(),
                                                             body[request_key::user_id].s(),
                                                             body[request_key::chat_room_id].s());
        });
    CROW_ROUTE(app, "/get_all_messages")
        .methods(crow::HTTPMethod::GET)([&chat_activity_module, &mongo](const crow::request &req) {
            std::string chat_room_id = req.url_params.get(request_key::chat_room_id);
            return chat_activity_module.get_all_messages_from_room(mongo, chat_room_id);
        });
    app.port(18080).multithreaded().run();
}
