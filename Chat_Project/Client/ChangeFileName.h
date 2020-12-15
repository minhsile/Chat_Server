#pragma once
namespace Client {
	ref class ChangeFileName;
}
#include "Controller.h"
namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ChangeFileName
	/// </summary>
	public ref class ChangeFileName : public System::Windows::Forms::Form
	{
	public:
		ChangeFileName(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChangeFileName()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labFileName;
	private: System::Windows::Forms::TextBox^ txtFileRename;

	protected:

	private: System::Windows::Forms::Button^ butChange;

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
			this->labFileName = (gcnew System::Windows::Forms::Label());
			this->txtFileRename = (gcnew System::Windows::Forms::TextBox());
			this->butChange = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			this->labFileName->AutoSize = true;
			this->labFileName->Location = System::Drawing::Point(13, 19);
			this->labFileName->Name = L"labFileName";
			this->labFileName->Size = System::Drawing::Size(63, 13);
			this->labFileName->TabIndex = 0;
			this->labFileName->Text = L"New Name:";
			this->txtFileRename->Location = System::Drawing::Point(79, 16);
			this->txtFileRename->Name = L"txtFileRename";
			this->txtFileRename->Size = System::Drawing::Size(194, 20);
			this->txtFileRename->TabIndex = 1;
			this->butChange->Location = System::Drawing::Point(101, 43);
			this->butChange->Name = L"butChange";
			this->butChange->Size = System::Drawing::Size(75, 23);
			this->butChange->TabIndex = 2;
			this->butChange->Text = L"Change";
			this->butChange->UseVisualStyleBackColor = true;
			this->butChange->Click += gcnew System::EventHandler(this, &ChangeFileName::butChange_Click);
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(281, 73);
			this->Controls->Add(this->butChange);
			this->Controls->Add(this->txtFileRename);
			this->Controls->Add(this->labFileName);
			this->Name = L"ChangeFileName";
			this->Text = L"Rename File";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void butChange_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
