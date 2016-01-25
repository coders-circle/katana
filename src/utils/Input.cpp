#include <stdinc.h>
#include <utils/Input.h>


std::vector<bool> Input::s_keys(500, false);
int Input::s_winW = 1;
int Input::s_winH = 1;
glm::vec2 Input::s_cursorPos;
glm::vec2 Input::s_oldCursorPos;


bool Input::IsKeyPressed(int key)
{
    return s_keys[key];
}


void Input::SetKeyPressed(int key, bool value)
{
    s_keys[key] = value;
}


void Input::SetCursorPos(int x, int y)
{
    s_oldCursorPos = s_cursorPos;
    s_cursorPos.x = x;
    s_cursorPos.y = y;
}


glm::vec2 Input::GetCursorPos()
{
    return s_cursorPos;
}


glm::vec2 Input::GetNormalCursorPos()
{
    return glm::vec2(s_cursorPos.x/s_winW, s_cursorPos.y/s_winH);
}


glm::vec2 Input::GetCursorDelta()
{
    return glm::vec2(s_cursorPos.x-s_oldCursorPos.x,
        s_cursorPos.y-s_oldCursorPos.y);
}


glm::vec2 Input::GetNormalCursorDelta()
{
    glm::vec2 cursorDelta = Input::GetCursorDelta();
    cursorDelta.x /= s_winW;
    cursorDelta.y /= s_winH;
    return cursorDelta;
}

void Input::SetWindowSize(int w, int h)
{
    s_winW = w;
    s_winH = h;
}
