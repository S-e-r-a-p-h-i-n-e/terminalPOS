cmake_minimum_required(VERSION 3.10)

# 1. Project Setup
# We use "MarketApp" (no spaces) to be safe.
# We explicitly specify CXX (C++) as the language.
project(MarketApp LANGUAGES CXX)

# 2. Standard C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 3. Find Threading Library (Required for Linux/Arch)
find_package(Threads REQUIRED)

# 4. Create the Executable
# Note: Do not put .hpp files here, only .cpp
add_executable(market_app 
    main.cpp 
    logic.cpp 
    ui.cpp
)

# 5. Link the Threading Library
target_link_libraries(market_app Threads::Threads)
