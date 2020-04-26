#include "Object.h"

#include <iostream>

#include <rttr/type>

// RTTR

RTTR_REGISTRATION
{
    using namespace rttr;

    registration::class_<Object>("Object")
        .constructor<>();
}

// Constructors
Object::Object()
{

}

// Methods
void Object::Serialize()
{
    rttr::string_view name = this->get_type().get_name();

    std::cout << name << std::endl;
}