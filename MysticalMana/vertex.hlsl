cbuffer Constants
{
    float4x4 g_WorldViewProj;
    float4x4 g_NormalTransform;
    float4 g_LightDirection;
};

struct VSInput
{
    float3 Position: ATTRIB0;
    float3 Normal: ATTRIB1;
    float2 UV: ATTRIB2;
};

struct PSInput
{
    float4 Position: SV_POSITION;
    float2 UV: TEX_COORD;
    float NdotL: N_DOT_L;
};

void main(in VSInput VSIn, out PSInput PSIn)
{
    //Transform the vertex from object space to world space
    PSIn.Position = mul(float4(VSIn.Position, 1.0), g_WorldViewProj);
    PSIn.UV = VSIn.UV;
}