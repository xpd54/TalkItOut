#include "mongo.h"
#include "../common/constant.hpp"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/types.hpp>
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

mongocxx::collection create_collection(const mongocxx::database &db,
                                       const std::string &collection_name) {
  if (!db.has_collection(collection_name)) {
    std::cout << "collection " << collection_name << " is missing"
              << "\n";
  }
  return db.collection(collection_name);
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
  return isVersionFound;
}

bsoncxx::stdx::optional<bsoncxx::document::value>
Mongo::findUser(const std::string &user_name, const std::string &password) {

  using bsoncxx::builder::basic::kvp;
  mongocxx::collection user_collection =
      create_collection(db, db_collection::users);
  // check for user if exists before signup
  bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(
      kvp(user_schema::user_name, user_name));

  bsoncxx::stdx::optional<bsoncxx::document::value> user =
      user_collection.find_one(filter.view());
  return user;
}

mongocxx::cursor Mongo::find_rooms(const std::string &room_name) {
  using bsoncxx::builder::basic::kvp;
  mongocxx::collection room_collection =
      create_collection(db, db_collection::rooms);
  bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(
      kvp(room_schema::room_name, room_name));
  mongocxx::cursor room = room_collection.find(filter.view());
}

bsoncxx::stdx::optional<bsoncxx::document::value>
Mongo::find_a_room(const bsoncxx::types::b_oid &roomId) {
  using bsoncxx::builder::basic::kvp;
  mongocxx::collection room_collction =
      create_collection(db, db_collection::rooms);
  bsoncxx::document::value filter =
      bsoncxx::builder::basic::make_document(kvp(room_schema::id, roomId));
  bsoncxx::stdx::optional<bsoncxx::document::value> room =
      room_collction.find_one(filter.view());
}

bsoncxx::types::b_oid Mongo::signUp(const std::string &user_name,
                                    const std::string &password) {
  using bsoncxx::builder::basic::document;
  using bsoncxx::builder::basic::kvp;
  mongocxx::collection user_collection =
      create_collection(db, db_collection::users);
  // check for user if exists before signup
  bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(
      kvp(user_schema::user_name, user_name));

  bsoncxx::stdx::optional<bsoncxx::document::value> user =
      user_collection.find_one(filter.view());
  if (user) {
    bsoncxx::document::view view = user->view();
    bsoncxx::types::b_oid current_user_id = view[user_schema::id].get_oid();
    return current_user_id;
  }

  std::chrono::system_clock::time_point register_time =
      std::chrono::system_clock::now();
  document doc = document{};
  doc.append(kvp(user_schema::user_name, user_name));
  doc.append(kvp(user_schema::password, password));
  doc.append(
      kvp(user_schema::timestamp, bsoncxx::types::b_date(register_time)));

  bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
      user_collection.insert_one(doc.view());
  return result->inserted_id().get_oid();
}

bsoncxx::stdx::optional<bsoncxx::types::b_oid>
Mongo::signIn(const std::string &user_name, const std::string &password) {
  bsoncxx::stdx::optional<bsoncxx::document::value> user =
      findUser(user_name, password);
  if (user) {
    bsoncxx::document::view view = user->view();
    bsoncxx::types::b_oid current_user_id = view[user_schema::id].get_oid();
    return current_user_id;
  }

  return bsoncxx::stdx::nullopt;
}

bsoncxx::types::b_oid
Mongo::create_a_room(const std::string &room_name,
                     const bsoncxx::types::b_oid &userId) {
  using bsoncxx::builder::basic::document;
  using bsoncxx::builder::basic::kvp;
  mongocxx::cursor rooms = find_rooms(room_name);
  int32_t name_version = 0;
  if (rooms.begin() != rooms.end()) {
    for (const bsoncxx::document::view &room : rooms) {
      if (room[room_schema::name_version].get_int32() > name_version) {
        name_version = room[room_schema::name_version].get_int32();
      }
    }
  }

  document doc = {};
  std::vector<bsoncxx::types::b_oid> users;
  users.push_back(userId);
  doc.append(kvp(room_schema::room_name, room_name));
  doc.append(kvp(room_schema::name_version, name_version++));
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
  doc.append(kvp(room_schema::created_at, bsoncxx::types::b_date(now)));
  doc.append(kvp(room_schema::updated_at, bsoncxx::types::b_date(now)));
  doc.append(kvp(room_schema::members, users));
  bsoncxx::stdx::optional<mongocxx::result::insert_one> result =
      room_collction.insert_one(doc.view());
  // add newly created room _id into user rooms list
  return result->inserted_id().get_oid();
}

bool join_a_room(const bsoncxx::types::b_oid &userId) {}
bool exit_a_room(const bsoncxx::types::b_oid &userId) {}

}; // namespace mongo_connection