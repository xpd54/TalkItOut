#pragma once
#include <bsoncxx/types.hpp>
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
  bool checkConnection() const;
  bsoncxx::types::b_oid signUp(const std::string &user_name,
                               const std::string &passsword);
  bsoncxx::stdx::optional<bsoncxx::types::b_oid>
  signIn(const std::string &user_name, const std::string &password);
  // pass
  bsoncxx::types::b_oid create_a_room(const std::string &room_name,
                                      const bsoncxx::types::b_oid &userId);
  int32_t join_a_room(const bsoncxx::types::b_oid &chat_room_id,
                      const bsoncxx::types::b_oid &user_id);
  bool exit_a_room(const bsoncxx::types::b_oid &roomId);

private:
  mongocxx::uri uri;
  mongocxx::client client;
  mongocxx::database db;
  bsoncxx::stdx::optional<bsoncxx::document::value>
  findUser(const std::string &user_name, const std::string &password);
  bsoncxx::stdx::optional<bsoncxx::document::value>
  find_a_room(const bsoncxx::types::b_oid &roomId);
  mongocxx::cursor find_rooms(const std::string &room_name);
};
}; // namespace mongo_connection