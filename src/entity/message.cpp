#include "message.h"
namespace chat_box {
Message::Message(const std::string &payload, const bsoncxx::oid &user_id,
                 const bsoncxx::oid &chat_room_id)
    : payload(payload), user_id(user_id), chat_room_id(chat_room_id) {
  this->time_stamp = std::chrono::system_clock::now();
}
} // namespace chat_box