#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Log.h"
#include <cassert>

Texture::Texture() 
{

}

Texture::Texture(std::string path)
{

}

void Texture::LoadTexture(std::string Path)
{
    int texWidth, texHeight, texChannels;
    stbi_uc* pixels = stbi_load("textures/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);


    assert(pixels);

    if (!pixels) {
        ULogError("Vulkan Texture", "Failed to load texture!");
    }
}