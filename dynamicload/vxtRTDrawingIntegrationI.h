//=============================================================================
// $URL: http://svn/svn/VAPSXT178/branches/XT/4.2/VAPSXT_DIR/src/Integration/include/vxtRTDrawingIntegrationI.h $
//
// Version: $Revision: 48096 $
//
// Last Revision $Author: mdosogne $
//
// Last Revision $Date: 2015-07-08 18:50:10 -0400 (Wed, 08 Jul 2015) $
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

#ifndef VXT_RT_DRAWING_INTEGRATIONI_H
#define VXT_RT_DRAWING_INTEGRATIONI_H

//---------------------------------------------------------------------
// Coding Standard Deviation: SCS.LAN.POR.ABS.TYPES
// Description: The basic types defined in VAPS XT shall be used.
// Rationale: This file is meant to be include by client code without 
//            any other header from VAPS XT.
//---------------------------------------------------------------------
// PRQA S 2427 EOF
// PRQA S 2428 EOF

//=============================================================================
//                   F O R W A R D   D E C L A R A T I O N
//=============================================================================

class vxtRTDrawingIntegrationI;
class vxtRTDrawingIntegration_V2I;
class vxtRTDrawingIntegration_V3I;

//=============================================================================
//                   G L O B A L   D E C L A R A T I O N
//=============================================================================

#ifdef WIN32
   #define VXT_RT_DRAWING_INTEGRATIONI_SPEC __declspec(dllexport)
#else
   #define VXT_RT_DRAWING_INTEGRATIONI_SPEC
#endif

//=============================================================================
//                      E X T E R N   F U N C T I O N
//=============================================================================

extern "C" VXT_RT_DRAWING_INTEGRATIONI_SPEC vxtRTDrawingIntegrationI* vxtGetDrawingIntegrationI();
extern "C" VXT_RT_DRAWING_INTEGRATIONI_SPEC vxtRTDrawingIntegration_V2I* vxtGetDrawingIntegration_V2I();
extern "C" VXT_RT_DRAWING_INTEGRATIONI_SPEC vxtRTDrawingIntegration_V3I* vxtGetDrawingIntegration_V3I();

extern "C" VXT_RT_DRAWING_INTEGRATIONI_SPEC const char* vxtGetDrawingIntegrationApiVersion();
extern "C" VXT_RT_DRAWING_INTEGRATIONI_SPEC const char* vxtGetVapsXTVersion();

//=============================================================================
//                                C L A S S
//=============================================================================

const char *const VXT_RT_DRAWING_INTEGRATION_API_VERSION = "3.0";

enum vxtRTDrawingIntegrationEvent
{
   VXT_RT_DI_EVT_POINTER_DBLCLK,
   VXT_RT_DI_EVT_POINTER_DRAGGED, // OBSOLETE: This event is equivalent to VXT_RT_DI_EVT_POINTER_MOVED.
   VXT_RT_DI_EVT_POINTER_ENTERED, // OBSOLETE: This event is ignored.
   VXT_RT_DI_EVT_POINTER_EXITED,  // OBSOLETE: This event is ignored.
   VXT_RT_DI_EVT_POINTER_MOVED,
   VXT_RT_DI_EVT_POINTER_PRESSED,
   VXT_RT_DI_EVT_POINTER_RELEASED,
   VXT_RT_DI_EVT_POINTER_ROTATED,

   VXT_RT_DI_EVT_DISCRETE_PRESSED,
   VXT_RT_DI_EVT_DISCRETE_RELEASED,
   VXT_RT_DI_EVT_DISCRETE_TYPED
};

typedef unsigned int vxtRTDrawingIntegrationModifier;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_NONE       = 0x00000000;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_SHIFT      = 0x00000002;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_CONTROL    = 0x00000004;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_ALT        = 0x00000008;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_CAPSLOCK   = 0x00000010;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_NUMLOCK    = 0x00000020;
const vxtRTDrawingIntegrationModifier VXT_RT_DI_MODIFIER_SCROLLLOCK = 0x00000040;

typedef unsigned int vxtRTDrawingIntegrationEvtButtons;
const vxtRTDrawingIntegrationEvtButtons VXT_RT_DI_BUTTON_NONE   = 0x00000000;
const vxtRTDrawingIntegrationEvtButtons VXT_RT_DI_BUTTON_LEFT   = 0x00000001;
const vxtRTDrawingIntegrationEvtButtons VXT_RT_DI_BUTTON_RIGHT  = 0x00000002;
const vxtRTDrawingIntegrationEvtButtons VXT_RT_DI_BUTTON_MIDDLE = 0x00000004;
const vxtRTDrawingIntegrationEvtButtons VXT_RT_DI_BUTTON_WHEEL  = 0x00000008; // OBSOLETE: This constant is ignored.

//==========================================================================
// Version 1.0 of Drawing Integration Interface
// - Supported by all VAPS XT versions since Drawing Integration Interface was introduced.
//==========================================================================
class vxtRTDrawingIntegrationI
{
public:

   // Initialize function (its name really shouldn't start with "v" since it has a return value
   //                      but we don't plan to change it in order to maintain compatibility)
   virtual bool vInit(int a_Argc, char* a_aArgv[], bool a_UseClipPlane = false) = 0;

   // Close function.
   virtual void vClose() = 0;

   // Function to execute one iteration.
   virtual void vExecuteIteration() = 0;

   // Function to set size of drawing window.
   // By default the position of drawing window is (0,0).
   // See vxtRTDrawingIntegration_V2I:vSetPosition.
   virtual void vSetSize(int a_RenderingContextId, short a_X, short a_Y) = 0;

   // Data communication functions
   virtual void vSetBuffer(const char *a_pBufferName, void *a_pBufferData, unsigned int a_Size) = 0;

   virtual void* pGetBuffer(const char *a_pBufferName, unsigned int &a_rSize) = 0;

   virtual void vUpdateBuffer(const char *a_pBufferName) = 0;

   // Event handling functions
   virtual bool ProcessPointerEvent(int a_RenderingContextId,
                                    vxtRTDrawingIntegrationEvent a_Evt,
                                    vxtRTDrawingIntegrationEvtButtons a_Button,
                                    vxtRTDrawingIntegrationModifier a_Modifiers,
                                    short a_RotatedDistance,
                                    float a_X, 
                                    float a_Y) = 0;

   virtual bool ProcessDiscreteEvent(int a_RenderingContextId,
                                     vxtRTDrawingIntegrationEvent a_Evt, 
                                     unsigned int a_Key,  // Only unsigned short values are accepted
                                     vxtRTDrawingIntegrationModifier a_Modifiers,
                                     bool a_Repeat = false) = 0;

   virtual ~vxtRTDrawingIntegrationI();
};

//==========================================================================
// Version 2.0 of Drawing Integration Interface
// - supported by VAPS XT 4.0.1 and later versions.
//==========================================================================
class vxtRTDrawingIntegration_V2I : public vxtRTDrawingIntegrationI
{
public:

   // Function to set position of drawing window.
   // See vxtRTDrawingIntegrationI::vSetSize.
   virtual void vSetPosition(int a_RenderingContextId, float a_X, float a_Y) = 0;

   virtual ~vxtRTDrawingIntegration_V2I();
};

//==========================================================================
// Version 3.0 of Drawing Integration Interface
// - supported by VAPS XT 4.1 and later versions.
//==========================================================================
class vxtRTDrawingIntegration_V3I : public vxtRTDrawingIntegration_V2I
{
public:
   enum TouchInputState
   {
      VXT_RT_DI_TOUCH_INVALID = 0, // Touch is out of sensor range or not valid. It should be ignored.
      VXT_RT_DI_TOUCH_DOWN,        // Touch has contacted with input device.
      VXT_RT_DI_TOUCH_MOVE,        // Touch already in contact with input device has moved.
      VXT_RT_DI_TOUCH_UP           // Touch has broken contact with input device.
   };

   struct TouchInput
   {
      TouchInputState m_State; // State of touch input.
      unsigned int  m_SystemId;  // Unique system-assigned touch ID. After a touch is removed, the ID may be re-used.
      float m_X;                 // X coordinate of the touch (in pixels, measured from the left of the window)
      float m_Y;                 // Y coordinate of the touch (in pixels, measured from the bottom of the window)
   };

   // @pre a_pTouchArray must contain at least a_NumberOfTouches entries.
   virtual void vProcessTouchEvents(int               a_RenderingContextId,
                                    const TouchInput *a_pTouchArray,
                                    unsigned int      a_NumberOfTouches) = 0;

   virtual ~vxtRTDrawingIntegration_V3I();
};

#endif // VXT_RT_DRAWING_INTEGRATIONI_H

// END OF FILE 
