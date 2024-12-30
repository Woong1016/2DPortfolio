struct PixelInput
{
	// 픽셀 UV 셰이더 : 그림이 원본 파일에서 읽어들여질 때 사용되는 셰이더
	
	float4 pos : SV_POSITION;
	float2 uv : UV;
};

Texture2D map : register(t0);
SamplerState samp : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
	return map.Sample(samp, input.uv);
}