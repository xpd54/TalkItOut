#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"

namespace route {
class Signin {
private:
  /* data */
public:
  crow::json::wvalue Signin::sing_in(const mongo_connection::Mongo &mongo,
                                     const std::string &user_name,
                                     const std::string &password) const {}
};

} // namespace route