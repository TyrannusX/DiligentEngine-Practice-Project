cbuffer Constants
{
    float4x4 g_WorldViewProj;
};

struct VSInput
{
    float3 Position: ATTRIB0;
    float2 UV: ATTRIB1;
};

struct PSInput
{
    float4 Position: SV_POSITION;
    float2 UV: TEX_COORD;
};

void main(in VSInput VSIn, out PSInput PSIn)
{
    //Transform the vertex from object space to world space
    PSIn.Position = mul(float4(VSIn.Position, 1.0), g_WorldViewProj);
    PSIn.UV = VSIn.UV;
}