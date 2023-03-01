struct PSInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

cbuffer ConstantBufferPerObject : register(b0)
{
    float4x4 gWorldViewProj;
};

Texture2D gTexture : register(t0);
SamplerState gSampler : register(s0);

PSInput VSMain(float4 position : POSITION, float4 normal : NORMAL, float4 uv : TEXCOORD)
{
    PSInput result;

    result.position = mul(position, gWorldViewProj);
    result.uv = uv;

    return result;
}

float4 PSMain(PSInput input) : SV_TARGET
{
    return gTexture.Sample(gSampler, input.uv);
}