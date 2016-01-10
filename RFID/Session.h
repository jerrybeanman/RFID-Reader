#ifndef SESSION_H
#define SESSION_H
#include "Resources.h"
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
VOID Initialize_Window(HINSTANCE &hInst, int nCmdShow, HWND &hwnd, WNDCLASSEX &wcl);

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
VOID Initialize_WNDCLASSEX(WNDCLASSEX &wcl, HINSTANCE &hInst);

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Display_Help
--
-- DATE: September 28, 2015
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
--	Display help message box containing the information about the functionality of the program
----------------------------------------------------------------------------------------------------------------------*/
VOID Display_Help();



#endif