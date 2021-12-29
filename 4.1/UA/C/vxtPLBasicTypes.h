/******************************************************************************
* $URL: http://svn/svn/VAPSXT178/branches/XT/4.1/VAPSXT_DIR/src/Ports/OS/win32/include/vxtPLBasicTypes.h $
*
* Version: $Revision: 47341 $
*
* Last Revision $Author: mwaldvogel $
*
* Last Revision $Date: 2015-05-01 16:03:54 -0400 (Fri, 01 May 2015) $
*
* IMPORTANT NOTICE: This software program ("Software") including the source
* code is a confidential and/or proprietary product of Presagis Canada Inc.
* and/or its subsidiaries and affiliated companies. ("Presagis") and is
* protected by copyright laws. The use of the Software is subject to the terms
* of the Presagis Software License Agreement.
*
* (c) Copyright 2004 - 2008, All Rights Reserved.
*
* AVIS IMPORTANT: Ce logiciel incluant le code source est de l'information
* confidentielle et/ou propriete de Presagis Canada Inc. et/ou ses filiales et
* compagnies affiliees ("Presagis") et est protege par les lois sur le droit
* d'auteur. L'utilisation de ce logiciel est sujet aux termes d'une licence de
* Presagis.
*
* (c) Copyright 2004 - 2008, Tous Droits Reserves.
*
******************************************************************************/

#ifndef VXT_PL_BASIC_TYPES_H
#define VXT_PL_BASIC_TYPES_H

/******************************************************************************
** Coding Standard Deviation: Rule SCS.LAN.STY.REM.CPP
** Description: Use C++ style comments (//).
** Rationale: This header file is intended to be used by both C and C++ code,
**            hence it uses the C style comments.
******************************************************************************/

/******************************************************************************
*                             B A S I C   T Y P E S
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*!
** @name Types and Constants
**@{
*/

/*!
** @ingroup BasicTypes
**@{
*/

/******************************************************************************
** Coding Standard Deviation: Rule SCS.LAN.PRE.MACRO
** Description: C++ macros shall only be used for include guards, type
**              qualifiers, storage class specifiers and VAPSXT feature
**              configuration.
** Rationale: In this header file alone constants will be defined using
**            #define.  Because C treats constants differently than C++, they
**            need to be defined rather than declared as constants, to avoid
**            potential linkage error when integrating C and C++ libraries
**            together.
******************************************************************************/
/* PRQA S 1020,1025 EOF */

/*!
** @brief Enables support of platform where the size of an int is the same as
**        a long.
**
** @desc
**    Define @c VXT_INT_SAME_SIZE_AS_LONG_SUPPORT if the size of an int is the same
**    as a long.
*/
#define VXT_INT_SAME_SIZE_AS_LONG_SUPPORT 1


/*!
** @brief Enables support for bool as a unique type
**
** @desc
**    Define @c VXT_BUILTIN_BOOL_SUPPORT if bool is a unique type (not simply a macro for int).
*/
#define VXT_BUILTIN_BOOL_SUPPORT 1

/*!
** @brief Boolean type (one-byte) - Corresponds to VAPS XT "Bool" type.
**
** @desc
**    vxtBool must NOT be defined to use the standard C++ "bool".
**    We want to be sure sizeof(vxtBool) == 1, we want to allow
**    "C" compatibility with vxtBool, and we don't want to have
**    to deal with other subtle differences between the semantics of
**    unsigned char vs C++ "bool".
*/
typedef unsigned char vxtBool;

#ifdef __cplusplus
/*!
** @brief Representation of true for vxtBool
*/
const vxtBool VXT_TRUE  = 1U;
/*!
** @brief Representation of false for vxtBool
*/
const vxtBool VXT_FALSE = 0U;
#else
#define VXT_TRUE  ((vxtBool)1)
#define VXT_FALSE ((vxtBool)0)
#endif

/*!
** @brief Unsigned byte type - Corresponds to VAPS XT "UByte" type.
*/
typedef unsigned char vxtUByte;

/*!
** @brief Signed byte type - Corresponds to VAPS XT "SByte" type.
*/
typedef signed char vxtSByte;

/*!
** @brief Plain character type
*/
typedef char vxtChar;

/*!
** @brief Enables support for wchar_t as a unique type
**
** @desc
**    Define @c VXT_WCHAR_T_SUPPORT if ::vxtWChar is the standard wchar_t data type.
**
** @note
**    Most targets support the use of wchar_t and need to have it supported.
*/
#define VXT_WCHAR_T_SUPPORT 1

/*!
** @brief Wide character types.
*/
#if VXT_WCHAR_T_SUPPORT && defined(__cplusplus)
typedef wchar_t vxtWChar;
#else
typedef unsigned short vxtWChar;
#endif

/*!
** @brief Signed short type - Corresponds to VAPS XT "Short" type.
*/
typedef short vxtShort;

/*!
** @brief Unsigned short type - Corresponds to VAPS XT "UShort" type.
*/
typedef unsigned short vxtUShort;

/*!
** @brief Signed integer type - Corresponds to VAPS XT "Int" type.
*/
typedef int vxtInt;

/*!
** @brief Unsigned integer type - Corresponds to VAPS XT "UInt" type.
*/
typedef unsigned int vxtUInt;

#if VXT_CODEGEN_MODE || VXT_EDITOR_MODE
/* Deprecated.  Use vxtInt, vxtInt64, vxtNativeInt or vxtPtrDiffT instead. */
typedef long vxtLong;
/* Deprecated.  Use vxtUInt, vxtUInt64, vxtNativeUInt or vxtSizeT instead. */
typedef unsigned long vxtULong;
/* Deprecated. */
typedef int vxtHandle;
#endif

/*!
** @brief Enables support for size_t as a unique type
**
** @desc
**  When defined to 1, ::vxtSizeT is identical to size_t;
**  otherwise size_t is a unique type (i.e. not the same as unsigned int)
**  and different from ::vxtSizeT.
**
** @note
**  Most targets support the use of size_t and need to have it supported.
*/

/*
   NOTE: On WIN32, size_t is a typedef to (unsigned int);
         on WIN64, it is a unique type.
*/
#define VXT_SIZE_T_SUPPORT VXT_CFG_64_BIT

/*!
** @brief Enables support for ptrdiff_t as a unique type
**
** @desc
**  When defined to 1, ::vxtPtrDiffT is identical to ptrdiff_t;
**  otherwise ptrdiff_t is a unique type (i.e. not the same as int)
**  and different from ::vxtPtrDiffT.
**
** @note
**  Most targets support the use of ptrdiff_t and need to have it supported.
*/

/*
   NOTE: On WIN32, ptrdiff_t is a typedef to (int);
         on WIN64, it is a unique type.
*/
#define VXT_PTRDIFF_T_SUPPORT VXT_CFG_64_BIT

/* Either of size_t or ptrdiff_t may require inclusion of header files to compile */
#if VXT_SIZE_T_SUPPORT || VXT_PTRDIFF_T_SUPPORT
   #include <stddef.h>
#endif

/*!
 ** @brief When defined to 1, ::vxtUInt is identical to ::vxtNativeUInt;
 **        otherwise those types are different and have different sizes.
 */
#if VXT_SIZE_T_SUPPORT || VXT_CFG_64_BIT
   #define VXT_NATIVEUINT_IS_UINT 0
#else
   #define VXT_NATIVEUINT_IS_UINT 1
#endif

/*!
 ** @brief Size type
 */
#if VXT_SIZE_T_SUPPORT
   typedef size_t vxtSizeT;
#elif VXT_CFG_64_BIT
   /* In case a 64-bit compiler doesn't treat size_t as a unique type. */
   typedef unsigned long long vxtSizeT;
#else
   typedef unsigned int vxtSizeT;
#endif

/*!
 ** @brief Type for longest unsigned integer type on the target platform
 */
typedef vxtSizeT vxtNativeUInt;

#if VXT_CFG_64_BIT
/*!
** @brief Unsigned 64 bit integer type.
*/
typedef unsigned long long vxtUInt64;
#endif

/*!
 ** @brief When defined to 1, ::vxtInt is identical to ::vxtNativeInt;
 **        otherwise those types are different and have different sizes.
 */
#if VXT_PTRDIFF_T_SUPPORT || VXT_CFG_64_BIT
   #define VXT_NATIVEINT_IS_INT 0
#else
   #define VXT_NATIVEINT_IS_INT 1
#endif

/*!
 ** @brief Pointer difference type
 */
#if VXT_PTRDIFF_T_SUPPORT
   typedef ptrdiff_t vxtPtrDiffT;
#elif VXT_CFG_64_BIT
   /* In case a 64-bit compiler doesn't treat ptrdiff_t as a unique type. */
   typedef long long vxtPtrDiffT;
#else
   typedef int vxtPtrDiffT;
#endif

/*!
** @brief Type for longest signed integer type on the target platform
*/
typedef vxtPtrDiffT vxtNativeInt;

#if VXT_CFG_64_BIT
/*!
** @brief Signed 64 bit integer type.
*/
typedef long long vxtInt64;
#endif

/*!
** @brief 32-bit IEEE754 floating point type - Corresponds to VAPS XT "Float" type.
*/
typedef float  vxtFloat;

/*!
** @brief 64-bit IEEE754 floating point type - Corresponds to VAPS XT "Double" type.
*/
typedef double vxtDouble;

/*!
** @brief Null pointer constant definition
**
** @par Description
**      Null pointer constant defined in accordance with Rule SCS.LAN.PTR.ZERO.
*/
#define VXT_NULL 0

/*!
** @brief Execution status returned from functions
*/
typedef enum vxtStatusEnum
{
   VXT_ERROR   = -1, /*!< Error   */
   VXT_SUCCESS = 0,  /*!< Success */
   VXT_WARNING = 1   /*!< Warning */
} vxtStatus;

/*!@} */

/*!@} */

/*!
** @ingroup BasicTypes
** @brief A structure in ROM, used in place of file system support.
**
** @desc
**    Use an array of these structures to store the name, address and size of ROM "files".
*/
typedef struct vxtPLROMFileStruct
{
   const vxtChar  *m_pName;  /*!< Address of the file name, which is null-terminated. */
   const void     *m_pData;  /*!< Address of the file data. */
   vxtUInt         m_Size;   /*!< Size of the file data in bytes. */
} vxtPLROMFile;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VXT_PL_BASIC_TYPES_H */

/* END OF FILE */
