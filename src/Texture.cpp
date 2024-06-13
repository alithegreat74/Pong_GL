#include "Texture.h"

TextureInfo TextureLoader::LoadImage(const char* filePath)
{
    int width, height, nChannels;
    //Loads the image data using the stb_image library
    unsigned char* data = stbi_load(filePath, &width, &height, &nChannels, 0);
    if (data == NULL) {
        std::cout << "Unable to load textue\n";
    }

    return { width,height,nChannels,data };
}

void TextureLoader::UnloadImage(unsigned char* data)
{
    stbi_image_free(data);
}

Texture2D::Texture2D(TextureInfo info)
{
    //Create a texture
    glGenTextures(1, &object_id);
    Bind();
    //Setting the texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //Setting the texture data based on it's channels
    info.nChannels == 1 ? glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, GL_RED, GL_UNSIGNED_BYTE, info.data):
    info.nChannels == 4 ? glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, info.width, info.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, info.data):
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.width, info.height, 0, GL_RGB, GL_UNSIGNED_BYTE, info.data);


    glGenerateMipmap(GL_TEXTURE_2D);

    TextureLoader::UnloadImage(info.data);

    Unbind();
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &object_id);
}

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, object_id);
}

void Texture2D::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
