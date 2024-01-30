#include "../include/crow.h"
#include "./entity/user.h"
#include "./router/health.h"
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
  std::string user_name = "xpd54";
  std::string password = "hellow_kdf@test..";
  bsoncxx::stdx::optional<bsoncxx::types::b_oid> user =
      mongo.signUp(user_name, password);
  std::cout << user->value.to_string() << "\n";
  if (user) {
    mongo.create_a_room("weekend plans", user.value());
  }

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
            return crow::response(200, res);
          });
  CROW_ROUTE(app, "/signin")([]() { return "you are signed in"; });
  app.port(18080).multithreaded().run();
}
