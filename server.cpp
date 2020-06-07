#include "mongoose/mongoose.h"
#include "json/json.h"
#include <string>
#include <iostream>
#include <sstream>
#include <set>

using json = nlohmann::json;

static const char *httpPort = "8000";
static mg_serve_http_opts httpServeOptions;

std::set<std::string> knownUsers;

static void broadcast(mg_connection *nc, const std::string &str) {
    for (mg_connection *c = mg_next(nc->mgr, NULL);
         c != NULL; c = mg_next(nc->mgr, c)) {
        mg_send_websocket_frame(c, WEBSOCKET_OP_TEXT, str.c_str(), str.size());
    }
}

static void updateGlobalStatus(mg_connection *nc) {
    json status;
    status["kind"] = "statusUpdate";
    status["gameStatus"] = "pregame";
    json users = "[]"_json;
    for (const std::string &user : knownUsers)
        users.push_back(user);
    status["knownUsers"] = users;

    std::ostringstream oss;
    oss << status;
    broadcast(nc, oss.str());
}

static void registerNewUser(mg_connection *nc, const std::string &username) {
    if (knownUsers.find(username) != knownUsers.end()) {
        fprintf(stderr, "username '%s' already exists!\n", username.c_str());
        return;
    }

    knownUsers.insert(username);
    updateGlobalStatus(nc);
}

static void handleIncomingData(mg_connection *nc, std::string jsonData) {
    json data;
    try {
        data = json::parse(jsonData);
    } catch (...) {
        std::cerr << jsonData << '\n';
        return;
    }

    auto iter = data.find("action");
    if (iter == data.end() || !iter->is_string())
        return;
    std::string action = iter->get<std::string>();

    if (action == "registerUser") {
        iter = data.find("username");
        if (iter == data.end() || !iter->is_string())
            return;
        registerNewUser(nc, iter->get<std::string>());
        return;
    }
}

static void eventHandler(mg_connection *nc, int event, void *eventData) {
    switch (event) {
    case MG_EV_WEBSOCKET_HANDSHAKE_DONE: {
        /* New websocket connection. Tell everybody. */
        break;
    }
    case MG_EV_WEBSOCKET_FRAME: {
        struct websocket_message *wm = (websocket_message *)eventData;
        handleIncomingData(nc, std::string((const char *)wm->data, wm->size));
        break;
    }
    case MG_EV_HTTP_REQUEST: {
        mg_serve_http(nc, (http_message *)eventData, httpServeOptions);
        break;
    }
    case MG_EV_CLOSE: {
        // if (nc->flags & MG_F_IS_WEBSOCKET)
        //     broadcast(nc, mg_mk_str("-- left"));
        break;
    }
    }
}

int main(int argc, char **argv) {
    mg_mgr manager;
    mg_connection *conn;

    mg_mgr_init(&manager, NULL);

    conn = mg_bind(&manager, httpPort, eventHandler);
    mg_set_protocol_http_websocket(conn);
    httpServeOptions.document_root = ".";  // Serve current directory
    httpServeOptions.enable_directory_listing = "yes";

    while (1) {
        mg_mgr_poll(&manager, 200);
    }
}
