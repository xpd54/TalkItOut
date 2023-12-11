#include "mongo.h"
#include "../common/constant.hpp"
#include <bsoncxx/builder/list.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <iostream>
namespace mongo_connection {

Mongo::Mongo()
    : uri(mongocxx::uri(connection_constant::mongodbUri)),
      client(mongocxx::client(uri)),
      db(client[connection_constant::databaseName]) {
  std::cout << "Database Initialized"
            << "\n";
}

bool setVersion(const mongocxx::database &db) {
  if (!db.has_collection(db_collection::version)) {
    mongocxx::collection version_collection = db[db_collection::version];
    bsoncxx::builder::stream::document version;
    version << "version" << 1 << bsoncxx::builder::stream::finalize;
    version_collection.insert_one(version.view());
  }
  return true;
}

bool Mongo::checkConnection() {
  bool isVersionFound = setVersion(this->db);
  return isVersionFound;
}

bool Mongo::AddMarioCharecterToDb(const std::string &charrecter_name,
                                  const int16_t &size, const int16_t &win) {
  mongocxx::collection collection = Mongo::db[db_collection::version];
  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value doc_to_add =
      builder << "charecterName" << charrecter_name << "size" << size << "wins"
              << win << bsoncxx::builder::stream::finalize;
  collection.insert_one(doc_to_add.view());
  return true;
}
}; // namespace mongo_connection