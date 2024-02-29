#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"

namespace route {
class Chat {
  public:
    Crow::response send_message_to_room(const mongo_connection::Mongo &mongo, const std::string message,
                                        const std::string user_id, const std::string chat_room_id) const;
    Crow::response get_all_messages_from_room(const mongo_connection::Mongo &mongo,
                                              const std::string chat_room_id) const;
    Crow::response get_all_rooms_for_user(const mongo_connection::Mongo &mongo, const std::string user_id) const;
}
} // namespace route