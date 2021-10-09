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
        it++;
        this->cvarManager->getCvar("MJServerName").setValue(it->second);
        it++;
        this->cvarManager->getCvar("MJServerPass").setValue(it->second);
        it++;
        this->cvarManager->getCvar("MJRegion").setValue(it->second);
        //this->cvarManager->getCvar("MJServerHasSetVars").setValue("1"); //doesnt work what the fuck, works when gotomatch called manually, correctly interprets event, maybe copypasta whole function in thread
        response->write("alright"); //put valid response / html here

        //this->cvarManager->executeCommand("MJGotoMatch");
        //gotoPrivateMatch(); //cant call member function?? probably a problem with calling this in a thread
    };
}



void MatchJoinerBakkesComponent::startServer() {
    server_thread = std::thread([this](){
        cvarManager->log("Starting server...");
        this->server->start();
        cvarManager->log("Thread closed.");
        return;
        });
    
    server_thread.detach(); 
}

void MatchJoinerBakkesComponent::stopServer() {
    cvarManager->log("Stopping server...");
    server->stop();
}
