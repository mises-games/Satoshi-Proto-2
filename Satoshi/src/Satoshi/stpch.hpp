#ifndef STPCH_HPP
#define STPCH_HPP

#include <cstdint>
#include <cstdlib>
#include <cassert>
#include <cstdarg>
#include <cmath>
#include <cuchar>

#include <iostream>
#include <fstream>
#include <sstream>
#include <locale>
#include <codecvt>

#include <functional>
#include <memory>
#include <algorithm>
#include <chrono>
#include <utility>

#include <thread>
#include <mutex>
#include <future>
#include <atomic>

#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>

#include <yaml-cpp/yaml.h>

#ifdef ST_PLATFORM_WINDOWS

#define WIN32_LEAN_AND_MEAN

#include <sdkddkver.h>
#include <windows.h>
#include <ws2tcpip.h>

#endif

#ifdef ST_PLATFORM_LINUX

#include <sys/socket.h>

#endif

#include <Satoshi/Core/Base.hpp>
#include <Satoshi/Core/Log.hpp>

#endif
