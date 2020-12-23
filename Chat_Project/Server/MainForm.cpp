#include "pch.h"
// #include "Form1.h"
#include "MainForm.h"
#include "../Struct/AllStruct.h"
using namespace Server;

System::Void MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	ServerController^ serverController = ServerController::getObject();

	//Set default serverIPAddr, serverPort
	//txtIPServer->Text = serverController->serverIPAddr;
	//txtPortServer->Text = Convert::ToString(serverController->serverPort);
	//String^ ipAddr = txtIPServer->Text->ToString();
	//int portAddr = Convert::ToInt32(txtPortServer->Text->ToString());
	//serverController->serverIPAddr = ipAddr;
	//serverController->serverPort = portAddr;
	//UpdateClientList(serverController->getRegisteredClientList());
}

void MainForm::ListenClientMessage(Object^ obj)
{
	Socket^ socket = (Socket^)obj;

	while (true)
	{
		try
		{
			array<Byte>^ buff = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
			int recv = socket->Receive(buff);
			//MessageBox::Show("Received: " + Convert::ToString(recv) + " bytes from Client!");
			ChatStruct^ msgReceived = ChatControl::unpack(buff);

			switch (msgReceived->messageType)
			{
			case ChatStruct::MessageType::Login:
			{
				LoginStruct^ loginStruct = (LoginStruct^)msgReceived;
				if (loginStruct->isEncrypted)
				{
					loginStruct->strUsername = convertHexToString(loginStruct->strUsername);
					loginStruct->strPassword = convertHexToString(loginStruct->strPassword);
				}
				ServerController::getObject()->login(loginStruct->strUsername, loginStruct->strPassword, socket);
				break;
			}
			case ChatStruct::MessageType::SetInfor:
			{
				SetInformationStruct^ setInforStruct = (SetInformationStruct^)msgReceived;
				ServerController::getObject()->setInfor(setInforStruct->userName, setInforStruct->birthDate);
				break;
			}
			case ChatStruct::MessageType::Signup:
			{
				SignupStruct^ signupStruct = (SignupStruct^)msgReceived;
				if (signupStruct->isEncrypted)
				{
					signupStruct->strUsername = convertHexToString(signupStruct->strUsername);
					signupStruct->strPassword = convertHexToString(signupStruct->strPassword);
				}
				ServerController::getObject()->signup(signupStruct->strUsername, signupStruct->strPassword, socket);
				break;
			}
			case ChatStruct::MessageType::ChangePassword:
			{
				ChangePasswordStruct^ changepasswordStruct = (ChangePasswordStruct^)msgReceived;
				if (changepasswordStruct->isEncrypted)
				{
					changepasswordStruct->strUsername = convertHexToString(changepasswordStruct->strUsername);
					changepasswordStruct->strOldPassword = convertHexToString(changepasswordStruct->strOldPassword);
					changepasswordStruct->strNewPassword = convertHexToString(changepasswordStruct->strNewPassword);
					changepasswordStruct->strConfirmNewPassword = convertHexToString(changepasswordStruct->strConfirmNewPassword);
				}
				ServerController::getObject()->changePassword(changepasswordStruct->strUsername, changepasswordStruct->strOldPassword, changepasswordStruct->strNewPassword,changepasswordStruct->strConfirmNewPassword, socket);
				break;
			}
			case ChatStruct::MessageType::PrivateMessage:
			{
				PrivateMessageStruct^ privateMsgStr = (PrivateMessageStruct^)msgReceived;
				ServerController::getObject()->sendPrivateMessage(privateMsgStr->strToUsername, privateMsgStr->strMessage, socket);

				break;
			}
			case ChatStruct::MessageType::UserStatus:
			{
				ServerController::getObject()->userStatusResponse(socket);
				break;
			}
			case ChatStruct::MessageType::LogoutNotification:
			{
				ServerController::getObject()->sendLogoutNotification(socket);
				break;
			}
			case ChatStruct::MessageType::RequestSendFile:
			{
				RequestSendFileStruct^ rqSendFileStruct = (RequestSendFileStruct^)msgReceived;
				//MessageBox::Show("Server received\nUsername: " + rqSendFileStruct->strUsername + "\nFile name: " + rqSendFileStruct->strFileName + "\nFile size: " + Convert::ToString(rqSendFileStruct->iFileSize));
				ServerController::getObject()->requestSendFile(rqSendFileStruct->strUsername, rqSendFileStruct->strFileName, rqSendFileStruct->iFileSize, socket);
				break;
			}
			case ChatStruct::MessageType::ResponseSendFile:
			{
				ResponseSendFileStruct^ rpSendFileStruct = (ResponseSendFileStruct^)msgReceived;
				ServerController::getObject()->responseSendFile(rpSendFileStruct->strUsername, rpSendFileStruct->IsAccept, socket);
				break;
			}
			case ChatStruct::MessageType::PrivateFile:
			{
				try {
					//MessageBox::Show("Server received: ");
					PrivateFileStruct^ prvFileStruct = (PrivateFileStruct^)msgReceived;
					ServerController::getObject()->sendPrivateFilePackage(prvFileStruct->strUsername, prvFileStruct->strFilename, prvFileStruct->iPackageNumber, prvFileStruct->iTotalPackage, prvFileStruct->bData, socket);
				}
				catch (Exception^ e) {
					MessageBox::Show(e->Message, "Error Server(Private File)");
				}
				break;
			}
			case ChatStruct::MessageType::RequestInfor:
			{
				RequestInforStruct^ rpSendFileStruct = (RequestInforStruct^)msgReceived;
				ServerController::getObject()->responseInfor(rpSendFileStruct->friendUsername, socket);
				break;
			}
			case ChatStruct::MessageType::ListPublicFileName:
			{
				ServerController::getObject()->listFileNameResponse(socket);
				break;
			}
			case ChatStruct::MessageType::UploadPublicFile:
			{
				UploadPublicFileStruct^ pubFile = (UploadPublicFileStruct^)msgReceived;
				try {

					if (pubFile->iPackageNumber == 1) {
					//	MessageBox::Show(Convert::ToString(pubFile->iPackageNumber)); //Delete
						ServerController::getObject()->addFileName(pubFile->fileName);
						ServerController::getObject()->fileStream = gcnew System::IO::FileStream(ServerController::getObject()->filePath + pubFile->fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
						ServerController::getObject()->fileSize = pubFile->iFileSize;
					}

					ServerController::getObject()->fileStream->Write(pubFile->bData, 0, pubFile->bData->Length);
					//System::IO::File::WriteAllBytes(ServerController::getObject()->filePath + pubFile->fileName, pubFile->bData);

					if (pubFile->iPackageNumber == pubFile->iTotalPackage)
					{
					//	MessageBox::Show(Convert::ToString(pubFile->iPackageNumber)); //Delete
						if ((int)ServerController::getObject()->fileStream->Length == pubFile->iFileSize)
							ServerController::getObject()->mainForm->AddTextToContent(ServerController::getObject()->getUsernameBySocket(socket) + " uploaded " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + " bytes) successfully!");
						else
							ServerController::getObject()->mainForm->AddTextToContent(ServerController::getObject()->getUsernameBySocket(socket) + " uploaded " + pubFile->fileName + "(" + Convert::ToString((int)ServerController::getObject()->fileStream->Length) + " bytes) (missed " + Convert::ToString(pubFile->iFileSize - (int)ServerController::getObject()->fileStream->Length) + "bytes)");

						ServerController::getObject()->fileStream->Close();
						ServerController::getObject()->fileStream = nullptr;
					}
				}
				catch (Exception^ e) {
					//ServerController::getObject()->fileStream->Close();
					//ServerController::getObject()->fileStream = nullptr;
					MessageBox::Show(e->Message, "Error ServerController(Receive Public File)");
					//continue;
				}

				break;

			}
			case ChatStruct::MessageType::RequestSendPublicFile:
			{
				try {
					RequestSendPublicFileStruct^ pubFile = (RequestSendPublicFileStruct^)msgReceived;
					ServerController::getObject()->sendPublicFile(pubFile->fileName, socket);
					if (ServerController::getObject()->fileStream != nullptr) {
						ServerController::getObject()->fileStream->Close();
						ServerController::getObject()->fileStream = nullptr;
					}

				}
				catch (Exception^ e) {

					ServerController::getObject()->fileStream->Close();
					ServerController::getObject()->fileStream = nullptr;
					MessageBox::Show(e->Message, "Error ServerController(Send Public File)");
				}
				break;
			}
			default:
				break;
			}

		}
		catch (Exception^ e)
		{
			return; //Finish this thread
		}
	}

}

System::Void MainForm::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e)
{
	Socket^ serverSocket = ServerController::getObject()->serverSocket;

	while (true)
	{
		Socket^ connectionSocket = serverSocket->Accept(); //Accept Connection From Client
		//lstConnectionSocket->Add(connectionSocket); //Add connection Socket to list

		threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(MainForm::ListenClientMessage));
		threadListenClient->IsBackground = true;
		threadListenClient->Start(connectionSocket); //Listen messages from client
	}

}

void MainForm::AddTextToContent(String^ text)
{
	txtClientChatBox->AppendText(text);
	txtClientChatBox->AppendText("\r\n");
}

void MainForm::UpdateConnectedClient(List<String^>^ lstClient) //
{
	txtConnected->Text = nullptr;
	for each (String ^ user in lstClient)
	{
		txtConnected->AppendText(user);
		txtConnected->AppendText("\r\n");
	}
}

//void MainForm::UpdateClientList(List<String^>^ lstClient)
//{
//	txtConnected->Text = nullptr;
//	for each (String ^ user in lstClient)
//	{
//		txtClientList->AppendText(user);
//		txtClientList->AppendText("\n");
//	}
//}

System::Void MainForm::btListen_Click(System::Object^ sender, System::EventArgs^ e)
{
	ServerController^ serverController = ServerController::getObject();
	String^ ipAddr = txtIPServer->Text->ToString();
	int portAddr = Convert::ToInt32(txtPortServer->Text->ToString());
	serverController->serverIPAddr = ipAddr;
	serverController->serverPort = portAddr;
	//Listen 
	IPAddress^ serverIPAddress = IPAddress::Parse(serverController->serverIPAddr);
	int serverPort = serverController->serverPort;
	IPEndPoint^ serverIPEndPoint = gcnew IPEndPoint(serverIPAddress, serverPort);

	serverController->serverSocket->Bind(serverIPEndPoint);
	serverController->serverSocket->Listen(10);

	backgroundWorker1->WorkerSupportsCancellation = true;
	backgroundWorker1->RunWorkerAsync();

	//Disable this button
	btListen->Enabled = false;
	txtIPServer->ReadOnly = true;
	txtPortServer->ReadOnly = true;
}

String^ MainForm::MainForm::convertHexToString(String^ hexInput)
{
	int numberChars = hexInput->Length;
	array<Byte>^ bytes = gcnew array<Byte>(numberChars / 2);
	for (int i = 0; i < numberChars; i += 2)
	{
		bytes[i / 2] = Convert::ToByte(hexInput->Substring(i, 2), 16);
	}
	return Encoding::UTF8->GetString(bytes);
}
