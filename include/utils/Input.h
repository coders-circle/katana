#pragma once


class Input
{
public:
    // Returns true if the specified key is pressed
    // eg: Input::IsKeyPressed(GLFW_KEY_A)
    static bool IsKeyPressed(int key);

    // Sets the state value of the specified key
    // eg: Input::SetKeyPressed(GLFW_KEY_A, true)
    static void SetKeyPressed(int key, bool value);

    // Returns the current cursor position
    static glm::vec2 GetCursorPos();

    // Returns the current cursor position in normalized coordinate
    static glm::vec2 GetNormalCursorPos();

    // Sets the cursor position
    // note: this doesn't move mouse to the specified position
    static void SetCursorPos(int x, int y);

    // Returns the change in cursor position (dx, dy)
    static glm::vec2 GetCursorDelta();

    // Returns the change in cursor position in Normalized coordinate
    static glm::vec2 GetNormalCursorDelta();

    // Sets window size (for normalized coordinate calculation)
    static void SetWindowSize(int w, int h);
private:
    static std::vector<bool> s_keys;
    static glm::vec2 s_cursorPos;
    static glm::vec2 s_oldCursorPos;
    static int s_winW, s_winH;
};
