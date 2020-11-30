#include "pch.h"
#include "ConnectServer.h"
using namespace Client;

System::Void ConnectServer::ConnectServer_Load(System::Object^ sender, System::EventArgs^ e)
{}
System::Void ConnectServer::butConnect_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ ipAddr = this->txtIP->Text->ToString();
	int portAddr = Convert::ToInt32(this->txtPort->Text->ToString());

	AppController^ controller = AppController::getObject();
	controller->appSocket = gcnew AppSocket(ipAddr, portAddr);
	if (!controller->appSocket->connectToServer() && controller->appSocket != nullptr && controller->appSocket->clientSocket != nullptr) {
		MessageBox::Show("Connected!");
		controller->connectServer->Hide();
		controller->loginScreen = gcnew LoginScreen;
		controller->loginScreen->ShowDialog();
		//Application::Run(controller->logInScreen);
	}


	else
		Application::Exit();
}
