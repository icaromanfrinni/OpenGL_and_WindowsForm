#pragma once

//#include <GL/glew.h>
#include <GL/glut.h>

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		//OPENGL BEGIN
		HDC hDC; // Private GDI Device Context (glut.h)
		HGLRC hRC; // Get handle to panel on form and call initialization function (glut.h)
		//OPENGL END
		MyForm(void)
		{
			InitializeComponent();

			//OPENGL BEGIN
			HWND hWnd = (HWND)panel1->Handle.ToInt64(); //glut.h
			InitializeOpenGL(GetDC(hWnd)); // Definida abaixo
			InitGL(); // Definida abaixo
			//OPENGL END

			//
			//TODO: Add the constructor code here
			//
		}

	bool InitializeOpenGL(HDC hdc)
	{
		hDC = hdc;
		//CreateParams^ cp = gcnew CreateParams; // "WTF"

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),	// size of this pfd
			1,								// version number
			PFD_DRAW_TO_WINDOW |			// support window 
			PFD_SUPPORT_OPENGL |			// support OpenGL
			PFD_DOUBLEBUFFER,				// double buffered
			PFD_TYPE_RGBA,					// RGBA type
			32,								// 32-bit color depth
			0,0,0,0,0,0,					// color bits ignored
			8,								// alpha buffer
			0,								// shift bit ignored
			0,								// no accumulation buffer
			0,0,0,0,						// accum bits ignored
			24,								// 24-bit z-buffer
			0,								// no stencil buffer
			0,								// no auxiliary buffer
			PFD_MAIN_PLANE,					// main layer
			0,								// reserved
			0,0,0							// layer masks ignored
		};

		int PixelFormat = ChoosePixelFormat(hDC, &pfd);
		SetPixelFormat(hDC, PixelFormat, &pfd);

		wglDeleteContext(hRC);
		hRC = wglCreateContext(hDC);

		if (hRC == NULL) { return false; }

		if (wglMakeCurrent(hDC, hRC) == false) { return false; }

		return true;
	}

	int InitGL(GLvoid)
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
		glClearDepth(1.0f);									// Depth Buffer Setup
		glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
		glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		//glColor4f(0.6f, 0.0f, 0.0f, 1.0);					// Full Brightness.  50% Alpha
		return TRUE;										// Initialization Went OK
	}

	void Render()
	{
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glPushMatrix();
		glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(0.0f, 1.0f);
		glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.87f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(-0.87f, -0.5f);
		glEnd();
		glPopMatrix();

		SwapBuffers(hDC);
	}
			   		 	  	  	   	
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->Location = System::Drawing::Point(25, 27);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(229, 196);
			this->panel1->TabIndex = 0;
			this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 262);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"MyForm";
			this->Text = L"OpenGL WinForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
	}
	private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
	}
	private: System::Void panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
	{
		Render();
	}

	};
}
