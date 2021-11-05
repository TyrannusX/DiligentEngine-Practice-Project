#ifndef UNIFORMCONSTANTS_H
#define UNIFORMCONSTANTS_H

#include <DiligentCore/Common/interface/BasicMath.hpp>

struct UniformConstants
{
    Diligent::float4x4 WorldViewProj;
    Diligent::float4x4 NormalTransform;
    Diligent::float4 LightDirection;
};

#endif