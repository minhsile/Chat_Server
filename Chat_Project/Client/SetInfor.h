#pragma once

namespace Client {
	ref class SetInfor;
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
	/// Summary for SetInfor
	/// </summary>
	public ref class SetInfor : public System::Windows::Forms::Form
	{
	public:
		SetInfor(void)
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
		~SetInfor()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labBirthdate;
	private: System::Windows::Forms::TextBox^ txtBirthdate;
	private: System::Windows::Forms::Button^ butSave;
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
			this->labBirthdate = (gcnew System::Windows::Forms::Label());
			this->txtBirthdate = (gcnew System::Windows::Forms::TextBox());
			this->butSave = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// labBirthdate
			// 
			this->labBirthdate->AutoSize = true;
			this->labBirthdate->Location = System::Drawing::Point(12, 20);
			this->labBirthdate->Name = L"labBirthdate";
			this->labBirthdate->Size = System::Drawing::Size(52, 13);
			this->labBirthdate->TabIndex = 0;
			this->labBirthdate->Text = L"Birthdate:";
			// 
			// txtBirthdate
			// 
			this->txtBirthdate->Location = System::Drawing::Point(70, 17);
			this->txtBirthdate->Name = L"txtBirthdate";
			this->txtBirthdate->Size = System::Drawing::Size(100, 20);
			this->txtBirthdate->TabIndex = 1;
			// 
			// butSave
			// 
			this->butSave->Location = System::Drawing::Point(49, 54);
			this->butSave->Name = L"butSave";
			this->butSave->Size = System::Drawing::Size(75, 23);
			this->butSave->TabIndex = 2;
			this->butSave->Text = L"Save";
			this->butSave->UseVisualStyleBackColor = true;
			this->butSave->Click += gcnew System::EventHandler(this, &SetInfor::butSave_Click);
			// 
			// SetInfor
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(196, 89);
			this->Controls->Add(this->butSave);
			this->Controls->Add(this->txtBirthdate);
			this->Controls->Add(this->labBirthdate);
			this->Name = L"SetInfor";
			this->Text = L"Set your information";
			this->Load += gcnew System::EventHandler(this, &SetInfor::SetInfor_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SetInfor_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butSave_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
