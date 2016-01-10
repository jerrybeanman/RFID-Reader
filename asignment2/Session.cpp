
#include "Session.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Initialize_Window
--
-- DATE: September 28, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: void Initialize_Window (HINSTANCE		hInst,
--									  int			nCmndShow
--									  HANDLE		hwnd,
--								      WNDCLASSEX	wcl)
--				-HINSTANCE hInst:	A handle to the current instance of the application.
--				-int nCmndShow:		Controls how the window is to be shown. In this case it's set to default
--				-HANDLE hwnd:		The handle returned by CreateWindow()
--				-WNDCLASSEX wcl:	The windows class to initilize, register and update
--
-- RETURNS: void.
--
-- NOTES:
--	This function is called on the start of the application to initialize WNDCLASSEX by calling Initialize_WNDCLASSSEX().
--	It is then registered and associated with the corresponding handle for the window.
--	and associate hwnd with it
----------------------------------------------------------------------------------------------------------------------*/
VOID Initialize_Window(HINSTANCE &hInst, int nCmdShow, HWND &hwnd, WNDCLASSEX &wcl)
{
	Initialize_WNDCLASSEX(wcl, hInst);			//Set valuues to the current windows class
	if (!RegisterClassEx(&wcl))					//Register window class 
		MessageBox(NULL, "Error Registering class:", "", MB_OK);
	if (!(hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 10, 10,
		600, 400, NULL, NULL, hInst, NULL)))	//Create an overlapped window
		MessageBox(NULL, "Error Creating window:", "", MB_OK);
	ShowWindow(hwnd, nCmdShow);					//Set the window show state
	UpdateWindow(hwnd);							//Display the window graphically
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Initialize_WNDCLASSEX
--
-- DATE: September 28, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: void Initialize_WNDCLASSEX (WNDCLASSEX	wcl,
--										  HINSTANCE		hInst);
--					-WNDCLASSEX wcl:	The structure that contains the windows class information to initialize
--					-HINSTANCE hInst:	The handle to the current instance of the application
--
-- RETURNS: VOID.
--
-- NOTES:
--	Initializes all members of a WNDCLASSEX to some default values
----------------------------------------------------------------------------------------------------------------------*/
VOID Initialize_WNDCLASSEX(WNDCLASSEX &wcl, HINSTANCE &hInst)
{
	wcl.cbSize = sizeof(WNDCLASSEX);
	wcl.style = CS_HREDRAW | CS_VREDRAW;
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// large icon 
	wcl.hIconSm = NULL;								// use small version of large icon
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// cursor style

	wcl.lpfnWndProc = WndProc;
	wcl.hInstance = hInst;
	wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //white background
	wcl.lpszClassName = Name;

	wcl.lpszMenuName = "MYMENU"; // The menu Class
	wcl.cbClsExtra = 0;		// no extra memory needed
	wcl.cbWndExtra = 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Display_Help
--
-- DATE: October 18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: void Display_Help ()
--
-- RETURNS: VOID.
--
-- NOTES:
--	Display help message box containing the information about the functionality of the program. The content is parsed from
--	a text file(Help.txt) using ifstream
----------------------------------------------------------------------------------------------------------------------*/
VOID Display_Help()
{
	std::ifstream iF("Help.txt");						//Open file for reading
	std::string s((std::istreambuf_iterator<char>(iF)),	//Store file content in a string
		std::istreambuf_iterator<char>());
	MessageBox(NULL, s.c_str(), "Help", MB_OK);			//Display help message box with the file content
	iF.close();											//Close file
}






