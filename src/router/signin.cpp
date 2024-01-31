namespace route {
    crow::json::wvalue sing_in(const mongo_connection::Mongo &mongo,
                             const std::string &user_name,
                             const std::string &password) const;
}