////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float g_PowerBlink;   
float g_BlinkThreshold;

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float  psize  : PSIZE;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultPointSprite(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_psize  : PSIZE,
      float2 prm_uv     : TEXCOORD0,
      float4 prm_col    : COLOR0

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*�ˉe�ϊ�
	out_vs.psize = 256.0;
	out_vs.col = prm_col;
	out_vs.uv = float2(1.0, 1.0);
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultPointSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	return tex_color;
}

float4 PS_DestBlendOne( 
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	return tex2D( MyTextureSampler, prm_uv) * g_MaterialDiffuse;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	return tex2D( MyTextureSampler, prm_uv) * g_MaterialDiffuse * float4(7.0, 7.0, 7.0, 1.0);
}

technique DefaultPointSpriteTechnique
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
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁi�F��Ambient���˂Ƌ��ʁj
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
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultPointSprite();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

