cbuffer Constants
{
    float4x4 g_WorldViewProj;
};

struct VSInput
{
    float3 Pos: ATTRIB0;
    float3 Norm: ATTRIB1;
    float2 Tex: ATTRIB2;
    float4 Color: ATTRIB3;
};

struct PSInput
{
    float4 Pos: SV_POSITION;
    float2 Tex: TEXCOORD0;
    float3 Norm: NORMAL;
};

void main(in VSInput VSIn, out PSInput PSIn)
{
    //Set the position for the pixel shader 
    PSIn.Pos = mul(float4(VSIn.Pos, 1.0), g_WorldViewProj);
    
    //Set the texture coordinate for the pixel shader
    PSIn.Tex = VSIn.Tex;

    //Set the normal for the pixel shader
    PSIn.Norm = VSIn.Norm;
}