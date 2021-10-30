struct PSInput
{
    float4 Pos: SV_POSITION;
    float2 Tex: TEXCOORD0;
    float3 Norm: NORMAL;
};

struct PSOutput
{
    float4 Color : SV_TARGET;
};

void main(in  PSInput  PSIn, out PSOutput PSOut)
{
    float4 textureColor;
    float3 lightDir;
    float lightIntensity;
    float4 color;
    float3 lightDirection = float3(0.0, 0.0, 1.0); //points to origin where we render object
    float4 diffuseColor = float4(1.0, 0.0, 1.0, 1.0);

    //Sample the pixel color from the texture using the texture coordinates
    textureColor = float4(PSIn.Tex, 0.5, 0.0);

    //Calculate the diffuse lighting of the pixel (dot product of the pixel's normal vector and the light direction vector)
    lightDir = lightDirection;
    lightIntensity = saturate(dot(PSIn.Norm, lightDir));

    //Combine the diffuse color with the texture color to get the final color result (lighting magic result)
    //NEED DIFFUSE COLOR
    color = saturate(diffuseColor * lightIntensity);
    color = color * textureColor;

    PSOut.Color = color;
}