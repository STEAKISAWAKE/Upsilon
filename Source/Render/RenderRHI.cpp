#include "RenderRHI.h"

#include <rttr/registration>

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<RenderRHI>("RenderRHI")
        .constructor<>()
        
        .method("Initalize", &RenderRHI::Initalize)
        .method("Cleanup", &RenderRHI::Cleanup)
    ; 

}