cmake_minimum_required(VERSION 3.29)
project(LR_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(LR_1
    arr.cpp
    arr_funcs.cpp
    generalFuncs.cpp
    hashMap.cpp
    hashMap_funcs.cpp
    list.cpp
    list_funcs.cpp
    main.cpp
    Pair.cpp
    queue.cpp
    queue_funcs.cpp
    singleConnList.cpp
    Stack.cpp
    stack_funcs.cpp
        set_funcs.cpp
        Set.cpp)
