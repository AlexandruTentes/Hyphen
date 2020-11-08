#pragma once

#define UTILITYMACROS_H_

/////////////////////////////////////////////////////////////////////////////
//===== Singleton-ize macros that will turn a class into a singtleton =====//
/////////////////////////////////////////////////////////////////////////////

#define EVENT_MEMBER_SINGLETONIZE(T)			static T & get_instance() { static T instance; return instance; } \
												T() { } \
												T(const T &) = delete; \
												T operator = (const T &) = delete; \
												T(T &&) = delete; \
												T operator = (T &&) = delete; 

#define EVENT_MEMBER_PARTIAL_SINGLETONIZE(T)	static T & get_instance() { static T instance; return instance; } \
												T() { } 												