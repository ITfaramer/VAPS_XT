//=============================================================================
//
// Code generated by [VAPS XT 4.2.1]
//
//=============================================================================

#ifndef VXTCLSOPENGLTRIANGLE_H
#define VXTCLSOPENGLTRIANGLE_H

//=============================================================================
//                        I N C L U D E   F I L E S
//=============================================================================

#include "vxtBaseClsOpenGLTriangle.h"
#include "vxtRTCodedGrObject.h"
#include "vxtRTPropIdPath.h"
#include "vxtRTTopContext.h"
#include "vxtRTValue.h"
#include "vxtTypCoord.h"


//=============================================================================
//                                C L A S S
//=============================================================================

class VXTCLSOPENGLTRIANGLE_SPEC vxtClsOpenGLTriangle : public vxtBaseClsOpenGLTriangle
{
   
   
public:

 

   
   explicit vxtClsOpenGLTriangle(const InitData &a_rInitData);

   virtual ~vxtClsOpenGLTriangle();

   
#if VXT_EDITOR_MODE
   virtual vxtRTGrObject * pGetSelectedObject(const vxtRTTopContext &a_rTopContext, vxtFloat a_X, vxtFloat a_Y, vxtFloat a_CurrentScaling = 1.0F, vxtRTObject *a_pRootObj = VXT_NULL);
#endif

   
#if VXT_EDITOR_MODE
   // Remove these functions if the object cannot be rotated
   //    by adjusting its properties.
   virtual vxtBool CanRotate() const; // OVERRIDE
   virtual void vRotate(vxtFloat a_Angle); // OVERRIDE
#endif

   
protected:

   virtual void vDraw(vxtRTDrawMode &a_rMode);

   
#if VXT_EDITOR_MODE || VXT_CGRUNTIME_MODE
   virtual void vCalculateExtent(const vxtRTTopContext &a_rTopContext, vxtRRegion &a_rExtent);
#endif

private:

   // Disallow copy
   vxtClsOpenGLTriangle( const vxtClsOpenGLTriangle& );
   vxtClsOpenGLTriangle& operator=( const vxtClsOpenGLTriangle& );
};


#endif // VXTCLSOPENGLTRIANGLE_H

// END OF FILE

