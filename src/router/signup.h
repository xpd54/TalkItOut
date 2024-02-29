#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"
#include "../entity/user.h"
namespace route {
class Signup {
  private:
    /* data */
  public:
    crow::response sign_up(const mongo_connection::Mongo &mongo, const chat_box::User &user) const;
};

} // namespace route
