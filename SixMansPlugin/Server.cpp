#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::startServer() {
	server_thread = std::thread([this]() {
		SimpleWeb::Server<SimpleWeb::HTTP> server = SimpleWeb::Server<SimpleWeb::HTTP>();
		server.config.port = 6969;
		//cvarManager->logt("[Server] Server loaded");
		logt("[Server] Server loaded!");

		server.on_error = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request, const SimpleWeb::error_code& ec) {
			//cvarManager->logt("[Server] Server error occurred! Probably a request to stop the server.");
			logt("[Server] Server error occurred! Probably a request to stop the server.");
		};

		//URL syntax: localhost:[port]/match?event=[eventcode]?name=[servername]?pass=[serverpass]?region=[serverregion]
		//Example: http://localhost:6969/match?event=0&name=b1234&pass=h1jk&region=0
		server.resource["^/match$"]["GET"] = [this](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
			this->logt("[Server] Request received...");
			auto fields = request->parse_query_string();

			auto it = fields.begin();
			this->cvarManager->getCvar("6mEventType").setValue(it->second);
			it++;
			this->cvarManager->getCvar("6mServerName").setValue(it->second);
			it++;
			this->cvarManager->getCvar("6mServerPass").setValue(it->second);
			it++;
			this->cvarManager->getCvar("6mRegion").setValue(it->second);
			//cvarManager->logt("[Server] Vars sent!");
			logt("[Server] Vars sent!");

			response->close_connection_after_response = true;
			response->write(SimpleWeb::StatusCode::success_accepted, "alright");
			response->send();

			//move openinterface above branches
			//gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("6mReady"); /*cvarManager->executeCommand("openmenu SixMansPluginInterface");*/});
			if(is_autotab_enabled) MoveGameToFront();
			if (is_autojoin_enabled) gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("openmenu SixMansPluginInterface"); cvarManager->executeCommand("6mReady"); });
			else gameWrapper->Execute([this](GameWrapper* gw) {cvarManager->executeCommand("openmenu SixMansPluginInterface");});
		};

		//URL syntax: localhost:[port]/halt
		//stops server, closing the thread
		server.resource["^/halt$"]["GET"] = [this,&server](std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Response> response, std::shared_ptr<SimpleWeb::Server<SimpleWeb::HTTP>::Request> request) {
			//this->cvarManager->logt("[Server] Request received...");
			this->logt("[Server] Request received...");

			response->close_connection_after_response = true;
			response->write(SimpleWeb::StatusCode::success_accepted, "[Server] Stopping server!");
			response->send();
			//this->cvarManager->logt("[Server] Stopping server...");
			this->logt("[Server] Stopping server...");
			
			server.stop();
		};

		server.start();
		//this->cvarManager->logt("[Server] Thread closing!");
		this->logt("[Server] Thread closing!");
		return;
	});
	server_thread.detach();
}

//from Martinii, https://github.com/Martinii89/BallchasingReplayPlayer
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

		return std::vector<HWND>();
	}
	return args.handles;
}

void SixMansPlugin::MoveGameToFront()
{
	auto handles = getToplevelWindows();

	for (auto* h : handles)
	{
		int const bufferSize = 1 + GetWindowTextLength(h);
		std::wstring title(bufferSize, L'\0');
		int const nChars = GetWindowText(h, &title[0], bufferSize);
		if (title.find(L"Rocket League (64-bit, DX11, Cooked)") != std::wstring::npos)
		{
			::SetForegroundWindow(h);
			::ShowWindow(h, SW_RESTORE);
			break;
		}
	}
}