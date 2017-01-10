# pragma once

# include "targetver.h"

# pragma warning(disable:4710 4711)

# pragma warning(push, 1)
#	include <gtest\gtest.h>
#	ifdef _DEBUG
#		pragma comment(lib, "gtestd")
#		pragma comment(lib, "gtest_main-mdd")
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