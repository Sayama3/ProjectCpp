cmake_minimum_required(VERSION 3.20)

# set enable the debugger (when the debug mode is enable?)
#if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
#    if(NOT MSVC)
#        set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
#    endif()
#endif()
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

set(EXE_TARGET_NAME ProjectCpp)

set(SRC src/main.cpp
        src/ThirdPartiesImplementor.cpp
        src/Image.cpp
        include/Image.hpp
        include/array.hpp
        src/test.cpp
        include/test.hpp
        src/ImageIterator.cpp
        include/ImageIterator.hpp
)

add_executable(${EXE_TARGET_NAME} ${SRC})

target_include_directories(${EXE_TARGET_NAME} PUBLIC include)
target_include_directories(${EXE_TARGET_NAME} PUBLIC vendor)

if(CMAKE_BUILD_TYPE MATCHES "[Dd][Ee][Bb][Uu][Gg]")
    target_compile_definitions(${EXE_TARGET_NAME} PUBLIC PC_DEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES "[Rr][Ee][Ll][Ee][Aa][Ss][Ee]")
    target_compile_definitions(${EXE_TARGET_NAME} PUBLIC PC_RELEASE)
elseif(CMAKE_BUILD_TYPE MATCHES "[Dd][Ii][Ss][Tt]")
    target_compile_definitions(${EXE_TARGET_NAME} PUBLIC PC_DIST)
endif()

target_compile_features(${EXE_TARGET_NAME} PUBLIC cxx_std_20)

target_link_libraries(${EXE_TARGET_NAME} PUBLIC glm spdlog::spdlog_header_only imgui tracy)
target_link_libraries(${EXE_TARGET_NAME} PRIVATE glad glfw)
