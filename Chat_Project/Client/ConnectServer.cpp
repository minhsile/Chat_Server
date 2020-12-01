#include "pch.h"
#include "ConnectServer.h"
using namespace Client;

System::Void ConnectServer::ConnectServer_Load(System::Object^ sender, System::EventArgs^ e)
{}
System::Void ConnectServer::butConnect_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ ipAddr = this->txtIP->Text->ToString();
	int portAddr = Convert::ToInt32(this->txtPort->Text->ToString());

	AppController::getObject()->appSocket = gcnew AppSocket(ipAddr, portAddr);
	if (!AppController::getObject()->appSocket->connectToServer() && AppController::getObject()->appSocket != nullptr && AppController::getObject()->appSocket->clientSocket != nullptr) {
		MessageBox::Show("Connected successfully!");
		AppController::getObject()->connectServer->Hide();
		AppController::getObject()->loginScreen = gcnew LoginScreen;
		AppController::getObject()->loginScreen->ShowDialog();
	}
	else
		Application::Exit();
}
