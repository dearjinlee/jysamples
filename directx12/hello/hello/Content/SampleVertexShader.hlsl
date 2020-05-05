// ���� ���� �ۼ��� ���� �� ���� �⺻ �� �߽� ����� �����ϴ� ��� �����Դϴ�.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

// ������ ���̴��� ���� �Է����� ���Ǵ� �������� �������Դϴ�.
struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

// �ȼ� ���̴��� ����� �ȼ��� �� �������Դϴ�.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

// GPU���� ������ ó���� �ϱ� ���� ������ ���̴��Դϴ�.
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos, 1.0f);

	// ������ ��ġ�� �������ǵ� �������� ��ȯ�մϴ�.
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// ���� ���� ���� ����մϴ�.
	output.color = input.color;

	return output;
}
