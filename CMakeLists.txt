cmake_minimum_required(VERSION 3.8)
project(CorrectorOrtografico)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c map.c map.h trie.c trie.h wordcreation.c wordcreation.h array.h array.c)
add_executable(CorrectorOrtografico ${SOURCE_FILES})