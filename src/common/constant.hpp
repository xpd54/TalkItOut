#pragma once
#include <string>
#define MONGO_DB_URI "MONGO_DB_URI"
#define DB_NAME "DB_NAME"

namespace connection_constant {
const std::string mongodbUri = "mongodb://localhost:27017";
const std::string databaseName = "talk_it_out";
} // namespace connection_constant

namespace db_collection {
const std::string version("version");
}