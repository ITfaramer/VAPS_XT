/******************************************************************************
*  $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/Examples/UserIntegration/C/CSampleMain.c $
* 
*  Version: $Revision: 32173 $
* 
*  Last Revision $Author: sparadis $
* 
*  Last Revision $Date: 2013-05-07 18:53:55 -0400 (Tue, 07 May 2013) $
* 
*  IMPORTANT NOTICE: This software program ("Software") including the source
*  code is a confidential and/or proprietary product of Presagis Canada Inc.
*  and/or its subsidiaries and affiliated companies. ("Presagis") and is
*  protected by copyright laws. The use of the Software is subject to the terms
*  of the Presagis Software License Agreement.
* 
*  (c) Copyright 2002 - 2012, All Rights Reserved.
* 
*  AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
*  confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales et
*  compagnies affiliees ("Presagis") et est protege par les lois sur le droit
*  d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une licence de
*  Presagis.
* 
*  (c) Copyright 2002 - 2012, Tous Droits Reserves.
* 
******************************************************************************/

/******************************************************************************
*
*                      M O D U L E    P U R P O S E
*
*  This module implements the following:
*
*    Name: CPPSampleMain
*
*    Description: The C application is packaged within one file 
*                 (CSampleMain.c). In this file all the buffer names, 
*                 structures, and global pointers are defined. 
*                 This is where the callbacks and data send handlers 
*                 are defined. This is also where the main loop is executed.
*
*                 The buffers are initialized in the init IO buffer 
*                 function.
*
*                 I/O Buffers are managed though the post and pre 
*                 update functions as well as the data send handler 
*                 callback function. Throughout each of these functions 
*                 examples can be found that show each of the C 
*                 API's functionalities.
*
******************************************************************************/

/******************************************************************************
*                          I N C L U D E   F I L E S
******************************************************************************/

#include "vxtRTCUserIntegrationI.h"
#include "UserDefinedUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32) && _MSC_VER >= 1400
   #pragma warning(disable : 4996)
#endif

/* Keep this in sync with vxtPLConfig.h */
#define VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT 1

/******************************************************************************
*                    G L O B A L    C O N S T A N T S
******************************************************************************/
static const vxtChar VXT_BUFFER_NAME_POSITION[]         = "PositionBuf";

/******************************************************************************
*                    G L O B A L    S T R U C T U R E S 
******************************************************************************/

typedef struct Position{
	vxtFloat lat;
	vxtFloat alt;
	vxtFloat height;
}Position;

/******************************************************************************
*                    G L O B A L    V A R I A B L E S
******************************************************************************/
Position *g_pPosition;

/******************************************************************************
*                    G L O B A L    F U N C T I O N S
******************************************************************************/

void vPositionSendFunction
(
	const vxtChar *a_pIOBufferName,
	vxtRTIOBufferI *a_pIOBuffer
)
{
	vxtUInt Size;
	void *pBufferData = vxtRTCUI_pGetDataAddress(a_pIOBuffer, &Size);

	int a = ((Position*)pBufferData)->lat;
	if(a>=1000){
		g_pPosition->lat=0;
	}
}

/***************************<vInitIOBuffersFunction>***************************
*
*  Summary:  Function that will be called by VAPSXT to initialize the buffers.
*          
*  Return Value: none
*
******************************************************************************/
void vInitIOBuffersFunction()
{
   vxtUInt Size = 0;

   /*
   ** Initialize the global pointers to buffers. 
   */

   g_pPosition          = (Position*)(vxtRTCUI_pGetDataAddress(
	                          vxtRTCUI_pGetIOBuffer(VXT_BUFFER_NAME_POSITION),&Size));

   /*
   ** Initialize the callback functions 
   */
   vxtRTCUI_vSetDataSendHandler(vxtRTCUI_pGetIOBuffer(VXT_BUFFER_NAME_POSITION),
	                                   vPositionSendFunction);
}

/******************************<vPreUpdateFunction>****************************
*
*  Summary:  Function that will be called by VAPSXT before update is done.
*          
*  Return Value: none
*
******************************************************************************/
void vPreUpdateFunction
(
#if VXT_CFG_TIME_CRITICAL_OBJECTS_SUPPORT
   vxtBool a_IsCriticalUpdate
#endif                        
)
{
#if VXT_CFG_TIME_CRITICAL_OBJECTS_SUPPORT
   if(VXT_FALSE == a_IsCriticalUpdate)
#endif
   {
      /*
      ** Notify VAPSXT that a buffer data update is done by calling the 
      ** vUpdateBuffer with the name of the buffer.
      */

      /*
      ** 1) Modify the buffer:
      **    This function is called at the beginning of each iteration.
      **    A buffer that keeps a count on the iteration is connected through 
      **    an internal transition with a text field that writes it's value to 
      **    the format. 
      **    When using data flows, a call to vUpdateBuffer is not necessary.
      **    When using internal transitions, vUpdateBuffer is used as a trigger.
      */
	  g_pPosition->lat++;

      /*
      ** 2) Notifying VAPSXT that an update is done:
      **    Calling the vxtRTCUI_vNotifyDataUpdated will notify VAPSXT that the iteration 
      **    count was updated.  In this example it will trigger the internal 
      **    transition and change the value of the text field with the new
      **    value of the iteration count buffer.
      */
      vxtRTCUI_vNotifyDataUpdated(vxtRTCUI_pGetIOBuffer(VXT_BUFFER_NAME_POSITION));
   }
}

/*****************************<vPostUpdateFunction>****************************
*
*  Summary:  Function that will be called by VAPSXT after update is done.
*          
*  Return Value: none
*
******************************************************************************/
void vPostUpdateFunction
(
#if VXT_CFG_TIME_CRITICAL_OBJECTS_SUPPORT
   vxtBool a_IsCriticalUpdate
#endif
)
{
#if VXT_CFG_TIME_CRITICAL_OBJECTS_SUPPORT
   if(VXT_FALSE == a_IsCriticalUpdate)
#endif
   {
      /*
      ** Reading from a buffer
      ** There are two main approaches to read from a data buffer.
      ** This is the second approach which is done through the post update 
      ** function. This will be called each time update is done in VAPSXT, 
      ** meaning after each iteration.
      **
      ** Sample execution information:
      ** The SliderVert drives the SignalGenerator's value2.
      ** The SliderVert is connected to the BarChartMaxValue buffer.
      ** The SignalGenerator's OutputSignal drives the BarChart's value.
      ** The SignalGenerator's OutputSignal is connected to the 
      ** BarChartValue buffer.
      */

      /*
      ** 1) Read from a buffer that was updated:
      **    Call to the vxtRTCUI_pGetDataAddress function to access the pointer to the buffer 
      **    structure.  The structure that the return value is casted to must
      **    correspond to the buffer or values will be incorrect.
      */
   }
}

vxtBool HandleErrorFunction(vxtUInt a_ErrorCode,  const void* a_Data)
{
   vxtChar Buff[255];
   sprintf(Buff, "Handle error #%u with the following description:\n", a_ErrorCode);
   fprintf(stderr, Buff);

   /* The following error code is artificially injected to simulate a warning */
   if (VXT_PL_GRAPHICS_ERROR == a_ErrorCode)
   {
      sprintf(Buff, "\nArtificially injected VXT_PL_GRAPHICS_ERROR error: error handled\n\n");
      fprintf(stderr, Buff);

      return VXT_TRUE;
   }
   else
   {
      return VXT_FALSE;
   }
}

#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT

void vOutputMessageFunction(const vxtChar *a_pStr)
{
   printf(a_pStr);
}

void vEndMessageFunction()
{
   printf("\n");
}

#endif

void vOnShutdownFunction()
{
   printf("APPLICATION SHUTTING DOWN\n");
}

/**********************************<main>**************************************
*
*  Summary:  Application Main
*          
*  Return Value: 0
*
******************************************************************************/
vxtInt main(vxtInt a_Argc, vxtChar *a_apArgv[])
{
   /*
   ** This is a C Application main function.  
   ** Users can use this as a template in calling VAPSXT code-generated 
   ** application from anywhere in C applications by following these steps:
   */

   /*
   ** 1) Initialize the C VAPSXT User Integration Callback functions.
   **    Callback functions will be called before and after iterations
   **    with the pre and post update functions.
   **    This will also initialize the I/O buffers pointers that will be
   **    used in the previous functions.
   */
   vxtRTCUserIntegrationCallbacksI Callbacks = { 0 };
   Callbacks.m_pfInitIOBuffersFunction = &vInitIOBuffersFunction;
   Callbacks.m_pfPreUpdateFunction     = &vPreUpdateFunction;
   Callbacks.m_pfPostUpdateFunction    = &vPostUpdateFunction;
   Callbacks.m_pfOnShutdownFunction    = &vOnShutdownFunction;

   vxtRTCUI_vSetCallbacks(&Callbacks);

   vxtRTCUI_vSetErrorHandler(  &HandleErrorFunction
#if VXT_CFG_DBG_ERROR_MESSAGE_SUPPORT
                             , &vOutputMessageFunction
                             , &vEndMessageFunction
#endif
                             );

   printf("APPLICATION STARTS\n");

   /*
   ** 3) Initialize VAPSXT runtime: returns VXT_TRUE on success.
   **
   **    This step processes command line arguments, prepares the graphical
   **    resources and initializes the VAPSXT runtime kernel.
   */

   {
      /*
      ** Create an RT Options object to configure the user integration.
      */
      vxtRTOptionsI *pRTOptions = vxtRTCUI_pCreateRTOptions();

      /*
      ** The following user code is optional: it parses the command line arguments and 
      ** populates the RT Options.  This line processes command-line arguments in 
      ** non-certified applications.  In certified applications this needs to be removed, 
      ** except for testing purposes.
      */
      vxtStatus UserCodeStatus = UserDefinedParseCommandLine(a_Argc, a_apArgv, pRTOptions);

      if (VXT_SUCCESS == UserCodeStatus)
      {
         /*
         ** 2) Initialize the VAPSXT runtime: returns VXT_TRUE on success.
         **
         **    This step processes run time options, prepares the graphical
         **    resources and initializes the VAPSXT runtime kernel.
         */

         vxtRTCUI_vInitialize(pRTOptions);

         if (!vxtRTCUI_HasError())
         {
            /*
            ** 3) Execute VAPSXT iterations. 
            **    
            **    There are two main approaches to execute VAPSXT iterations: 
            **    i)  By calling the blocking vxtRTCUserInteg_vMainLoop function
            **        (which calls vMainLoop in the porting layer).
            **        This function does not provide control on how update and 
            **        drawing are done, except via the porting layer.
            **        On Microsoft Windows, the vMainLoop porting layer function 
            **        takes care of translating MS Windows paint messages as well as
            **        messages received due to user input (pointer, keyboard).
            **
            **    ii) By calling vxtRTCUserInteg_vExecuteIteration, and either 
            **        vxtRTCUserInteg_vDrawAll or vxtRTCUserInteg_vDrawTopContext.
            **        This allows controlling when to update and/or draw.  On embedded 
            **        systems this approach will typically be used.
            **
            **    For more information, refer to the Code nGEN Programmer's Guide.
            */

            vxtRTCUI_vMainLoop();
         }

         /*
         **  4) Shutdown VAPSXT runtime.  This frees up graphical resources that were
         **     allocated in the Init step.
         */

         vxtRTCUI_vShutdown();
      }

      /* Destroy the RT Options object */
   vxtRTCUI_vDeleteRTOptions(&pRTOptions);
   }

   printf("APPLICATION ENDS\n");

   return 0;
}

#ifdef VXWORKS
vxtInt vxw_main()
{
   vxtInt Argc;
   vxtChar *pExampleBasicArgv[] =
   {   
      "vxw_main",
      "-fit",
      "-minmsecs",
      "20"
   };

   Argc = sizeof(pExampleBasicArgv) / sizeof(pExampleBasicArgv[0]);

   return main(Argc, pExampleBasicArgv);
}
#endif

