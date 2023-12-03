#include "mongo.h"
#include "../common/constant.hpp"
#include <bsoncxx/builder/stream/document.hpp>
namespace mongo_connection {

Mongo::Mongo()
    : uri(mongocxx::uri(connection_constant::mongodbUri)),
      client(mongocxx::client(uri)),
      db(client[connection_constant::databaseName]) {}
bool Mongo::AddMarioCharecterToDb(const std::string &charrecter_name,
                                  const int16_t &size, const int16_t &win) {
  mongocxx::collection collection = Mongo::db[connection_constant::marioDb];
  auto builder = bsoncxx::builder::stream::document{};
  bsoncxx::document::value doc_to_add =
      builder << "charecterName" << charrecter_name << "size" << size << "wins"
              << win << bsoncxx::builder::stream::finalize;
  collection.insert_one(doc_to_add.view());
  return true;
}
}; // namespace mongo_connection