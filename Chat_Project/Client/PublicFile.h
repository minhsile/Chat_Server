#pragma once
namespace Client {
	ref class PublicFile;
}
#include "Controller.h"
#include "ChangeFileName.h"
namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for PublicFile
	/// </summary>
	public ref class PublicFile : public System::Windows::Forms::Form
	{
	public:
		PublicFile(void)
		{
			InitializeComponent();
			pathFileToReceiver = splitPathFileToReceiver(System::Reflection::Assembly::GetEntryAssembly()->Location);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PublicFile()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labName;
	private: System::Windows::Forms::ListBox^ listBox_fileName;
	private: System::Windows::Forms::Button^ butUpLoad;
	private: System::Windows::Forms::Button^ butDownLoad;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ labFileNameChosen;

	private: System::Windows::Forms::TextBox^ txtFileChosen;
	private: System::Windows::Forms::Button^ butChangeName;
	private: System::Windows::Forms::Button^ butChooseFile;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labName = (gcnew System::Windows::Forms::Label());
			this->listBox_fileName = (gcnew System::Windows::Forms::ListBox());
			this->butUpLoad = (gcnew System::Windows::Forms::Button());
			this->butDownLoad = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->labFileNameChosen = (gcnew System::Windows::Forms::Label());
			this->txtFileChosen = (gcnew System::Windows::Forms::TextBox());
			this->butChangeName = (gcnew System::Windows::Forms::Button());
			this->butChooseFile = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->labName->AutoSize = true;
			this->labName->Location = System::Drawing::Point(21, 9);
			this->labName->Name = L"labName";
			this->labName->Size = System::Drawing::Size(63, 13);
			this->labName->TabIndex = 0;
			this->labName->Text = L"FILE NAME";

			this->listBox_fileName->FormattingEnabled = true;
			this->listBox_fileName->Location = System::Drawing::Point(24, 25);
			this->listBox_fileName->Name = L"listBox_fileName";
			this->listBox_fileName->Size = System::Drawing::Size(154, 186);
			this->listBox_fileName->TabIndex = 1;
			this->listBox_fileName->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PublicFile::listBoxFileName_OnMouseClick);

			this->butUpLoad->Location = System::Drawing::Point(184, 25);
			this->butUpLoad->Name = L"butUpLoad";
			this->butUpLoad->Size = System::Drawing::Size(95, 23);
			this->butUpLoad->TabIndex = 2;
			this->butUpLoad->Text = L"UPLOAD";
			this->butUpLoad->UseVisualStyleBackColor = true;
			this->butUpLoad->Click += gcnew System::EventHandler(this, &PublicFile::butUpLoad_Click);

			this->butDownLoad->Location = System::Drawing::Point(184, 54);
			this->butDownLoad->Name = L"butDownLoad";
			this->butDownLoad->Size = System::Drawing::Size(95, 23);
			this->butDownLoad->TabIndex = 2;
			this->butDownLoad->Text = L"DOWNLOAD";
			this->butDownLoad->UseVisualStyleBackColor = true;
			this->butDownLoad->Click += gcnew System::EventHandler(this, &PublicFile::butDownLoad_Click);

			this->progressBar1->Location = System::Drawing::Point(24, 253);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(255, 23);
			this->progressBar1->TabIndex = 3;

			this->labFileNameChosen->AutoSize = true;
			this->labFileNameChosen->Location = System::Drawing::Point(21, 226);
			this->labFileNameChosen->Name = L"labFileNameChosen";
			this->labFileNameChosen->Size = System::Drawing::Size(66, 13);
			this->labFileNameChosen->TabIndex = 4;
			this->labFileNameChosen->Text = L"FILE NAME:";

			this->txtFileChosen->Location = System::Drawing::Point(93, 223);
			this->txtFileChosen->Name = L"txtFileChosen";
			this->txtFileChosen->Size = System::Drawing::Size(186, 20);
			this->txtFileChosen->TabIndex = 5;

			this->butChangeName->Location = System::Drawing::Point(184, 188);
			this->butChangeName->Name = L"butChangeName";
			this->butChangeName->Size = System::Drawing::Size(95, 23);
			this->butChangeName->TabIndex = 2;
			this->butChangeName->Text = L"CHANGE NAME";
			this->butChangeName->UseVisualStyleBackColor = true;
			this->butChangeName->Click += gcnew System::EventHandler(this, &PublicFile::butChangeName_Click);

			this->butChooseFile->Location = System::Drawing::Point(184, 159);
			this->butChooseFile->Name = L"butChooseFile";
			this->butChooseFile->Size = System::Drawing::Size(95, 23);
			this->butChooseFile->TabIndex = 6;
			this->butChooseFile->Text = L"SELECT FILE";
			this->butChooseFile->UseVisualStyleBackColor = true;
			this->butChooseFile->Click += gcnew System::EventHandler(this, &PublicFile::butChooseFile_Click);

			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(291, 288);
			this->Controls->Add(this->butChooseFile);
			this->Controls->Add(this->txtFileChosen);
			this->Controls->Add(this->labFileNameChosen);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->butChangeName);
			this->Controls->Add(this->butDownLoad);
			this->Controls->Add(this->butUpLoad);
			this->Controls->Add(this->listBox_fileName);
			this->Controls->Add(this->labName);
			this->Name = L"PublicFile";
			this->Text = L"File";
			this->Load += gcnew System::EventHandler(this, &PublicFile::PublicFile_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: String^ fileName = nullptr;
	public: String^ fileFormat = nullptr;

	public: String^ fileNameToSend = nullptr;
	public: int fileSizeToSend = 0;

	public: FileStream^ writerStream = nullptr;
	public: String^ filePathToSend = nullptr;

	public: String^ fileNameToReceive = nullptr;
	public: String^ pathFileToReceiver;
	public: int fileSize = 0;
	public: ChangeFileName^ changeFileName = nullptr;

	private: System::Void PublicFile_Load(System::Object^ sender, System::EventArgs^ e);
	public: String^ splitPathFileToReceiver(String^ pathFile);
	public: String^ splitNameFile(String^ fileName);
	public: System::Void ThreadChooseFile();

	public:void SetListFileName(array<String^>^ listFileName);
	public: void setUpProcessBar(int min, int max);
	public: void resetProcessBar();
	public: void setValueOfProcessBar(int value);

	private: System::Void butUpLoad_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butDownLoad_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butChangeName_Click(System::Object^ sender, System::EventArgs^ e);
	private:System::Void listBoxFileName_OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	public: void setFileNameChosen(String^ text);
	public: void resetFileNameChosen();
	private: System::Void butChooseFile_Click(System::Object^ sender, System::EventArgs^ e);
};
}
