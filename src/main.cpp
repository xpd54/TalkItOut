#include "../include/crow.h"
#include "connection/mongo.h"
#include <iostream>
#include <mongocxx/instance.hpp>
int main(int argc, char *argv[]) {
  mongo_connection::Mongo mongo;
  mongo.connect();
  std::cout << mongo.checkConnection() << '\n';
  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([]() { return "Hello world"; });
  app.port(18080).multithreaded().run();
}
