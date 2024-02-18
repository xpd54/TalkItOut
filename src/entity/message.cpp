#include "message.h"
#include <iostream>
namespace chat_box {
Message::Message(const bsoncxx::types::b_oid &message_id,
                 const std::string &payload,
                 const bsoncxx::types::b_oid &user_id,
                 const bsoncxx::types::b_oid &chat_room_id)
    : payload(payload), user_id(user_id), chat_room_id(chat_room_id),
      message_id(message_id) {
  this->time_stamp = std::chrono::system_clock::now();
}

void Message::logDetails() {
  std::cout << "Message Payload " << this->payload << "\n"
            << "Userid " << this->user_id.value.to_string() << "\n"
            << "register_time_stamp "
            << std::chrono::system_clock::to_time_t(this->time_stamp) << "\n";
}
} // namespace chat_box