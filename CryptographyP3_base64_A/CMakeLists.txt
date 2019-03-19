cmake_minimum_required(VERSION 3.6)
project(CryptographyP3_base64_A)

set(CMAKE_CXX_STANDARD 14)

add_executable(CryptographyP3_base64_A main.cpp base64.h base64.cpp sha256.h sha256.cpp)