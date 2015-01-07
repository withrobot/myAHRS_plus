/*
 * This confidential and proprietary software may be used only as
 * authorised by a licensing agreement from ARM Limited
 * (C) COPYRIGHT 2009 ARM Limited
 * ALL RIGHTS RESERVED
 * The entire notice above must be reproduced on all authorised
 * copies and copies may only be made to the extent permitted
 * by a licensing agreement from ARM Limited.
 */
 
/**
 * @file ump_ref_drv.h 
 *
 * Reference driver extensions to the UMP user space API for allocating UMP memory
 */

#ifndef _UNIFIED_MEMORY_PROVIDER_REF_DRV_H_
#define _UNIFIED_MEMORY_PROVIDER_REF_DRV_H_

#include <ump/ump.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
	/* This enum must match with the IOCTL enum in ump_ioctl.h */
	UMP_REF_DRV_CONSTRAINT_NONE = 0,
	UMP_REF_DRV_CONSTRAINT_PHYSICALLY_LINEAR = 1
} ump_alloc_constraints;



/** Allocate a buffer which can be used directly by hardware. Internal ref_count is 1. */
UMP_API_EXPORT ump_handle ump_ref_drv_allocate(unsigned long size, ump_alloc_constraints constrains);




#ifdef __cplusplus
}
#endif

#endif /*_UNIFIED_MEMORY_PROVIDER_REF_DRV_H_ */
