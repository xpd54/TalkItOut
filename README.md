# Talk It Out

TalkItOut is a CRUD RESTful API server built using the mongo-cxx-driver and BSON. This application allows users to interact with a chat system via api, enabling functionalities such as signing up, signing in, creating rooms, sending messages, and retrieving messages over http.

## Table of Contents

- [Dependency](#dependency)
- [Compiling & Building](#compiling-and-building)
- [APIs Details](#apis)
- [How to Run](#run)
- [License](#license)

#### Dependency

1. [crow](https://github.com/CrowCpp/Crow) header only library already included.
2. [Mongdb](https://github.com/mongodb/mongo-cxx-driver) need to be installed as internal dependency.

#### Compiling-And-Building

#### APIs

###### Health Check

- **Endpoint**: `/health`
- **Method**: `GET`
- **Description**: Checks the health status of the application.

###### User Signup

- **Endpoint**: `/signup`
- **Method**: `POST`
- **Description**: Registers a new user in the system.
- **Request Body**:

```json
{
  "user_name": "string",
  "password": "string"
}
```

###### User Signin

- **Endpoint**: `/signin`
- **Method**: `POST`
- **Description**: Authenticates a user and allows them to sign in.
- **Request Body**:

```json
{
  "user_name": "string",
  "password": "string"
}
```

###### Create Room

- **Endpoint**: `/create_room`
- **Method**: `POST`
- **Description**: Creates a new chat room.
- **Request Body**:

```json
{
  "chat_room_name": "string",
  "user_id": "string"
}
```

###### Create Room

- **Endpoint**: `/join_room`
- **Method**: `POST`
- **Description**: Allows a user to join an existing chat room.
- **Request Body**:

```json
{
  "chat_room_id": "string",
  "user_id": "string"
}
```

###### Create Room

- **Endpoint**: `/send_message`
- **Method**: `POST`
- **Description**: Sends a message to a specific chat room.
- **Request Body**:

```json
{
  "message_payload": "string",
  "user_id": "string",
  "chat_room_id": "string"
}
```

###### Get All Messages

- **Endpoint**: /get_all_messages
- **Method**: `GET`
- **Query Parameters**: `chat_room_id`: The ID of the chat room.
- **Description**: Retrieves all messages from a specified chat room.

###### Get All Chat Rooms

- **Endpoint**: /get_all_chat_rooms
- **Method**: `GET`
- **Query Parameters**: `user_id`: The ID of the user.
- **Description**: Retrieves all messages from a specified chat room.
