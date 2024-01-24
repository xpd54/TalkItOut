#pragma once
#include <string>
#define MONGO_DB_URI "MONGO_DB_URI"
#define DB_NAME "DB_NAME"

namespace connection_constant {
const std::string mongodbUri = "mongodb://localhost:27017";
const std::string databaseName = "talk_it_out";
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
