#include "../include/crow.h"
#include "./router/health.h"
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
  CROW_ROUTE(app, "/signup")([]() { return "You got signed up"; });
  CROW_ROUTE(app, "/signin")([]() { return "you are signed in"; });
  app.port(18080).multithreaded().run();
}
