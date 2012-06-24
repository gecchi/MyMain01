#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxSpriteModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
float g_alpha; //��
float g_offset_u; //�e�N�X�`��U���W����
float g_offset_v; //�e�N�X�`��V���W����
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;
float g_far_rate;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultSprite(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
        }
    } 

	//UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}


//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//���߂�F
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	}         
	out_color.a = tex_color.a * g_alpha * g_alpha_master;
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 out_color = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
	out_color.a = out_color.a * g_alpha * g_alpha_master;
	return out_color;
}

//���e�N�j�b�N�FDefaultSpriteTechnique��
//�y�@�\�z
//GgafDxSpriteModel�p�W���V�F�[�_�[
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
// float g_alpha			:	���l
// float g_offset_u			:	�e�N�X�`��U���W����
// float g_offset_v			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique DefaultSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSprite();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSprite();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}