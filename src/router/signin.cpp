#include "signin.h"
#include "../common/constant.hpp"
namespace route {
crow::response Signin::sing_in(const mongo_connection::Mongo &mongo,
                               const chat_box::User &user) const {
  bsoncxx::stdx::optional<bsoncxx::types::b_oid> id =
      mongo.signIn(user.user_name, user.password);
  crow::json::wvalue res;
  if (id) {
    res[response_key::user_id] = id->value.to_string();
    res[response_key::status] = response_value::success;
    return crow::response(200, res);
  } else {
    res[response_key::status] = response_value::not_found;
    return crow::response(404, res);
  }
}
} // namespace route