struct PixelInput
{
	// �ȼ� �����͸� ���̴��� �����ϱ� ���� �����ϴ� ����� �߰� ����ü
	
	float4 pos : SV_POSITION;	// ��Ʈ�� ��ġ
	float4 color : COLOR;	    // ������ ��
};

float4 PS(PixelInput input) : SV_TARGET // <- �Է��� ������ �׷����� �����Ѵ�
{
	return input.color; // ���� ���� : "�ƹ� �߰��۾� ���� ���� �ִ� �״�� ����϶�"
}