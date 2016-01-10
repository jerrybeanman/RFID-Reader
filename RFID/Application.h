#ifndef APPLICATION_H
#define APPLICATION_H
#include "Resources.h"
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
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

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
HWND CreateListView(HWND hWndParent);

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
VOID AddTag(LPSKYETEK_TAG tag);

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
int findTag(const char* name);

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
VOID Handle_Menu_Commands(HWND hwnd, WPARAM wParam);
#endif