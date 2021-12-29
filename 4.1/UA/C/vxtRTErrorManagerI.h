//=============================================================================
// $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/RT/Foundation/include/vxtRTErrorManagerI.h $
//
// Code Category: Certifiable
//
// Version: $Revision: 44818 $
//
// Last Revision $Author: mdosogne $
//
// Last Revision $Date: 2015-02-04 17:13:14 -0500 (Wed, 04 Feb 2015) $
//
// IMPORTANT NOTICE: This software program ("Software") including the source
// code is a confidential and/or proprietary product of Presagis Canada Inc.
// and/or its subsidiaries and affiliated companies. ("Presagis") and is
// protected by copyright laws. The use of the Software is subject to the terms
// of the Presagis Software License Agreement.
//
// (c) Copyright 2005 - 2008, All Rights Reserved.
//
// AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
// confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales et
// compagnies affiliees ("Presagis") et est protege par les lois sur le droit
// d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une licence de
// Presagis.
//
// (c) Copyright 2005 - 2008, Tous Droits Reserves.
//
//=============================================================================

#ifndef VXT_RT_ERROR_MANAGER_I_H
#define VXT_RT_ERROR_MANAGER_I_H

//=============================================================================
//                        I N C L U D E  F I L E S
//=============================================================================

#include "vxtPLConfig.h"
#include "vxtPLBasicTypes.h"
#include "vxtPLOSFoundationExport.h"
#include "vxtRTErrorManagerDefs.h"

//=============================================================================
//                   F O R W A R D   D E C L A R A T I O N
//=============================================================================

class vxtRTErrorHandlerI;

//=============================================================================
//                                C L A S S
//=============================================================================

//=============================================================================
///
/// @brief Runtime Error Manager Interface.
///
/// @ingroup Foundation
///
/// @desc
///  This interface allows user's code to call the error manager functions without
///  directly linking with the library. This interface provides methods to post
///  errors and query whether certain errors have occurred. This interface also
///  provides a method to set/get an error handler to handle the error when it
///  occurred.
///
/// @par Design Constraints
///  This class is an Interface class.
///
/// @par
///  Object of this class must not be copied.
///
/// @par
///  This class is only derived by vxtRTErrorManager.
///
/// @invariant None.
///
//=============================================================================
class VXT_PLOSFOUNDATION_SPEC vxtRTErrorManagerI
{
public:

   //==========================================================================
   //             P U B L I C   F U N C T I O N   M E M B E R S
   //==========================================================================

   //=============================================================================
   ///
   /// @brief Set the error handler.
   ///
   /// @param[in] a_rErrHandlerI Reference to the error handler
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGER_I.SET_ERROR_HANDLER.01]
   ///
   /// @pre @e a_rErrHandlerI must persist until this object is destroyed OR
   ///      vSetErrorHandler() function is called again.
   ///
   //=============================================================================
   virtual void vSetErrorHandler(vxtRTErrorHandlerI &a_rErrHandlerI) = 0;

   //==========================================================================
   ///
   /// @brief Get the error handler.
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGER_I.GET_ERROR_HANDLER.01]
   ///
   /// @pre None.
   ///
   //==========================================================================
   virtual vxtRTErrorHandlerI& rGetErrorHandler() = 0;

   //=============================================================================
   ///
   /// @brief Post an error.
   ///
   /// @param[in] a_ErrCode  Error code.
   /// @param[in] a_pMessage Message describing the error.
   ///
   /// @desc
   ///  The following is requirements should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.LOCAL_ERROR_HANDLER.01]
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.ERROR_HANDLER.01]
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.RECORD_ERROR.01]
   ///  - [RL1.RT.GENERAL.OBJ.BUILTIN_POSTERROR_OPERATION.01]
   ///
   /// @pre a_pMessage must be @c ::VXT_NULL or a null-terminated string.
   ///
   //=============================================================================
   virtual void vPostErrorMessage(vxtUInt        a_ErrCode,
                                  const vxtChar *a_pMessage) = 0;

   //=============================================================================
   ///
   /// @brief Post an error.
   ///
   /// @param[in] a_ErrCode  Error code.
   /// @param[in] a_pErrData Parameter providing additional information on the error condition.
   ///
   /// @desc
   ///  The following is requirements should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.LOCAL_ERROR_HANDLER.01]
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.ERROR_HANDLER.01]
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.POST_ERROR.RECORD_ERROR.01]
   ///
   /// @pre (@c ::VXT_NO_ERROR < @e a_ErrCode) && (@e a_ErrCode < @c ::VXT_ERROR_NUM)
   ///
   //=============================================================================
   virtual void vPostError(vxtErrorCode a_ErrCode,
                           const void  *a_pErrData = VXT_NULL) = 0;

#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT || VXT_CODEGEN_MODE || VXT_EDITOR_MODE
   virtual void vEnableMessages(vxtBool a_Enable)                   = 0;
   virtual void vPostMessage(const vxtChar *a_pMsg)                 = 0;
   virtual void vEndMessage()                                       = 0; 
#endif

   //=============================================================================
   ///
   /// @brief Determine whether there is any error.
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.HAS_ERROR.01]
   ///
   /// @pre None.
   ///
   //=============================================================================
   virtual vxtBool HasError() const = 0;
   
   //=============================================================================
   ///
   /// @brief Determines whether a specific error has been posted.
   ///
   /// @param[in] a_ErrCode Error Code
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.IS_ERROR_POSTED.01]
   ///
   /// @pre (@c ::VXT_NO_ERROR < @e a_ErrCode) && (@e a_ErrCode < @c ::VXT_ERROR_NUM)
   ///
   //=============================================================================
   virtual vxtBool IsErrorPosted(vxtErrorCode a_ErrCode) const = 0;
   
   //=============================================================================
   ///
   /// @brief Clear all errors.
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.CLEAR_ALL_ERRORS.01]
   ///
   /// @pre None.
   ///
   //=============================================================================
   virtual void vClearAllErrors() = 0;
   
   //=============================================================================
   ///
   /// @brief Clear a specified error.
   ///
   /// @param[in] a_ErrCode Error to be cleared.
   ///
   /// @desc
   ///  The following requirement should be treated as LSP.
   ///
   /// @additional_reqs
   ///  - [RL1.RT.CONTROLFLOW.ERRORMANAGR_I.CLEAR_ERROR.01]
   ///
   /// @pre (@c ::VXT_NO_ERROR < @e a_ErrCode) && (@e a_ErrCode < @c ::VXT_ERROR_NUM)
   ///
   //=============================================================================
   virtual void vClearError(vxtErrorCode a_ErrCode) = 0;

   // Destructor
   virtual ~vxtRTErrorManagerI() = 0;

protected:

   //==========================================================================
   ///
   /// @brief Default constructor
   ///
   /// @desc
   ///  This constructor has no side-effect.
   ///
   //==========================================================================
   vxtRTErrorManagerI()
   {
      /// @pre None
   }

   // Disallow copy
   vxtRTErrorManagerI(const vxtRTErrorManagerI&);
   vxtRTErrorManagerI& operator=(const vxtRTErrorManagerI&);
};

#endif // VXT_RT_ERROR_MANAGER_I_H

// END OF FILE 
