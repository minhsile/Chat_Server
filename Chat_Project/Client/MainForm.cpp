#include "pch.h"
#include "MainForm.h"
using namespace Client;


System::Void MainScreen::MainScreen_Load(System::Object^ sender, System::EventArgs^ e)
{
	//txtUsername->Text = AppController::getObject()->strUsername;
	AppController::getObject()->createThreadListenMessageFromServer();
	AppController::getObject()->requestListOnlineUsers();
}


System::Void MainScreen::MainScreen_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	AppController::getObject()->logout(); 
}


void MainScreen::UpdateOnlineUsers()
{

}
System::Void MainScreen::butShowInfor_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->requestInfor(AppController::getObject()->strUsername);
}
System::Void Client::MainScreen::butPublicFile_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->publicFileScreen = gcnew Client::PublicFile();
	AppController::getObject()->publicFileScreen->Show();
}
void MainScreen::AddAnOnlineUser(String^ username)
{
	lbOnlineUser->Items->Add(username);
}

void MainScreen::DeleteAnOnlineUser(String^ username)
{
	for (int i = 0; i < lbOnlineUser->Items->Count; ++i)
		if (lbOnlineUser->Items[i]->ToString() == username)
		{
			lbOnlineUser->Items->Remove(lbOnlineUser->Items[i]);
			break;
		}
}

void MainScreen::SetOnlineUsers(array<String^>^ arrOnlineUsers)
{
	lbOnlineUser->Items->Clear();

	String^ myUsername = AppController::getObject()->strUsername;
	for each (String ^ user in arrOnlineUsers)
	{
		if (user != myUsername)
			lbOnlineUser->Items->Add(user);
	}
}

System::Void MainScreen::lbOnlineUser_MouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	int index = this->lbOnlineUser->IndexFromPoint(e->Location);
	if (index != System::Windows::Forms::ListBox::NoMatches)
	{
		String^ friendUsername = lbOnlineUser->Items[index]->ToString();
		PrivateChat^ Prf = gcnew PrivateChat(AppController::getObject()->strUsername, friendUsername);
		AppController::getObject()->lstPrivateChatForm->Add(Prf);
		//Application::Run(Prf);
		Prf->Show();
	}
}

System::Void MainScreen::butDisconnect_Click(System::Object^ sender, System::EventArgs^ e)
{
	////MessageBox::Show("Disconnect!");
	//AppController::getObject()->logout();
	////AppController::getObject()->loginScreen->Show();
	////Application::Run(AppController::getObject()->loginScreen);
	//AppController::getObject()->mainScreen->Close();
	Application::Restart();
}

System::Void MainScreen::MainScreen_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
	Application::Exit();
}

System::Void MainScreen::butChangePass_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->changePasswordScreen = gcnew Client::ChangePasswordScreen;
	//AppController::getObject()->changePasswordScreen->ShowDialog();
	AppController::getObject()->changePasswordScreen->Show();
}

System::Void Client::MainScreen::butSetInfor_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->setInforScreen = gcnew Client::SetInfor;
	//AppController::getObject()->changePasswordScreen->ShowDialog();
	AppController::getObject()->setInforScreen->Show();
}
