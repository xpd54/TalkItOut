#pragma once
#include "../connection/mongo.h"
#include <chrono>
#include <string>
namespace chat_box {
class Message {
  private:
    /* data */
  public:
    Message(const bsoncxx::types::b_oid &message_id, // nowrap
            const std::string &payload,              // nowrap
            const bsoncxx::types::b_oid &sender_id,  // nowrap
            const bsoncxx::types::b_oid &destination_id);

    bsoncxx::types::b_oid message_id;
    std::string payload;
    bsoncxx::types::b_oid sender_id;
    bsoncxx::types::b_oid destination_id;
    std::chrono::system_clock::time_point time_stamp;
    void logDetails();
};

} // namespace chat_box