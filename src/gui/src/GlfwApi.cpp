#include "GlfwApi.hpp"

#include "stb_image.h"

int GlfwApi::LoadTexture(const char* filepath)
{
    int width, height, channels;
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);
    if (!data) {
        std::cout << "Error could not load file: " << filepath << "\n";
        exit(-2);
    }

    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureId;
}
