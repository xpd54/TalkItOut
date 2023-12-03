#pragma once
#include <bsoncxx/json.hpp>
#include <iostream>
#include <mongocxx/client.hpp>
#include <mongocxx/uri.hpp>
namespace mongo_connection {

class Mongo {
public:
  Mongo();
  bool AddMarioCharecterToDb(const std::string &charrecter_name,
                             const int16_t &size, const int16_t &win);

private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database db;
};
}; // namespace mongo_connection