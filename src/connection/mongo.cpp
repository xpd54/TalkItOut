#include "mongo.h"
#include "../common/constant.hpp"
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_array;
using bsoncxx::builder::basic::make_document;
using bsoncxx::types::b_timestamp;
namespace mongo_connection {

Mongo::Mongo() {}

void Mongo::connect() {
    uri = mongocxx::uri(connection_constant::mongodbUri);
    client = mongocxx::client(uri);
    db = client[connection_constant::databaseName];
    std::cout << "Database Initialized"
              << "\n";
}

mongocxx::collection create_collection(const mongocxx::database &db, const std::string &collection_name) {
    if (!db.has_collection(collection_name)) {
        std::cout << "collection " << collection_name << " is missing"
                  << "\n";
    }
    return db.collection(collection_name);
}

bool setVersion(const mongocxx::database &db) {
    if (!db.has_collection(db_collection::version)) {
        mongocxx::collection version_collection = db.collection(db_collection::version);
        bsoncxx::document::value version = bsoncxx::builder::basic::make_document(kvp(db_collection::appVersion, 5));
        bsoncxx::stdx::optional<mongocxx::result::insert_one> result = version_collection.insert_one(version.view());
        std::int32_t count = result->result().inserted_count();
        return count > 0;
    } else {
        mongocxx::collection version_collection = db.collection(db_collection::version);
        bsoncxx::stdx::optional<bsoncxx::document::value> version = version_collection.find_one({});
        bsoncxx::document::view view = version->view();
        bsoncxx::document::element version_view = view[db_collection::appVersion];
        std::int32_t version_number = version_view.get_int32();
        std::cout << "Current Version is set as " << version_number << "\n";
        return version_number > 0;
    }
    return false;
}

bool Mongo::checkConnection() const {
    bool isVersionFound = setVersion(this->db);
    return isVersionFound;
}

bsoncxx::stdx::optional<bsoncxx::document::value> Mongo::findUser(const std::string &user_name,
                                                                  const std::string &password) const {
    mongocxx::collection user_collection = create_collection(db, db_collection::users);
    // check for user if exists before signup
    bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(kvp(user_schema::user_name, user_name));

    bsoncxx::stdx::optional<bsoncxx::document::value> user = user_collection.find_one(filter.view());
    return user;
}

mongocxx::cursor Mongo::find_rooms(const std::string &room_name) const {
    mongocxx::collection room_collection = create_collection(db, db_collection::rooms);
    bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(kvp(room_schema::room_name, room_name));
    mongocxx::cursor room = room_collection.find(filter.view());
    return room;
}

bsoncxx::stdx::optional<bsoncxx::document::value> Mongo::find_a_room(const bsoncxx::types::b_oid &chat_room_id) {
    mongocxx::collection room_collction = create_collection(db, db_collection::rooms);
    bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(kvp(room_schema::id, chat_room_id));
    bsoncxx::stdx::optional<bsoncxx::document::value> room = room_collction.find_one(filter.view());
    return room;
}

bsoncxx::types::b_oid Mongo::signUp(const std::string &user_name, const std::string &password) const {
    mongocxx::collection user_collection = create_collection(db, db_collection::users);
    // check for user if exists before signup
    bsoncxx::document::value filter = bsoncxx::builder::basic::make_document(kvp(user_schema::user_name, user_name));

    bsoncxx::stdx::optional<bsoncxx::document::value> user = user_collection.find_one(filter.view());
    if (user) {
        bsoncxx::document::view view = user->view();
        bsoncxx::types::b_oid current_user_id = view[user_schema::id].get_oid();
        return current_user_id;
    }

    std::chrono::system_clock::time_point register_time = std::chrono::system_clock::now();
    bsoncxx::builder::basic::document doc = {};
    doc.append(kvp(user_schema::user_name, user_name));
    doc.append(kvp(user_schema::password, password));
    doc.append(kvp(user_schema::timestamp, bsoncxx::types::b_date(register_time)));
    doc.append(kvp(user_schema::chat_rooms, bsoncxx::builder::basic::array()));
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = user_collection.insert_one(doc.view());
    return result->inserted_id().get_oid();
}

bsoncxx::stdx::optional<bsoncxx::types::b_oid> Mongo::signIn(const std::string &user_name,
                                                             const std::string &password) const {
    bsoncxx::stdx::optional<bsoncxx::document::value> user = findUser(user_name, password);
    if (user) {
        bsoncxx::document::view view = user->view();
        bsoncxx::types::b_oid current_user_id = view[user_schema::id].get_oid();
        return current_user_id;
    }
    return bsoncxx::stdx::nullopt;
}

bsoncxx::types::b_oid Mongo::create_a_room(const std::string &room_name, const bsoncxx::types::b_oid &user_id) const {
    mongocxx::cursor rooms = find_rooms(room_name);
    int32_t name_version = 0;
    if (rooms.begin() != rooms.end()) {
        for (const bsoncxx::document::view &room : rooms) {
            if (room[room_schema::name_version].get_int32() >= name_version) {
                name_version = room[room_schema::name_version].get_int32();
            }
        }
    }

    bsoncxx::builder::basic::document doc = {};
    bsoncxx::builder::basic::array users;
    users.append(user_id);
    doc.append(kvp(room_schema::room_name, room_name));
    // If name_version if room is found get next name_version
    doc.append(kvp(room_schema::name_version, ++name_version));
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    doc.append(kvp(room_schema::created_at, bsoncxx::types::b_date(now)));
    doc.append(kvp(room_schema::updated_at, bsoncxx::types::b_date(now)));
    doc.append(kvp(room_schema::members, users));
    mongocxx::collection room_collection = create_collection(db, db_collection::rooms);
    bsoncxx::stdx::optional<mongocxx::result::insert_one> result = room_collection.insert_one(doc.view());

    if (result) {
        // after saving a room do join the room as using
        int32_t count = join_a_room(result->inserted_id().get_oid(), user_id);
        std::cout << "room joined " << count << '\n';
    }
    return result->inserted_id().get_oid();
}

int32_t Mongo::join_a_room(const bsoncxx::types::b_oid &chat_room_id, const bsoncxx::types::b_oid &user_id) const {
    mongocxx::collection user_collection = create_collection(db, db_collection::users);
    mongocxx::collection chat_room_collection = create_collection(db, db_collection::rooms);

    using bsoncxx::builder::basic::make_array;
    using bsoncxx::builder::basic::make_document;
    // update users in chat_rooms list, only if it doesn't exist.
    bsoncxx::stdx::optional<mongocxx::result::update> user_update = user_collection.update_one(
        make_document(kvp(user_schema::id, user_id)),
        make_document(kvp("$addToSet", make_document(kvp(user_schema::chat_rooms,
                                                         make_document(kvp("$each", make_array(chat_room_id))))))));
    // add user_id to members list in room
    bsoncxx::stdx::optional<mongocxx::result::update> chat_room_update = chat_room_collection.update_one(
        make_document(kvp(room_schema::id, chat_room_id)),
        make_document(kvp("$addToSet",
                          make_document(kvp(room_schema::members, make_document(kvp("$each", make_array(user_id))))))));
    return chat_room_update->matched_count();
}
bool exit_a_room(const bsoncxx::types::b_oid &userId) { return true; }

/*
Sending message to a room.
*/
int32_t Mongo::add_message_to_room(const std::string &payload, const bsoncxx::types::b_oid &user_id,
                                   const bsoncxx::types::b_oid &chat_room_id) const {
    mongocxx::collection user_collection = create_collection(db, db_collection::users);
    mongocxx::collection chat_room_collection = create_collection(db, db_collection::rooms);

    std::chrono::system_clock::time_point created_at = std::chrono::system_clock::now();
    bsoncxx::document::view_or_value message =
        make_document(kvp(message_schema::sender, user_id), kvp(message_schema::payload, payload),
                      kvp(message_schema::created_at, bsoncxx::types::b_date(created_at)));
    bsoncxx::document::view_or_value filter = make_document(kvp(room_schema::id, chat_room_id));
    bsoncxx::document::view_or_value update_query = make_document(
        kvp("$addToSet", make_document(kvp(room_schema::messages, make_document(kvp("$each", make_array(message)))))));
    bsoncxx::stdx::optional<mongocxx::result::update> chat_room_update =
        chat_room_collection.update_one(filter.view(), update_query.view());
    return chat_room_update->matched_count();
}

bsoncxx::stdx::optional<bsoncxx::types::b_array>
Mongo::get_all_messages_for_room(const bsoncxx::types::b_oid &chat_room_id) const {
    mongocxx::collection chat_room_collection = create_collection(db, db_collection::rooms);
    bsoncxx::document::view_or_value filter = make_document(kvp(room_schema::id, chat_room_id));
    mongocxx::options::find options;
    bsoncxx::document::view_or_value projection = make_document(kvp(room_schema::messages, 1));
    bsoncxx::stdx::optional<bsoncxx::document::value> chat_room = chat_room_collection.find_one(filter.view());

    if (chat_room) {
        bsoncxx::document::value chat_room_view = chat_room.value();
        bsoncxx::types::b_array messages = chat_room_view[room_schema::messages].get_array();

        // to convert messages to an array and access value to
        std::string array_json = bsoncxx::to_json(messages);
        std::cout << "Array JSON: " << array_json << "\n";
        return messages;
    }
    return bsoncxx::stdx::nullopt;
}

}; // namespace mongo_connection