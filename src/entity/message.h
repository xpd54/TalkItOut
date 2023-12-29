#pragma once
#include <bsoncxx/oid.hpp>
#include <chrono>
#include <string>
namespace chat_box {
class Message {
private:
  /* data */
public:
  Message(const std::string &payload, const bsoncxx::oid &user_id,
          const bsoncxx::oid &chat_room_id);
  std::string payload;
  bsoncxx::oid user_id;
  bsoncxx::oid chat_room_id;
  std::chrono::system_clock::time_point time_stamp;
  void logDetails();
};

} // namespace chat_box