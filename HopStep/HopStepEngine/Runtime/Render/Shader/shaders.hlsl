cbuffer ConstantBufferPerObject : register(b0)
{
    float4x4 gWorldViewProj;
};

struct VertexInput
{
    float3 Position : POSITION;
    float4 Color : COLOR;
};

struct PixelInput
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
};

PixelInput VSMain(VertexInput Input)
{
    PixelInput Out;

    Out.Position = mul(float4(Input.Position, 1.0f), gWorldViewProj);
    Out.Color = Input.Color;
    
    return Out;
}

float4 PSMain(PixelInput Input) : SV_Target
{
    return Input.Color;
}
