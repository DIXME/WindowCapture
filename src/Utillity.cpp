#include "Utillity.hpp"
#include <vector>

HBITMAP CaptureWindow(HWND hwnd) {
    // this function was made with ai (it found it from somewhere i assume)
    // i did this beacuse FUCK the windows api
    if (!hwnd) return nullptr;

    HDC hdcWindow = GetWindowDC(hwnd);
    if (!hdcWindow) return nullptr;

    HDC hdcMemDC = CreateCompatibleDC(hdcWindow);
    if (!hdcMemDC) {
        ReleaseDC(hwnd, hdcWindow);
        return nullptr;
    }

    RECT rect;
    GetClientRect(hwnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcWindow, width, height);
    if (!hBitmap) {
        DeleteDC(hdcMemDC);
        ReleaseDC(hwnd, hdcWindow);
        return nullptr;
    }

    HGDIOBJ oldBitmap = SelectObject(hdcMemDC, hBitmap);

    BitBlt(hdcMemDC, 0, 0, width, height, hdcWindow, 0, 0, SRCCOPY);

    SelectObject(hdcMemDC, oldBitmap);
    DeleteDC(hdcMemDC);
    ReleaseDC(hwnd, hdcWindow);
    // std::println("[+] Capture Window function returned hitmap");
    return hBitmap;
}

void LoadTextureFromHBITMAP(HBITMAP hBitmap, GLuint textureID) {
    BITMAP bm;
    if (!GetObject(hBitmap, sizeof(bm), &bm))
        return;

    int width = bm.bmWidth;
    int height = bm.bmHeight;
    int bytesPerPixel = (bm.bmBitsPixel / 8);

    // Retrieve actual pixel bits
    BITMAPINFO bmi = {0};
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height; // negative to flip rows top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = bm.bmBitsPixel;
    bmi.bmiHeader.biCompression = BI_RGB;

    size_t dataSize = width * height * bytesPerPixel;
    std::vector<unsigned char> buffer(dataSize);

    HDC hdc = GetDC(nullptr);
    if (!GetDIBits(hdc, hBitmap, 0, height, buffer.data(), &bmi, DIB_RGB_COLORS)) {
        ReleaseDC(nullptr, hdc);
        return;
    }
    ReleaseDC(nullptr, hdc);

    // Swap BGR → RGB if needed
    if (bytesPerPixel >= 3) {
        for (int i = 0; i < width * height; ++i) {
            std::swap(buffer[i*bytesPerPixel + 0], buffer[i*bytesPerPixel + 2]);
        }
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum format = (bytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0,
                 (format == GL_RGBA) ? GL_RGBA8 : GL_RGB8,
                 width, height, 0, format, GL_UNSIGNED_BYTE, buffer.data());

    GLenum err = glGetError();
    if (err != GL_NO_ERROR)
        std::fprintf(stderr, "glTexImage2D error: 0x%X\n", err);
}

LPCSTR str2lpc(std::string str){
    return str.c_str();
};

HWND getHWND(std::string title){
    // if you want the desktop you can get it by doing getDesktopWindow with windows.hs
    HWND hwnd = FindWindowA(NULL, str2lpc(title));
    std::println("[+/-] Waiting for [{}] window to open!", title);
    while (!hwnd){hwnd = FindWindowA(NULL, str2lpc(title));Sleep(100);}
    std::println("[+] Found window [{}] hwnd [{}]", title, (void*)&hwnd);
    return hwnd;
}