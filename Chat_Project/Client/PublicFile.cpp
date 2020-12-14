#include "pch.h"
#include "PublicFile.h"

System::Void Client::PublicFile::PublicFile_Load(System::Object^ sender, System::EventArgs^ e)
{
	AppController::getObject()->createThreadListenMessageFromServer();
	AppController::getObject()->requestListPublicFileName();
}

String^ Client::PublicFile::splitPathFileToReceiver(String^ pathFile)
{
	int length = pathFile->Length;
	int i = length - 1;
	for (i; i >= 0; --i) {
		if (pathFile[i] == '\\')
			break;
	}
	pathFile = pathFile->Remove(i + 1);
	return pathFile;
}

System::Void Client::PublicFile::ThreadChooseFile()
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ _info = ofd->SafeFileName;
		String^ info = ofd->FileName;
		int size = IO::FileInfo(ofd->FileName).Length;

		fileNameToSend = _info;
		filePathToSend = info;
		fileSizeToSend = size;

		AppController::getObject()->uploadPublicFileToServer(info, _info);
	}
}

void Client::PublicFile::SetListFileName(array<String^>^ listFileName)
{
	this->listBox_fileName->Items->Clear();
	for each (String ^ fileName in listFileName) {
		this->listBox_fileName->Items->Add(fileName);
	}
}

void Client::PublicFile::setUpProcessBar(int min, int max)
{
	this->progressBar1->Minimum = min;
	this->progressBar1->Maximum = max;
}

void Client::PublicFile::resetProcessBar()
{
	this->progressBar1->Minimum = 0;
	this->progressBar1->Maximum = 0;
	this->progressBar1->Value = 0;
}

void Client::PublicFile::setValueOfProcessBar(int value)
{
	this->progressBar1->Value = value;
}

System::Void Client::PublicFile::butUpLoad_Click(System::Object^ sender, System::EventArgs^ e)
{
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &PublicFile::ThreadChooseFile));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}

System::Void Client::PublicFile::butDownLoad_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (fileNameToReceive != nullptr)
		AppController::getObject()->requestDownloadPublicFile(fileNameToReceive);
}

System::Void Client::PublicFile::listBoxFileName_OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	int index = this->listBox_fileName->IndexFromPoint(e->Location);
	if (index != System::Windows::Forms::ListBox::NoMatches)
	{
		String^ fileName = this->listBox_fileName->Items[index]->ToString();
		fileNameToReceive = fileName;
	}
}
