#include "mongo.h"
#include "../common/constant.hpp"
#include "../entity/user.h"
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

bool create_collection(const mongocxx::database &db) {
  mongocxx::collection new_collection = db.collection("Hello");
  auto hello = bsoncxx::builder::basic::make_document(
      bsoncxx::builder::basic::kvp("hello", "world"));
  new_collection.insert_one(hello.view());
  return true;
}

bool setVersion(const mongocxx::database &db) {
  if (!db.has_collection(db_collection::version)) {
    mongocxx::collection version_collection =
        db.collection(db_collection::version);

    bsoncxx::document::value version = bsoncxx::builder::basic::make_document(
        bsoncxx::builder::basic::kvp(db_collection::appVersion, 5));

    bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
        version_collection.insert_one(version.view());
    std::int32_t count = result->result().inserted_count();
    return count > 0;
  } else {
    mongocxx::collection version_collection =
        db.collection(db_collection::version);
    bsoncxx::stdx::optional<bsoncxx::document::value> version =
        version_collection.find_one({});
    bsoncxx::document::view view = version->view();
    bsoncxx::document::element version_view = view[db_collection::appVersion];
    std::int32_t version_number = version_view.get_int32();
    std::cout << "Current Version is set as " << version_number << "\n";
    return version_number > 0;
  }
  return false;
}

bool Mongo::checkConnection() {
  bool isVersionFound = setVersion(this->db);
  create_collection(this->db);
  return isVersionFound;
}

std::string Mongo::signUp(const std::string &user_name,
                          const std::string &password) {
  chat_box::User user(user_name, password);
  user.register_time_stamp = std::chrono::system_clock::now();
  user.logDetails();
  // key for user would be user_name + sha256(password)
  // check if user exist than return user_name
  // if doesn't exist save and return user_name
  // if more than one exists return first user_name, use findOne.
  return "https://github.com/xpd54/TalkItOut/pulls";
}

}; // namespace mongo_connection