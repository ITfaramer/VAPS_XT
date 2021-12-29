/******************************************************************************
* $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/RT/include/vxtRTCUserIntegrationCallbacksI.h $
*
* Version: $Revision: 39509 $
*
* Last Revision $Author: mdosogne $
*
* Last Revision $Date: 2014-07-23 17:43:42 -0400 (Wed, 23 Jul 2014) $
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

#ifndef VXT_RT_C_USER_INTEGRATION_CALLBACKS_I_H
#define VXT_RT_C_USER_INTEGRATION_CALLBACKS_I_H

/******************************************************************************
** Coding Standard Deviation: Rule SCS.LAN.STY.REM.CPP
** Description: Use C++ style comments (//).
** Rationale: This header file is intended to be used by both C and C++ code, 
**            hence it uses the C style comments.
******************************************************************************/

#include "vxtPLConfig.h"
#include "vxtPLBasicTypes.h"

/****************************************************************************
*                           C   I N T E R F A C E
****************************************************************************/

/*
* C users need to declare a vxtRTCUserIntegrationCallbacksI struct to define
* their own callback handlers.  Each field of this structure needs to be set,
* either VXT_NULL or to point to the required function.  An instance of this
* structure variable needs to be passed as the 3rd argument of
* vxtRTCUI_Init.
*/

#ifdef __cplusplus

class vxtRTIOBufferI;

extern "C" {

#else

typedef struct vxtRTIOBufferI vxtRTIOBufferI;

#endif

/******************************************************************************
* Callback function prototypes
******************************************************************************/
/*
** I/O buffers initialization callback function prototype
*/
typedef void (*pfInitIOBuffersFunction)();

/* 
** Data send handler callback function prototype
** a_pIOBufferName: name of the buffer that is updated
** a_pIOBuffer:     pointer to I/O buffer
*/
typedef void (*pfDataSendHandlerFunction)(const vxtChar *a_pIOBufferName, vxtRTIOBufferI *a_pIOBuffer);

/* 
** Pre/Post update handler callback function prototype
** See below for the description of a_IsCriticalUpdate
*/
typedef void (*pfUpdateHandlerFunction)
(
#if VXT_CFG_TIME_CRITICAL_OBJECTS_SUPPORT
   vxtBool a_IsCriticalUpdate
#endif
);

/* 
** On-shutdown callback function prototype
*/
typedef void (*pfOnShutdownFunction)();

/*
** When declaring variable of this structure, be sure to initialize every field.
*/
typedef struct vxtRTCUserIntegrationCallbacksI
{
   /***************************************************************************
   *  Initialize I/O Buffers
   ***************************************************************************/

   /*
   ** Pointer to function to initialize I/O buffers for data communication.  
   ** This gets called by vxtRTCUI_Init . Typically this function uses 
   ** one or more of the following VAPS XT User Integration API functions: 
   ** vxtRTCUI_pGetBuffer, vxtRTCUI_vSetBuffer, and 
   ** vxtRTCUI_vSetDataSendHandler.
   */
   pfInitIOBuffersFunction m_pfInitIOBuffersFunction;


   /***************************************************************************
   * Update handlers
   *
   * In the following update handler functions, if a_IsCriticalUpdate is TRUE, 
   * then the update functions are called in an iteration that is executed due
   * to a scheduled critical object update.  If a_IsCriticalUpdate is FALSE,
   * the functions are called at the regular iterations.  a_IsCriticalUpdate 
   * will always be VXT_FALSE if the critical object support is disabled by
   * using -disabletimecriticalobjectssupport flag in the command line.
   ***************************************************************************/

   /*
   ** Pointer to function that defines pre-update behavior, e.g. to get the data 
   ** into the I/O buffers, and/or notify when it has changed. Typically would 
   ** call one or more of the following VAPS XT User Integration API functions: 
   ** vxtRTCUI_vSetBuffer, vxtRTCUI_vUpdateBuffer.  This function 
   ** is called by vxtRTCUI_vExecuteIteration before data flow processing.
   */
   pfUpdateHandlerFunction m_pfPreUpdateFunction;

   /*
   ** Pointer to function that defines post-update behavior, e.g. to handle
   ** data that was modified by VAPS XT objects.  Note: the data send handler
   ** callbacks can also be used.  This may call the following VAPS XT User 
   ** Integration API function: vxtRTCUI_pGetBuffer.  This function is 
   ** called by vxtRTCUI_vExecuteIteration after data flow processing.
   */
   pfUpdateHandlerFunction m_pfPostUpdateFunction;

   /*
   ** Pointer to function that defines on-shutdown behavior. 
   */
   pfOnShutdownFunction m_pfOnShutdownFunction;

} vxtRTCUserIntegrationCallbacksI;

#ifdef __cplusplus
}
#endif

#endif /* VXT_RT_C_USER_INTEGRATION_CALLBACKS_I_H */

/* END OF FILE */
