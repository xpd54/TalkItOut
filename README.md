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
3. Docker using docker to run quickly.

#### Compiling-And-Building

1. clone the repo `git clone https://github.com/xpd54/TalkItOut.git`
2. create a build folder and build `mkdir build && cd build && cmake .. && make`

##### running on docker

1. run mongodb `cd mongodb && docker compose up` in one terminal
2. update your local ip address or if using atlas-database use uri. [here](https://github.com/xpd54/TalkItOut/blob/9e594c195df34d57d5a5298e79d69e39e8374564/docker-compose.yml#L9)
3. `docker compose up` and make get request to `http://0.0.0.0:18080/health` to see if it's up.

```bash
talkitout-app-1  | (2025-02-04 11:17:21) [INFO    ] Crow/master server is running at http://0.0.0.0:18080 using 4 threads
talkitout-app-1  | (2025-02-04 11:17:21) [INFO    ] Call `app.loglevel(crow::LogLevel::Warning)` to hide Info level logs.
talkitout-app-1  | (2025-02-04 11:17:44) [INFO    ] Request: 192.168.192.1:38464 0x113e710 HTTP/1.1 GET /health
talkitout-app-1  | (2025-02-04 11:17:44) [INFO    ] Response: 0x113e710 /health 200 0
talkitout-app-1  | Current Version is set as 5
```

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
