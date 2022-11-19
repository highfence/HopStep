cbuffer MatrixBuffer
{
	matrix WorldMatrix;
	matrix ViewMatrix;
	matrix ProjectionMatrix;
};

struct VertexInputType
{
	float4 Position : POSITION;
	float4 Color : COLOR;
};

struct PixelInputType
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};

PixelInputType ColorVertexShader(VertexInputType Input)
{
	Input.Position.w = 1.0f;

	PixelInputType Output;
	Output.Position = mul(Input.Position, WorldMatrix);
	Output.Position = mul(Output.Position, ViewMatrix);
	Output.Position = mul(Output.Position, ProjectionMatrix);
	Output.Color = Input.Color;

	return Output;
}