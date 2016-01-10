#ifndef RESOURCES_H
#define RESOURCES_H
#define MAX 502
#include <fstream>
#include <windows.h> 
#include <sstream>
#include <commctrl.h>   
#include "stdafx.h"
#include "SkyeTekAPI.h"
#include "SkyeTekProtocol.h"
#include "Application.h"
#include "Session.h"
#include "Physical.h"
#include "menu.h"
struct RFID_Port						// Stores information in the communication port of the RFID reader
{
	DWORD DevicesCount = 0;				// Number of availiable  devices discovered on the system
	DWORD ReadersCount = 0;				// Number of availiable readers discovered on the device
	BOOL connected = false;				// Current connection status of the port
	LPSKYETEK_DEVICE *lpDevice = NULL;	// Long pointer to the actual device
	LPSKYETEK_READER *lpReader = NULL;	// Long pointer to the RFID reader
};
const	 char		Name[] = "RFID Reader";	// Name of the program
static	 HANDLE		rThread;				// Handle to the read thread
static   RFID_Port  port;					// Communication port to the RFID reader
static	 HINSTANCE	hInst;					// HINSTANCE to instantiate the main and listview window on
static	 HWND		hWndListView;			// Window handle to the list view 
static	 bool		isReaderSet = false;	// Current status of the reader
static	 LV_COLUMN	lvC;					// List View Column structure
static	 LV_ITEM	lvI;					// List view item structure
#endif
