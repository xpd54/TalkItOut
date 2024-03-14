#include "chat_activity.h"
#include "../common/constant.hpp"
#include <bsoncxx/json.hpp>
namespace route {
crow::response Chat::send_message_to_room(const mongo_connection::Mongo &mongo, const std::string message,
                                          const std::string user_id, const std::string chat_room_id) const {
    bsoncxx::oid user_oid(user_id);
    bsoncxx::types::b_oid user_b_oid;
    user_b_oid.value = user_oid;

    bsoncxx::oid chat_room_oid(chat_room_id);
    bsoncxx::types::b_oid chat_room_b_oid;
    chat_room_b_oid.value = chat_room_oid;

    int32_t added_count = mongo.add_message_to_room(message, user_b_oid, chat_room_b_oid);
    crow::json::wvalue res;
    res[response_key::messages_sent] = added_count;
    return crow::response(200, res);
}
crow::response Chat::get_all_messages_from_room(const mongo_connection::Mongo &mongo,
                                                const std::string chat_room_id) const {
    bsoncxx::oid chat_room_oid(chat_room_id);
    bsoncxx::types::b_oid chat_room_b_oid;
    chat_room_b_oid.value = chat_room_oid;

    bsoncxx::stdx::optional<bsoncxx::types::b_array> messages = mongo.get_all_messages_for_room(chat_room_b_oid);
    crow::json::wvalue res;
    bsoncxx::types::b_array message_array = messages.value();
    res[response_key::message] = bsoncxx::to_json(message_array);
    return crow::response(200, res);
}
crow::response Chat::get_all_rooms_for_user(const mongo_connection::Mongo &mongo, const std::string user_id) const {
    bsoncxx::oid user_oid(user_id);
    bsoncxx::types::b_oid user_boid;
    user_boid.value = user_oid;

    bsoncxx::stdx::optional<bsoncxx::types::b_array> all_rooms = mongo.get_all_rooms_for_user(user_boid);
    std::string array_json = bsoncxx::to_json(all_rooms.value());
    std::cout << array_json << "\n";
    crow::json::wvalue res;
    res[response_key::chat_rooms] = array_json;
    return crow::response(200, res);
}
} // namespace route