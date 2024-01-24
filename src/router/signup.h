#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"
namespace route {
class Signup {
private:
  /* data */
public:
  crow::json::wvalue signup(mongo_connection::Mongo &mongo) const;
};

} // namespace route
