#include "pch.h"
#include "SetInfor.h"

System::Void Client::SetInfor::SetInfor_Load(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->createThreadListenMessageFromServer();
}
System::Void Client::SetInfor::butSave_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->setInfor(AppController::getObject()->strUsername, txtBirthdate->Text);
	butSave->Enabled = false;
}
