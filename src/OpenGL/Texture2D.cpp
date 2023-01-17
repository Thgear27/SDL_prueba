#include "Texture2D.hpp"
#include "stb_image.hpp"
#include "stdexcept"

Texture2D::Texture2D(const std::string& fileName, int desiredChannels, GLint internalFormat, GLenum format) {
    loadImageData(fileName, desiredChannels, internalFormat, format);
}

Texture2D::Texture2D() {
    
}

Texture2D::~Texture2D() {
    if (Id != 0) glDeleteTextures(1, &Id);
}

void Texture2D::deleteTexture() {
    if (Id != 0) {
        glDeleteTextures(1, &Id);
        Id = 0;
    } 
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture2D::unBind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::setTextureUnit(int texUnit) {
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture2D::loadImageData(const std::string& fileName, int desiredChannels, GLint internalFormat, GLenum format) {
    unsigned char* imgData = stbi_load(fileName.c_str(), &width, &height, &nrChanels, desiredChannels);
    if (imgData == nullptr) throw std::runtime_error("Can not load img");
    glGenTextures(1, &Id);
    glBindTexture(GL_TEXTURE_2D, Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(imgData);
}