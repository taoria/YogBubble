#pragma pack_matrix( row_major )
cbuffer myCbuffer : register(b0){
  float4x4 wvpMatrix;
  float4x4 worldMatrix;
}
struct VS_INPUT
{
    float3 inPos : POSITION;
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    
};

struct VS_OUTPUT
{
    float4 outPos :SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
    float3 outWorldPos : WORLD_POSITION;
};
VS_OUTPUT main(VS_INPUT input){
    VS_OUTPUT output;
    output.outPos = mul(float4(input.inPos, 1),wvpMatrix);
    output.outTexCoord = input.inTexCoord;
    output.outNormal = normalize(mul(float4(input.inNormal,0), worldMatrix));
    output.outWorldPos = mul(float4(input.inPos, 1), worldMatrix);
    return output;
}