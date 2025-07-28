#include <windows.h>
#include <glad/glad.h>

class WindowStream {
public:
    HWND hwnd;
    GLuint textureID;

    WindowStream(HWND hwnd);

    void loop(); // get image stream (draw with the opengl texture id)
};