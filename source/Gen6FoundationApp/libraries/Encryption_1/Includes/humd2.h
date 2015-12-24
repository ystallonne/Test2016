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
 * $Source: Includes/humd2.h $
 * $Name:  $
 */
#ifndef HUMD2_H
#define HUMD2_H

/** @file */

#ifdef __cplusplus
extern "C" {
#endif

#include "sbdef.h"

/** @addtogroup hu_md2_api MD2 APIs
 *
 * @{
 */

#define SB_MD2_DIGEST_LEN 16


/** Creates an MD2 context object.

Yielding is not supported for message digest operations.

@param digestLen   [Input]  The length (in bytes) of an MD2 digest. The only 
                            acceptable value is <tt>SB_MD2_DIGEST_LEN</tt>.
@param yieldCtx    [Input]  Ignored.
@param hashContext [Output] The MD2 context object pointer.
@param sbCtx       [Input]  A global context.

@retval SB_ERR_BAD_DIGEST_LEN   <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hashContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2Begin(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    sb_Context *hashContext,
    sb_GlobalCtx sbCtx
);


/** Updates an MD2 context with the given data.

@param hashContext [Input] The MD2 context object.
@param messageLen  [Input] The length (in bytes) of the data.
@param messageData [Input] Data buffer.
@param sbCtx       [Input] A global context.

@retval SB_ERR_NULL_CONTEXT   The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT    The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_INPUT_BUF <tt>messageData</tt> is <tt>NULL</tt>.
@retval SB_SUCCESS            Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2Hash(
    sb_Context hashContext,
    size_t messageLen,
    const unsigned char *messageData,
    sb_GlobalCtx sbCtx
);


/** Completes the message digest operation by generating the digest
and destroying the MD2 context object.

@param hashContext [Input/Output] The MD2 context object pointer.
@param digest      [Output]       Message digest buffer. The length (in bytes) 
                                  of the buffer must be at least 
				  <tt>SB_MD2_DIGEST_LEN</tt>.
@param sbCtx       [Input]        A global context.

@retval SB_ERR_NULL_CONTEXT_PTR The <tt>hashContext</tt> object pointer is 
                                <tt>NULL</tt>.
@retval SB_ERR_NULL_CONTEXT     The <tt>hashContext</tt> object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The <tt>hashContext</tt> object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF  <tt>digest</tt> is <tt>NULL</tt>.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2End(
    sb_Context *hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the MD2 message digest for the given data.

Yielding is not supported for message digest operations.

This function should only be called for data that can be stored entirely in
memory.

@param digestLen   [Input]  The length (in bytes) of an MD2 digest. The only 
                            acceptable value is <tt>SB_MD2_DIGEST_LEN</tt>.
@param yieldCtx    [Input]  Ignored.
@param messageLen  [Input]  The length (in bytes) of the data.
@param messageData [Input]  Data buffer.
@param digest      [Output] Message digest buffer. The length (in bytes) of the
                            buffer must be at least <tt>SB_MD2_DIGEST_LEN</tt>.
@param sbCtx       [Input]  A global context.

@retval SB_ERR_BAD_DIGEST_LEN  <tt>digestLen</tt> is an invalid digest length.
@retval SB_ERR_NULL_INPUT_BUF  <tt>messageData</tt> is <tt>NULL</tt>.
@retval SB_ERR_NULL_OUTPUT_BUF <tt>digest</tt> is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2Msg(
    size_t digestLen,
    sb_YieldCtx yieldCtx,
    size_t messageLen,
    const unsigned char *messageData,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Generates the message digest from the data that has been updated
to the given MD2 context.

This function does not change the state of the context object.

@param hashContext [Input]  The MD2 context object.
@param digest      [Output] The message digest buffer. The length (in bytes) of
                            the buffer must be at least 
			    <tt>SB_MD2_DIGEST_LEN</tt>.
@param sbCtx       [Input]  A global context.

@retval SB_ERR_NULL_CONTEXT    The context object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT     The context object is invalid.
@retval SB_ERR_NULL_OUTPUT_BUF The message digest buffer is <tt>NULL</tt>.
@retval SB_SUCCESS             Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2DigestGet(
    sb_Context hashContext,
    unsigned char *digest,
    sb_GlobalCtx sbCtx
);


/** Resets the given MD2 context so it can be reused.

This function returns the state of the context to the same state as
a context created after a call to <tt>hu_MD2Begin()</tt>.

@param hashContext [Input] The MD2 context object.
@param sbCtx       [Input] A global context.

@retval SB_ERR_NULL_CONTEXT The <tt>hashContext</tt> object is <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT  The <tt>hashContext</tt> object is invalid.
@retval SB_SUCCESS          Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2CtxReset(
    sb_Context hashContext,
    sb_GlobalCtx sbCtx
);


/** Duplicates an MD2 context.

This function can be used to compute the digest of multiple items of data
with identical prefixes.

@param hashContext    [Input]  The original MD2 context object.
@param newHashContext [Output] The target MD2 context object pointer.
@param sbCtx          [Input]  A global context.

@retval SB_ERR_NULL_CONTEXT     The original MD2 context object is 
                                <tt>NULL</tt>.
@retval SB_ERR_BAD_CONTEXT      The original MD2 context object is invalid.
@retval SB_ERR_NULL_CONTEXT_PTR The target MD2 context object pointer is 
                                <tt>NULL</tt>.
@retval SB_FAIL_ALLOC           Memory allocation failure.
@retval SB_SUCCESS              Success.
*/

extern
SB_EXPORT
int
SB_CALLCONV
hu_MD2CtxDuplicate(
    sb_Context hashContext,
    sb_Context *newHashContext,
    sb_GlobalCtx sbCtx
);


/** @} */

#ifdef __cplusplus
}
#endif

#endif
