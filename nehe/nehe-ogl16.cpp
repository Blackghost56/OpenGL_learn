/*
 *		��� ��������� ������� ������ ������ (Jeff Molofee) � 2000 �.
 *		�������� ������� ��������� ������ (Fredric Echols) �� ���������
 *		� ����������� �������� ����, �� ���������� ��� ��������!
 *		���� �� ����� ��� ��������� ��������, ����������, ����� ��� �����.
 *		�������� ��� ���� nehe.gamedev.net
 */

#include <windows.h>		// ������������ ���� ��� Windows
#include <stdio.h>			// ������������ ���� ������������ �����/������
#include <gl\gl.h>			// ������������ ���� ��� OpenGL32 ����������
#include <gl\glu.h>			// ������������ ���� ��� GLu32 ����������
#include <gl\glaux.h>		// ������������ ���� ��� GLaux ����������

HDC			hDC=NULL;		// ������� �������� GDI ����������
HGLRC		hRC=NULL;		// ���������� �������� �����������
HWND		hWnd=NULL;		// �������� ����� ������ ����
HINSTANCE	hInstance;		// �������� ��������� ����������

bool	keys[256];			// ������ ����������� ��� ������������ ����������
bool	active=TRUE;		// ���� "��������" ����. ��������������� �������� (TRUE) �� ���������.
bool	fullscreen=TRUE;	// ���� "�� ������ �����". ��������������� � ������������� ����� �� ���������.
bool	light;				// ��������� ���./����.
bool	lp;					// L ������?
bool	fp;					// F ������?
bool	gp;					// G ������? ( ����� )

GLfloat	xrot;				// �������� ����� ��� X
GLfloat	yrot;				// �������� ����� ��� Y
GLfloat xspeed;				// �������� �������� ����� ��� X
GLfloat yspeed;				// �������� �������� ����� ��� X
GLfloat	z=-5.0f;			// ������� � �����.

// ������ ��������� ���������
GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

GLuint	filter;				// ������������ ������ ��� ������� 
GLuint	texture[3];			// ������ 3 ��������
GLuint	fogMode[]= { GL_EXP, GL_EXP2, GL_LINEAR };	// ������ ��� ���� ������
GLuint	fogfilter = 0;								// ��� ������������ ������
GLfloat	fogColor[4] = {0.5f,0.5f,0.5f,1.0f};		// ���� ������

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// ���������� ��� WndProc

AUX_RGBImageRec *LoadBMP(char *Filename)				// ��������� ��������� ����� - BitMaP
{
	FILE *File=NULL;									// ����� �����

	if (!Filename)										// ��������� ��� ��� ����� ������
	{
		return NULL;									// ���� ���, ������� NULL
	}

	File=fopen(Filename,"r");							// ��������, ��������� �� ����?

	if (File)											// ����������?
	{
		fclose(File);									// ������� �����
		return auxDIBImageLoad(Filename);				// ��������� ����� � ������� ���������
	}

	return NULL;										// ���� �� ���������� ���������, ������� NULL
}

int LoadGLTextures()									// ��������� ������ � ����������� � ��������
{
	int Status=FALSE;									// ��������� ���������

	AUX_RGBImageRec *TextureImage[1];					// ������� ������������ ��� �������� ��������

	memset(TextureImage,0,sizeof(void *)*1);           	// ������������� ��������� � NULL

	// ��������� �����������, ��������� ������, ���� ����������� �� �������, �� �������.
	if (TextureImage[0]=LoadBMP("Data/Crate.bmp"))
	{
		Status=TRUE;									// ������������� ��������� � TRUE

		glGenTextures(3, &texture[0]);					// ������� 3 ��������.

		// ������� �������� � ������� �����������
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// ������� �������� � �������� �����������
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// ������� ������-��������
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])									// ���� �������� ����������
	{
		if (TextureImage[0]->data)							// ���� ���������� ����������� ����������
		{
			free(TextureImage[0]->data);					// ����������� ������ ����������� ��������
		}

		free(TextureImage[0]);								// ����������� ��������� �����������
	}

	return Status;										// ���������� ���������
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// �������� ������� � ������������������� ���� GL
{
	if (height==0)										// ������������� ������� �� 0
	{
		height=1;										// ������������ ������ �������
	}

	glViewport(0,0,width,height);						// ��������� ������� ���� �����������

	glMatrixMode(GL_PROJECTION);						// �������� ������� ��������
	glLoadIdentity();									// ������������� ������� ��������

	// ��������� ����������� ������ ����
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// �������� ������� ������ �����������
	glLoadIdentity();									// ������������� ������� ������ �����������
}

int InitGL(GLvoid)										// ��� ��������� OpenGL ���������� �����
{
	if (!LoadGLTextures())								// ������� � ��������� �������� ��������
	{
		return FALSE;									// ���� �������� �� ��������� ��������� FALSE
	}

	glEnable(GL_TEXTURE_2D);							// ��������� ��������� �������
	glShadeModel(GL_SMOOTH);							// ��������� ������� �������� (smooth shading)
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);				// ������ ������, � ��������� ��� ������ ������. ( �������� ) 
	glClearDepth(1.0f);									// ��������� ������ �������
	glEnable(GL_DEPTH_TEST);							// ��������� �������� �������
	glDepthFunc(GL_LEQUAL);								// ��� ����������� �������� �������
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ������� ��������� �����������

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// ���������� ���� �����
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// ���������� ��������� (������������) ����
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);	// ���������� ��������
	glEnable(GL_LIGHT1);								// �������� �������� ����� #1

	glFogi(GL_FOG_MODE, fogMode[fogfilter]);			// ����� ������
	glFogfv(GL_FOG_COLOR, fogColor);					// ���� ������
	glFogf(GL_FOG_DENSITY, 0.35f);						// ��������� ������ ����� �����
	glHint(GL_FOG_HINT, GL_DONT_CARE);					// ��������������� ��������� ������
	glFogf(GL_FOG_START, 1.0f);							// �������, � ������� ���������� �����
	glFogf(GL_FOG_END, 5.0f);							// �������, ��� ����� �������������.
	glEnable(GL_FOG);									// �������� ����� (GL_FOG)
	return TRUE;										// ������������� ������ OK
}

int DrawGLScene(GLvoid)									// ����� �� ��������� ��� ���������
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// ������� ����� � ����� �������
	glLoadIdentity();									// �������� ��������� ����
	glTranslatef(0.0f,0.0f,z);

	glRotatef(xrot,1.0f,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);

	glBindTexture(GL_TEXTURE_2D, texture[filter]);

	glBegin(GL_QUADS);
		// �������� �����
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// ������ �����
		glNormal3f( 0.0f, 0.0f,-1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// ������� �����
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// ������ �����
		glNormal3f( 0.0f,-1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// ������ �����
		glNormal3f( 1.0f, 0.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// ����� �����
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();

	xrot+=xspeed;
	yrot+=yspeed;
	return TRUE;										// ������������ �������.
}
GLvoid KillGLWindow(GLvoid)								// ������� ������� ���������� ����
{
	if (fullscreen)										// �� � ����� �������� �������?
	{
		ChangeDisplaySettings(NULL,0);					// ���� ��, �� ������������ �� ������� ����
		ShowCursor(TRUE);								// ���������� ������ ����
	}

	if (hRC)											// �������� ����������� ��� ����?
	{
		if (!wglMakeCurrent(NULL,NULL))					// �� ����� ���������� RC � DC ���������?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// �� ����� ������� RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// ������������� RC � NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// �� ����� ����������� �������� DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// ������������� DC � NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// �� ����� ���������� ����?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// ������������� hWnd � NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// ����� ����������������� �����
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// ������������� hInstance � NULL
	}
}

/*	��� ����� ��������� ������� ���� ���� OpenGL.  ���������:							*
 *	title			- ���������, ������������ ������� ����								*
 *	width			- ������ GL ���� ��� �������������� ������							*
 *	height			- ������ GL ���� ��� �������������� ������							*
 *	bits			- ���������� ��� �� ���� (8/16/24/32)								*
 *	fullscreenflag	- ������������� �������������� (TRUE) ��� ��������(FALSE) �������	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// �������� ���������� ������� ������� �����
	WNDCLASS	wc;						// ��������� ������� Windows
	DWORD		dwExStyle;				// ����������� ����� ����
	DWORD		dwStyle;				// ����� ����
	RECT		WindowRect;				// �������� �������� �������� ������ � ������� ������� ����� ��������������
	WindowRect.left=(long)0;			// ������������� �������� ���� (Left) � 0
	WindowRect.right=(long)width;		// ������������� �������� ����� (Right) � ��������� ������ (Width)
	WindowRect.top=(long)0;				// ������������� �������� ���� (Top) � 0
	WindowRect.bottom=(long)height;		// ������������� �������� ��� (Bottom) � ��������� ������ (Height)

	fullscreen=fullscreenflag;			// ������������� ���������� ���� Fullscreen

	hInstance			= GetModuleHandle(NULL);				// ����������� Instance ��� ������ ����
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// �������������� �� �������, � �������� DC ��� ����.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// ��� �������������� ������ ����
	wc.cbWndExtra		= 0;									// ��� �������������� ������ ����
	wc.hInstance		= hInstance;							// ��������� Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// ������� ������ �� ���������
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// ������� ������� �������
	wc.hbrBackground	= NULL;									// ��� ��� GL �� ���������
	wc.lpszMenuName		= NULL;									// ��� �� ����� ����
	wc.lpszClassName	= "OpenGL";								// ��������� ��� ������

	if (!RegisterClass(&wc))									// ���������� ���������������� ����� ����
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// ��������� FALSE
	}
	
	if (fullscreen)												// ���������� �������� �������������� �����?
	{
		DEVMODE dmScreenSettings;								// ����� ����������
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// ��������, ��� ������ �������
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// ������ ��������� devmode
		dmScreenSettings.dmPelsWidth	= width;				// ������� ������ ������
		dmScreenSettings.dmPelsHeight	= height;				// ������� ������ ������
		dmScreenSettings.dmBitsPerPel	= bits;					// ������� ���������� ��� �� �������
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// ���������� ���������� ��������� ����� � �������� ����������.  � �������: CDS_FULLSCREEN ����������� �� ������ �����Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// ���� ������ �� ���������, ��������� ��� �����������. ����� ��� ������������ ������� �����.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// ������ ������� �����.  Fullscreen = FALSE
			}
			else
			{
				// �������� ���������, ��� ���������� ��������� ������.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// ���������� FALSE
			}
		}
	}

	if (fullscreen)												// ��� �� � ������������� ������?
	{
		dwExStyle=WS_EX_APPWINDOW;								// ����������� ����� ����
		dwStyle=WS_POPUP;										// ����� ����
		ShowCursor(FALSE);										// ������ ������ ����
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ����������� ����� ����
		dwStyle=WS_OVERLAPPEDWINDOW;							// ����� ����
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// ���������� ����, ����� ��� ��������������� ���������� �������

	// ������� ����
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// ����������� ����� ��� ����
								"OpenGL",							// ������������ ������
								title,								// ��������� ����
								dwStyle |							// ������������ ����� ����
								WS_CLIPSIBLINGS |					// ��������� ����� ����
								WS_CLIPCHILDREN,					// ��������� ����� ����
								0, 0,								// �������������� ����
								WindowRect.right-WindowRect.left,	// ���������� ������ ����
								WindowRect.bottom-WindowRect.top,	// ���������� ������ ����
								NULL,								// ��� ������������� ����
								NULL,								// ��� ����
								hInstance,							// Instance
								NULL)))								// �� �������� ��������� �� WM_CREATE
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd �������� Windows ����� ��������� �� �����
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// ������ ����������� ������� ��������
		1,											// ����� ������
		PFD_DRAW_TO_WINDOW |						// ������ ������ ������������ ����
		PFD_SUPPORT_OPENGL |						// ������ ������ ������������ OpenGL
		PFD_DOUBLEBUFFER,							// ������ �������������� ������� �����������
		PFD_TYPE_RGBA,								// ������ RGBA �������
		bits,										// ����� ������� �����
		0, 0, 0, 0, 0, 0,							// ���� ����� ������������
		0,											// ��� ����� �����������
		0,											// ��� ������ ������������
		0,											// ��� ������ ����������
		0, 0, 0, 0,									// ���� ���������� ������������
		16,											// 16������ Z-����� (����� �������)  
		0,											// ��� ������ ��������� (stencil buffer)
		0,											// ��� ���������������� ������
		PFD_MAIN_PLANE,								// ������� ��������� ���������
		0,											// ���������������
		0, 0, 0										// ���� ����� ������������
	};
	
	if (!(hDC=GetDC(hWnd)))							// �� �������� �������� ����������?
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Windows ����� ��������������� ������ �������?
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// �� ����� ���������� ������ �������?
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// �� ����� �������� �������� �����������?
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// �������� ������������ �������� �����������
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ������� FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// �������� ����
	SetForegroundWindow(hWnd);						// ������ �������� ���������
	SetFocus(hWnd);									// ������������� ����� ����������� �� ����
	ReSizeGLScene(width, height);					// ������������� ���� GL ���� � ������������

	if (!InitGL())									// �������������� ���� GL ����
	{
		KillGLWindow();								// ������������� �������
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// ��������� FALSE
	}

	return TRUE;									// �������� ���������� ��������������
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// ����� ��� ����� ����
							UINT	uMsg,			// ��������� ��� ����� ����
							WPARAM	wParam,			// �������������� ���������� ���������
							LPARAM	lParam)			// �������������� ���������� ���������
{
	switch (uMsg)									// �������� ��������� ����
	{
		case WM_ACTIVATE:							// ��������� �� ���������� �� ����������� ����
		{
			if (!HIWORD(wParam))					// �������� ��������� ������������
			{
				active=TRUE;						// ��������� �������
			}
			else
			{
				active=FALSE;						// ��������� ������ �� �������
			}

			return 0;								// ���������� � ����� ���������
		}

		case WM_SYSCOMMAND:							// ������������ ��������� �������
		{
			switch (wParam)							// �������� ������ �������
			{
				case SC_SCREENSAVE:					// ��������� ���������� �����������?
				case SC_MONITORPOWER:				// ������� �������� �������������� � ����� ���������� �������?
				return 0;							// �� ������ ����� ���������
			}
			break;									// �����
		}

		case WM_CLOSE:								// �� �������� ��������� � �������� ���������?
		{
			PostQuitMessage(0);						// ������� ��������� � ������
			return 0;								// ���������
		}

		case WM_KEYDOWN:							// ������� ���� ������?
		{
			keys[wParam] = TRUE;					// ���� ��� ��� ������� ��� TRUE
			return 0;								// ���������
		}

		case WM_KEYUP:								// ������� ���� ��������?
		{
			keys[wParam] = FALSE;					// ���� ��� ��� ������� ��� FALSE
			return 0;								// ���������
		}

		case WM_SIZE:								// ���������� ���� OpenGL
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=������, HiWord=������
			return 0;								// ���������
		}
	}

	// ���������� ��� ������ ��������� � DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// ���������� Instance
					LPSTR		lpCmdLine,			// ��������� ��������� ������
					int			nCmdShow)			// �������� ��������� ����
{
	MSG		msg;									// ��������� ��������� ����
	BOOL	done=FALSE;								// ��������� ���������� ������ �� �����

	// �������� ������������ ����� ����� ����������� �� ������������
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// ������� �����
	}

	// �������� ���� ���� OpenGL
	if (!CreateGLWindow("NeHe's Display List Tutorial",640,480,16,fullscreen))
	{
		return 0;									// ������� ���� ���� �� ���� �������
	}

	while(!done)									// ����, ������� ������������ ���� done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// ���� ��������� ���������?
		{
			if (msg.message==WM_QUIT)				// �� �������� ��������� � ������?
			{
				done=TRUE;							// ���� ��� done=TRUE
			}
			else									// ���� ���,���������� �������� � ����������� ����
			{
				TranslateMessage(&msg);				// ��������� ���������
				DispatchMessage(&msg);				// �������� ���������
			}
		}
		else										// ���� ��������� ���
		{
			// ������ �����.  ������� ������� ������ ESC � ��������� � ������ �� DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// �������?  ���� �������� ��������� � ������?
			{
				done=TRUE;							// ESC ��� DrawGLScene ������������ "�����"
			}
			else									// �� ����� ��������, ��������� �����
			{
				SwapBuffers(hDC);					// ����������� ������ (Double Buffering)
				if (keys[VK_LEFT])					// ���� ������ ������� �����?
				{
					yrot-=0.2f;						// ���� ���, �� �������� ���� �����
				}
				if (keys[VK_RIGHT])					// ���� ������ ������� ������?
				{
					yrot+=0.2f;						// ���� ���, �� �������� ���� ������
				}
				if (keys[VK_UP])					// ���� ������ ������� �����?
				{
					xrot-=0.2f;						// ���� ���, �� �������� ���� ����� (� ������ - �����)
				}
				if (keys[VK_DOWN])					// ���� ������ ������� ����?
				{
					xrot+=0.2f;						// ���� ���, �� �������� ���� ����
				}
				if (keys[VK_PRIOR])
				{
					z-=0.02f;
				}
				if (keys[VK_NEXT])
				{
					z+=0.02f;
				}
				if (keys['L'] && !lp)
				{
					lp=TRUE;
					light=!light;
					if (!light)
					{
						glDisable(GL_LIGHTING);
					}
					else
					{
						glEnable(GL_LIGHTING);
					}
				}
				if (!keys['L'])
				{
					lp=FALSE;
				}
				if (keys['F'] && !fp)
				{
					fp=TRUE;
					filter+=1;
					if (filter>2)
					{
						filter=0;
					}
				}
				if (!keys['F'])
				{
					fp=FALSE;
				}

				if (keys['G'] && !gp)
				{
					gp=TRUE;
					fogfilter+=1;								// �������� �� �����
					if (fogfilter>2)							// ��� ��������
					{											// ������ �������������
						fogfilter=0;							// 
					}
					glFogi (GL_FOG_MODE, fogMode[fogfilter]);	// ����� ������
				}
				if (!keys['G'])
				{
					gp=FALSE;
				}
				if (keys[VK_F1])						// ���� ������ ������ F1?
				{
					keys[VK_F1]=FALSE;					// ���� ��� - ��������� �������� FALSE
					KillGLWindow();						// ������� ������� ���� OpenGL	
					fullscreen=!fullscreen;				// ���������� ����� "������ �����"/"�������"
					// ������ �������� ���� ���� OpenGL
					if (!CreateGLWindow("Chris Aliotta & NeHe's Fog Tutorial",640,480,16,fullscreen))
					{
						return 0;						// �����, ���� ���� �� ���� �������
					}
				}
			}
		}
	}

	// ���������� ������ ���������
	KillGLWindow();									// ������� ����
	return (msg.wParam);							// ������ �� ���������
}
