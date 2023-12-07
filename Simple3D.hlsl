//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matWorld;		// ���[���h�s��
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matNormal;		// �@���ό`�s��
	float4		diffuseColor;	// �}�e���A���̐F���g�U���ˌW��
	float4		lightPos;		// �����̈ʒu
	float4		eyePos;			// ���_
	bool		isTextured;		// �e�N�X�`���[���\���Ă��邩�ǂ���
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos  : SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 eyeDir	: POSITION;	// ���_�x�N�g��
	float4 normal	: NORMAL;	// �@��
	float4 color	: COLOR;	//�F�i���邳�j
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);

	// UV���W�͂��̂܂�
	outData.uv = uv;

	// �@����ό`
	normal = mul(normal , matNormal);
	normal = normalize(normal);

	outData.normal = normal;

	// �����̈ʒu�𐳋K��
	float4 light = normalize(lightPos);
	outData.color = clamp(dot(normal, light), 0, 1);

	// ���_�x�N�g�����l��
	float4 posWorld = mul(pos, matWorld);
	outData.eyeDir = eyePos - posWorld;

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightColor = float4(1.0, 1.0, 1.0, 1.0);		// �����̐F
	float4 ambientColor = float4(1.0, 1.0, 1.0, 1.0);	// �����̐F

	float4 diffuse;
	float4 ambient;
	float4 specular;

	if (isTextured) {
		diffuse = lightColor * g_texture.Sample(g_sampler, inData.uv) * inData.color;
		ambient = lightColor * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
	}
	else {
		diffuse = lightColor * diffuseColor * inData.color;
		ambient = lightColor * diffuseColor * ambientColor;
	}

	float4 normalLight = clamp(dot(inData.normal, normalize(lightPos)), 0, 1);
	float4 ref = normalize(2 * normalLight * inData.normal - normalize(lightPos));
	specular = pow(clamp(dot(ref, normalize(inData.eyeDir)), 0, 1), 8);

	return (diffuse + ambient + specular);
}
