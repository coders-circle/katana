#pragma once
#include <SOIL/SOIL.h>


class Texture
{
public:
    Texture(const std::string& path);
    Texture(unsigned char* image, int width, int height);

    ~Texture()
    {
        glDeleteTextures(1, &m_texture);
    }

    // Get size
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

    // Get texture object
    GLuint GetTexture() const { return m_texture; }

private:
    int m_width, m_height;
    GLuint m_texture;

    void CreateTexture(unsigned char* image);
};
