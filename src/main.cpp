#include "../include/crow.h"
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
  bool is_db_connected = mongo.checkConnection();
  is_db_connected ? std::cout << "MongoDb is connected\n"
                  : std::cout << "Mongdb is not connected\n";
  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([]() { return "Hello world"; });
  app.port(18080).multithreaded().run();
}
