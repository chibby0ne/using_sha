cmake_minimum_required(VERSION 3.0)

project(sha256_test)

find_package(OpenSSL REQUIRED)

if (NOT OPENSSL_FOUND)
    message(FATAL_ERROR "Could not find openssl library. Please install it and try building again")
endif (NOT OPENSSL_FOUND)

set(SOURCES src/sha256_test.c)
include_directories(${OPENSSL_INCLUDE_DIR})
add_executable(${PROJECT_NAME} src/sha256_test.c)
target_link_libraries(${PROJECT_NAME} ${OPENSSL_CRYPTO_LIBRARY})
