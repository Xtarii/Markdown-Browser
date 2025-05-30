#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <ws2tcpip.h>
#include <MDTP/parser/parser.h>

/**
 * Network Namespace
 */
namespace Network {
    /// Address Information
    struct AddressInfo {
        /// Address
        std::string address;

        /// Port
        int port = 0;

        /// Address Command
        std::string command;



        /**
         * Converts Object to String
         *
         * @return Object as a String
         */
        std::string toString() const { return "{ address: " + address + ", port: " + std::to_string(port) + ", command: " + command + " }"; }
    };

    /// Network Query
    struct Query {
        /// Address Info
        AddressInfo address;

        /// Protocol
        std::string protocol;



        /**
         * Converts Object to String
         *
         * @return String Object
         */
        std::string toString() const { return "{ address: " + address.toString() + ", protocol: " + protocol + " }"; }
    };





    /**
     * Parses Query
     *
     * @param query Query
     * @return Parsed Query
     */
    Query parseQuery(const std::string& query);



    /**
     * Parses Protocol from Query
     *
     * @param x Index Position
     * @param query Query
     * @return Protocol
     */
    std::string parseProtocol(int* x, const std::string& query);

    /**
     * Parses Address from Query
     *
     * @param x Index Position
     * @param query Query
     * @return Adress
     */
    AddressInfo parseAddress(int* x, const std::string& query);

    /**
     * Parses Port from Address Query
     *
     * @param x Index Position
     * @param query Query
     * @return Port
     */
    int parsePort(int* x, const std::string& query);

    /**
     * Parses Command from Address Query
     *
     * @param x Index Position
     * @param query Query
     * @return Command
     */
    std::string parseCommand(int* x, const std::string& query);





    /**
     * Fetches Data from Address Endpoint
     *
     * @param host Host Address
     * @param port Port
     * @param command Command
     * @return Data
     */
    MDTPObject fetch(const char* host, int port, const char* command);





    /**
     * Gets Address Info from Host
     *
     * @param host Host
     * @param service Port
     * @param output Output Address
     * @return Status
     */
    bool getAddressInfo(const std::string& host, const std::string& service, std::string& output);
}

#endif //NETWORK_H
