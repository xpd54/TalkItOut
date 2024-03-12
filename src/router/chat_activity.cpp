#include "chat_activity.h"
#include "../common/constant.hpp"
namespace route {
crow::response Chat::send_message_to_room(const mongo_connection::Mongo &mongo, const std::string message,
                                          const std::string user_id, const std::string chat_room_id) const {
    bsoncxx::oid user_oid(user_id);
    bsoncxx::types::b_oid user_b_oid;
    user_b_oid.value = user_oid;

    bsoncxx::oid chat_room_oid(chat_room_id);
    bsoncxx::types::b_oid chat_room_b_oid;
    chat_room_b_oid.value = chat_room_oid;

    int32_t added_count = mongo.add_message_to_room(message, user_b_oid, chat_room_b_oid);
    crow::json::wvalue res;
    res[response_key::messages_sent] = added_count;
    return crow::response(200, res);
}
// Crow::response Chat::get_all_messages_from_room(const mongo_connection::Mongo &mongo,
//                                                 const std::string chat_room_id) const;
// Crow::response Chat::get_all_rooms_for_user(const mongo_connection::Mongo &mongo, const std::string user_id) const;
} // namespace route