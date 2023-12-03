#include "mongo.h"
#include <bsoncxx/builder/stream/document.hpp>
namespace mongo_connection {
const char mongodbUri[] = "mongodb://localhost:27017";
const char databaseName[] = "talk_it_out";
Mongo::Mongo()
    : uri(mongocxx::uri(mongodbUri)), client(mongocxx::client(uri)),
      db(client[databaseName]) {}
bool Mongo::AddMarioCharecterToDb(const std::string &charrecter_name,
                                  const int16_t &size, const int16_t &win) {
  mongocxx::collection collection = Mongo::db["mario"];
  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value doc_to_add =
      builder << "charecterName" << charrecter_name << "size" << size << "wins"
              << win << bsoncxx::builder::stream::finalize;
  collection.insert_one(doc_to_add.view());
  return true;
}
}; // namespace mongo_connection