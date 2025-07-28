#include <windows.h>
#include <string>
#include <print>
#include <glad/glad.h>
#pragma once

HBITMAP CaptureWindow(HWND hWnd);

void LoadTextureFromHBITMAP(HBITMAP hBitmap, GLuint textureID);

LPCSTR str2lpc(std::string str);

HWND getHWND(std::string title);