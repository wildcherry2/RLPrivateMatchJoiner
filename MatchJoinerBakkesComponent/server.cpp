#include "pch.h"
#include "MatchJoinerBakkesComponent.h"
#include "Simple-Web-Server/server_http.hpp"

//// Added for the json-example
//#define BOOST_SPIRIT_THREADSAFE
//#include <boost/property_tree/json_parser.hpp>
//#include <boost/property_tree/ptree.hpp>
//
//// Added for the default_resource example
//#include "Simple-Web-Server/crypto.hpp"
//#include <algorithm>
//#include <boost/filesystem.hpp>
//#include <fstream>
//#include <vector>
//
//// Added for the default_resource example
//#include <algorithm>
//#include <boost/filesystem.hpp>
//#include <fstream>
//#include <vector>
//#ifdef HAVE_OPENSSL
//#include "crypto.hpp"
//#endif

using namespace std;
// Added for the json-example:
//using namespace boost::property_tree;

void MatchJoinerBakkesComponent::initServer() {
    cvarManager->log("Initializing server...");
	server = new SimpleWeb::Server<SimpleWeb::HTTP>;
	server->config.port = 6969;

    server->resource["^/match$"]["GET"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
        cvarManager->log("Request received...");
        auto fields = request->parse_query_string();
        for (auto& field : fields) 
            cvarManager->log(field.first + " " + field.second);

            //stream << field.first << ": " << field.second << "<br>";
        /*stringstream stream;
        stream << "<h1>Request from " << request->remote_endpoint_address() << ":" << request->remote_endpoint_port() << "</h1>";

        stream << request->method << " " << request->path << " HTTP/" << request->http_version;

        stream << "<h2>Query Fields</h2>";
        auto query_fields = request->parse_query_string();
        for (auto& field : query_fields)
            stream << field.first << ": " << field.second << "<br>";

        stream << "<h2>Header Fields</h2>";
        for (auto& field : request->header)
            stream << field.first << ": " << field.second << "<br>";*/

        response->write("");
    };

    server_thread = new std::thread([this]() {
        cvarManager->log("Server started!");
        this->server->start();
    });

    server_thread->detach();
}