//
// Created by Matis on 16/12/2024.
//

#ifndef ERROR_H
#define ERROR_H

typedef unsigned int ErrorCode;

#define TETRIS_SUCCESS 0x00
#define TETRIS_ERROR 0x01
#define TETRIS_GRID_SIZE_ERROR 0x10
#define TETRIS_DYNAMIC_ALLOCATION_FAILED 0x11
#define TETRIS_FREE_DYNAMIC_ALLOCATION_FAILED 0x12

#endif //ERROR_H
