#pragma once
#include "../common/constant.hpp"
#include "../connection/mongo.h"
namespace route {
class Health {
public:
  connection_constant::status
  health_check(const mongo_connection::Mongo &mongo) const;
};

}; // namespace route