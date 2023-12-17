#include "user.h"
#include <iostream>
namespace chat_box {
User::User(const std::string &user_name, const std::string &password) {
  this->user_name = user_name;
  this->password = password;
}
User::~User() {
  std::cout << "User is getting deallocated"
            << "\n";
}

void User::logDetails() {
  std::cout << "user_name " << this->user_name << "\n"
            << "password " << this->password << "\n"
            << "register_time_stamp "
            << std::chrono::system_clock::to_time_t(this->register_time_stamp)
            << "\n";
}
} // namespace chat_box