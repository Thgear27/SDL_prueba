#ifndef TEXTURE_2D_HPP
#define TEXTURE_2D_HPP

#include <glad/glad.h>
#include <string>

class Texture2D {
public:
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;

    Texture2D(const std::string& fileName, int desiredChannels, GLint internalFormat, GLenum format);
    Texture2D();
    ~Texture2D();

    void bind();
    void unBind();
    void loadImageData(const std::string& fileName, int desiredChannels, GLint internalFormat, GLenum format);
    void setTextureUnit(int texUnit);
    void deleteTexture();

    GLuint Id;
    int width;
    int height;
    int nrChanels;
};

#endif // TEXTURE_2D_HPP