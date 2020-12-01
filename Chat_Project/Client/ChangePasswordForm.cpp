#include "pch.h"
#include "ChangePasswordForm.h"

using namespace Client;
System::Void ChangePasswordScreen::ChangePasswordScreen_Load(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->createThreadListenMessageFromServer();
}
System::Void ChangePasswordScreen::butChange_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ username = txtUsername->Text;
	String^ oldPassword = txtOldPass->Text;
	String^ newPassword = txtNewPass->Text;

	AppController::getObject()->strUsername = username;
	AppController::getObject()->changePassword(username, oldPassword, newPassword);
	//AppController::getObject()->changePasswordScreen->Hide();

}
