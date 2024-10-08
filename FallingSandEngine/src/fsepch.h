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
#include <queue>


//platform headers

#ifdef FSE_PLATFORM_WINDOWS
//some wacky stuff with the file path dialog so i added this because i was having trouble with char* and wchar_t's
	#undef UNICODE
	#include <Windows.h>
#endif
