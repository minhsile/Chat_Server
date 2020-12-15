#include "pch.h"
#include "ChangeFileName.h"

System::Void Client::ChangeFileName::butChange_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ fileName = this->txtFileRename->Text->ToString();
	AppController::getObject()->publicFileScreen->fileName = fileName + AppController::getObject()->publicFileScreen->fileFormat;
	AppController::getObject()->publicFileScreen->setFileNameChosen(fileName + AppController::getObject()->publicFileScreen->fileFormat);
	this->butChange->Enabled = false;
	this->Close();
}
