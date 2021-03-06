#include <stdinc.h>
#include <texture/Texture.h>


Texture::Texture(const std::string& path)
{
    if (!DoesFileExist(path))
        throw FileNotFoundError(path);

    // Load the image
    unsigned char* image = SOIL_load_image(path.c_str(),
        &m_width, &m_height, 0, SOIL_LOAD_RGBA);

    CreateTexture(image);

    // Free the image data
    SOIL_free_image_data(image);

    // TODO: Exceptions
}


Texture::Texture(unsigned char* image, int width, int height)
{
    m_width = width;
    m_height = height;
    CreateTexture(image);
}

void Texture::CreateTexture(unsigned char* image)
{    // Create texture object
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    // Set texture data to image
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}
