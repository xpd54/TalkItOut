#include "message.h"
#include <iostream>
namespace chat_box {
Message::Message(const bsoncxx::types::b_oid &message_id, // nowrap
                 const std::string &payload,              // nowrap
                 const bsoncxx::types::b_oid &sender_id,  // nowrap
                 const bsoncxx::types::b_oid &destination_id)
    : payload(payload), sender_id(sender_id), destination_id(destination_id), message_id(message_id) {
    this->time_stamp = std::chrono::system_clock::now();
}

void Message::logDetails() {
    std::cout << "Message Payload " << this->payload << "\n"
              << "Userid " << this->sender_id.value.to_string() << "\n"
              << "register_time_stamp " << std::chrono::system_clock::to_time_t(this->time_stamp) << "\n";
}
} // namespace chat_box