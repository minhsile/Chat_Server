#include"pch.h"
#include "Server.h"
#include "../Struct/AllStruct.h"

ServerController::ServerController()
{
	serverIPAddr = "192.168.0.100";
	serverPort = 2020;

	createSocket();
}

ServerController^ ServerController::getObject()
{
	if (_instance == nullptr)
	{
		_instance = gcnew ServerController();
	}

	return _instance;
}

ServerController::~ServerController()
{
	delete serverSocket;
}

int ServerController::createSocket()
{
	serverSocket = gcnew Socket(AddressFamily::InterNetwork,
		SocketType::Stream, ProtocolType::Tcp);

	return 0;
}

//Helper


bool ServerController::addFileName(String^ fileName)
{
	try {
		array<String^>^ lines = System::IO::File::ReadAllLines(fileNamePath);
		for (int i = 0; i < lines->Length; i++)
		{
			if (lines[i]->Contains(fileName))
			{
				return false;
			}
		}
		System::IO::File::AppendAllText(this->fileNamePath, fileName + "\n");
	}
	catch (Exception^ e) {
		return false;
	}

	return true;
}

void ServerController::sendPublicFile(String^ fileName, Socket^ clientSocket)
{
	array<Byte>^ buffer = System::IO::File::ReadAllBytes(filePath + fileName);
	DownloadPublicFileStruct^ pubFile = gcnew DownloadPublicFileStruct();
	pubFile->fileName = fileName;
	pubFile->iFileSize = buffer->Length;
	int check = 0;
	int sum = buffer->Length;
	int counter = 0;
	int curPackageNumber = 1;
	int iTotalPackage = sum / (BUFFER_SIZE + 1) + 1;
	for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
	{
		Thread::Sleep(5);
		int copyLength = BUFFER_SIZE < sum ? BUFFER_SIZE : (sum % BUFFER_SIZE);
		sum -= copyLength;
		pubFile->bData = gcnew array<Byte>(copyLength);
		System::Array::Copy(buffer, counter, pubFile->bData, 0, copyLength);
		counter += copyLength;
		check += pubFile->bData->Length;
		pubFile->iPackageNumber = curPackageNumber;
		pubFile->iTotalPackage = iTotalPackage;
		array<Byte>^ byteData = pubFile->pack();
		clientSocket->Send(byteData);
		//delete[] pubFile->bData;
	}


	if (check == buffer->Length)
		ServerController::getObject()->mainForm->AddTextToContent("Sent " + pubFile->fileName + "(" + Convert::ToString(check) + ") bytes" + " to " + getUsernameBySocket(clientSocket) + " successfully !");
	//delete[] buffer;

}
void ServerController::listFileNameResponse(Socket^ clientSocket)
{
	ListPublicFileNameStruct^ listFileName = gcnew ListPublicFileNameStruct();
	listFileName->listFileName = getListFileName();
	array<Byte>^ data = listFileName->pack();
	clientSocket->Send(data);
}
array<String^>^ ServerController::getListFileName()
{
	{
		array<String^>^ lines = nullptr;
		lines = System::IO::File::ReadAllLines(fileNamePath);

		return lines;
	}
}
bool ServerController::checkLogin(String^ Username, String^ Password, String^& errorMsg)
{
	//Check for blank!
	if (String::IsNullOrEmpty(Username) || String::IsNullOrEmpty(Password))
	{
		errorMsg = "Username or Password can't be blank!";
		return false;
	}

	//Check for special characters
	//String^ lstSpecialCharacters = "|"
	if (Username->Contains("|") || Username->Contains("|"))
	{
		errorMsg = "Username or password can't contain special characters!";
		return false;
	}

	//Check account in database
	if (!checkAccount(Username, Password))
	{
		errorMsg = "Username or Password is not correct!";
		return false;
	}

	//Check account in current online
	for each (String ^ user in getListClient())
	{
		if (Username == user)
		{
			errorMsg = user + " is current login on another client!";
			return false;
		}
	}

	return true;
}

bool ServerController::checkAccount(String^ Username, String^ Password)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
	for each (String ^ line in lines)
	{
		//MessageBox::Show(line);
		if (line == Username + "|" + Password)
		{
			return true;
		}
	}

	return false;
}
void ServerController::setInfor(String^ userName, String^ birthDate)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(inforPath);
	for (int i = 0; i < lines->Length; i++)
	{
		if (lines[i]->Contains(userName + "|"))
		//if (lines[i] == userName + "|")
		{
			//MessageBox::Show("Hello guy");
			lines[i] = userName + "|" + birthDate;
			break;
		}
	}
	System::IO::File::WriteAllLines(inforPath, lines);
}

bool ServerController::checkSignup(String^ Username, String^ Password, String^& errorMsg)
{
	//Check for blank!
	if (String::IsNullOrEmpty(Username) || String::IsNullOrEmpty(Password))
	{
		errorMsg = "Username or Password can't be blank!";
		return false;
	}

	//Check for special characters
	//String^ lstSpecialCharacters = "|"
	if (Username->Contains("|") || Password->Contains("|"))
	{
		errorMsg = "Username or password can't contain special characters!";
		return false;
	}

	//Check exists username in database
	if (checkAccountExists(Username))
	{
		errorMsg = "This username has been registered!";
		return false;
	}

	if (!addAnAccountToDatabase(Username, Password))
	{
		errorMsg = "Can't register!";
		return false;
	}

	return true;
}
bool ServerController::checkChangePass(String^ Username, String^ Password, String^ newPassword, String^ confirmnewPassword, String^& errorMsg)
{
	//Check for blank!
	if (String::IsNullOrEmpty(Username) || String::IsNullOrEmpty(Password))
	{
		errorMsg = "Username or Password can't be blank!";
		return false;
	}

	//Check for special characters
	//String^ lstSpecialCharacters = "|"
	if (Username->Contains("|") || Username->Contains("|"))
	{
		errorMsg = "Username or password can't contain special characters!";
		return false;
	}

	//Check account in database
	if (!checkAccount(Username, Password))
	{
		errorMsg = "Username or Password is not correct!";
		return false;
	}
	if (newPassword != confirmnewPassword)
	{
		errorMsg = "Password and Confirm Password does not match!";
		return false;
	}
	return true;
}
bool ServerController::checkAccountExists(String^ Username)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
	for each (String ^ line in lines)
	{
		//MessageBox::Show(line);
		if (line->Contains(Username + "|"))
		{
			return true;
		}
	}

	return false;
}

bool ServerController::addAnAccountToDatabase(String^ Username, String^ Password)
{
	try
	{
		System::IO::File::AppendAllText(accountPath, Username + "|" + Password + "\n");
		System::IO::File::AppendAllText(inforPath, Username + "|" + "\n");
	}
	catch (Exception^ e)
	{
		return false;
	}
	return true;
}

bool ServerController::login(String^ Username, String^ Password, Socket^ _ClientSocket)
{
	String^ errorMsg = "";
	if (checkLogin(Username, Password, errorMsg))
	{
		lstClientInfo->Add(gcnew ClientInfo(_ClientSocket, Username));
		mainForm->UpdateConnectedClient(getListClient()); //Update list connected

		mainForm->AddTextToContent(Username + " hast just online!");
		loginResponse(true, errorMsg, _ClientSocket);
		mainForm->UpdateConnectedClient(getListClient());
		sendLoginNotification(Username, _ClientSocket);

		return true; //Login successs
	}

	loginResponse(false, errorMsg, _ClientSocket);

	return false; //Error login
}

void ServerController::loginResponse(bool IsSucc, String^ _errorMsg, Socket^ _ClientSocket)
{
	ResponseLoginStruct^ resLogin = gcnew ResponseLoginStruct;
	resLogin->IsSucc = IsSucc;
	resLogin->errorMsg = _errorMsg;
	array<Byte>^ buff = resLogin->pack();

	_ClientSocket->Send(buff); //Send the result to client.
}

bool ServerController::signup(String^ Username, String^ Password, Socket^ _ClientSocket)
{
	String^ errorMsg = "";
	if (checkSignup(Username, Password, errorMsg))
	{
		signupResponse(true, errorMsg, _ClientSocket);
		//mainForm->UpdateClientList(getRegisteredClientList());

		return true; //Signup successs
	}
	signupResponse(false, errorMsg, _ClientSocket);

	return false; //Error sign up
}

void ServerController::signupResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket)
{
	ResponseSignupStruct^ resSignup = gcnew ResponseSignupStruct;
	resSignup->IsSucc = IsSucc;
	resSignup->errorMsg = errorMsg;
	array<Byte>^ buff = resSignup->pack();

	_ClientSocket->Send(buff); //Send the result to client.
}

bool ServerController::changePassword(String^ Username, String^ oldPassword, String^ newPassword, String^ confirmnewPassword, Socket^ _ClientSocket)
{
	String^ errorMsg = "";
	if (checkChangePass(Username, oldPassword,newPassword, confirmnewPassword, errorMsg))
	{
		array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
		//for each (String ^ line in lines)
		for (int i = 0; i < lines->Length; i++)
		{
			//MessageBox::Show(line);
			if (lines[i] == Username + "|" + oldPassword)
			{
				//MessageBox::Show(line);
				//line->Replace(/*Username + "|" + oldPassword*/line, Username + "|" + newPassword);
				lines[i] = Username + "|" + newPassword;
				break;
			}
		}
		System::IO::File::WriteAllLines(accountPath, lines);
		changePassResponse(true, errorMsg, _ClientSocket);
		return true;
	}
	changePassResponse(false, errorMsg, _ClientSocket);
	return false; //Error 
}
void ServerController::changePassResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket)
{
	ResponseChangePasswordStruct^ resChangePass = gcnew ResponseChangePasswordStruct;
	resChangePass->IsSucc = IsSucc;
	resChangePass->errorMsg = errorMsg;
	array<Byte>^ buff = resChangePass->pack();

	_ClientSocket->Send(buff); //Send the result to client.
}

void ServerController::sendLoginNotification(String^ Username, Socket^ _ClientSocket)
{
	LoginNotificationStruct^ loginNoti = gcnew LoginNotificationStruct;
	loginNoti->strUsername = Username;
	array<Byte>^ buff = loginNoti->pack();

	for each (ClientInfo ^ clientInfo in lstClientInfo)
	{
		if (clientInfo->clientSocket != _ClientSocket) //Send the others login notication
		{
			clientInfo->clientSocket->Send(buff);
		}
	}
}

void ServerController::sendLogoutNotification(Socket^ _ClientSocket)
{
	String^ clientUsername = getUsernameBySocket(_ClientSocket);
	LogoutNotificationStruct^ logoutNoti = gcnew LogoutNotificationStruct;
	logoutNoti->strUsername = clientUsername;
	array<Byte>^ buff = logoutNoti->pack();

	mainForm->AddTextToContent(clientUsername + " hast just offline!");
	removeClientInfoByUsername(clientUsername);
	mainForm->UpdateConnectedClient(getListClient()); //Update list connected

	for each (ClientInfo ^ clientInfo in lstClientInfo)
	{
		if (clientInfo->clientSocket != _ClientSocket) //Send the others logout notication
		{
			clientInfo->clientSocket->Send(buff);
		}
	}
}
void ServerController::userStatusResponse(Socket^ _ClientSocket)
{
	UserStatusStruct^ userStatusStruct = gcnew UserStatusStruct;
	userStatusStruct->lstOnlineUsers = getListClient()->ToArray();
	array<Byte>^ buff = userStatusStruct->pack();
	_ClientSocket->Send(buff);
}


String^ ServerController::getUsernameBySocket(Socket^ _socket)
{
	for each (ClientInfo ^ clientInfo in lstClientInfo)
		if (clientInfo->clientSocket == _socket)
			return clientInfo->strUsermame;

	return nullptr;
}

Socket^ ServerController::getSocketByUsername(String^ Username)
{
	for each (ClientInfo ^ clientInfo in lstClientInfo)
		if (clientInfo->strUsermame == Username)
			return clientInfo->clientSocket;

	return nullptr;
}

void ServerController::removeClientInfoByUsername(String^ Username)
{
	for each (ClientInfo ^ clientInfo in lstClientInfo)
		if (clientInfo->strUsermame == Username)
		{
			lstClientInfo->Remove(clientInfo);
			break;
		}
}

List<String^>^ ServerController::getListClient()
{
	List<String^>^ listClient = gcnew List<String^>;
	for each (ClientInfo ^ clientInfo in lstClientInfo)
	{
		listClient->Add(clientInfo->strUsermame);
	}
	return listClient;
}

//List<String^>^ ServerController::getRegisteredClientList()
//{
//	array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
//	List<String^>^ listLines = gcnew List<String^>();
//	for each (String ^ line in lines)
//	{
//
//		listLines->Add(line->Substring(0, line->IndexOf("|")));
//	}
//
//	return listLines;
//}

void ServerController::requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	RequestSendFileStruct^ rqSendFileStruct = gcnew RequestSendFileStruct;
	rqSendFileStruct->strUsername = sender;
	rqSendFileStruct->strFileName = _FileName;
	rqSendFileStruct->iFileSize = _iFileSize;

	Socket^ receiver = getSocketByUsername(_ToUsername);
	array<Byte>^ byteData = rqSendFileStruct->pack();
	receiver->Send(byteData);
}

void ServerController::responseSendFile(String^ _ToUsername, bool _IsAccept, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	ResponseSendFileStruct^ rpSendFileStruct = gcnew ResponseSendFileStruct;
	rpSendFileStruct->strUsername = sender;
	rpSendFileStruct->IsAccept = _IsAccept;

	Socket^ receiver = getSocketByUsername(_ToUsername);
	array<Byte>^ byteData = rpSendFileStruct->pack();
	receiver->Send(byteData);
}

void ServerController::responseInfor(String^ _friendUsername, Socket^ _ClientSocket)
{
	array<String^>^ lines = System::IO::File::ReadAllLines(inforPath);
	String^ BirthDate;
	for (int i = 0; i < lines->Length; i++)
	{
		if (lines[i]->Contains(_friendUsername + "|"))
		{
			//MessageBox::Show("Hello guy");
			BirthDate = lines[i]->Remove(0, _friendUsername->Length + 1);
			break;
		}
	}
	//System::IO::File::WriteAllLines(inforPath, lines);
	ResponseInforStruct^ resInfor = gcnew ResponseInforStruct;
	resInfor->friendUsername = _friendUsername;
	resInfor->birthDate = BirthDate;

	//Socket^ receiver = getSocketByUsername(_ToUsername);
	array<Byte>^ buff = resInfor->pack();
	_ClientSocket->Send(buff);
}

void ServerController::sendPrivateFilePackage(String^ _ToUsername, String^ _Filename, int _iPackageNumber, int _TotalPackage, array<Byte>^ _bData, Socket^ _ClientSocket)
{
	String^ sender = getUsernameBySocket(_ClientSocket);
	PrivateFileStruct^ prvFileStruct = gcnew PrivateFileStruct;
	prvFileStruct->strUsername = sender;
	prvFileStruct->strFilename = _Filename;
	prvFileStruct->bData = _bData;
	prvFileStruct->iPackageNumber = _iPackageNumber;
	prvFileStruct->iTotalPackage = _TotalPackage;

	array<Byte>^ byteData = prvFileStruct->pack();
	Socket^ receiver = getSocketByUsername(_ToUsername);
	receiver->Send(byteData);
}

int ServerController::sendPrivateMessage(String^ _ToUsername, String^ _Message, Socket^ _SenderSocket)
{
	String^ sender = getUsernameBySocket(_SenderSocket);
	Socket^ receiverSocket = getSocketByUsername(_ToUsername);
	//If receiver is offline (nullptr)

	PrivateMessageStruct^ privateMessageStruct = gcnew PrivateMessageStruct;
	if (receiverSocket == nullptr)
	{
		//Send error message back to sender
		privateMessageStruct->strMessage = "Error: " + _ToUsername + " is offline!";
		privateMessageStruct->strToUsername = _ToUsername;
		array<Byte>^ byteData = privateMessageStruct->pack();
		_SenderSocket->Send(byteData);
	}
	else
	{
		privateMessageStruct->strMessage = sender + ": " + _Message;
		privateMessageStruct->strToUsername = sender;
		array<Byte>^ byteData = privateMessageStruct->pack();
		receiverSocket->Send(byteData);
	}

	return 0;
}