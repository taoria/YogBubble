
cbuffer lightBuffer:register(b0){
    float3 color;
    float lightStrength;
    float3 dynamicColor;
    float3 dynamicLightPosition;
    float dynamicLightStrength;
}
struct PS_INPUT{
    float4 inPos : SV_POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inWorldPos: WORLD_POSITION;

};
Texture2D objTexture : TEXTURE : register(t0);
SamplerState objSamplerState : SAMPLER : register(s0);
float4 main(PS_INPUT input):SV_TARGET {
    float4 pixelColor = objTexture.Sample(objSamplerState, input.inTexCoord);

    float3 appliedLight = color * lightStrength;

    float3 vecToLight = normalize(dynamicLightPosition - input.inWorldPos);

    float3 diffuseLightIntensity = dot(vecToLight, input.inNormal);

    float3 diffuseLight = diffuseLightIntensity * 1.0f * dynamicColor;

    appliedLight += diffuseLight;

    float3 lightedPixelColor = pixelColor * appliedLight;
    return float4(lightedPixelColor.x,lightedPixelColor.y,lightedPixelColor.z,pixelColor.a);
}