#pragma once
#include <bsoncxx/json.hpp>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
namespace mongo_connection {

class Mongo {
public:
  Mongo();
  void connect();
  bool checkConnection();

  bool AddMarioCharecterToDb(const std::string &charrecter_name,
                             const int16_t &size, const int16_t &win);

private:
  // The mongocxx::instance constructor initialize the driver:
  // it must be created before using the driver and
  // must remain alive for as long as the driver is in use.
  mongocxx::instance inst{};

  mongocxx::uri uri;
  mongocxx::client connection;
  mongocxx::database db;
};
}; // namespace mongo_connection