#include "signup.h"
#include "../common/constant.hpp"
namespace route {
crow::json::wvalue Signup::sign_up(const mongo_connection::Mongo &mongo,
                                   const chat_box::User &user) const {
  bsoncxx::types::b_oid id = mongo.signUp(user.user_name, user.password);
  crow::json::wvalue res;
  res[response_key::status] = response_value::success;
  res[response_key::user_id] = id.value.to_string();
  return res;
}
} // namespace route