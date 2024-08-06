#pragma once

//commmon
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include "FallingSandEngine/Core/Log.h"
#include "FallingSandEngine/Debug/Instrumentor.h"

#include <sstream>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>


//platform headers

#ifdef FSE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif
