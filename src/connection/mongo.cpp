#include "mongo.h"
#include "../common/constant.hpp"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
namespace mongo_connection {

Mongo::Mongo() {}

void Mongo::connect() {
  uri = mongocxx::uri(connection_constant::mongodbUri);
  client = mongocxx::client(uri);
  db = client[connection_constant::databaseName];
  std::cout << "Database Initialized"
            << "\n";
}

bool setVersion(const mongocxx::database &db) {
  if (!db.has_collection(db_collection::version)) {
    mongocxx::collection version_collection = db.collection(db_collection::version);
    bsoncxx::document::value version = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("version", 5)
    );
    auto result = version_collection.insert_one(version.view());
    return true;
  } else {
    mongocxx::collection version_collection = db.collection(db_collection::version);
    bsoncxx::stdx::optional<bsoncxx::document::value> version  = version_collection.find_one({});
    bsoncxx::document::view view = version->view();
    bsoncxx::document::element version_view = view["version"];
    int32_t version_number = version_view.get_int32();
    std::cout << "Current Version is set as " << version_number << "\n";
    return version_number > 0;
  }
  return false;
}

bool Mongo::checkConnection() {
  bool isVersionFound = setVersion(this->db);
  return isVersionFound;
}
}; // namespace mongo_connection