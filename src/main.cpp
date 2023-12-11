#include "../include/crow.h"
#include "connection/mongo.h"
#include <iostream>
#include <mongocxx/instance.hpp>
int main(int argc, char *argv[]) {
  mongocxx::instance instance;
  mongo_connection::Mongo connection;
  std::cout << connection.checkConnection() << '\n';
  crow::SimpleApp app;
  CROW_ROUTE(app, "/")([]() { return "Hello world"; });
  app.port(18080).multithreaded().run();
}
