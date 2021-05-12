#ifndef STPCH_HPP
#define STPCH_HPP

#include <cstdint>
#include <cassert>
#include <cstdarg>
#include <cmath>

#include <iostream>
#include <fstream>
#include <sstream>

#include <functional>
#include <memory>
#include <algorithm>
#include <chrono>

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

#ifdef ST_PLATFORM_WINDOWS

#include <windows.h>

#endif

#ifdef ST_PLATFORM_LINUX

#include <sys/socket.h>

#endif

#include <Satoshi/Core/Base.hpp>
#include <Satoshi/Core/Log.hpp>

#endif
