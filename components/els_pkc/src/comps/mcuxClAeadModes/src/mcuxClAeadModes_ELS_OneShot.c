/*--------------------------------------------------------------------------*/
/* Copyright 2021-2023 NXP                                                  */
/*                                                                          */
/* NXP Confidential. This software is owned or controlled by NXP and may    */
/* only be used strictly in accordance with the applicable license terms.   */
/* By expressly accepting such terms or by downloading, installing,         */
/* activating and/or otherwise using the software, you are agreeing that    */
/* you have read, and that you agree to comply with and are bound by, such  */
/* license terms. If you do not agree to be bound by the applicable license */
/* terms, then you may not retain, install, activate or otherwise use the   */
/* software.                                                                */
/*--------------------------------------------------------------------------*/

/** @file  mcuxClAeadModes_ELS_OneShot.c
 *  @brief implementation of the oneshot functions of the mcuxClAead component */

#include <mcuxClAead.h>
#include <internal/mcuxClAeadModes_ELS_Types.h>
#include <internal/mcuxClAeadModes_ELS_Functions.h>
#include <internal/mcuxClAeadModes_Common_Functions.h>
#include <mcuxClSession.h>
#include <mcuxCsslFlowProtection.h>
#include <mcuxClCore_FunctionIdentifiers.h>
#include <internal/mcuxClSession_Internal.h>

MCUX_CSSL_FP_FUNCTION_DEF(mcuxClAeadModes_crypt)
MCUX_CSSL_FP_PROTECTED_TYPE(mcuxClAead_Status_t)  mcuxClAeadModes_crypt(
  mcuxClSession_Handle_t session,
  mcuxClKey_Handle_t key,
  mcuxClAead_Mode_t mode,
  mcuxCl_InputBuffer_t pNonce,
  uint32_t nonceLength,
  mcuxCl_InputBuffer_t pIn,
  uint32_t inLength,
  mcuxCl_InputBuffer_t pAdata,
  uint32_t adataLength,
  mcuxCl_Buffer_t pOut,
  uint32_t * const pOutLength,
  mcuxCl_Buffer_t pTag,
  uint32_t tagLength
)
{
  MCUX_CSSL_FP_FUNCTION_ENTRY(mcuxClAeadModes_crypt);
    /* [Design]
        - allocate a context in the session
        - initialize the context:
            - copy mode to mode in context
            - copy key to key in context
            - copy inLength to dataLength in context
            - copy adataLength to aadLength in context
            - copy tagLength to tagLength in context
            - initialize processedDataLength in context to zero
        - call the Skeleton with
            - context
            - options = 15: oneshot
            - all other arguments
            - unused arguments = NULL/0
        - clean up session
    */

    // TODO: like this?
    mcuxClAeadModes_Context_t ctx; // = (mcuxClAead_Context_t) mcuxClSession_allocateWords_cpuWa(session, sizeInNumberOfWords)
    // also call mcuxClSession_freeWords_cpuWa(session, sizeInNumberOfWords) before returning to caller

    ctx.common.mode = mode;
    ctx.key = key;
    ctx.dataLength = inLength;
    ctx.aadLength = adataLength;
    ctx.tagLength = tagLength;
    ctx.processedDataLength = 0u;
    ctx.partialDataLength = 0u;

    MCUX_CSSL_FP_FUNCTION_CALL(ret_Skeleton, mode->algorithm->pSkeleton(
      /* mcuxClSession_Handle_t session,        */ session,
      /* mcuxClAead_Context_t * const pContext, */ &ctx,
      /* mcuxCl_InputBuffer_t pNonce,           */ pNonce,
      /* uint32_t nonceLength,                 */ nonceLength,
      /* mcuxCl_InputBuffer_t pIn,              */ pIn,
      /* uint32_t inLength,                    */ inLength,
      /* mcuxCl_InputBuffer_t pAdata,           */ pAdata,
      /* uint32_t adataLength,                 */ adataLength,
      /* mcuxCl_Buffer_t pOut,                  */ pOut,
      /* uint32_t * const pOutLength,          */ pOutLength,
      /* mcuxCl_Buffer_t pTag,                  */ pTag,
      /* uint32_t tagLength,                   */ tagLength,
      /* uint32_t options                      */ MCUXCLAEAD_OPTION_ONESHOT
    ));

    if(MCUXCLAEAD_STATUS_OK != ret_Skeleton)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_crypt, MCUXCLAEAD_STATUS_ERROR,
                                ctx.common.mode->algorithm->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_CALL(ret_cleanup, mcuxClSession_cleanup(session));
    if(MCUXCLSESSION_STATUS_OK != ret_cleanup)
    {
      MCUX_CSSL_FP_FUNCTION_EXIT(mcuxClAeadModes_crypt, MCUXCLAEAD_STATUS_ERROR,
                                ctx.common.mode->algorithm->protection_token_skeleton);
    }

    MCUX_CSSL_FP_FUNCTION_EXIT_WITH_CHECK(mcuxClAeadModes_crypt, MCUXCLAEAD_STATUS_OK, MCUXCLAEAD_STATUS_FAULT_ATTACK,
                                        ctx.common.mode->algorithm->protection_token_skeleton,
                                        MCUX_CSSL_FP_FUNCTION_CALLED(mcuxClSession_cleanup));
}

