#ifndef PHYSICAL_H
#define PHYSICAL_H
#include "Resources.h"

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
BOOL Connect();

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
BOOL ConnectReader();

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
DWORD WINAPI read(LPVOID lpVoid);

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
unsigned char readTag(LPSKYETEK_TAG tag, void *user);

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
BOOL Disconnect();
#endif