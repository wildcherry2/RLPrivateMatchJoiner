#include "pch.h"
#include "MatchJoinerBakkesComponent.h"


BAKKESMOD_PLUGIN(MatchJoinerBakkesComponent, "Takes match data from a pipe and creates/joins a private match", plugin_version, PLUGINTYPE_FREEPLAY)

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

//for testing, comment out once pipe is implemented
const std::string events = "0";
const std::string name = "b12";
const std::string pass = "b11";

void MatchJoinerBakkesComponent::onLoad()
{
	_globalCvarManager = cvarManager;
	cvarManager->log("Match joiner plugin loaded");
	cvarManager->registerCvar("MJEventType","1","Set to 0 for create mode, 1 for join mode",true,true,0,true,1,false);
	cvarManager->registerCvar("MJServerName", "default", "Enter the server name", true, false, false, false);
	cvarManager->registerCvar("MJServerPass", "", "Enter the server password", true, false, false, false);
	cvarManager->registerNotifier("matchjoiner", [this](std::vector<std::string> args) { //first arg is bool (true = join, false = create), next 2 are lobby info
		setServerCvars();
		},"", PERMISSION_ALL);
	//createPrivateMatch("b1000","8xma");
	//cvarManager->log("Plugin loaded!");

	//cvarManager->registerNotifier("my_aweseome_notifier", [&](std::vector<std::string> args) {
	//	cvarManager->log("Hello notifier!");
	//}, "", 0);

	//auto cvar = cvarManager->registerCvar("template_cvar", "hello-cvar", "just a example of a cvar");
	//auto cvar2 = cvarManager->registerCvar("template_cvar2", "0", "just a example of a cvar with more settings", true, true, -10, true, 10 );

	//cvar.addOnValueChanged([this](std::string cvarName, CVarWrapper newCvar) {
	//	cvarManager->log("the cvar with name: " + cvarName + " changed");
	//	cvarManager->log("the new value is:" + newCvar.getStringValue());
	//});

	//cvar2.addOnValueChanged(std::bind(&MatchJoinerBakkesComponent::YourPluginMethod, this, _1, _2));

	// enabled decleared in the header
	//enabled = std::make_shared<bool>(false);
	//cvarManager->registerCvar("TEMPLATE_Enabled", "0", "Enable the TEMPLATE plugin", true, true, 0, true, 1).bindTo(enabled);

	//cvarManager->registerNotifier("NOTIFIER", [this](std::vector<std::string> params){FUNCTION();}, "DESCRIPTION", PERMISSION_ALL);
	//cvarManager->registerCvar("CVAR", "DEFAULTVALUE", "DESCRIPTION", true, true, MINVAL, true, MAXVAL);//.bindTo(CVARVARIABLE);
	//gameWrapper->HookEvent("FUNCTIONNAME", std::bind(&TEMPLATE::FUNCTION, this));
	//gameWrapper->HookEventWithCallerPost<ActorWrapper>("FUNCTIONNAME", std::bind(&MatchJoinerBakkesComponent::FUNCTION, this, _1, _2, _3));
	//gameWrapper->RegisterDrawable(bind(&TEMPLATE::Render, this, std::placeholders::_1));


	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", [this](std::string eventName) {
	//	cvarManager->log("Your hook got called and the ball went POOF");
	//});
	// You could also use std::bind here
	//gameWrapper->HookEvent("Function TAGame.Ball_TA.Explode", std::bind(&MatchJoinerBakkesComponent::YourPluginMethod, this);
}

void MatchJoinerBakkesComponent::onUnload()
{
	cvarManager->log("Match joiner unloaded.");
}

//check that user is in freeplay or main menu (gamewrapper getonlinegame)
void MatchJoinerBakkesComponent::createPrivateMatch(std::string name, std::string pass) {
	MatchmakingWrapper* mm = new MatchmakingWrapper(true);
	CustomMatchTeamSettings* blue = new CustomMatchTeamSettings();
	CustomMatchTeamSettings* red = new CustomMatchTeamSettings();
	CustomMatchSettings* cm = new CustomMatchSettings();
	//GameWrapper* gw = &gameWrapper;
	ServerWrapper sw = (gameWrapper->GetCurrentGameState());
	
	cm->GameTags = "BotsNone";
	cm->MapName = "EuroStadium_P"; //map options
	cm->ServerName = name;
	cm->Password = pass;
	cm->BlueTeamSettings = *blue;
	cm->OrangeTeamSettings = *red;
	cm->bClubServer = false;

	//while (sw->IsNull()) {
		mm->CreatePrivateMatch(Region::USE,*cm);
		//add 10-15 sec delay before trying again/check to be on menu, black screen edge case?
	//}
	

	delete mm;
	delete blue;
	delete red;
	delete cm;
}

void MatchJoinerBakkesComponent::joinPrivateMatch(std::string name, std::string pass) {
	MatchmakingWrapper* mm = new MatchmakingWrapper(true);
	mm->JoinPrivateMatch(name, pass);

	delete mm;
}

//remember to add tab into rl functionality
void MatchJoinerBakkesComponent::gotoPrivateMatch() {
	if (cvarManager->getCvar("MJEventType").getBoolValue() == true) joinPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue());
	else createPrivateMatch(cvarManager->getCvar("MJServerName").getStringValue(), cvarManager->getCvar("MJServerPass").getStringValue());
}

void MatchJoinerBakkesComponent::setServerCvars() {
	//replace with pipe functionality, placeholder for now
	//listen for changes on each cvar? define them with no defaults if so 
	cvarManager->getCvar("MJEventType").setValue(events);
	cvarManager->getCvar("MJServerName").setValue(name);
	cvarManager->getCvar("MJServerPass").setValue(pass);
	gotoPrivateMatch();
}