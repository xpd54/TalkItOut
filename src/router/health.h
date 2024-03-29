#pragma once
#include "../common/constant.hpp"
#include "../connection/mongo.h"
#include "../include/crow.h"
namespace route {
class Health {
  public:
    crow::response health_check(const mongo_connection::Mongo &mongo) const;
};

}; // namespace route