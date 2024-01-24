#include "health.h"

namespace route {
connection_constant::status
Health::health_check(const mongo_connection::Mongo &mongo) const {
  bool is_db_connected = mongo.checkConnection();
  return is_db_connected ? connection_constant::status::connected
                         : connection_constant::status::disconnected;
}
}; // namespace route