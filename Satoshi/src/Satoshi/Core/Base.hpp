#ifndef BASE_HPP
#define BASE_HPP

#ifdef ST_DEBUG
	#define ST_ENABLE_ASSERTS
#endif

#ifdef ST_ENABLE_ASSERTS
	#define ST_ASSERT(x, ...) {if(!(x)) { ST_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define ST_CORE_ASSERT(x, ...) {if(!(x)) { ST_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define ST_ASSERT(x, ...)
	#define ST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ST_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)

#endif 
