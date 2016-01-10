/*------------------------------------------------------------------------------------------------------------------
-- SOURCE FILE: Application.cpp - Main application for the program
--
-- PROGRAM: Dumb terminal emulator
--
-- FUNCTIONS:
--	int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance,
--
--
--
-- DATE: October 10/18, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- NOTES:
--	This application contains the WinMain, which acts as the main application for the RFID reader program.
--	The program's main objective is to perform read operation asynchrounously on a SkyTek RFID reader.
--	Additionally, a help menu will be availiable alongside with the user manual.
--
--  Note: All functionalities for the program is throughly outlined in Physical.h/cpp and Session.h/cpp
----------------------------------------------------------------------------------------------------------------------*/
#include "Application.h"
//testing
#include<string.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance,
	LPSTR lspszCmdParam, int nCmdShow)
{
	hInst = hInstance;
	HWND hwnd;
	WNDCLASSEX wcl;
	MSG Msg;
	Initialize_Window(hInstance, nCmdShow, hwnd, wcl);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: WndProc
--
-- DATE: September 28, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: LRESULT CALLBACK WndProc(HWND		hwnd,
--									   UINT		Message,
--									   WPARAM	wParam,
--									   LPARAM	lParam);
--					-HWND hwnd:		Handle to the current window
--					-UINT Message:	Message retrieved from WinMain
--					-WPARAM wParam:	Additional message information
--					-LPARAM lParam:	Additional message information
--
-- RETURNS: The return value is the result of the message processing and depends on the message sent.
--
-- NOTES:
--	Processes messages sent to a window from WinMain
----------------------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message,
	WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_CREATE:
		if ((hWndListView = CreateListView(hwnd)) == NULL)	// Creates the listview window
			MessageBox(NULL, "Listview not created!", NULL, MB_OK);
		break;
	case WM_COMMAND:
		Handle_Menu_Commands(hwnd, wParam);	//Handles menuitem commands
		break;
	case WM_CHAR:
		SendMessage(hWndListView, LVM_DELETEALLITEMS, 0, 0);
		break;
	case WM_SIZE:
		MoveWindow(hWndListView, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		break;
	case WM_DESTROY:						// Terminate program
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			CreateListView
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			NONE
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			HWND CreateListView(HWND hWndParent);
--								HWND hWndParent - The parent handle which the listview will be instantiated to.
--
-- RETURNS:				HWND - The handle of the created list view.
--
-- NOTES:				This function creates a list view, including building the columns and establishing the window
--						and variables needed to allow list items to be ready to be added to it.
----------------------------------------------------------------------------------------------------------------------*/
HWND CreateListView(HWND hWndParent)
{
	RECT rcl;							// Rectangle for setting the size of the window
	int index;							// Index used in for loops
	char szText[MAX_PATH];				// Place to store some text
	int iSubItem;						// Index for inserting sub items

	InitCommonControls();				// Ensure that the common control DLL is loaded.

										
	GetClientRect(hWndParent, &rcl);	// Get the size and position of the parent window


	hWndListView = CreateWindowEx(0L,		// Create the list view window that starts out in report view
		WC_LISTVIEW,		                // list view class
		"",							        // no default text
		WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | WS_EX_CLIENTEDGE,
		0, 0,
		rcl.right - rcl.left, rcl.bottom - rcl.top,
		hWndParent,
		(HMENU)1000,
		hInst,
		NULL);

	if (hWndListView == NULL)				// Check if list view is created successfully
		return NULL;

	// Initialize the LV_COLUMN structure
	memset(&lvC, 0, sizeof(lvC));									// Zero Members
	lvC.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;				// Type of mask
	lvC.cx = 0x28;													// width between each coloum
	lvC.pszText = "Tag#";											// First Header Text
	lvC.cx = 0x42;													// width of column
	SendMessage(hWndListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
	SendMessage(hWndListView, LVM_INSERTCOLUMN, 0, (LPARAM)&lvC);	
	lvC.pszText = "Tag ID";											
	lvC.cx = 0x100;													
	SendMessage(hWndListView, LVM_INSERTCOLUMN, 1, (LPARAM)&lvC);	
	lvC.pszText = "Tag Type";
		lvC.cx = 0x100;	//
	SendMessage(hWndListView, LVM_INSERTCOLUMN, 2, (LPARAM)&lvC);

	memset(&lvI, 0, sizeof(lvI));	// Zero struct's Members
	lvI.mask = LVIF_TEXT;			// Text Style
	lvI.cchTextMax = 256;			// Max size of test
	lvI.iItem = 0;					// choose item  
	return (hWndListView);
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			AddTag
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			Jaegar Sarauer, October 18th, 2015
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			VOID AddTag(LPSKYETEK_TAG tag)
--								LPSKYETEK_TAG tag - A pointer to the tag which was read from the RFID reader.
--
-- RETURNS:				VOID
--
-- NOTES:				This function extracts information from the tag passed in from the RFID reader (including id
--						and type). After extracting the data, it will test to see if the id already exists in another
--						list item on the list view.
--						If the item does not exist, a new list item will be added to the list.
--						The values used in creating the list are:
--							- The list index (to keep track of the amount and position of each list item).
--							- The tag id (the value to of the tag).
--							- The tag type (what type the tag is).
----------------------------------------------------------------------------------------------------------------------*/
VOID AddTag(LPSKYETEK_TAG tag)
{
	std::stringstream iss_id;
	std::stringstream iss_type;
	int itemIndex;
	char iItemText[100] = "";
	char iSubItemText[100] = "";
	TCHAR* tagType = SkyeTek_GetTagTypeNameFromType(tag->type);	// Get tag type

	for (int i = 0; i < sizeof(tag->friendly); i++)		// Store tag name into istringstream
		iss_id << (tag->friendly + i);
	for (int i = 0; i < (sizeof(tagType) * 16); i++)	// Store tag type into isringstream 
		iss_type << tagType + i;
	itemIndex = SendMessage(hWndListView, LVM_GETITEMCOUNT, 0, 0);   // number of items
	sprintf_s(iItemText, "%d", itemIndex);							 // Convert tag number to string	
	memset(&lvI, 0, sizeof(lvI));									 // Zero struct's Members
	lvI.mask = LVIF_TEXT;											 // Text Style
	lvI.cchTextMax = 256;											 // Max size of test
	lvI.iItem = 0;													 // choose item  
	lvI.iSubItem = 0;												 // Put in first coluom
	lvI.pszText = iItemText;										 // Text to display (can be from a char variable) (Items)
	SendMessage(hWndListView, LVM_INSERTITEM, 0, (LPARAM)&lvI);		 // Send info to the Listview

	lvI.iSubItem = 1;
	sprintf_s(iItemText, "%s", iss_id.str().c_str());
	lvI.pszText = iItemText;
	SendMessage(hWndListView, LVM_SETITEM, 0, (LPARAM)&lvI);	// Enter text to SubItems

	SendMessage(hWndListView, LVM_INSERTITEM, 0, (LPARAM)&lvI); // Send info to the Listview
	lvI.iSubItem = 2;
	sprintf_s(iItemText, "%s", iss_type.str().c_str());
	lvI.pszText = iItemText;
	SendMessage(hWndListView, LVM_SETITEM, 0, (LPARAM)&lvI);	// Enter text to SubItems

	//SendMessage(hWndListView, LVM_SETBKCOLOR, 0, (LPARAM)RGB(0x80, 0x80, 0x80));

}



/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			findTag
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			NONE
--
-- DESIGNER:			Jaegar Sarauer
--
-- PROGRAMMER:			Jaegar Sarauer
--
-- INTERFACE:			int findTag(const char* name)
--								const char* name - The ID of the tag to compare to the list.
--
-- RETURNS:				int - index of where the list item specified by the name parameter is found. If there was
--						no list item found, -1 will be returned.
--
-- NOTES:				This function iterates through the listview, searching for a match for the 2nd column. If
--						the char* name parameter matches any name in the 2nd column, the index of that list item will
--						be returned, else it will return -1.
----------------------------------------------------------------------------------------------------------------------*/
int findTag(const char* name) {
	lvI.iSubItem = 1;
	for (size_t i = 0; i < SendMessage(hWndListView, LVM_GETITEMCOUNT, 0, 0); i++) {
		lvI.iItem = i;
		ListView_GetItem(hWndListView, &lvI);
		if (strcmp(name, lvI.pszText) == 0)
			return i;
	}
	return -1;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: Handle_Menu_Commands
--
-- DATE: October 4, 2015
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER: Ruoqi Jia
--
-- PROGRAMMER: Ruoqi Jia
--
-- INTERFACE: VOID Handle_Menu_Commands(HWND hwnd, WPARAM wParam);
--					-HWND	hwnd:	Handle to the current window
--					-WPARAM wParam: Contains information of the current message
-- RETURNS: VOID
--
-- NOTES:
--	Handle and process all menu items that are being triggered in the program.
----------------------------------------------------------------------------------------------------------------------*/
VOID Handle_Menu_Commands(HWND hwnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case IDM_CONNECT:
		Connect();		// Connect to the device and reader
		break;
	case IDM_DISCONNECT:
		Disconnect();	// Disconnect from the device and reader
		break;
	case IDM_HELP:
		Display_Help();	// Display help message box 
		break;
	case IDM_CLEAR:
		SendMessage(hWndListView, LVM_DELETEALLITEMS, 0, 0);
		break;
	default:
		break;
	}
}