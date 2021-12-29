/******************************************************************************
* $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/RT/include/vxtRTCUserIntegrationI.h $
*
* Version: $Revision: 47158 $
*
* Last Revision $Author: mdosogne $
*
* Last Revision $Date: 2015-04-12 11:52:53 -0400 (Sun, 12 Apr 2015) $
*
* IMPORTANT NOTICE: This software program ("Software") including the source
* code is a confidential and/or proprietary product of Presagis Canada Inc.
* and/or its subsidiaries and affiliated companies. ("Presagis") and is
* protected by copyright laws. The use of the Software is subject to the terms
* of the Presagis Software License Agreement.
*
* (c) Copyright 2005 - 2008, All Rights Reserved.
*
* AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
* confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales et
* compagnies affiliees ("Presagis") et est protege par les lois sur le droit
* d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une licence de
* Presagis.
*
* (c) Copyright 2005 - 2008, Tous Droits Reserves.
*
******************************************************************************/

#ifndef VXT_RT_C_USER_INTEGRATION_I_H
#define VXT_RT_C_USER_INTEGRATION_I_H

/******************************************************************************
** Coding Standard Deviation: Rule SCS.LAN.STY.REM.CPP
** Description: Use C++ style comments (//).
** Rationale: This header file is intended to be used by both C and C++ code, 
**            hence it uses the C style comments.
******************************************************************************/

/******************************************************************************
* C VAPSXT User Integration Interface.
******************************************************************************/

#include "vxtPLConfig.h"
#include "vxtPLBasicTypes.h"      /* Contains the basic types used in VAPSXT */
#include "vxtRTEvtInputTypes.h"
#include "vxtRTCUserIntegrationCallbacksI.h"
#include "vxtRTErrorManagerDefs.h"

#ifdef __cplusplus
#if VXT_CFG_RECORD_AND_PLAYBACK_SUPPORT
class vxtRTClockI;
class vxtRTTime;
#endif
class vxtRTTopContextI;
class vxtRTIOBufferI;
class vxtRTOptionsI;

extern "C" {

#else
#if VXT_CFG_RECORD_AND_PLAYBACK_SUPPORT
typedef struct vxtRTClockI vxtRTClockI;
typedef struct vxtRTTime vxtRTTime;
#endif
typedef struct vxtRTTopContextI vxtRTTopContextI;
/* struct vxtRTIOBufferI is already typedef'ed in vxtRTCUserIntegrationCallbacksI.h */
typedef struct vxtRTOptionsI vxtRTOptionsI;
#endif

/***************************************************************************
* RunTime Options related functions
***************************************************************************/

/* Creates a RunTime Options */
extern vxtRTOptionsI *vxtRTCUI_pCreateRTOptions();

/* Deletes the provided RunTime Options */
extern void vxtRTCUI_vDeleteRTOptions(vxtRTOptionsI **a_ppRTOptions);

/***************************************************************************
* Top context related functions
***************************************************************************/

/* Gets the top context for the given window ID */
extern const vxtRTTopContextI *vxtRTCUI_pGetTopContext(vxtInt a_RenderingContextID);

/* Gets the first top context of this task */
extern const vxtRTTopContextI *vxtRTCUI_pGetFirstTopContext();

/* Gets the last top context of this task */
extern const vxtRTTopContextI *vxtRTCUI_pGetLastTopContext();

/* Gets the next top context of the given top context */
extern const vxtRTTopContextI *vxtRTCUI_pGetNextTopContext(const vxtRTTopContextI *a_pTopContext);

/* Gets the previous top context of the given top context */
extern const vxtRTTopContextI *vxtRTCUI_pGetPrevTopContext(const vxtRTTopContextI *a_pTopContext);

/* Get the rendering context ID associated to the given top context */
extern vxtInt vxtRTCUI_GetRenderingContextID(const vxtRTTopContextI *a_pTopContext);

/***************************************************************************
* I/O Buffer manipulation functions
***************************************************************************/

/* Sets the data pointer to the named buffer if size matches the buffer size */
extern void vxtRTCUI_vSetDataAddress(vxtRTIOBufferI *a_pRTIOBuffer, 
                                     void           *a_pBufferData, 
                                     vxtUInt         a_Size);

/* Gets the pointer to the buffer with the given name */
extern void *vxtRTCUI_pGetDataAddress(vxtRTIOBufferI *a_pRTIOBuffer,
                                      vxtUInt        *a_pSize);

/* Notifies that the given buffer has updated */
extern void vxtRTCUI_vNotifyDataUpdated(vxtRTIOBufferI *a_pRTIOBuffer);

/* Sets the callback function to call when the given buffer is updated in VAPSXT */
extern void vxtRTCUI_vSetDataSendHandler(vxtRTIOBufferI *a_pRTIOBuffer,
                                         pfDataSendHandlerFunction a_pfDataSendHandlerFunction);

extern vxtRTIOBufferI* vxtRTCUI_pGetIOBuffer(const vxtChar *a_pIOBufferName); 


/***************************************************************************
* Clock replacement functions
***************************************************************************/

/* Replace default clock and required time adjustment. */
#if VXT_CFG_RECORD_AND_PLAYBACK_SUPPORT
extern const vxtRTClockI* vxtRTCUI_pReplaceClock(const vxtRTClockI* a_pClock,
                                                        const vxtRTTime*   a_pTimeAdjustment);
#endif

/***************************************************************************
* Draw functions 
***************************************************************************/

/* Draws the given top context if necessary or forced: returns whether it drew. */
extern vxtBool vxtRTCUI_DrawTopContext(const vxtRTTopContextI *a_pTopContext, vxtBool a_ForceFullDraw);

/* Draws all top contexts */
extern void vxtRTCUI_vDrawAll(vxtBool a_ForceFullDraw);

/***************************************************************************
* Error manager functions
***************************************************************************/

/*
** Error handler callback function prototypes
*/
typedef vxtBool (*pfHandleErrorFunction)(vxtUInt a_ErrorCode,  const void* a_pErrData);
#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT
typedef void (*pfOutputMessageFunction)(const vxtChar *a_pStr);
typedef void (*pfEndMessageFunction)();
#endif

#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT
extern void vxtRTCUI_vSetErrorHandler(pfHandleErrorFunction a_pErrHandlerFunc,
                                      pfOutputMessageFunction a_pOutputMsgFunc,
                                      pfEndMessageFunction a_pEndMsgFunc);
#else
extern void vxtRTCUI_vSetErrorHandler(pfHandleErrorFunction a_pErrHandlerFunc);
#endif

extern void vxtRTCUI_vPostError(vxtErrorCode a_ErrCode, const void* a_pErrData);

#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT
/*  */
extern void vxtRTCUI_vPostError1Arg(vxtErrorCode a_ErrCode, 
                                    const vxtChar *a_pParam1, 
                                    const void* a_pErrData);
/*  */
extern void vxtRTCUI_vPostError2Arg(vxtErrorCode a_ErrCode, 
                                    const vxtChar *a_pParam1, 
                                    const vxtChar *a_pParam2, 
                                    const void* a_pErrData);
/*  */
extern void vxtRTCUI_vPostErrorNArg(vxtErrorCode a_ErrCode, 
                                    const vxtChar **a_apArr, 
                                    vxtUByte a_ArgNum, 
                                    const void* a_pErrData);

/*  */
extern void vxtRTCUI_vPostMessage(const vxtChar *a_pMsg);

/*  */
extern void vxtRTCUI_vEndMessage();
#endif

/*  */
extern vxtBool vxtRTCUI_HasError();

/*  */
extern vxtBool vxtRTCUI_IsErrorPosted(vxtErrorCode a_ErrCode);

/*  */
extern void vxtRTCUI_vClearAllErrors();

/*  */
extern void vxtRTCUI_vClearError(vxtErrorCode a_ErrCode);


/***************************************************************************
* Main 
***************************************************************************/

/*
** Initializes the VAPSXT runtime with the given command line arguments,
** prepares the graphical resources, and returns VXT_TRUE on success.
**
** a_pCallbacks allows users to specify the address of a 
** vxtRTCUserIntegrationCallbacksI struct.  Refer to 
** vxtRTCUserIntegrationCallbacksI.h for more information.
*/

extern void vxtRTCUI_vSetCallbacks(vxtRTCUserIntegrationCallbacksI *a_pCallbacks);

extern void vxtRTCUI_vInitialize(vxtRTOptionsI *a_pRTOptions);

/* Executes the port main loop: returns only when the port main loop exits. */
extern void vxtRTCUI_vMainLoop();

/* Request shutdown. */
extern void vxtRTCUI_vRequestShutdown();

/* Report whether a request to shutdown was made. */
extern vxtBool vxtRTCUI_HasRequestedShutdown();

/* 
** Executes a VAPSXT iteration. 
** If a_DoDraw is set VXT_TRUE, the function updates and draws all top contexts.
** If a_DoDraw is set VXT_FALSE, the function only updates VAPS XT and the Draw
** methods above must be used after to draw.
** The pre/post update callback functions (if registered) are called before/after 
** the update phase.  See vxtRTCUserIntegrationCallbacksI.h for information.
*/
extern void vxtRTCUI_vExecuteIteration(vxtBool a_DoDraw);

/* Returns the minimum period of a VAPSXT iteration. */
extern vxtUInt vxtRTCUI_GetMinIterationPeriod();

/* Stops the VAPSXT runtime */
extern void vxtRTCUI_vShutdown();


/***************************************************************************
* Input event handlers
***************************************************************************/

/* 
** Handles a pointer event at screen position (a_X, a_Y) of the given window.
** Refer to vxtPLBasicTypes.h for allowed values for a_Evt (input event type),
** a_Button (buttons pressed), and a_Modifiers (input modifiers).
** a_RotatedDistance gives the amount the pointer wheel (ex: mouse wheel) has
** been rotated.
*/
extern void vxtRTCUI_vProcessPointerEvent( const vxtRTTopContextI *a_pTopContext, 
                                           const vxtRTEvtPointerInputParameters *a_pParams,
                                           vxtBool *a_pIsConsumed );

/* 
** Handles a discrete event in the given window.
** Refer to vxtPLBasicTypes.h for allowed values for a_Evt (input event type),
** a_Key (key pressed), and a_Modifiers (input modifiers).
** a_Repeat specifies whether to allow repeated key event.
*/
extern void vxtRTCUI_vProcessDiscreteEvent( const vxtRTTopContextI *a_pTopContext,
                                            const vxtRTEvtDiscreteInputParameters *a_pParams,
                                            vxtBool *a_pIsConsumed );

#if VXT_CFG_MULTI_TOUCH_SUPPORT
extern void vxtRTCUI_vProcessTouchEvents( const vxtRTTopContextI             *a_pTopContext,
                                          const vxtRTEvtTouchInputParameters *a_pParams );
#endif

#ifdef __cplusplus
}
#endif

#endif /* VXT_RT_C_USER_INTEGRATION_I_H */

/* END OF FILE */
