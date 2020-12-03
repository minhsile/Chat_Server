#include "pch.h"
#include "ChangePasswordForm.h"

using namespace Client;
System::Void ChangePasswordScreen::ChangePasswordScreen_Load(System::Object^ sender, System::EventArgs^ e)
{
	txtOldPass->PasswordChar = '*';
	txtNewPass->PasswordChar = '*';
	txtConfirmPass->PasswordChar = '*';
	AppController::getObject()->createThreadListenMessageFromServer();
}
System::Void ChangePasswordScreen::butChange_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ username = txtUsername->Text;
	String^ oldPassword = txtOldPass->Text;
	String^ newPassword = txtNewPass->Text;
	String^ confirmnewPassword = txtConfirmPass->Text;

	AppController::getObject()->strUsername = username;
	AppController::getObject()->changePassword(username, oldPassword, newPassword, confirmnewPassword);
	//AppController::getObject()->changePasswordScreen->Hide();

}
