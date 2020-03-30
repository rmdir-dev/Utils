#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <functional>
#include <memory>
#include <thread>
#include <utility>


// DATA STRUCTURE
#include <string>
#include <cstring>
#include <string_view>
#include <stack>
#include <deque>
#include <array>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

// DEFINITIONS
#define BITFIELD(x) (1 << x)

typedef unsigned int uint;
typedef unsigned char byte;
typedef std::string String;
typedef std::string_view StrView;

#ifdef _WINDOWS
//WINDOWS
#include <Windows.h>
#endif // _WINDOWS