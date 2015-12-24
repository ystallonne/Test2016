#ifndef _UDEFS_S_H_
#define _UDEFS_S_H_

/****************************************************************************
 *
 *            Copyright (c) 2005-2008 by HCC Embedded
 *
 * This software is copyrighted by and is the sole property of
 * HCC.  All rights, title, ownership, or other interests
 * in the software remain the property of HCC.  This
 * software may only be used in accordance with the corresponding
 * license agreement.  Any unauthorized use, duplication, transmission,
 * distribution, or disclosure of this software is expressly forbidden.
 *
 * This Copyright notice may not be removed or modified without prior
 * written consent of HCC.
 *
 * HCC reserves the right to modify this software without notice.
 *
 * HCC Embedded
 * Budapest 1133
 * Vaci ut 110
 * Hungary
 *
 * Tel:  +36 (1) 450 1302
 * Fax:  +36 (1) 450 1303
 * http: www.hcc-embedded.com
 * email: info@hcc-embedded.com
 *
 ***************************************************************************/

/****************************************************************************
 *
 * Open bracket for C++ Compatibility
 *
 ***************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * if Common Interface is used then set CAPI_USED to 1
 *
 ***************************************************************************/

#define FS_CAPI_USED 0

/****************************************************************************
 *
 * Open bracket for CAPI
 *
 ***************************************************************************/

#if FS_CAPI_USED

/****************************************************************************
 *
 * Include porting of CAPI
 *
 ***************************************************************************/

#include "../../fw_port.h"

/****************************************************************************
 *
 * Set FS_CASE_SENSITIVE to 1 if you want a case sensitive file system
 *
 ***************************************************************************/

#define FS_EFFS_CASE_SENSITIVE 0

/****************************************************************************
 *
 * Open bracket for non CAPI
 *
 ***************************************************************************/

#else

/****************************************************************************
 *
 * volumes definitions
 *
 ***************************************************************************/

#define FS_MAXVOLUME	2	/* maximum number of volumes */
#define FS_MAXTASK		10	/* maximum number of task */

#define FS_MAXPATH	   128	/* maximum lenght for path */
#define FS_CURRDRIVE	0	/* setting the current drive at startup (-1 means no default current drive)*/

#define FS_MUTEX_TYPE unsigned long /* mutex type for locking mechanism */

/****************************************************************************
 *
 * Set FS_CASE_SENSITIVE to 1 if you want a case sensitive file system
 *
 ***************************************************************************/

#define FS_EFFS_CASE_SENSITIVE 0

/****************************************************************************
 *
 * Set HCC_16BIT_CHAR to 1 if a char is 16bit length (e.g. on DSPs)
 *
 ***************************************************************************/

#define	HCC_16BIT_CHAR 0

/****************************************************************************
 *													
 * Set TI_COMPRESS to 1 if a char is 16bit length (e.g. on DSPs)
 * and character compression (2 times 8 bit byte into one 16 bit byte)
 * is selected
 *
 ***************************************************************************/

#define TI_COMPRESS 0

/****************************************************************************
 *
 * Set CRCONFILES to 1 if files need crc protection at open and calculation
 * at close. Default state is 0.
 *
 ***************************************************************************/

#define	CRCONFILES 1

/****************************************************************************
 *
 *	if Unicode is used then comment in HCC_UNICODE define
 *
 ***************************************************************************/

/* #define HCC_UNICODE */ /* enable this line for unicode compatibility */

typedef unsigned short wchar; /* typedef for wide char */

/* define W_CHAR type according to HCC_UNICODE */

#ifdef HCC_UNICODE
#define W_CHAR wchar
#else
#define W_CHAR char
#endif

/* select system directory separator char */
/* the system will use it as default, but */
/* it also recognizes both incoming parameter */

#if 1
#define FS_SEPARATORCHAR '/'
#else
#define FS_SEPARATORCHAR '\\'
#endif

/* this define is needed for compatibility of CAPI */

#define F_SEPARATOR FS_SEPARATORCHAR

/****************************************************************************
 *
 * Last error usage
 *
 ***************************************************************************/

#if 1
/* simple asignment */
#define F_SETLASTERROR(ec) (fm->lasterror=(ec))
#define F_SETLASTERROR_NORET(ec) (fm->lasterror=(ec))
#elif 0
/* function calls used for it */
#define F_SETLASTERROR(ec) fg_setlasterror(fm,ec)
#define F_SETLASTERROR_NORET(ec) fg_setlasterror_noret(fm,ec)
#elif 0
/* no last error is used (save code space) */
#define F_SETLASTERROR(ec) (ec)
#define F_SETLASTERROR_NORET(ec) 
#endif

/****************************************************************************
 *
 * Close bracket for non CAPI
 *
 ***************************************************************************/

#endif /* FS_CAPI_USED */

/****************************************************************************
 *
 * typedef for 32 bit long variable type, this is for processors
 * where 'long' type is longer than 32 bit (e.g. 40bit) but 'int' is 32. 
 * Then this typedef can be set to 'int'.
 *
 ***************************************************************************/

typedef long hcc_32;
typedef unsigned long hcc_u32;

/****************************************************************************
 *
 * Close bracket for C++
 *
 ***************************************************************************/

#ifdef __cplusplus
}
#endif

/****************************************************************************
 *
 * end of udefs_s.h
 *
 ***************************************************************************/

#endif /* _UDEFS_S_H_ */
