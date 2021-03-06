/*
 * Copyright � 1996-2011 Certicom Corp. All rights reserved.
 * 
 * This software contains trade secrets, confidential information, and other
 * intellectual property of Certicom Corp. and its licensors. This software
 * cannot be used, reproduced, or distributed in whole or in part by any means
 * without the explicit prior consent of Certicom Corp. Such consent must arise
 * from a separate license agreement from Certicom or its licensees, as 
 * appropriate.
 * 
 * Certicom, Certicom AMS, ACC, Asset Control Core, Certicom Bar Code
 * Authentication Agent, Certicom ECC Core, Certicom Security Architecture,
 * Certicom Trusted Infrastructure, Certicom CodeSign, Certicom KeyInject,
 * ChipActivate, DieMax, Security Builder, Security Builder API, 
 * Security Builder API for .NET, Security Builder BSP, Security Builder Crypto,
 * Security Builder ETS, Security Builder GSE, Security Builder IPSec, Security
 * Builder MCE, Security Builder NSE, Security Builder PKI, Security Builder SSL
 * and SysActivate are trademarks or registered trademarks of Certicom Corp.
 * All other companies and products listed herein are trademarks or registered
 * trademarks of their respective holders.
 *
 * BlackBerry�, RIM�, Research In Motion� and related trademarks are owned by
 * Research In Motion Limited. Used under license.
 * 
 * Certicom Corp. has intellectual property rights relating to technology
 * embodied in the product that is described in this document. In particular,
 * and without limitation, these intellectual property rights may include one or
 * more of the U.S. and non-U.S. patents listed at www.certicom.com/patents and
 * one or more additional patents or pending patent applications in the U.S. and
 * in other countries. Information subject to change.
 *
 */
 * $Source: Includes/huyield.h $
 * $Name:  $
 */
#ifndef HUYIELD_H
#define HUYIELD_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_yield_api Yielding APIs
 *
 * @{
 */

/** Prototype of user-provided callback function to process information
during a long computation inside the library.

The callback should be registered during yield context creation.

@param yieldarg [Input] User defined data pointer.

@retval - This user-provided function should return <tt>0</tt> to indicate 
          successful completion. However, it can return any value. Currently, 
	  this value is ignored.
*/

typedef
int
SB_CALLCONV
hu_YieldFunc(
    void *yieldarg
);


/** Creates a yield context object with the given callback function and data.

<em>Note</em>: This function is not supported in the Palm version.

@param yieldFunc [Input]  User-provided callback function.
@param yieldData [Input]  User-defined data that will be passed to 
                          <tt>yieldFunc</tt>. (Optional - set to <tt>NULL</tt> 
			  if not required.)
@param yieldCtx  [Output] Yield context object pointer.
@param sbCtx     [Input]  Global context.

@retval SB_ERR_NULL_CONTEXT_PTR Context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_INPUT       Yield function is <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_YieldCreate(
    hu_YieldFunc* yieldFunc,
    void *yieldData,
    sb_YieldCtx *yieldCtx,
    sb_GlobalCtx sbCtx
);

/** Yield.

<em>Note</em>: This function is not supported in the Palm version.

@param yieldCtx [Input] Yield context object pointer.

@retval SB_ERR_NULL_CONTEXT Context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  Context object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_Yield(
    sb_YieldCtx yieldCtx
);


/** Destroys a yield context object.

<em>Note</em>: This function is not supported in the Palm version.

@param yieldCtx [Input/Output] Yield context object pointer.
@param sbCtx    [Input]        Global context.

@retval SB_ERR_NULL_CONTEXT_PTR Context object pointer is <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     Context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      Context object is invalid.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_YieldDestroy(
    sb_YieldCtx *yieldCtx,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
