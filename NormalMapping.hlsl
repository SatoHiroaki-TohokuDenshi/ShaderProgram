//������������������������������������������������������������������������������
// �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture	: register(t0);	//�e�N�X�`���[
SamplerState	g_sampler	: register(s0);	//�T���v���[

Texture2D		g_nmap		: register(t1);	//�m�[�}���}�b�v

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer gModel : register(b0)
{
	float4x4	matWorld;		// ���[���h�s��
	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matNormal;		// �@���ό`�s��
	float4		diffuseColor;	// �}�e���A���̐F���g�U���ˌW��
	float4		ambientColor;	// �����W��
	float4		specularColor;	// ���ʔ��ˌW��
	float		shininess;		// ���ʔ��ˋ��x
	bool		isTextured;		// �e�N�X�`���[���\���Ă��邩�ǂ���
	bool		isNMap;			// �e�N�X�`���[���\���Ă��邩�ǂ���
};

cbuffer gModel : register(b1)
{
	float4		lightPos;		// �����̈ʒu
	float4		eyePos;			// ���_
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos  : SV_POSITION;		// �ʒu
	float2 uv	: TEXCOORD;			// UV���W
	float4 eyeDir	: POSITION;		// ���_�x�N�g��
	float4 nEyeDir	: POSITION1;	// �m�[�}���}�b�v�p�����x�N�g��
	float4 light	: POSITION2;	// �m�[�}���}�b�v�p�����x�N�g��
	float4 normal	: NORMAL;		// �@��
	float4 color	: COLOR;		// �F�i���邳�j
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL, float4 tangent : TANGENT)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData = (VS_OUT)0;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);

	// UV���W�͂��̂܂�
	outData.uv = uv.xy;

	float3 binormal = cross(normal, tangent);

	// �@����ό`
	normal.w = 0;
	normal = mul(normal, matNormal);
	normal = normalize(normal);

	outData.normal = normal;
	
	tangent.w = 0;
	tangent = mul(tangent, matNormal);
	tangent = normalize(tangent);

	binormal = mul(binormal, matNormal);
	binormal = normalize(binormal);

	// �����̈ʒu�𐳋K��
	float4 light = normalize(lightPos);
	outData.color = saturate(dot(normal, light));

	// ���_�x�N�g�����l��
	float4 posWorld = mul(pos, matWorld);
	outData.eyeDir = eyePos - posWorld;

	outData.nEyeDir = dot(outData.eyeDir, tangent);
	outData.nEyeDir = dot(outData.eyeDir, binormal);
	outData.nEyeDir = dot(outData.eyeDir, normal);
	outData.nEyeDir = 0;

	outData.light.x = dot(light, tangent);
	outData.light.y = dot(light, binormal);
	outData.light.z = dot(light, normal);
	outData.light.w = 0;

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 lightColor = float4(1.0, 1.0, 1.0, 1.0);		// �����̐F(����)

	float4 diffuse;		// �g�U����
	float4 ambient;		// ����
	float4 specular;	// ���ʔ���

	if (isNMap) {
		inData.light = normalize(inData.light);

		float4 tmpNormal = g_nmap.Sample(g_sampler, inData.uv) * 2 - 1;
		tmpNormal.w = 0;
		tmpNormal = normalize(tmpNormal);

		float4 S = dot(tmpNormal, normalize(inData.light));
		S = clamp(S, 0, 1);

		//float4 nLight = dot(inData.normal, normalize(lightPos));
		//float4 ref = normalize(2 * nLight * inData.normal - normalize(lightPos));
		float4 ref = reflect(normalize(lightPos), tmpNormal);
		specular = pow(saturate(dot(ref, normalize(inData.eyeDir))), shininess) * specularColor;

		if (isTextured) {
			diffuse = g_texture.Sample(g_sampler, inData.uv) * S;
			ambient = g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = diffuseColor * S;
			ambient = diffuseColor * ambientColor;
		}

		diffuse = diffuseColor * S;
		ambient = diffuseColor * ambientColor* S;
	}
	else {
		if (isTextured) {
			diffuse = lightColor * g_texture.Sample(g_sampler, inData.uv) * inData.color;
			ambient = lightColor * g_texture.Sample(g_sampler, inData.uv) * ambientColor;
		}
		else {
			diffuse = lightColor * diffuseColor * inData.color;
			ambient = lightColor * diffuseColor * ambientColor;
		}

		float4 nLight = dot(inData.normal, normalize(lightPos));
		float4 ref = normalize(2 * nLight * inData.normal - normalize(lightPos));
		specular = pow(saturate(dot(ref, normalize(inData.eyeDir))), shininess) * specularColor;
	}
	return diffuse;
	return (diffuse + ambient + specular);
}
