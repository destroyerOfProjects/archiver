cmake_minimum_required(VERSION 3.0)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_executable(archiver
        main.cpp
        argument_parser.cpp argument_parser.h
        heap.cpp heap.h
        reader.cpp reader.h
        trie.cpp trie.h
        writer.cpp writer.h
        archiver.cpp archiver.h
        dearchiver.cpp dearchiver.h
        my_char.h
        )
