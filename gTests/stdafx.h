# pragma once

# include "targetver.h"

# pragma warning(disable:4710 4711)
# pragma warning(push, 1)
# pragma warning(disable:4365 4571 4625 4623 4626 4774 4820 5026 5027 5045)
# pragma warning(disable:26439 26495)
# pragma warning(disable:28182)	// Dereferencing NULL pointer
								// 'p' contains the same NULL value as 'next_' did - linked_ptr.h 131
#	include <gtest\gtest.h>
#	ifdef _DEBUG
#		pragma comment(lib, "gtestd")
#		pragma comment(lib, "gtest_maind")
#	else
#		pragma comment(lib, "gtest")
#		pragma comment(lib, "gtest_main")
#	endif

#	include <boost\function.hpp>
#	include <boost\noncopyable.hpp>
# pragma warning(pop)

# pragma warning(disable:4514)
# pragma warning(disable:4625 4626)
# pragma warning(disable:4571)