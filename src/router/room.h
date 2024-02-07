#pragma once
#include "../../include/crow.h"
#include "../connection/mongo.h"
namespace route {
    class Room
    {
    private:
        /* data */
    public:
        crow::response create_a_room(const std::string &room_name, const bsoncxx::types::b_oid &user_id) const;
    };
}