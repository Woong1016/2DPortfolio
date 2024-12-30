struct PixelInput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

cbuffer ColorBuffer : register(b0)
{
	float4 color;
}

float4 PS(PixelInput input) : SV_TARGET
{
	float4 tex = map.Sample(samp, input.uv);
	
	return tex;				// 텍스처 자료 그대로 사용
	//return tex * color;		// 색보정 수치 적용시 사용
}