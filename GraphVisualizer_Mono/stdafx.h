# pragma once

# include "targetver.h"

# pragma warning(disable:4710 4711)

#pragma warning(push, 3)
#pragma warning(disable:4365 4571 4625 4626 4774 4820 5026 5027)
#	include <iostream>
#	include <list>
#	include <memory>
#	include <vector>
#pragma warning(pop)

# pragma warning(push, 2)
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	pragma warning(disable:4571 4625 4626 4774 4820 5026 5027)
#	pragma warning(disable:26433 26439 26440 26455 26472 26475 26477 26481 26495 26496)
#	include <boost\lexical_cast.hpp>
#	include <boost\noncopyable.hpp>
# pragma warning(pop)

# pragma warning(disable:4514)
# pragma warning(disable:4625 4626)