Texture2D g_Texture;
SamplerState g_Texture_sampler;

struct PSInput
{
    float4 Position: SV_POSITION;
    float2 UV: TEX_COORD;
    float NdotL: N_DOT_L;
};

struct PSOutput
{
    float4 Color : SV_TARGET;
};

void main(in  PSInput  PSIn, out PSOutput PSOut)
{
    //Set the final color of the pixel using the calculated saturation from the VSH
    PSIn.Color = g_Texture.Sample(g_Texture_sampler, PSIn.UV) * (PSIn.NdotL * 0.8 + 0.2);
}