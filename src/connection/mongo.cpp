#include "mongo.h"
namespace mongo_connection {
const char mongodbUri[] = "mongodb://localhost:27017";
const char databaseName[] = "talk_it_out";
Mongo::Mongo()
    : uri(mongocxx::uri(mongodbUri)), client(mongocxx::client(uri)),
      db(client[databaseName]) {}
}; // namespace mongo_connection