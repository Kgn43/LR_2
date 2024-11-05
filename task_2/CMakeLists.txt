cmake_minimum_required(VERSION 3.29)
project(LR_1)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(LR_1
        structures/arr.cpp
        structures/hashMap.cpp
        structures/list.cpp
        structures/Pair.cpp
        structures/queue.cpp
        structures/singleConnList.cpp
        structures/Stack.cpp
        structures/Set.cpp
        arr_funcs.cpp
        generalFuncs.cpp
        hashMap_funcs.cpp
        list_funcs.cpp
        main.cpp
        queue_funcs.cpp
        stack_funcs.cpp
        set_funcs.cpp
)
