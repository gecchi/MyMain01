////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshModel�p�V�F�[�_�[
//
// Auther:Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_X; //��O���s���`�b�vX
float g_Y; //��O���s���`�b�vX
float g_Z; //��O���s���`�b�vX



float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	if (prm_pos.x > 0) {
		out_vs.pos.x = g_X;  // �o�͂ɐݒ�
		out_vs.pos.y = g_Y;  // �o�͂ɐݒ�
		out_vs.pos.z = g_Z;  // �o�͂ɐݒ�
	} else {

		//���_�v�Z
		float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
		float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
		float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
		out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	}
	//�@���v�Z
	out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_LaserChip(
	float4 prm_in_color : COLOR0,
	float2 prm_uv	    : TEXCOORD0,
	float3 prm_normal   : TEXCOORD1
) : COLOR  {
	//���߂�F
	float4 out_color; 

	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                

	if (prm_in_color.a < tex_color.a) {
		out_color.a = tex_color.a;               
	} else {
		out_color.a = prm_in_color.a;
	}

	if (prm_in_color.r < tex_color.r) {
		out_color.r = tex_color.r;               
	} else {
		out_color.r = prm_in_color.r;               
	}

	if (prm_in_color.g < tex_color.g) {
		out_color.g = tex_color.g;               
	} else {
		out_color.g = prm_in_color.g;               
	}

	if (prm_in_color.a < tex_color.b) {
		out_color.b = tex_color.b;               
	} else {
		out_color.b = prm_in_color.b;               
	}

	//���v�Z�A
	out_color.a = g_MaterialDiffuse.a * out_color.a ; 

	return out_color;
}

technique LaserChipTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//�E�@���� World�ϊ�
	//--- PS ---
	//�EDiffuse���C�g�F
	//�EAmbient���C�g�F
	//�E���C�g����
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	//�E�I�u�W�F�N�g�̃e�N�X�`��
	//�E���������iDiffuse���˃��ƃe�N�X�`�����̏�Z�j
	//�y�g�p�����z
	//�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
	//�y�ݒ�p�����[�^�z
	// float4x4 g_matWorld		:	World�ϊ��s��
	// float4x4 g_matView		:	View�ϊ��s��
	// float4x4 g_matProj		:	�ˉe�ϊ��s��   
	// float3 g_LightDirection	:	���C�g�̕���
	// float4 g_LightAmbient	:	Ambien���C�g�F�i���ːF�j
	// float4 g_LightDiffuse	:	Diffuse���C�g�F�i���ːF�j
	// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}
}



