#include "health.h"
#include "../common/constant.hpp"
namespace route {
crow::json::wvalue
Health::health_check(const mongo_connection::Mongo &mongo) const {
  bool is_db_connected = mongo.checkConnection();
  crow::json::wvalue res;
  res[response_key::status] = is_db_connected;
  return res;
}
}; // namespace route