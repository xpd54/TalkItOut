#pragma once
#include <cstdlib>
#include <string>
#define MONGO_URI "MONGO_URI"
#define DB_NAME "DB_NAME"

namespace connection_constant {
inline const char *mongodbUri = getenv(MONGO_URI);
const std::string databaseName = "talk-it-out";
enum status { disconnected = 0, connected };
} // namespace connection_constant

namespace db_collection {
const std::string version("version");
const std::string appVersion("app_version");
const std::string users("users");
const std::string rooms("rooms");
} // namespace db_collection

namespace user_schema {
const std::string user_name("user_name");
const std::string password("password");
const std::string timestamp("timestamp");
const std::string id("_id");
const std::string chat_rooms("chat_rooms");
} // namespace user_schema

namespace room_schema {
const std::string id("_id");
const std::string room_name("room_name");
const std::string name_version("name_version");
const std::string created_at("created_at");
const std::string updated_at("updated_at");
const std::string members("members");
const std::string messages("messages");
} // namespace room_schema

namespace message_schema {
const std::string sender("sender");
const std::string created_at("created_at");
const std::string payload("paylaod");
} // namespace message_schema

namespace response_key {
const std::string status("status");
const std::string user_id("user_id");
const std::string room_id("room_id");
const std::string messages_sent("messages_sent");
const std::string message("message");
const std::string message_count("message_count");
const std::string chat_rooms("chat_rooms");
} // namespace response_key

namespace response_value {
const std::string success("success");
const std::string not_found("not_found");
} // namespace response_value

namespace request_key {
const std::string chat_room_id("chat_room_id");
const std::string chat_room_name("chat_room_name");
const std::string user_id("user_id");
const std::string user_name("user_name");
const std::string password("password");
const std::string message_payload("message_payload");
} // namespace request_key