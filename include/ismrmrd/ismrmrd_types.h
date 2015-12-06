/* ISMRMRD MR Raw Data Types  (version 2.x)                */
/*                                                         */
/* Needed on some platforms prior including ismrmrd.h      */

/**
 * @file ismrmrd_types.h
 */

#pragma once

#ifdef _MSC_VER /* MS compiler */
#ifndef HAS_INT_TYPE
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#endif /* HAS_INT_TYPE */
#else  /* non MS C or C++ compiler */
#include <stdint.h>
#endif /* _MSC_VER */

