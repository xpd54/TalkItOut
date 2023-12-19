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
  std::string user_name = "xpd54_hello";
  std::string password = "hellow_kdf@test..";
  bsoncxx::stdx::string_view user = mongo.signUp(user_name, password);
  std::cout << user << "\n";

  bool is_db_connected = mongo.checkConnection();
  is_db_connected ? std::cout << "MongoDb is connected\n"
                  : std::cout << "Mongdb is not connected\n";
  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([]() { return "Hello world"; });
  app.port(18080).multithreaded().run();
}
