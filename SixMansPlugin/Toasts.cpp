#include "pch.h"
#include "SixMansPlugin.h"

void SixMansPlugin::renderJoinToast() {
	//extract lobby number by substring
	gameWrapper->Toast("Join 6Mans:\nLobby #0001","\n\nThe match info is loaded in the game!\nPress the button below to join:\n\n\n\n\n\nNOTE: For options, press \nF2->Plugins->6Mans Plugin Settings",TOAST_LOGO,TOAST_TIME,TOAST_TYPE);
}
void SixMansPlugin::renderCreateToast() {
	gameWrapper->Toast("Create 6Mans:\nLobby #0001", "\n\nThe match info is loaded in the game!\nPress the button below to create:\n\n\n\n\n\nNOTE: For options, press \nF2->Plugins->6Mans Plugin Settings", TOAST_LOGO, TOAST_TIME, TOAST_TYPE);
}
void SixMansPlugin::renderErrorToast() {
	gameWrapper->Toast("6Mans Plugin Error", "\nSome error!", TOAST_LOGO, TOAST_TIME, 2);

}