#ifndef __UPSILON_RENDER_RENDERRHI_H__
#define __UPSILON_RENDER_RENDERRHI_H__

#include <rttr/registration>

class Render;

class RenderRHI
{

RTTR_ENABLE()

// Constructors
public:

    RenderRHI();

// Variables
public:



// Methods
public:
    virtual void Initalize() {};
    virtual void Cleanup() {};

};

#endif // __UPSILON_RENDER_RENDERRHI_H__