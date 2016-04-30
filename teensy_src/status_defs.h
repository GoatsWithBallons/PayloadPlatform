/****************************************************************************************
 *
 * File:
 * 		status_def.h
 *
 * Purpose:
 * 		Contains a number of defines for module status reporting.
 *
 ***************************************************************************************/


 #define STATUS_OK					1
 #define STATUS_NOT_INITIALISED		0		/* Indicates the module hasn't been setup */
 #define STATUS_EMPTY_NULL_DATA		-1		/* Indicates the module was provided with bad data */
 #define STATUS_WRONG_PIN			-2		/* Indicates that the pin cannot be used for something */
 #define STATUS_PIN_NOT_SUPPORTED	-3		/* Indicates that there currently isn't support for that pin */