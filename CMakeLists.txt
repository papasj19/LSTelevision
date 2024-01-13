cmake_minimum_required(VERSION 3.21)
project(For_Stories C)

set(CMAKE_C_STANDARD 11)

add_executable(For_Stories main.c
        actor.c
        user.c
        program.h
        program.c
        format_checking.h
        format_checking.c
        menu.c
        menu.c
        client.h
        client.c
        channel.c)
