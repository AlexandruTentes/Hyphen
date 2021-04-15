#pragma once

#define UTILITYMACROS_H_

/////////////////////////////////////////////////////////////////////////////
//===== Singleton-ize macros that will turn a class into a singtleton =====//
/////////////////////////////////////////////////////////////////////////////

#define SINGLETONIZE(T)							static T & get_instance() { static T instance; return instance; } \
												T() { } \
												T(const T &) = delete; \
												T operator = (const T &) = delete; \
												T(T &&) = delete; \
												T operator = (T &&) = delete; 

#define PARTIAL_SINGLETONIZE(T)					static T & get_instance() { static T instance; return instance; } \
												T() { } 	

#define PI										3.141592653f
#define HALF_PI									1.570796326f
#define DEG_TO_RAD								0.017453293f
#define COLOR_CORRECTION						0.00390625