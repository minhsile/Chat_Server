#include "pch.h"

using namespace System;

//int main(array<System::String ^> ^args)
//{
//    return 0;
//}

#include "MainForm.h"

using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ServerController::getObject()->mainForm = gcnew Server::MainForm;
	Application::Run(ServerController::getObject()->mainForm);

	return 0;
}