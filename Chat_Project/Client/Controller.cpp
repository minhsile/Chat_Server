#include"pch.h"
#include "Controller.h"
#define NULL 0
#define DEFAULT_BUFFER_LENGTH 10752
#define BUFFER_SIZE 10240
using namespace System::IO;

AppController::AppController() //Don't allow to create object
{
	appSocket = gcnew AppSocket();
}

AppController::~AppController()
{
	delete appSocket;
}

AppController^ AppController::getObject()
{
	if (_instance == nullptr)
	{
		_instance = gcnew AppController();
	}
	return _instance;
}

System::Void AppController::ListenMessage()
{
	while (true)
	{
		array<Byte>^ buff = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
		Socket^ clientSocket = AppController::getObject()->appSocket->clientSocket;
		int revc;
		try
		{
			revc = clientSocket->Receive(buff);
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Server has just disconnected!");
			AppController::getObject()->appSocket->clientSocket = nullptr;
			/*Application::Exit();
			break;*/
			Environment::Exit(0);
		}

		ChatStruct^ msgReceived = ChatControl::unpack(buff);
		switch (msgReceived->messageType)
		{
		case ChatStruct::MessageType::Login:
			//MessageBox::Show("Login Message?");
			break;
		case ChatStruct::MessageType::ResponseLogin:
		{
			//MessageBox::Show("Hello!");
			ResponseLoginStruct^ resLoginStruct = (ResponseLoginStruct^)msgReceived;
			if (resLoginStruct->IsSucc)
			{
				AppController::getObject()->loginScreen->Hide();
				//Create new form
				AppController::getObject()->mainScreen = gcnew Client::MainScreen;
				AppController::getObject()->mainScreen->ShowDialog();
				//Application::Run(AppController::getObject()->mainScreen);
			}
			else
			{
				MessageBox::Show(resLoginStruct->errorMsg);
			}

			break;
		}
		case ChatStruct::MessageType::ChangePassword:
			break;
		case ChatStruct::MessageType::ResponseChangePassword:
		{
			ResponseChangePasswordStruct^ resChangepassStruct = (ResponseChangePasswordStruct^)msgReceived;
			//MessageBox::Show("Hello!");
			if (resChangepassStruct->IsSucc)
			{
				MessageBox::Show("Password changed successfully!");
				AppController::getObject()->changePasswordScreen->Hide();
				//Create new form
				AppController::getObject()->mainScreen = gcnew Client::MainScreen;
				//AppController::getObject()->mainScreen->Show();
				//Application::Run(AppController::getObject()->mainScreen);
			}
			else
			{
				MessageBox::Show(resChangepassStruct->errorMsg);
			}

			break;
		}
		case ChatStruct::MessageType::PrivateMessage:
		{
			PrivateMessageStruct^ privateMsgStruct = (PrivateMessageStruct^)msgReceived;
			AppController::getObject()->setPrivateMessage(privateMsgStruct->strToUsername, privateMsgStruct->strMessage);
			break;
		}
		case ChatStruct::MessageType::ResponseSignup:
		{
			ResponseSignupStruct^ resSignUpStruct = (ResponseSignupStruct^)msgReceived;
			if (resSignUpStruct->IsSucc)
			{
				MessageBox::Show("Congratulation! You registered successfully!");
			}
			else
			{
				MessageBox::Show(resSignUpStruct->errorMsg);
			}
			break;
		}
		case ChatStruct::MessageType::Signup:
		{
			MessageBox::Show("Sign up received?");
			break;
		}
		case ChatStruct::MessageType::UserStatus:
		{
			//MessageBox::Show("Client Received: online users list");
			UserStatusStruct^ userStaStruct = (UserStatusStruct^)msgReceived;
			AppController::getObject()->mainScreen->SetOnlineUsers(userStaStruct->lstOnlineUsers);
			break;
		}
		case ChatStruct::MessageType::LoginNotification:
		{
			LoginNotificationStruct^ logNoti = (LoginNotificationStruct^)msgReceived;
			//AppController::getObject()->mainScreen->AddTextToContent(logNoti->strUsername + " has just online!");
			AppController::getObject()->mainScreen->AddAnOnlineUser(logNoti->strUsername);
			break;
		}
		case ChatStruct::MessageType::LogoutNotification:
		{
			LogoutNotificationStruct^ logOut = (LogoutNotificationStruct^)msgReceived;
			//MessageBox::Show("sax");
			//MessageBox::Show("Username: " + logOut->strUsername);
			//AppController::getObject()->mainScreen->AddTextToContent(logOut->strUsername + " has just offline!");
			AppController::getObject()->mainScreen->DeleteAnOnlineUser(logOut->strUsername);
			break;
		}
		case ChatStruct::MessageType::RequestSendFile:
		{
			RequestSendFileStruct^ rqSendFileStruct = (RequestSendFileStruct^)msgReceived;
			if (MessageBox::Show(rqSendFileStruct->strUsername + " want to send you a file " +
				rqSendFileStruct->strFileName + " (" + Convert::ToString(rqSendFileStruct->iFileSize) +
				" bytes).\nDo you want to receive?", "Receive a file", MessageBoxButtons::YesNo) == DialogResult::Yes)
			{
				AppController::getObject()->responseSendFile(rqSendFileStruct->strUsername, true);
			}
			else
			{
				AppController::getObject()->responseSendFile(rqSendFileStruct->strUsername, false);
			}
			break;
		}
		case ChatStruct::MessageType::ResponseSendFile:
		{
			ResponseSendFileStruct^ rpSendFileStruct = (ResponseSendFileStruct^)msgReceived;
			Client::PrivateChat^ prvChat = getPrivateChatFormByFriendUsername(rpSendFileStruct->strUsername);
			if (rpSendFileStruct->IsAccept)
			{
				setPrivateMessage(rpSendFileStruct->strUsername, rpSendFileStruct->strUsername + " accept a file "
					+ prvChat->fileNameToSend + " (" + Convert::ToString(prvChat->fileSizeToSend) + " bytes) from you!");

				sendPrivateFile(prvChat->strFriendUsername, prvChat->fileNameToSend, prvChat->filePathToSend);
			}
			else
			{

				setPrivateMessage(rpSendFileStruct->strUsername, rpSendFileStruct->strUsername + " don't accept to receive file "
					+ prvChat->fileNameToSend + " (" + Convert::ToString(prvChat->fileSizeToSend) + " bytes) from you!");
			}
			break;
		}
		case ChatStruct::MessageType::PrivateFile:
		{
			MessageBox::Show("Received");
			PrivateFileStruct^ prvFileStruct = (PrivateFileStruct^)msgReceived;
			setPrivateMessage(prvFileStruct->strUsername, "Received: " + prvFileStruct->iPackageNumber + "/" + prvFileStruct->iTotalPackage);
			Client::PrivateChat^ prvChat = getPrivateChatFormByFriendUsername(prvFileStruct->strUsername);
			if (prvFileStruct->iPackageNumber == 1)
				prvChat->writerStream = gcnew FileStream(prvChat->pathFileToReceiver + prvFileStruct->strFilename, FileMode::Create, FileAccess::Write);

			prvChat->writerStream->Write(prvFileStruct->bData, 0, prvFileStruct->bData->Length);

			if (prvFileStruct->iPackageNumber == prvFileStruct->iTotalPackage)
			{
				prvChat->writerStream->Close();
				prvChat->writerStream = nullptr;
			}
			break;
		}
		case ChatStruct::MessageType::ResponseInfor:
		{
			ResponseInforStruct^ resInfor = (ResponseInforStruct^)msgReceived;
			MessageBox::Show("Name: " + resInfor->friendUsername + "\nBirthdate: " + resInfor->birthDate, "Information");
			break;
		}
		case ChatStruct::MessageType::ListPublicFileName:
		{
			ListPublicFileNameStruct^ fileName = (ListPublicFileNameStruct^)msgReceived;
			if (fileName->listFileName != nullptr)
				AppController::getObject()->publicFileScreen->SetListFileName(fileName->listFileName);

			break;
		}
		case ChatStruct::MessageType::DownloadPublicFile:
		{
			DownloadPublicFileStruct^ pubFile = (DownloadPublicFileStruct^)msgReceived;
			try {

				if (pubFile->iPackageNumber == 1) {
					AppController::getObject()->publicFileScreen->setUpProcessBar(1, pubFile->iTotalPackage);//
					//AppController::getObject()->createThreadListenMessageFromServer();
					AppController::getObject()->publicFileScreen->fileSize = pubFile->iFileSize;
					AppController::getObject()->publicFileScreen->writerStream = gcnew System::IO::FileStream(AppController::getObject()->publicFileScreen->pathFileToReceiver + AppController::getObject()->publicFileScreen->fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
				}
				AppController::getObject()->publicFileScreen->writerStream->Write(pubFile->bData, 0, pubFile->bData->Length);
				AppController::getObject()->publicFileScreen->setValueOfProcessBar(pubFile->iPackageNumber);//
				if (pubFile->iPackageNumber == pubFile->iTotalPackage) {
					AppController::getObject()->publicFileScreen->resetProcessBar();//
					if (pubFile->iFileSize == (int)AppController::getObject()->publicFileScreen->writerStream->Length)
						MessageBox::Show("Downloaded " + AppController::getObject()->publicFileScreen->fileName/*pubFile->fileName*/ + " (" + Convert::ToString(pubFile->iFileSize) + " bytes) successfully!", "Notification");
					else
						MessageBox::Show("Downloaded " + AppController::getObject()->publicFileScreen->fileName/*pubFile->fileName*/ + " (" + Convert::ToString(pubFile->iFileSize) + " bytes) (missed " + Convert::ToString(pubFile->iFileSize - (int)AppController::getObject()->publicFileScreen->writerStream->Length) + "bytes)!", "Notification");
					AppController::getObject()->publicFileScreen->writerStream->Close();
					AppController::getObject()->publicFileScreen->writerStream = nullptr;
				}

			}

			catch (Exception^ e) {
				MessageBox::Show(e->Message, "Error Client(Receive Public File)");
			}
			break;
		}
		default:
			break;
		}
	}
}

int AppController::createThreadListenMessageFromServer()
{
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &AppController::ListenMessage));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();

	return 0;
}

int AppController::login(String^ _Username, String^ _Password)
{
	LoginStruct^ loginStruct = gcnew LoginStruct();
	loginStruct->strUsername = _Username;
	loginStruct->strPassword = _Password;
	if (MessageBox::Show("Do you want to encrypt message before sending?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes)
	{
		loginStruct->isEncrypted = true;
		loginStruct->strUsername = convertStringToHex(_Username);
		loginStruct->strPassword = convertStringToHex(_Password);
		isEncryptedLogin = true;
	}
	array<Byte>^ byteData = loginStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}
int AppController::signup(String^ _Username, String^ _Password)
{
	SignupStruct^ signupStruct = gcnew SignupStruct();
	signupStruct->strUsername = _Username;
	signupStruct->strPassword = _Password;
	if (MessageBox::Show("Do you want to encrypt message before sending?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes)
	{
		signupStruct->isEncrypted = true;
		signupStruct->strUsername = convertStringToHex(_Username);
		signupStruct->strPassword = convertStringToHex(_Password);
		isEncryptedSignup = true;
	}
	array<Byte>^ byteData = signupStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}
int AppController::changePassword(String^ Username, String^ oldPassword, String^ newPassword, String^ confirmnewPassword)
{
	ChangePasswordStruct^ changepasswordStruct = gcnew ChangePasswordStruct();
	changepasswordStruct->strUsername = Username;
	changepasswordStruct->strOldPassword = oldPassword;
	changepasswordStruct->strNewPassword = newPassword;
	changepasswordStruct->strConfirmNewPassword = confirmnewPassword;
	if (MessageBox::Show("Do you want to encrypt message before sending?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes)
	{
		changepasswordStruct->isEncrypted = true;
		changepasswordStruct->strUsername = convertStringToHex(Username);
		changepasswordStruct->strOldPassword = convertStringToHex(oldPassword);
		changepasswordStruct->strNewPassword = convertStringToHex(newPassword);
		changepasswordStruct->strConfirmNewPassword = convertStringToHex(confirmnewPassword);
		isEncryptedSignup = true;
	}
	array<Byte>^ byteData = changepasswordStruct->pack();
	appSocket->sendMessage(byteData);
	return 0;
}

int AppController::logout()
{
	LogoutNotificationStruct^ logOut = gcnew LogoutNotificationStruct;

	array<Byte>^ byteData = logOut->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

String^ AppController::convertStringToHex(String^ input)
{
	List<Byte>^ stringBytes = gcnew List<Byte>();
	stringBytes->AddRange(Encoding::UTF8->GetBytes(input));
	array<Byte>^ temp = stringBytes->ToArray();
	StringBuilder^ sbBytes = gcnew StringBuilder(temp->Length * 2);
	for each (Byte b in temp)
	{
		sbBytes->AppendFormat("{0:X2}", b);
	}
	return sbBytes->ToString();
}
//int AppController::sendPublicMessage(String^ _Message)
//{
//	PublicMessageStruct^ publicMessageStruct = gcnew PublicMessageStruct;
//	publicMessageStruct->strMessage = _Message;
//
//	array<Byte>^ byteData = publicMessageStruct->pack();
//
//	appSocket->sendMessage(byteData);
//
//	return 0;
//}

int AppController::sendPrivateMessage(String^ _ToUsername, String^ _Message)
{
	PrivateMessageStruct^ privateMessageStruct = gcnew PrivateMessageStruct;
	privateMessageStruct->strToUsername = _ToUsername;
	privateMessageStruct->strMessage = _Message;

	array<Byte>^ byteData = privateMessageStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::requestListOnlineUsers()
{
	UserStatusStruct^ userStatusStruct = gcnew UserStatusStruct;
	array<Byte>^ byteData = userStatusStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::requestListPublicFileName()
{
	ListPublicFileNameStruct^ fileName = gcnew ListPublicFileNameStruct();
	array<Byte>^ byteData = fileName->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize)
{
	RequestSendFileStruct^ rqSendFileStruct = gcnew RequestSendFileStruct;
	rqSendFileStruct->strFileName = _FileName;
	rqSendFileStruct->strUsername = _ToUsername;
	rqSendFileStruct->iFileSize = _iFileSize;
	array<Byte>^ byteData = rqSendFileStruct->pack();
	appSocket->sendMessage(byteData);
	return 0;
}

int AppController::responseSendFile(String^ _ToUsername, bool _IsAccept)
{
	ResponseSendFileStruct^ rpSendFileStruct = gcnew ResponseSendFileStruct;
	rpSendFileStruct->strUsername = _ToUsername;
	rpSendFileStruct->IsAccept = _IsAccept;
	array<Byte>^ byteData = rpSendFileStruct->pack();
	appSocket->sendMessage(byteData);

	return 0;
}

int AppController::sendPrivateFile(String^ _ToUsername, String^ _FileName, String^ _FilePath)
{
	PrivateFileStruct^ prvFileStruct = gcnew PrivateFileStruct;
	prvFileStruct->strFilename = _FileName;
	prvFileStruct->strUsername = _ToUsername;
	array<Byte>^ buffer;

	FileStream^ fileStream = nullptr;
	try
	{
		fileStream = gcnew FileStream(_FilePath, FileMode::Open, FileAccess::Read);
		int length = (int)fileStream->Length;  // get file length
		buffer = gcnew array<Byte>(length);            // create buffer

		int count;                            // actual number of bytes read
		int sum = 0;                          // total number of bytes read

		// read until Read method returns 0 (end of the stream has been reached)
		while ((count = fileStream->Read(buffer, sum, length - sum)) > 0)
		{
			sum += count;  // sum is a buffer offset for next reading
		}

		int BUFF_SIZE = 512;
		int counter = 0;
		int curPackageNumber = 1;
		int iTotalPackage = sum / (BUFF_SIZE + 1) + 1;

		//Console::WriteLine("Start send file: ");
		for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
		{
			//System::Array::Copy(buffer, counter, bData, BUFF_SIZE);
			int copyLength = counter + BUFF_SIZE < sum ? BUFF_SIZE : (sum % BUFF_SIZE);
			array<Byte>^ bData = gcnew array<Byte>(copyLength);
			Console::WriteLine(copyLength);
			System::Array::Copy(buffer, counter, bData, 0, copyLength);
			counter += BUFF_SIZE;
		//	ProgressBar pro;
		//	pro.Maximum = curPackageNumber;
			prvFileStruct->iPackageNumber = curPackageNumber; 
			prvFileStruct->iTotalPackage = iTotalPackage;
			prvFileStruct->bData = bData;
			array<Byte>^ byteData = prvFileStruct->pack();
			appSocket->sendMessage(byteData);
		//	pro.PerformStep();
			//MessageBox::Show("Debug");
			setPrivateMessage(_ToUsername, "Sent: " + curPackageNumber + "/" + iTotalPackage);

			//writeSteam->Write(bData, 0, copyLength);
		}
		//fileStream->Close();
		//Console::WriteLine("End of sending file");

	}
	catch (Exception^ e)
	{
		Console::WriteLine(e->Message);
	}
	finally
	{
		if (fileStream != nullptr)
			fileStream->Close();
	}
	return 0;
}

int AppController::setInfor(String^ _Username,String^ _Birthdate)
{
	SetInformationStruct^ setInfor = gcnew SetInformationStruct();
	setInfor->userName = _Username;
	setInfor->birthDate = _Birthdate;

	array<Byte>^ byteData = setInfor->pack();
	appSocket->sendMessage(byteData);
	return 0;
}

int AppController::requestInfor(String^ _friendUsername)
{
	RequestInforStruct^ inforFriend = gcnew RequestInforStruct();
	inforFriend->friendUsername = _friendUsername;
	array<Byte>^ byteData = inforFriend->pack();
	appSocket->sendMessage(byteData);
	return 0;
}

void AppController::uploadPublicFileToServer(String^ filePath, String^ fileName)
{
	UploadPublicFileStruct^ pubFile = gcnew UploadPublicFileStruct();

	array<Byte>^ buffer = System::IO::File::ReadAllBytes(filePath);
	pubFile->fileName = fileName;
	pubFile->iFileSize = buffer->Length;
	int check = 0;
	try
	{
		int counter = 0;
		int curPackageNumber = 1;
		int sum = buffer->Length;
		int iTotalPackage = buffer->Length / BUFFER_SIZE + 1;
		AppController::getObject()->publicFileScreen->setUpProcessBar(1, iTotalPackage);
		pubFile->iTotalPackage = iTotalPackage;
		for (; curPackageNumber <= iTotalPackage; curPackageNumber++)
		{
			//MessageBox::Show("Pack:" + Convert::ToString(curPackageNumber));
			Thread::Sleep(5);
			int copyLength = BUFFER_SIZE < sum ? BUFFER_SIZE : (sum % BUFFER_SIZE);
			sum -= copyLength;
			array<Byte>^ bData = gcnew array<Byte>(copyLength);
			System::Array::Copy(buffer, counter, bData, 0, copyLength);
			counter += copyLength;

			pubFile->bData = bData;
			check += bData->Length;
			pubFile->iPackageNumber = curPackageNumber;
			//pubFile->iTotalPackage = iTotalPackage;
			array<Byte>^ byteData = pubFile->pack();
			AppController::getObject()->appSocket->sendMessage(byteData);
			AppController::getObject()->publicFileScreen->setValueOfProcessBar(curPackageNumber);
			//delete[] pubFile->bData;
			delete[] bData;
		}
	}
	catch (Exception^ e)
	{
		MessageBox::Show(e->Message, "Send public file");
	}
	finally
	{
		AppController::getObject()->requestListPublicFileName();
		AppController::getObject()->publicFileScreen->resetProcessBar();
		if (check == buffer->Length)
			MessageBox::Show("Uploaded " + fileName + "(" + Convert::ToString(check) + ") bytes sucessfully!", "Notification");

		delete[] buffer;
	}

}

int AppController::requestDownloadPublicFile(String^ fileName)
{
	RequestSendPublicFileStruct^ rqFile = gcnew RequestSendPublicFileStruct();
	rqFile->fileName = fileName;
	array<Byte>^ byteData = rqFile->pack();
	appSocket->sendMessage(byteData);
	return 0;
}

int AppController::setPrivateMessage(String^ _ToUsername, String^ _Message)
{
	Client::PrivateChat^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
	if (prvChatForm != nullptr)
	{
		prvChatForm->AddTextToDisplayChatbox(_Message);
	}
	else
	{
		Client::PrivateChat^ pChat = gcnew Client::PrivateChat(strUsername, _ToUsername);
		lstPrivateChatForm->Add(pChat);
		setPrivateMessage(_ToUsername, _Message); //Re set private message

		Application::Run(pChat);
	}

	return 0;
}

Client::PrivateChat^ AppController::getPrivateChatFormByFriendUsername(String^ _Username)
{
	for each (Client::PrivateChat ^ prvChat in lstPrivateChatForm)
	{
		if (prvChat->strFriendUsername == _Username)
			return prvChat;
	}

	return nullptr; //not found
}

void AppController::threadPrivateChatForm(Object^ obj)
{
	MessageBox::Show("Debug thread");
	Client::PrivateChat^ pChat = (Client::PrivateChat^)obj;
	pChat->Show();
	MessageBox::Show("End Debug thread");
}
