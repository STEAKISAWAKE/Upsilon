#ifndef __CHRONOS_RENDER_DESCRIPTORS_H__
#define __CHRONOS_RENDER_DESCRIPTORS_H__

#include <string>
#include <unordered_map>

class Shader;

struct DescriptorType
{
    enum class Enum
    {
        Unknown, // Null Error
        Int,
        Float,
        Vec2,
        Vec3,
        Vec4,
        Mat3,
        Mat4
    };
};

struct Descriptor
{
    DescriptorType::Enum descriptorType;
    void* data;
};

class Descriptors
{

public:
    Descriptors();
    Descriptors(std::unordered_map<std::string, Descriptor> descriptorSets, Shader* shader);
    ~Descriptors();

public:
    virtual void Bind();
    virtual void UnBind();

    virtual DescriptorType::Enum GetDescriptorType(std::string descriptor);
    virtual void UpdateDescriptor(std::string descriptor, void* newData);

public:
    std::unordered_map<std::string, Descriptor> descriptors;
    Shader* shader;

};

#endif // __CHRONOS_RENDER_DESCRIPTORS_H__