#include "pch.h"

using namespace System;

//#include "LoginForm.h"
#include"ConnectServer.h"
using namespace System::Windows::Forms;

[STAThread]
int main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	/*AppController::getObject()->loginScreen = gcnew Client::LoginScreen;
	Application::Run(AppController::getObject()->loginScreen);*/
	AppController::getObject()->connectServer = gcnew Client::ConnectServer;
	Application::Run(AppController::getObject()->connectServer);
	return 0;
}