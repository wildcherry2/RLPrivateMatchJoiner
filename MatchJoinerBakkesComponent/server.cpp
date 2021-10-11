#include "pch.h"
#include "MatchJoinerBakkesComponent.h"

using namespace std;

void MatchJoinerBakkesComponent::initServer() {
    cvarManager->log("Initializing server...");
	server = new SimpleWeb::Server<SimpleWeb::HTTP>;
	server->config.port = 6969;

    //URL syntax: localhost:[port]/match?event=[eventcode]?name=[servername]?pass=[serverpass]?region=[serverregion]
    //Example: http://localhost:6969/match?event=0&name=b1234&pass=h1jk&region=0
    server->resource["^/match$"]["GET"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
        this->cvarManager->log("Request received...");
        auto fields = request->parse_query_string();

        auto it = fields.begin();
        this->cvarManager->getCvar("MJEventType").setValue(it->second);
        event_code = std::stoi(it->second);
        it++;
        this->cvarManager->getCvar("MJServerName").setValue(it->second);
        name = it->second;
        it++;
        this->cvarManager->getCvar("MJServerPass").setValue(it->second);
        pass = it->second;
        it++;
        this->cvarManager->getCvar("MJRegion").setValue(it->second);
        region = getRegion(std::stoi(it->second));

        response->close_connection_after_response = true;
        response->write(SimpleWeb::StatusCode::success_accepted, "alright");
        response->send();

        stopServer();
    };
}

void MatchJoinerBakkesComponent::startServer() {  
    server_thread = std::thread([this](){      
        cvarManager->log("Starting server...");
        this->server->start();
        
        return;
        });
    cvarManager->log("Joining thread...");
    server_thread.join();
    cvarManager->log("Thread closed.");
    gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("MJReady"); }); //holy shit it works
    }

void MatchJoinerBakkesComponent::stopServer() {
    cvarManager->log("Stopping server...");
    server->stop();
}
