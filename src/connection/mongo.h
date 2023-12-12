#pragma once
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
namespace mongo_connection {

class Mongo {
public:
  Mongo();
  void connect();
  bool checkConnection();
private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database db;
};
}; // namespace mongo_connection