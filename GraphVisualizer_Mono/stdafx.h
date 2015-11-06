# pragma once

# include "targetver.h"

# pragma warning(disable:4710 4711)

# include <iostream>
# include <list>
# include <memory>
# include <vector>

# pragma warning(push, 2)
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	include <boost\lexical_cast.hpp>
# pragma warning(pop)

# include <boost\noncopyable.hpp>

# pragma warning(disable:4514)
# pragma warning(disable:4625 4626)