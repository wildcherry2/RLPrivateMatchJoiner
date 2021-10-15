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
    gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("MJReady"); }); //holy shit it works, need to add restart server once in menu/persistent threading?
    }

void MatchJoinerBakkesComponent::stopServer() {
    cvarManager->log("Stopping server...");
    server->stop();
}

struct EnumWindowsCallbackArgs
{
	EnumWindowsCallbackArgs(DWORD p) : pid(p) { }
	const DWORD pid;
	std::vector<HWND> handles;
};

static BOOL CALLBACK EnumWindowsCallback(HWND hnd, LPARAM lParam)
{
	EnumWindowsCallbackArgs* args = (EnumWindowsCallbackArgs*)lParam;

	DWORD windowPID;
	(void)::GetWindowThreadProcessId(hnd, &windowPID);
	if (windowPID == args->pid)
	{
		args->handles.push_back(hnd);
	}

	return TRUE;
}

std::vector<HWND> getToplevelWindows()
{
	EnumWindowsCallbackArgs args(::GetCurrentProcessId());
	if (::EnumWindows(&EnumWindowsCallback, (LPARAM)&args) == FALSE)
	{
		// XXX Log error here
		return std::vector<HWND>();
	}
	return args.handles;
}

void MatchJoinerBakkesComponent::MoveGameToFront()
{
	auto handles = getToplevelWindows();
	//LOG("handles: {}", handles.size());
	for (auto* h : handles)
	{
		int const bufferSize = 1 + GetWindowTextLength(h);
		std::wstring title(bufferSize, L'\0');
		int const nChars = GetWindowText(h, &title[0], bufferSize);
		if (title.find(L"Rocket League (64-bit, DX11, Cooked)") != std::wstring::npos)
		{
			::SetForegroundWindow(h);
			::ShowWindow(h, SW_RESTORE);
			//::SetWindowPos(h,       // handle to window
			//	HWND_TOPMOST,  // placement-order handle
			//	0,     // horizontal position
			//	0,      // vertical position
			//	0,  // width
			//	0, // height
			//	SWP_SHOWWINDOW|SWP_NOSIZE|SWP_NOMOVE// window-positioning options
			//);
			break;
		}
	}
}