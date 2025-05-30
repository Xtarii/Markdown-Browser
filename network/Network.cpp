#include "Network.h"

#include <MDTP/socket/MDTPClient.h>


Network::Query Network::parseQuery(const std::string& query) {
    Query data{};
    int x = 0;
    data.protocol = parseProtocol(&x, query);
    data.address = parseAddress(&x, query);
    return data;
}



std::string Network::parseProtocol(int* x, const std::string& query) {
    std::string value;

    do { // Parses Protocol
        const char c = query[*x];
        if(value.ends_with("://")) {
            value.erase(value.size() - 3);
            break;
        }

        value += c;
        (*x)++;
    }while(*x < query.length());
    return value;
}

Network::AddressInfo Network::parseAddress(int* x, const std::string& query) {
    AddressInfo info{};
    std::string value;
    do { // Parses Query Adress
        const char c = query[*x];
        if(c == ':') {
            (*x)++;
            info.port = parsePort(x, query);
            break;
        }
        if(c == '/') break;

        value += c;
        (*x)++;
    }while(*x < query.length());
    info.address = value;
    info.command = parseCommand(x, query);
    return info;
}

int Network::parsePort(int* x, const std::string& query) {
    std::string value;
    do { // Parse Port
        const char c = query[*x];
        if(c == '/' || c == ':' || c == '?') break;

        value += c;
        (*x)++;
    }while(*x < query.length());
    return std::stoi(value);
}

std::string Network::parseCommand(int* x, const std::string& query) {
    std::string value;
    do { // Parses Command
        const char c = query[*x];
        value += c;
        (*x)++;
    }while(*x < query.length());
    if(value.empty()) value = "/";
    return value;
}





MDTPObject Network::fetch(const char* host, const int port, const char* command) {
    try {
        MDTPClient client(host, port);
        return client.fetch(command);
    }catch(MDTP::NetworkException exception) {
        const std::string error = "# Error\r\n Error fetching data";
        return {
            .header = MDTPHeader{MDTP_VERSION, static_cast<unsigned short>(error.length()), STATUS_FAIL},
            .body = error
        };
    }
}





bool Network::getAddressInfo(const std::string& host, const std::string& service, std::string& output) {


    // FIX LATER


    return true;
}
