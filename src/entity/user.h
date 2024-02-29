#pragma once
#include <chrono>
#include <string>
namespace chat_box {
class User {
  private:
    /* data */
  public:
    std::string user_name;
    std::string password;
    std::chrono::system_clock::time_point register_time_stamp;
    User();
    User(const std::string &user_name, const std::string &password);
    void logDetails();
    ~User();
};

}; // namespace chat_box