#include "Utillity.hpp"

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
    ReleaseDC(hWnd, hdcWindow);

    return hBitmap;
}
