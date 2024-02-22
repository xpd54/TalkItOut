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
    bsoncxx::types::b_oid signUp(const std::string &user_name, const std::string &passsword) const;
    bsoncxx::stdx::optional<bsoncxx::types::b_oid> signIn(const std::string &user_name,
                                                          const std::string &password) const;
    // pass
    bsoncxx::types::b_oid create_a_room(const std::string &room_name, const bsoncxx::types::b_oid &user_id) const;
    int32_t join_a_room(const bsoncxx::types::b_oid &chat_room_id, const bsoncxx::types::b_oid &user_id) const;
    bool exit_a_room(const bsoncxx::types::b_oid &chat_room_id);

    int32_t add_message_to_room(const std::string &payload, const bsoncxx::types::b_oid &user_id,
                                const bsoncxx::types::b_oid &chat_room_id) const;

    bsoncxx::types::b_array get_all_messages_for_room(const bsoncxx::types::b_oid &chat_room_id) const;

    bsoncxx::types::b_array get_all_rooms_for_user(const bsoncxx::types::b_oid &user_id) const;

  private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
    bsoncxx::stdx::optional<bsoncxx::document::value> findUser(const std::string &user_name,
                                                               const std::string &password) const;
    bsoncxx::stdx::optional<bsoncxx::document::value> find_a_room(const bsoncxx::types::b_oid &chat_room_id);
    mongocxx::cursor find_rooms(const std::string &room_name) const;
};
}; // namespace mongo_connection