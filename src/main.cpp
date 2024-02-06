#include "../include/crow.h"
#include "./common/constant.hpp"
#include "./entity/user.h"
#include "./router/health.h"
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
  ([&health, &mongo]() {
    crow::json::wvalue res = health.health_check(mongo);
    return crow::response(200, res);
  });

  route::Signup signup_module;
  CROW_ROUTE(app, "/signup")
      .methods(crow::HTTPMethod::Post)(
          [&signup_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            const std::string user_name = body[user_schema::user_name].s();
            const std::string password = body[user_schema::password].s();
            chat_box::User user(user_name, password);
            crow::json::wvalue res = signup_module.sign_up(mongo, user);
            return crow::response(201, res);
          });

  route::Signin signin_module;
  CROW_ROUTE(app, "/signin")
      .methods(crow::HTTPMethod::POST)(
          [&signin_module, &mongo](const crow::request &req) {
            crow::json::rvalue body = crow::json::load(req.body);
            chat_box::User user(body[user_schema::user_name].s(),
                                body[user_schema::password].s());
            crow::response res = signin_module.sing_in(mongo, user);
            return res;
          });
  app.port(18080).multithreaded().run();
}
