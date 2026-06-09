#pragma once
#include <windows.h>

#define WIDTH 800
#define HEIGHT 600

int focal = 200;
int zfront = 1;
int zback = 2;

void Render(HDC hdc);

void DrawPixel(
    HDC hdc,
    int x,
    int y,
    int z,
    int size,
    COLORREF color
);

void DrawLine(
    HDC hdc,
    int x1,
    int x2,
    int y1,
    int y2,
    int z1,
    int z2,
    COLORREF color
);


int CubeArray[8][3] = {
    { 1, 1, zfront },
    { -1, 1, zfront },
    { 1, -1, zfront },
    { -1, -1, zfront },
    { 1, 1, zback },
    { -1, 1, zback },
    { 1, -1, zback },
    { -1, -1, zback }
};

int CubeEdges[12][2] = {
    // front
    {0, 1},
    {1, 3},
    {3, 2},
    {2, 0},

    // back
    {4, 5},
    {5, 7},
    {7, 6},
    {6, 4},

    // connects
    {0, 4},
    {1, 5},
    {2, 6},
    {3, 7}
};
