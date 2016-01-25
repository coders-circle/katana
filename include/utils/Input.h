#pragma once


class Input
{
public:
    Input(int windowWidth, int windowHeight);

    // Returns true if the specified key is pressed
    // eg: input.IsKeyPressed(GLFW_KEY_A)
    bool IsKeyPressed(int key);

    // Sets the state value of the specified key
    // eg: input.SetKeyPressed(GLFW_KEY_A, true)
    void SetKeyPressed(int key, bool value);

    // Returns the current cursor position
    glm::vec2 GetCursorPos();

    // Returns the current cursor position in normalized coordinate
    glm::vec2 GetNormalCursorPos();

    // Sets the cursor position
    // note: this doesn't move mouse to the specified position
    void SetCursorPos(int x, int y);

    // Returns the change in cursor position (dx, dy)
    glm::vec2 GetCursorDelta();

    // Returns the change in cursor position in Normalized coordinate
    glm::vec2 GetNormalCursorDelta();

    // Sets window size (for normalized coordinate calculation)
    void SetWindowSize(int w, int h);

private:
    std::vector<bool> m_keys;
    glm::vec2 m_cursorPos;
    glm::vec2 m_oldCursorPos;
    int m_winW, m_winH;
};
