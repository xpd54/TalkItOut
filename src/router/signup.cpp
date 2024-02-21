#include "signup.h"
#include "../common/constant.hpp"
namespace route {
crow::response Signup::sign_up(const mongo_connection::Mongo &mongo, const chat_box::User &user) const {
    bsoncxx::types::b_oid id = mongo.signUp(user.user_name, user.password);
    crow::json::wvalue res;
    res[response_key::status] = response_value::success;
    res[response_key::user_id] = id.value.to_string();
    return crow::response(200, res);
}
} // namespace route