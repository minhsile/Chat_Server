#include "pch.h"
#include "ChatForm.h"

using namespace Client;

System::Void PrivateChat::ThreadChooseFile()
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ _info = ofd->SafeFileName;
		String^ info = ofd->FileName;
		this->txtfName->Text = _info;
		this->txtPath->Text = info;
		int size = IO::FileInfo(ofd->FileName).Length;

		fileNameToSend = _info;
		filePathToSend = info;
		fileSizeToSend = size;
		AppController::getObject()->requestSendFile(strFriendUsername, _info, size);
	}
}

System::Void PrivateChat::butFile_Click(System::Object^ sender, System::EventArgs^ e) {
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &PrivateChat::ThreadChooseFile));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}
System::Void PrivateChat::butViewInfor_Click(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->requestInfor(strFriendUsername);
}


void PrivateChat::SetCaption(String^ txtCaption)
{
	this->Text = txtCaption;
}

void PrivateChat::AddTextToDisplayChatbox(String^ text)
{
	DisplayChatBox->AppendText(text);
	DisplayChatBox->AppendText("\r\n");
}
System::Void PrivateChat::butSend_Click(System::Object^ sender, System::EventArgs^ e) {

	AppController::getObject()->sendPrivateMessage(strFriendUsername, txtMessage->Text);
	AddTextToDisplayChatbox(strMyUsername + ": " + txtMessage->Text);
	txtMessage->Text = nullptr;
}

System::Void PrivateChat::PrivateChat_Load(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->createThreadListenMessageFromServer();
}

System::Void PrivateChat::PrivateChat_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e)
{
	AppController::getObject()->lstPrivateChatForm->Remove(this);
}

System::Void PrivateChat::PrivateChat_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e)
{
}

String^ PrivateChat::splitPathFileToReceiver(String^ pathFile) {
	int length = pathFile->Length;
	int i = length - 1;
	for (i; i >= 0; --i) {
		if (pathFile[i] == '\\')
			break;
	}
	pathFile = pathFile->Remove(i + 1);

	return pathFile;
}