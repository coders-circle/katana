#include <stdinc.h>
#include <utils/Input.h>


Input::Input(int windowWidth, int windowHeight) :
    m_keys(500, false),
    m_winW(windowWidth), m_winH(windowHeight)
      
{}

bool Input::IsKeyPressed(int key)
{
    return m_keys[key];
}


void Input::SetKeyPressed(int key, bool value)
{
    m_keys[key] = value;
}


void Input::SetCursorPos(int x, int y)
{
    m_oldCursorPos = m_cursorPos;
    m_cursorPos.x = x;
    m_cursorPos.y = y;
}


glm::vec2 Input::GetCursorPos()
{
    return m_cursorPos;
}


glm::vec2 Input::GetNormalCursorPos()
{
    return glm::vec2(m_cursorPos.x/m_winW, m_cursorPos.y/m_winH);
}


glm::vec2 Input::GetCursorDelta()
{
    return glm::vec2(m_cursorPos.x-m_oldCursorPos.x,
        m_cursorPos.y-m_oldCursorPos.y);
}


glm::vec2 Input::GetNormalCursorDelta()
{
    glm::vec2 cursorDelta = Input::GetCursorDelta();
    cursorDelta.x /= m_winW;
    cursorDelta.y /= m_winH;
    return cursorDelta;
}

void Input::SetWindowSize(int w, int h)
{
    m_winW = w;
    m_winH = h;
}
