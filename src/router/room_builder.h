#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"
namespace route {
class Room {
  private:
    /* data */
  public:
    crow::response create_a_room(const mongo_connection::Mongo &mongo, const std::string &room_name,
                                 const std::string &user_id) const;
    crow::response join_a_room(const mongo_connection::Mongo &mongo, const std::string &chat_room_id,
                               const std::string &user_id) const;
    crow::response exit_a_room(const std::string &chat_room_id);
};
} // namespace route