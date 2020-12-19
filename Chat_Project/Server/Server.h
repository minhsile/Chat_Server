#pragma once
//Singleton Pattern

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic; //List
using namespace System::Threading; //Thread
using namespace System::IO;

ref class ServerController; //Prototype
#include "MainForm.h"
#define DEFAULT_BUFFER_LENGTH 102912 // buffer file + buffer others
#define BUFFER_SIZE 102400
ref class ClientInfo
{
public:
	Socket^ clientSocket = nullptr;
	String^ strUsermame = nullptr;

	ClientInfo() {};
	ClientInfo(Socket^ _clientSocket, String^ _strUsermame) : clientSocket(_clientSocket), strUsermame(_strUsermame) {};
};


ref class ServerController
{
private:
	static ServerController^ _instance = nullptr;
	ServerController();
	int createSocket();
public:
	static ServerController^ getObject();
	~ServerController();

	//Database
	String^ accountPath = "../Server/Database/accounts.txt";
	String^ inforPath = "../Server/Database/infor.txt";

	FileStream^ fileStream = nullptr;
	int fileSize = 0;
	String^ fileNamePath = "../Server/Database/fileNames.txt";
	String^ filePath = "../Server/File/";

	//Form
	Server::MainForm^ mainForm;

	//Socket
	String^ serverIPAddr;
	int serverPort;
	Socket^ serverSocket;
	List<ClientInfo^>^ lstClientInfo = gcnew List<ClientInfo^>();

	//File
	bool addFileName(String^ fileName);
	void sendPublicFile(String^ fileName, Socket^ clientSocket);
	void listFileNameResponse(Socket^ clientSocket);
	array<String^>^ getListFileName();

	//Helper
	bool checkLogin(String^ Username, String^ Password, String^& errorMsg);
	bool checkAccount(String^ Username, String^ Password);
	bool checkSignup(String^ Username, String^ Password, String^& errorMsg);
	bool checkChangePass(String^ Username, String^ Password, String^ newPassword, String^ confirmnewPassword, String^& errorMsg);
	bool checkAccountExists(String^ Username);
	bool addAnAccountToDatabase(String^ Username, String^ Password);
	void setInfor(String^ userName, String^ birthDate);

	//Main calling
	bool login(String^ Username, String^ Password, Socket^ _ClientSocket);
	void loginResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket);
	bool signup(String^ Username, String^ Password, Socket^ _ClientSocket);
	void signupResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket);
	bool changePassword(String^ Username, String^ oldPassword, String^ newPassword, String^ confirmnewPassword, Socket^ _ClientSocket);
	void changePassResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket);
	void userStatusResponse(Socket^ _ClientSocket);
	void sendLoginNotification(String^ Username, Socket^ _ClientSocket);
	void sendLogoutNotification(Socket^ _ClientSocket);
	void requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize, Socket^ _ClientSocket);
	void responseSendFile(String^ _ToUsername, bool _IsAccept, Socket^ _ClientSocket);
	void responseInfor(String^ _friendUsername, Socket^ _ClientSocket);
	void sendPrivateFilePackage(String^ _ToUsername, String^ _Filename, int _iPackageNumber, int _TotalPackage, array<Byte>^ _bData, Socket^ _ClientSocket);

	//int sendPublicMsgToClients(String^ _strMessage, Socket^ _ClientSocket);

	////Server send message to specify username client socket
	int sendPrivateMessage(String^ _ToUsername, String^ _Message, Socket^ _ClientSocket);

	//Others
	List<String^>^ getListClient();
	//List<String^>^ getRegisteredClientList();
	String^ getUsernameBySocket(Socket^ _socket);
	Socket^ getSocketByUsername(String^ Username);
	void removeClientInfoByUsername(String^ Username);
};

