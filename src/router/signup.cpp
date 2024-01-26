#include "signup.h"

namespace route {
crow::json::wvalue Signup::sign_up(const mongo_connection::Mongo &mongo,
                                   const chat_box::User &user) const {
  bsoncxx::types::b_oid id = mongo.signUp(user.user_name, user.password);
}
} // namespace route