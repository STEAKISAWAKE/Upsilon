#ifndef __UPSILON_RENDER_TEXTURE_H__
#define __UPSILON_RENDER_TEXTURE_H__

#include <string>

class RenderRHI;

class Texture
{

// Constructors
public:
	Texture();
	Texture(std::string path);


// Variables
public:
	RenderRHI* rhi;

	unsigned int width;
	unsigned int height;



// Methods
public:
	virtual void LoadTexture(std::string Path);


	virtual void Initalize() {};
	virtual void Cleanup() {};


};

#endif // __UPSILON_RENDER_TEXTURE_H__