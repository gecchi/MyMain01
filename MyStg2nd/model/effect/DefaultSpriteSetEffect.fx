#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxSpriteSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;

float g_offsetU001;
float g_offsetU002;
float g_offsetU003;
float g_offsetU004;
float g_offsetU005;
float g_offsetU006;
float g_offsetU007;
float g_offsetU008;
float g_offsetU009;
float g_offsetU010;
float g_offsetU011;
float g_offsetU012;
float g_offsetU013;
float g_offsetU014;
float g_offsetU015;
float g_offsetU016;
float g_offsetU017;
float g_offsetU018;

float g_offsetV001;
float g_offsetV002;
float g_offsetV003;
float g_offsetV004;
float g_offsetV005;
float g_offsetV006;
float g_offsetV007;
float g_offsetV008;
float g_offsetV009;
float g_offsetV010;
float g_offsetV011;
float g_offsetV012;
float g_offsetV013;
float g_offsetV014;
float g_offsetV015;
float g_offsetV016;
float g_offsetV017;
float g_offsetV018;

float g_alpha001;
float g_alpha002;
float g_alpha003;
float g_alpha004;
float g_alpha005;
float g_alpha006;
float g_alpha007;
float g_alpha008;
float g_alpha009;
float g_alpha010;
float g_alpha011;
float g_alpha012;
float g_alpha013;
float g_alpha014;
float g_alpha015;
float g_alpha016;
float g_alpha017;
float g_alpha018;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 color    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultSpriteSet(                              
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@
      float  prm_index  : PSIZE ,    // ���f���ԍ�
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	//���_�v�Z
	float4x4 matWorld;
	float offsetU;
	float offsetV;
	float alpha;

	if (index == 0) {
		matWorld = g_matWorld001;
		offsetU  = g_offsetU001;
		offsetV  = g_offsetV001;
		alpha   = g_alpha001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		offsetU  = g_offsetU002;
		offsetV  = g_offsetV002;
		alpha   = g_alpha002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		offsetU  = g_offsetU003;
		offsetV  = g_offsetV003;
		alpha   = g_alpha003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		offsetU  = g_offsetU004;
		offsetV  = g_offsetV004;
		alpha   = g_alpha004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		offsetU  = g_offsetU005;
		offsetV  = g_offsetV005;
		alpha   = g_alpha005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		offsetU  = g_offsetU006;
		offsetV  = g_offsetV006;
		alpha   = g_alpha006;
	} else if (index == 6) {	
		matWorld = g_matWorld007;
		offsetU  = g_offsetU007;
		offsetV  = g_offsetV007;
		alpha   = g_alpha007;
	} else if (index == 7) {	
		matWorld = g_matWorld008;
		offsetU  = g_offsetU008;
		offsetV  = g_offsetV008;
		alpha   = g_alpha008;
	} else if (index == 8) {	
		matWorld = g_matWorld009;
		offsetU  = g_offsetU009;
		offsetV  = g_offsetV009;
		alpha   = g_alpha009;
	} else if (index == 9) {	
		matWorld = g_matWorld010;
		offsetU  = g_offsetU010;
		offsetV  = g_offsetV010;
		alpha   = g_alpha010;
	} else if (index == 10) {	
		matWorld = g_matWorld011;
		offsetU  = g_offsetU011;
		offsetV  = g_offsetV011;
		alpha   = g_alpha011;
	} else if (index == 11) {	
		matWorld = g_matWorld012;
		offsetU  = g_offsetU012;
		offsetV  = g_offsetV012;
		alpha   = g_alpha012;
	} else if (index == 12) {	
		matWorld = g_matWorld013;
		offsetU  = g_offsetU013;
		offsetV  = g_offsetV013;
		alpha   = g_alpha013;
	} else if (index == 13) {	
		matWorld = g_matWorld014;
		offsetU  = g_offsetU014;
		offsetV  = g_offsetV014;
		alpha   = g_alpha014;
	} else if (index == 14) {	
		matWorld = g_matWorld015;
		offsetU  = g_offsetU015;
		offsetV  = g_offsetV015;
		alpha   = g_alpha015;
	} else if (index == 15) {	
		matWorld = g_matWorld016;
		offsetU  = g_offsetU016;
		offsetV  = g_offsetV016;
		alpha   = g_alpha016;
	} else if (index == 16) {	
		matWorld = g_matWorld017;
		offsetU  = g_offsetU017;
		offsetV  = g_offsetV017;
		alpha   = g_alpha017;
	} else { 
		matWorld = g_matWorld018;
		offsetU  = g_offsetU018;
		offsetV  = g_offsetV018;
		alpha   = g_alpha018;
	}

	//World*View*�ˉe�ϊ�
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);  // �o�͂ɐݒ�
	//UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color.a  = alpha;
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}

//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultSpriteSet(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color    : COLOR0 
) : COLOR  {

	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//���߂�F
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	}           
	out_color.a = out_color.a * prm_color.a * g_alpha_master; 
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
	//���v�Z�A�e�N�X�`�����ƃI�u�W�F�N�g���̍��Z
	out_color.a = out_color.a * prm_color.a * g_alpha_master; 
	return out_color;
}

//���e�N�j�b�N�FDefaultSpriteSetTechnique��
//�y�@�\�z
//GgafDxSpriteSetModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
//�y�l�������v�f�z
//--- VS ---
//�E���_�� World�AView�A�ˉe �ϊ�
//�EUV���p�^�[���ԍ��̈ʒu��
//--- PS ---
//�E�I�u�W�F�N�g�̃e�N�X�`��
//�E���������i���p�����[�^�ƃe�N�X�`�����̏�Z�j
//�y�g�p�����z
//�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
//�y�ݒ�p�����[�^�z
// float4x4 g_matWorld		:	World�ϊ��s��
// float4x4 g_matView		:	View�ϊ��s��
// float4x4 g_matProj		:	�ˉe�ϊ��s��   
// float g_hAlpha			:	���l
// float g_offsetU			:	�e�N�X�`��U���W����
// float g_offsetV			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique DefaultSpriteSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSpriteSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSpriteSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
