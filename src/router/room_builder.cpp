#include "room_builder.h"
#include "../common/constant.hpp"
namespace route {
crow::response Room::create_a_room(const mongo_connection::Mongo &mongo,
                                   const std::string &room_name,
                                   const std::string &user_id) const {
  bsoncxx::oid user_oid(user_id);
  // handle error for non valud string for oid
  bsoncxx::types::b_oid user_b_oid;
  user_b_oid.value = user_oid;
  bsoncxx::types::b_oid room_id = mongo.create_a_room(room_name, user_b_oid);
  crow::json::wvalue res;
  res[response_key::room_id] = room_id.value.to_string();
  res[response_key::user_id] = user_id;
  return crow::response(200, res);
}
} // namespace route