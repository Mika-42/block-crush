cmake_minimum_required(VERSION 3.29)
project(projet_info C)

set(CMAKE_C_STANDARD 23)

add_executable(projet_info main.c
        grid.c
        grid.h
        dataType.h
        userInput.c
        userInput.h
        game.c
        game.h
        menu.c
        menu.h
        score.c
        score.h
)
