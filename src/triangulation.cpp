#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "Trian.h"
// Includes for OpenGL
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

// Variables for the Code
FILE *fp, *logfile;
double x, y, z, minx=0.0, miny=0.0, maxx=0.0, maxy=0.0;
int i, j, k;
vertex *p, *sa, *sb, *sc;
vertex_list *vl;
triangle *tri, *st;
triangle_list *tl;
edge *q;
edge_list *el;
char string[101], title[101];
// End of Variables

HDC			hDC=NULL;														// Private GDI Device Context
HGLRC		hRC=NULL;														// Permanent Rendering Context
HWND		hWnd=NULL;													// Holds Our Window Handle
HINSTANCE	hInstance;												// Holds The Instance Of The Application		

bool	keys[256];														// Array Used For The Keyboard Routine
bool	active=TRUE;													// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;											// Fullscreen Flag Set To Fullscreen Mode By Default
bool	light;																// Lighting ON/OFF ( NEW )
bool	lpr;																	// L Pressed? ( NEW )
bool	fpr;																	// F Pressed? ( NEW )

GLfloat	xrot;																// X Rotation
GLfloat	yrot;																// Y Rotation
GLfloat	z_d=-5.0f;													// Depth Into The Screen

GLfloat LightAmbient[]=		{ 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=		{ 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]=	{ 0.0f, 0.0f, 2.0f, 1.0f };

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);				// Declaration For WndProc



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)	{				// Resize And Initialize The GL Window
	if (height==0) height=1;																	// Prevent A Divide By Zero
	glViewport(0,0,width,height);															// Reset The Current Viewport
	glMatrixMode(GL_PROJECTION);															// Select The Projection Matrix
	glLoadIdentity();																					// Reset The Projection Matrix
// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);																// Select The Modelview Matrix
	glLoadIdentity();																					// Reset The Modelview Matrix
}

int InitGL(GLvoid) {																	// All Setup For OpenGL Goes Here
	glShadeModel(GL_SMOOTH);														// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);								// Black Background
	glClearDepth(1.0f);																	// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);														// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);															// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);			// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);			// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);		// Position The Light
	glEnable(GL_LIGHT1);																// Enable Light One
	return TRUE;																				// Initialization Went OK
}

int DrawGLScene(GLvoid)	{															// Here's Where We Do All The Drawing
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();																		// Reset The Current Modelview Matrix
	glTranslatef(0.0f,0.0f,z_d-2.0f);									
	glRotatef(xrot,1.0,0.0f,0.0f);
	glRotatef(yrot,0.0f,1.0f,0.0f);	
	glBegin(GL_TRIANGLES);
		for(j=0;j<tl->length();j++) {
			glColor3f(0.0f,0.0f,1.0f);
			glNormal3f((GLfloat)((tl->get(j)->v1->y-tl->get(j)->v2->y)*(tl->get(j)->v3->z-tl->get(j)->v2->z)-
				         (tl->get(j)->v3->y-tl->get(j)->v2->y)*(tl->get(j)->v1->z-tl->get(j)->v2->z)),
								 (GLfloat)(-(tl->get(j)->v1->z-tl->get(j)->v2->z)*(tl->get(j)->v3->x-tl->get(j)->v2->x)+
				         (tl->get(j)->v3->z-tl->get(j)->v2->z)*(tl->get(j)->v1->x-tl->get(j)->v2->x)),
								 (GLfloat)((tl->get(j)->v1->x-tl->get(j)->v2->x)*(tl->get(j)->v3->y-tl->get(j)->v2->y)-
				         (tl->get(j)->v3->x-tl->get(j)->v2->x)*(tl->get(j)->v1->y-tl->get(j)->v2->y)));
// To Normal tou trigonou einai to e3oteriko ginomeno ton (v1-v2) kai (v3-v2)
			glVertex3d(tl->get(j)->v1->x,tl->get(j)->v1->y,tl->get(j)->v1->z);
		  glColor3f(0.0f,1.0f,0.0f);
			glVertex3d(tl->get(j)->v2->x,tl->get(j)->v2->y,tl->get(j)->v2->z);
		  glColor3f(1.0f,0.0f,0.0f);
			glVertex3d(tl->get(j)->v3->x,tl->get(j)->v3->y,tl->get(j)->v3->z);
    }
	glEnd();
	return TRUE;																				// Keep Going
}

GLvoid KillGLWindow(GLvoid) {											// Properly Kill The Window
	if (fullscreen) {																// Are We In Fullscreen Mode?
		ChangeDisplaySettings(NULL,0);								// If So Switch Back To The Desktop
		ShowCursor(TRUE);															// Show Mouse Pointer
	}
	if (hRC) {																			// Do We Have A Rendering Context?
		if (!wglMakeCurrent(NULL,NULL)) {							// Are We Able To Release The DC And RC Contexts?
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))	{									// Are We Able To Delete The RC?
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;																			// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC)) {							// Are We Able To Release The DC
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;																			// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd)) {							// Are We Able To Destroy The Window?
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;																		// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance)) {			// Are We Able To Unregister Class
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;																// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				  *
 *	width			- Width Of The GL Window Or Fullscreen Mode			  	*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag) {
	GLuint		PixelFormat;														// Holds The Results After Searching For A Match
	WNDCLASS	wc;																			// Windows Class Structure
	DWORD		dwExStyle;																// Window Extended Style
	DWORD		dwStyle;																	// Window Style
	RECT		WindowRect;																// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;													// Set Left Value To 0
	WindowRect.right=(long)width;											// Set Right Value To Requested Width
	WindowRect.top=(long)0;														// Set Top Value To 0
	WindowRect.bottom=(long)height;										// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;												// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);						// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;						// WndProc Handles Messages
	wc.cbClsExtra		= 0;															// No Extra Window Data
	wc.cbWndExtra		= 0;															// No Extra Window Data
	wc.hInstance		= hInstance;											// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);		// Load The Arrow Pointer
	wc.hbrBackground	= NULL;													// No Background Required For GL
	wc.lpszMenuName		= NULL;													// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";											// Set The Class Name

	if (!RegisterClass(&wc)) {												// Attempt To Register The Window Class
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}
	
	if (fullscreen) {																	// Attempt Fullscreen Mode?
		DEVMODE dmScreenSettings;												// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);			// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;					// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;					// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;						// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL) {
// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES) {
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			} else {
// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;																// Return FALSE
			}
		}
	}

	if (fullscreen) {																	// Are We Still In Fullscreen Mode?
		dwExStyle=WS_EX_APPWINDOW;											// Window Extended Style
		dwStyle=WS_POPUP;																// Windows Style
		ShowCursor(FALSE);															// Hide Mouse Pointer
	}	else {
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;		// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;										// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,						// Extended Style For The Window
								"OpenGL",														// Class Name
								title,															// Window Title
								dwStyle |														// Defined Window Style
								WS_CLIPSIBLINGS |										// Required Window Style
								WS_CLIPCHILDREN,										// Required Window Style
								0, 0,																// Window Position
								WindowRect.right-WindowRect.left,		// Calculate Window Width
								WindowRect.bottom-WindowRect.top,		// Calculate Window Height
								NULL,																// No Parent Window
								NULL,																// No Menu
								hInstance,													// Instance
								NULL)))															// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=								// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																							// Version Number
		PFD_DRAW_TO_WINDOW |														// Format Must Support Window
		PFD_SUPPORT_OPENGL |														// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,																// Must Support Double Buffering
		PFD_TYPE_RGBA,																	// Request An RGBA Format
		bits,																						// Select Our Color Depth
		0, 0, 0, 0, 0, 0,																// Color Bits Ignored
		0,																							// No Alpha Buffer
		0,																							// Shift Bit Ignored
		0,																							// No Accumulation Buffer
		0, 0, 0, 0,																			// Accumulation Bits Ignored
		16,																							// 16Bit Z-Buffer (Depth Buffer)  
		0,																							// No Stencil Buffer
		0,																							// No Auxiliary Buffer
		PFD_MAIN_PLANE,																	// Main Drawing Layer
		0,																							// Reserved
		0, 0, 0																					// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd))) {													// Did We Get A Device Context?
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd))) {	// Did Windows Find A Matching Pixel Format?
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd)) {				// Are We Able To Set The Pixel Format?
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC))) {								// Are We Able To Get A Rendering Context?
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC)) {										// Try To Activate The Rendering Context
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);													// Show The Window
	SetForegroundWindow(hWnd);												// Slightly Higher Priority
	SetFocus(hWnd);																		// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);											// Set Up Our Perspective GL Screen

	if (!InitGL()) {																	// Initialize Our Newly Created GL Window
		KillGLWindow();																	// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;																		// Return FALSE
	}

	return TRUE;																			// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,								// Handle For This Window
							UINT	uMsg,														// Message For This Window
							WPARAM	wParam,												// Additional Message Information
							LPARAM	lParam) {											// Additional Message Information
	switch (uMsg) {																		// Check For Windows Messages
		case WM_ACTIVATE: {															// Watch For Window Activate Message
			if (!HIWORD(wParam)) active=TRUE; else active=FALSE;					// Check Minimization State	 // Program Is Active  // Program Is No Longer Active
			return 0;																			// Return To The Message Loop
		}
		case WM_SYSCOMMAND: {														// Intercept System Commands
			switch (wParam) {															// Check System Calls
				case SC_SCREENSAVE:													// Screensaver Trying To Start?
				case SC_MONITORPOWER:												// Monitor Trying To Enter Powersave?
				return 0;																		// Prevent From Happening
			}
			break;																				// Exit
		}
		case WM_CLOSE: {																// Did We Receive A Close Message?
			PostQuitMessage(0);														// Send A Quit Message
			return 0;																			// Jump Back
		}
		case WM_KEYDOWN: {															// Is A Key Being Held Down?
			keys[wParam] = TRUE;													// If So, Mark It As TRUE
			return 0;																			// Jump Back
		}
		case WM_KEYUP: {																// Has A Key Been Released?
			keys[wParam] = FALSE;													// If So, Mark It As FALSE
			return 0;																			// Jump Back
		}

		case WM_SIZE: {																	// Resize The OpenGL Window
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam)); // LoWord=Width, HiWord=Height
			return 0;																			// Jump Back
		}
	}

// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,										// Instance
					HINSTANCE	hPrevInstance,													// Previous Instance
					LPSTR		lpCmdLine,																// Command Line Parameters
					int			nCmdShow)																	// Window Show State
{
	MSG		msg;																								// Windows Message Structure
	BOOL	done=FALSE;																					// Bool Variable To Exit Loop

// * * * * * * * * * * * * * * * * * * * * * * * *
// * Code for creating the triangles in the list *
// * * * * * * * * * * * * * * * * * * * * * * * * 
	fp=fopen("vertices.txt", "r");									// Anoigma input arxeiou "vetrices.txt"
	logfile=fopen("log.txt", "w");									// Anoigma feedback arxeiou "logfile.txt"
	vl=new vertex_list();														// Arxikopoiisi listas simeion
	tl=new triangle_list();													// Arxikopoiisi listas trigonon
	el=new edge_list();															// Arxikopoiisi listas akmon

	while(!feof(fp)) {
		fscanf(fp, "%lf ", &x);												// Diavasma arxeiou sintetagmenon
		fscanf(fp, "%lf ", &y);
		fscanf(fp, "%lf\n", &z);
		fprintf(logfile, "%f %f %f\n", x, y, z);
		if(x<minx) minx=x;														// Elegxos min x,max x
		else if(x>maxx) maxx=x;
		if(y<miny) miny=y;														// Elegxos min y,max y
		else if(y>maxy) maxy=y;
		p=new vertex(x, y, z);												// Ylopoiisi enos simeiou
		vl->add(p);																		// kai pros8esi stin lista
	}
	fclose(fp);

	sa=new vertex(minx-1.0, miny-1.0, 0.0);					// min, max coordinations -> se simeia
	sb=new vertex(minx-1.0, 2*maxy+1.0, 0.0);
	sc=new vertex(2*maxx+1.0, miny-1.0, 0.0);
	st=new triangle(sa, sb, sc);										// Kataskeyi "Super Triangle"
	tl->add(st);																		// kai pros8esi stin triangle_list

// Triangulation...
	for(i=0; i<vl->length(); i++) {
		p=vl->get(i);
		fprintf(logfile, "Checking new vertex: %lf, %lf, %lf\n", p->x, p->y, p->z);
		for(j=0; j<tl->length(); j++) {
			tri=tl->get(j);
			if (((tri->cx-p->x)*(tri->cx-p->x)+(tri->cy-p->y)*(tri->cy-p->y))<=tl->get(j)->r2) {
				tri=tl->remove(j--);
				q=new edge(tri->v1, tri->v2);
				fprintf(logfile, "Adding new edge: (%lf, %lf)-(%lf, %lf)\n", q->v1->x, q->v1->y, q->v2->x, q->v2->y);
				el->add(q);
				q=new edge(tri->v2, tri->v3);
				fprintf(logfile, "Adding new edge: (%lf, %lf)-(%lf, %lf)\n", q->v1->x, q->v1->y, q->v2->x, q->v2->y);
				el->add(q);
				q=new edge(tri->v3, tri->v1);
				fprintf(logfile, "Adding new edge: (%lf, %lf)-(%lf, %lf)\n", q->v1->x, q->v1->y, q->v2->x, q->v2->y);
				el->add(q);
			}

		}
// Rem double edges..
		for(j=0; j<el->length(); j++) {
			q=el->get(j);
			for(k=j+1; k<el->length(); k++) {
				if ((el->get(k)->v1==q->v1 && el->get(k)->v2==q->v2) 
				 || (el->get(k)->v2==q->v1 && el->get(k)->v1==q->v2)) {
					fprintf(logfile, "Removing double edge: (%lf, %lf)-(%lf, %lf)\n", q->v1->x, q->v1->y, q->v2->x, q->v2->y);
					el->remove(k);
					el->remove(j--);
				}
			}
		}
// Build new triangles..
		for(j=0; j<el->length(); j++) {
			q=el->remove(j--);
			tri=new triangle(q->v1, q->v2, p);
			fprintf(logfile, "%d New triangle: [%lf, %lf]-[%lf, %lf]-[%lf, %lf]\n", el->length(), tri->v1->x, tri->v1->y, tri->v2->x, tri->v2->y, tri->v3->x, tri->v3->y);
			tl->add(tri);
		}
	}

// Kill the supertriangle!
	for(i=0;i<tl->length();i++) {
		if(sa==tl->get(i)->v1 ||
			 sa==tl->get(i)->v2 ||
			 sa==tl->get(i)->v3 ||
			 sb==tl->get(i)->v1 ||
			 sb==tl->get(i)->v2 ||
			 sb==tl->get(i)->v3 ||
			 sc==tl->get(i)->v1 ||
			 sc==tl->get(i)->v2 ||
			 sc==tl->get(i)->v3) tl->remove(i--);
	}
// Drawing to the Log file (log.txt)
	fprintf(logfile, "\nThe triangles are:  [ v1(x,y,z) v2(x,y,z) v3(x,y,z) ]\n");
	for(j=0;j<tl->length();j++) {
		tri=tl->get(j);
		fprintf(logfile, "Triangle %d [%lf, %lf, %lf]-[%lf, %lf, %lf]-[%lf, %lf, %lf]\n", j, tri->v1->x, tri->v1->y, tri->v1->z, tri->v2->x, tri->v2->y, tri->v2->z, tri->v3->x, tri->v3->y, tri->v3->z);
	}
	fclose(logfile);

// * * * * * * * 	
// End of Code *
// * * * * * * *

// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO) {
		fullscreen=FALSE;																				// Windowed Mode
	}

// Create Our OpenGL Window
	if (!CreateGLWindow("Mesh surface written by me..",640,480,16,fullscreen)) {
		return 0;																								// Quit If Window Was Not Created
	}

	while(!done) {																						// Loop That Runs While done=FALSE
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)) {							// Is There A Message Waiting?
			if (msg.message==WM_QUIT) {														// Have We Received A Quit Message?
				done=TRUE;																					// If So done=TRUE
			} else {																							// If Not, Deal With Window Messages
				TranslateMessage(&msg);															// Translate The Message
				DispatchMessage(&msg);															// Dispatch The Message
			}
		} else {																								// If There Are No Messages
// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE]) done=TRUE; 
			else {
				SwapBuffers(hDC);
				if (keys['L'] && !lpr) {
					lpr=TRUE;
					light=!light;
					if (!light)	glDisable(GL_LIGHTING);	else glEnable(GL_LIGHTING);
				}
				if (!keys['L']) lpr=FALSE;
				if (!keys['F']) fpr=FALSE;
				if (keys[VK_PRIOR])	z_d-=0.2f;
				if (keys[VK_NEXT]) z_d+=0.2f;
				if (keys[VK_UP]) xrot-=0.5f;
				if (keys[VK_DOWN]) xrot+=0.5f;
				if (keys[VK_RIGHT])	yrot+=0.5f;
				if (keys[VK_LEFT]) yrot-=0.5f;
				
			}
			// Active?  Was There A Quit Received?
			// ESC or DrawGLScene Signalled A Quit
			// Not Time To Quit, Update Screen
			// Swap Buffers (Double Buffering)
			
			if (keys[VK_F1]) {																		// Is F1 Being Pressed?
				keys[VK_F1]=FALSE;																	// If So Make Key FALSE
				KillGLWindow();																			// Kill Our Current Window
				fullscreen=!fullscreen;															// Toggle Fullscreen / Windowed Mode
// Recreate Our OpenGL Window
				if (!CreateGLWindow("Mesh surface written by me..",640,480,16,fullscreen)) {
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

// Shutdown
	KillGLWindow();																						// Kill The Window
	return (msg.wParam);																			// Exit The Program
}
