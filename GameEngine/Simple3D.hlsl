//float4 main( float4 pos : POSITION ) : SV_POSITION
//{
//	return pos;
//}

//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture		: register(t0);	//�e�N�X�`���[
Texture2D		g_normalTexture : register(t1); //�m�[�}���}�b�v
SamplerState	g_sampler		: register(s0);	//�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matW;				//���[���h�s��
	float4x4    g_matNormal;		//�@���ό`�s��(��]�s��Ɗg��s��̋t�s��)
	float4		g_diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		g_ambient;			//�A���r�G���g
	float4		g_speculer;			//�X�y�L�����[
	float4		g_lightDirection;	//���C�g�̌���
	float4		g_cameraPosition;	//�J�����̈ʒu
	float		g_shininess;		//�n�C���C�g�̋���
	bool		g_isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
	bool		g_isUseCustomClor;  //�v���O�������ŕς���F
	float4      g_customColor;		//�v���O�������ŐF��ς���ꍇ�̕ϐ�
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos		: SV_POSITION;	//�ʒu
	float4 normal	: TEXCOORD0;	//�@��
	float4 light	: TEXCOORD1;	//���C�g
	float4 eyeVector: TEXCOORD2;	//����
	float4 col		: COLOR;		//�J���[
	float2 uv		: TEXCOORD3;	//UV���W
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
	outData.pos = mul(pos, g_matWVP);
	//�����x�N�g��
	float4 cameraPos = mul(pos, g_matW);
	outData.eyeVector = normalize(g_cameraPosition - cameraPos);

	//�@��
	normal.w = 0;
	outData.normal = mul(normal, g_matNormal);

	//UV
	outData.uv = uv;

	//�܂Ƃ߂ďo��
	return outData;
}
//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	//PS_IN outData;
	inData.normal = normalize(inData.normal);
//���C�g�x�N�g��
float4 light = float4(0, -1, 0, 0);
	light = normalize(light);
	//�g�U���ˌ�(�f�B�t���[�Y)
	//�@���ƃ��C�g�̕����̓���
	float4 shade = saturate(dot(inData.normal, -light));
	shade.a = 1;
	//�e�N�X�`��
	float4 diffuse;
	if (g_isTexture == true)
	{
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		diffuse = g_diffuseColor;
	}
	//����(�A���r�G���g)
	float4 ambient = float4(0.2, 0.2, 0.2, 1.0f);// g_ambient;
	ambient.a = 1;
	//���ʔ��ˌ�(�X�y�L�����[)
	float4 speculer = float4(0, 0, 0, 0);
	if (g_speculer.a != 0)
	{
		float4 vecReflect = reflect(light, inData.normal);
		speculer = float4(1,1,1,0) * pow(saturate(dot(vecReflect, inData.eyeVector)), g_shininess) * g_speculer;
	}
	float4 outColor;
	outColor = diffuse * shade + diffuse * ambient + speculer;
	return outColor;
}

///////////normalMap///////////////////////////////////
////������������������������������������������������������������������������������
//// ���_�V�F�[�_
////������������������������������������������������������������������������������
//VS_OUT VS(float4 pos : POSITION,float4 uv : TEXCOORD,float4 normal : NORMAL, float4 tangent : TANGENT)
//{
//	//�s�N�Z���V�F�[�_�[�֓n�����
//	VS_OUT outData;
//
//	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
//	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
//	outData.pos = mul(pos, g_matWVP);
//	
//	//UV
//	outData.uv = uv;
//
//	//�]�@���x�N�g��
//	float3 biNormal = cross(normal, tangent);
//	biNormal = mul(biNormal, g_matNormal);
//	biNormal = normalize(biNormal);
//	
//	//�ڐ��̉�]
//	tangent = mul(tangent, g_matNormal);
//	tangent = normalize(tangent);
//	
//	//�@���x�N�g���̉�]
//	normal.w = 0;
//	normal = mul(normal, g_matNormal);
//	normal = normalize(normal);
//
//
//	//�����x�N�g��
//	//float4 eye = mul(pos, g_matW);
//	float4 eye = normalize(mul(pos,g_matW)-g_cameraPosition);
//	outData.eyeVector.x = dot(eye, tangent);
//	outData.eyeVector.y = dot(eye, biNormal);
//	outData.eyeVector.z = dot(eye, normal);
//	outData.eyeVector.w = 0;
//
//	float4 light = float4(0, -1, 0, 0);
//	light = normalize(light);
//	outData.light.x = dot(light, tangent);
//	outData.light.y = dot(light, biNormal);
//	outData.light.z = dot(light, normal);
//	outData.light.w = 0;
//	outData.light = normalize(outData.light);
//
//	outData.col = clamp(dot(normal, outData.light), 0, 1);
//	outData.normal = normal;
//
//	//�܂Ƃ߂ďo��
//	return outData;
//}
//
////������������������������������������������������������������������������������
//// �s�N�Z���V�F�[�_
////������������������������������������������������������������������������������
//float4 PS(VS_OUT inData) : SV_Target
//{
//	float4 diffuse;
//	float4 ambient = float4(0.2, 0.2, 0.2, 1.0f);// g_ambient;
//	float4 speculer = float4(0, 0, 0, 0);
//	
//	float4 normal = g_normalTexture.Sample(g_sampler, inData.uv) * 2 - 1;
//
//	inData.normal = normalize(inData.normal);
//	normal.w = 0;
//	normal = normalize(normal);
//
//	////���C�g�x�N�g��
//	//float4 light = float4(0, -1, 0, 0);
//	//light = normalize(light);
//
//
//
//	//�g�U���ˌ�(�f�B�t���[�Y)
//	//�@���ƃ��C�g�̕����̓���
//	float4 shade = saturate(dot(normal, -inData.light));
//	shade.a = 1;
//
//	//�e�N�X�`��
//	if (g_isTexture == true)
//	{
//		diffuse = g_texture.Sample(g_sampler, inData.uv)*shade;
//		ambient = g_texture.Sample(g_sampler, inData.uv) * g_ambient;
//	}
//	else
//	{
//		diffuse = g_diffuseColor * shade;
//		ambient = g_diffuseColor * g_ambient;
//	}
//
//	//����(�A���r�G���g)
//	ambient.a = 1;
//
//	//���ʔ��ˌ�(�X�y�L�����[)
//	float4 vecReflect = reflect(inData.light, inData.normal);
//	speculer = pow(saturate(dot(vecReflect, inData.eyeVector)), g_shininess) * g_speculer;
//	float4 outColor;
//	outColor = diffuse + diffuse * ambient + speculer;
//	return outColor;
//}



////������������������������������������������������������������������������������
// // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
////������������������������������������������������������������������������������
//Texture2D		g_texture : register(t0);	//�e�N�X�`���[
//SamplerState	g_sampler : register(s0);	//�T���v���[
//
////������������������������������������������������������������������������������
//// �R���X�^���g�o�b�t�@
//// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
////������������������������������������������������������������������������������
//cbuffer global
//{
//	float4x4	matWVP;			// ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
//	float4x4	matNormal;		//�@���ό`�p�̍s��
//	float4		diffuseColor;		// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
//	bool		isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
//};
//
////������������������������������������������������������������������������������
//// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
////������������������������������������������������������������������������������
//struct VS_OUT
//{
//	float4 pos  : SV_POSITION;	//�ʒu
//	float2 uv	: TEXCOORD;		//UV���W
//	float4 color	: COLOR;	//�F�i���邳�j
//};
//
////������������������������������������������������������������������������������
//// ���_�V�F�[�_
////������������������������������������������������������������������������������
//VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
//{
//	//�s�N�Z���V�F�[�_�[�֓n�����
//	VS_OUT outData;
//
//	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
//	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
//	outData.pos = mul(pos, matWVP);
//	outData.uv = uv;
//
//	normal = mul(normal, matNormal);
//
//	float4 light = float4(0, 1, 0, 0);
//	light = normalize(light);
//	outData.color = clamp(dot(normal, light), 0, 1);
//
//	//�܂Ƃ߂ďo��
//	return outData;
//}
//
////������������������������������������������������������������������������������
//// �s�N�Z���V�F�[�_
////������������������������������������������������������������������������������
//float4 PS(VS_OUT inData) : SV_Target
//{
//
//
//	float4 diffuse;
//	float4 ambient;
//	if (isTexture == true)
//	{
//		diffuse = g_texture.Sample(g_sampler, inData.uv) * inData.color;
//		ambient = g_texture.Sample(g_sampler, inData.uv) * float4(0.2, 0.2, 0.2, 1);
//	}
//	else
//		diffuse = diffuseColor * inData.color;
//	{
//		ambient = diffuseColor * float4(0.2, 0.2, 0.2, 1);
//	}
//	inData.color.a = 1;
//		return inData.color;// +ambient;
//}