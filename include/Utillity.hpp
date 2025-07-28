#include <windows.h>
#include <string>
#include <print>
#include <glad/glad.h>
#pragma once

HBITMAP CaptureWindow(HWND hWnd);
void LoadTextureFromHBITMAP(HBITMAP hBitmap, GLuint textureID) {
    // this also ai cuz FUCK the windows api
    BITMAP bm;
    GetObject(hBitmap, sizeof(BITMAP), &bm);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Assuming the bitmap is in BGR format and needs conversion to RGB
    int width = bm.bmWidth;
    int height = bm.bmHeight;
    int bytesPerPixel = 3; // For 24-bit images
    unsigned char* pData = new unsigned char[width * height * bytesPerPixel];
    memcpy(pData, bm.bmBits, width * height * bytesPerPixel);

    // Swap R and B channels to convert BGR to RGB
    for (int i = 0; i < width * height; ++i) {
        unsigned char temp = pData[i * 3];
        pData[i * 3] = pData[i * 3 + 2];
        pData[i * 3 + 2] = temp;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pData);

    delete[] pData;
}

LPCSTR str2lpc(std::string str){
    return str.c_str();
};

HWND getHWND(std::string title){
    // if you want the desktop you can get it by doing getDesktopWindow with windows.hs
    HWND hwnd = FindWindowA(NULL, str2lpc(title));
    std::println("[+/-] Waiting for [{}] window to open!", title);
    while (!hwnd){Sleep(100);}
    std::println("[+] Found window [{}] hwnd [{}]", title, (void*)&hwnd);
    return hwnd;
}