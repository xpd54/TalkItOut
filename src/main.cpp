#include "../include/crow.h"
#include "./common/constant.hpp"
#include "./entity/user.h"
#include "./router/health.h"
#include "./router/room_builder.h"
#include "./router/signin.h"
#include "./router/signup.h"
#include "connection/mongo.h"
#include <iostream>
int main(int argc, char *argv[]) {
  // The mongocxx::instance constructor initialize the driver:
  // it must be created before using the driver and
  // must remain alive for as long as the driver is in use.
  mongocxx::instance inst{};
  mongo_connection::Mongo mongo;
  mongo.connect();

  crow::SimpleApp app;

  route::Health health;
  /*Capture of lambdas is by reference avoid copy of object*/
  CROW_ROUTE(app, "/health")
  ([&health, &mongo]() { return health.health_check(mongo); });

  route::Signup signup_module;
  CROW_ROUTE(app, "/signup")
      .methods(crow::HTTPMethod::Post)(
          [&signup_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            chat_box::User user(body[user_schema::user_name].s(),
                                body[user_schema::password].s());
            return signup_module.sign_up(mongo, user);
          });

  route::Signin signin_module;
  CROW_ROUTE(app, "/signin")
      .methods(crow::HTTPMethod::POST)(
          [&signin_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            chat_box::User user(body[user_schema::user_name].s(),
                                body[user_schema::password].s());
            return signin_module.sing_in(mongo, user);
          });
  route::Room room_builder_module;
  CROW_ROUTE(app, "/create_room")
      .methods(crow::HTTPMethod::POST)([&room_builder_module,
                                        &mongo](const crow::request &req) {
        crow::json::rvalue body = crow::json::load(req.body);
        return room_builder_module.create_a_room(
            mongo, body[room_schema::room_name].s(), body[user_schema::id].s());
      });
  CROW_ROUTE(app, "/join_room")
      .methods(crow::HTTPMethod::POST)(
          [&room_builder_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
          });
  app.port(18080).multithreaded().run();
}
