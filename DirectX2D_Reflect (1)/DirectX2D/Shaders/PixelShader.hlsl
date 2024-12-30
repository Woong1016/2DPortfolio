struct PixelInput
{
	// 픽셀 데이터를 셰이더가 감지하기 위해 존재하는 저장용 중간 구조체
	
	float4 pos : SV_POSITION;	// 도트의 위치
	float4 color : COLOR;	    // 연산할 색
};

float4 PS(PixelInput input) : SV_TARGET // <- 입력을 받으면 그래픽을 연산한다
{
	return input.color; // 현재 연산 : "아무 추가작업 하지 말고 있는 그대로 출력하라"
}