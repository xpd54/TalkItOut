#include "room_builder.h"
#include "../common/constant.hpp"
namespace route {
crow::response Room::create_a_room(const mongo_connection::Mongo &mongo, // nowrap
                                   const std::string &room_name,         // nowrap
                                   const std::string &user_id) const {
    bsoncxx::oid user_oid(user_id);
    // handle error for non valud string for oid
    bsoncxx::types::b_oid user_b_oid;
    user_b_oid.value = user_oid; // b_oid is just a wrapper for oid
    bsoncxx::types::b_oid room_id = mongo.create_a_room(room_name, user_b_oid);
    crow::json::wvalue res;
    res[response_key::room_id] = room_id.value.to_string();
    res[response_key::user_id] = user_id;
    return crow::response(200, res);
}

crow::response Room::join_a_room(const mongo_connection::Mongo &mongo, // nowrap
                                 const std::string &chat_room_id,      // nowrap
                                 const std::string &user_id) const {
    bsoncxx::oid user_oid(user_id);
    bsoncxx::oid chat_room_oid(chat_room_id);
    bsoncxx::types::b_oid user_b_oid, chat_room_b_oid;
    user_b_oid.value = user_oid;
    chat_room_b_oid.value = chat_room_oid;

    int32_t joined = mongo.join_a_room(chat_room_b_oid, user_b_oid);
    crow::json::wvalue res;
    res[response_key::status] = joined;
    return crow::response(200, res);
}
} // namespace route