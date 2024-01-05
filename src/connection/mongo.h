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
  bsoncxx::types::b_oid signUp(const std::string &user_name,
                               const std::string &passsword);
  bsoncxx::stdx::optional<bsoncxx::types::b_oid>
  signIn(const std::string &user_name, const std::string &password);
  bsoncxx::type::b_oid find_a_room(const bsoncxx::type::b_oid &from,
                                   cosnt bsoncxx::type::b_oid &to);

private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database db;
  bsoncxx::stdx::optional<bsoncxx::document::value>
  findUser(const std::string &user_name, const std::string &password);
};
}; // namespace mongo_connection