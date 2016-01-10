#include "Physical.h"

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			Connect
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			Jaegar Sarauer, October 18th, 2015
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			BOOL Connect()
--
-- RETURNS:				bool - Whether or not the connection was successful.
--
-- NOTES:				This function will check to see if the reader and device is connected. If it isn't (determined
--						by the isReaderSet boolean), ConnectReader() will be called. If the attempt was successful,
--						the isReaderSet boolean will be set to true, and the thread for reading will be started.
--						port.connected will be set to true on a successful thread creation.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Connect()
{
	if (!isReaderSet) {
		if (!ConnectReader()) {
			MessageBox(NULL, "Reader not found, unable to establish connection.", "Error", MB_OK);
			return FALSE;
		}
		else {
			isReaderSet = true;
		}
	}
	//create thread for reading
	if ((rThread = CreateThread(NULL, 0, read, NULL, 0, NULL)
		) == NULL)
	{
		MessageBox(NULL, "Error creating read thread", "Error", MB_OK);
		return FALSE;
	}
	//set connection to true
	port.connected = TRUE;
	MessageBox(NULL, "Successfully connected.", "Success", MB_OK);
	return TRUE;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			ConnectReader
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			Jaegar Sarauer, October 18th, 2015
--							- Moved code to a new method to allow establishing outside of reconnecting.
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			BOOL ConnectReader()
--
-- RETURNS:				bool - Whether or not the reader and device connection was successful.
--
-- NOTES:				This function will attempt to open the device port to allow incomming connections from the 
--						computer's ports. It will also attempt to find an RFID reader to reference when the connection
--						thread will be established for reading.
--						On success for both device and reader, isReaderSet will be set to true and the function will
--						return true.
----------------------------------------------------------------------------------------------------------------------*/
BOOL ConnectReader() {
	//check if device is connected
	if ((port.DevicesCount = SkyeTek_DiscoverDevices(&port.lpDevice)) == 0)
	{
		MessageBox(NULL, "Device not found.", "Error", MB_OK);
		return FALSE;
	}
	//check if reader is connnected
	if ((port.ReadersCount = SkyeTek_DiscoverReaders(port.lpDevice, port.DevicesCount, &port.lpReader)) == 0)
	{
		MessageBox(NULL, "Reader not found.", "Error", MB_OK);
		return FALSE;
	}
	isReaderSet = true;
	return TRUE;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			read
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			NONE
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			DWORD WINAPI read(LPVOID lpVoid)
--
-- RETURNS:				DWORD - No significant use.
--
-- NOTES:				This function will attempt to read a tag from the open port. The SkyeTek_SelectTags runs on a
--						loop, awaiting input from the RFID reader when a tag has been read. The readTag() function
--						is called when a tag has been read.
----------------------------------------------------------------------------------------------------------------------*/
DWORD WINAPI read(LPVOID lpVoid)
{
	SKYETEK_STATUS status = SkyeTek_SelectTags(				// Excercises the reader in select mode
									port.lpReader[0],		// Reader to execute the command on
									AUTO_DETECT,			// Auto detect any tag type
									readTag,				// Action to take when a tag is detected
									0,						// Should not run in inventory/anti-collision mode
									1,						// Keep looping as long as readTag returns 1
									NULL);					// No extra parameter to pass in readTag
	if(status != SKYETEK_SUCCESS) // Check for reader malfunction
		MessageBox(NULL, "Error reading tag.", "error", MB_OK);
	return 0;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			readTag
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			Ruoqi Jia
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			unsigned char readTag(LPSKYETEK_TAG tag, void *user) 
--								-LPSKYETEK_TAG tag : Long pointer to the tag structure scanned by the RFID reader
--								-void *user		   : No signficant use
-- RETURNS:				1 to keep looping, 0 to stop
--
-- NOTES:				Processes tag values scanned by the RFID reader, if the tag is initialized to some values (detected),
--						add it to the list view on screen by calling AddTag.
----------------------------------------------------------------------------------------------------------------------*/
unsigned char readTag(LPSKYETEK_TAG tag, void *user) 
{
	if (tag != NULL)
		AddTag(tag);
	return port.connected;
}


/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:			Disconnect
--
-- DATE:				October 18th, 2015
--
-- REVISIONS:			Jaegar Sarauer, October 18th, 2015
--							- Removed reader and device closing to allow disconnects and reconnects. 
--							- Fixed crashing on disconnects and reconnects.
--
-- DESIGNER:			Ruoqi Jia
--
-- PROGRAMMER:			Ruoqi Jia
--
-- INTERFACE:			BOOL Disconnect()
--
-- RETURNS:				bool - Returns true at the end of the function. No real use.
--
-- NOTES:				This function will tell the global port's connected boolean to set to false, allowing the
--						read thread to close due to being notified reading is now off.
--						Alerts the user that the connection has been disconnected.
----------------------------------------------------------------------------------------------------------------------*/
BOOL Disconnect()
{
	port.connected = FALSE;
	Sleep(1000);
	SkyeTek_FreeDevices(port.lpDevice, port.DevicesCount);
	isReaderSet = false;
	MessageBox(NULL, "Disconnected", "Success", MB_OK);
	return TRUE;
}