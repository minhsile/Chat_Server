#include "pch.h"

using namespace System;

#include "LoginForm.h"

using namespace System::Windows::Forms;

[STAThread]
int main() {

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AppController::getObject()->loginScreen = gcnew Client::LoginScreen;
	Application::Run(AppController::getObject()->loginScreen);
	return 0;
}