//
// Created by ianpo on 06/07/2024.
//

#pragma once

#define PC_CONCAT(x, y) x ## y
#define PC_COMBINE(x, y) PC_CONCAT(x, y)

#ifndef __FUNCSIG__
	#ifdef __PRETTY_FUNCTION__
		#define __FUNCSIG__ __PRETTY_FUNCTION__
	#else
		#define __FUNCSIG__ __FUNCTION__
	#endif
#endif

#ifdef PC_USE_SIMPLE_FUNCTION
	#define PC_FUNC __FUNCTION__
#else
	#define PC_FUNC __FUNCSIG__
#endif


#ifndef BIT
	#define BIT(X) (1 << X)
#endif

#ifndef CHECK_BIT
	#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))
#endif

