#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"
#include "../entity/user.h"
namespace route {
class Signin {
  private:
    /* data */
  public:
    crow::response sing_in(const mongo_connection::Mongo &mongo, const chat_box::User &user) const;
};

} // namespace route