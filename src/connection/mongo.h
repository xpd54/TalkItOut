#pragma once
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <string>
namespace mongo_connection {

class Mongo {
public:
  Mongo();
  void connect();
  bool checkConnection();
  bsoncxx::stdx::string_view signUp(const std::string &user_name,
                                    const std::string &passsword);

private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database db;
};
}; // namespace mongo_connection