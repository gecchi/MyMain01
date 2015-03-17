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

float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
float g_offset_u010;
float g_offset_u011;
float g_offset_u012;
float g_offset_u013;
float g_offset_u014;
float g_offset_u015;
float g_offset_u016;
float g_offset_u017;
float g_offset_u018;

float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;
float g_offset_v010;
float g_offset_v011;
float g_offset_v012;
float g_offset_v013;
float g_offset_v014;
float g_offset_v015;
float g_offset_v016;
float g_offset_v017;
float g_offset_v018;

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
    float4 posModel_Proj    : POSITION;
	float4 color    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultSpriteSet(                              
      float4 prm_posModel_Local    : POSITION,     // ���f���̒��_
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@
      float  prm_index  : PSIZE ,    // ���f���ԍ�
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;
	const int index = (int)prm_index;
	//���_�v�Z
	float4x4 matWorld;
	float offsetU;
	float offsetV;
	float alpha;
	if (index == 0) {
		matWorld = g_matWorld001;
		offsetU  = g_offset_u001;
		offsetV  = g_offset_v001;
		alpha   = g_alpha001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		offsetU  = g_offset_u002;
		offsetV  = g_offset_v002;
		alpha   = g_alpha002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		offsetU  = g_offset_u003;
		offsetV  = g_offset_v003;
		alpha   = g_alpha003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		offsetU  = g_offset_u004;
		offsetV  = g_offset_v004;
		alpha   = g_alpha004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		offsetU  = g_offset_u005;
		offsetV  = g_offset_v005;
		alpha   = g_alpha005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		offsetU  = g_offset_u006;
		offsetV  = g_offset_v006;
		alpha   = g_alpha006;
	} else if (index == 6) {	
		matWorld = g_matWorld007;
		offsetU  = g_offset_u007;
		offsetV  = g_offset_v007;
		alpha   = g_alpha007;
	} else if (index == 7) {	
		matWorld = g_matWorld008;
		offsetU  = g_offset_u008;
		offsetV  = g_offset_v008;
		alpha   = g_alpha008;
	} else if (index == 8) {	
		matWorld = g_matWorld009;
		offsetU  = g_offset_u009;
		offsetV  = g_offset_v009;
		alpha   = g_alpha009;
	} else if (index == 9) {	
		matWorld = g_matWorld010;
		offsetU  = g_offset_u010;
		offsetV  = g_offset_v010;
		alpha   = g_alpha010;
	} else if (index == 10) {	
		matWorld = g_matWorld011;
		offsetU  = g_offset_u011;
		offsetV  = g_offset_v011;
		alpha   = g_alpha011;
	} else if (index == 11) {	
		matWorld = g_matWorld012;
		offsetU  = g_offset_u012;
		offsetV  = g_offset_v012;
		alpha   = g_alpha012;
	} else if (index == 12) {	
		matWorld = g_matWorld013;
		offsetU  = g_offset_u013;
		offsetV  = g_offset_v013;
		alpha   = g_alpha013;
	} else if (index == 13) {	
		matWorld = g_matWorld014;
		offsetU  = g_offset_u014;
		offsetV  = g_offset_v014;
		alpha   = g_alpha014;
	} else if (index == 14) {	
		matWorld = g_matWorld015;
		offsetU  = g_offset_u015;
		offsetV  = g_offset_v015;
		alpha   = g_alpha015;
	} else if (index == 15) {	
		matWorld = g_matWorld016;
		offsetU  = g_offset_u016;
		offsetV  = g_offset_v016;
		alpha   = g_alpha016;
	} else if (index == 16) {	
		matWorld = g_matWorld017;
		offsetU  = g_offset_u017;
		offsetV  = g_offset_v017;
		alpha   = g_alpha017;
	} else { 
		matWorld = g_matWorld018;
		offsetU  = g_offset_u018;
		offsetV  = g_offset_v018;
		alpha   = g_alpha018;
	}

	//World*View*�ˉe�ϊ�
	out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // �o�͂ɐݒ�
	//UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color.a  = alpha;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}

//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultSpriteSet(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color    : COLOR0 
) : COLOR  {

	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 colOut = tex2D( MyTextureSampler, prm_uv); 
	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	}           
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
	//���v�Z�A�e�N�X�`�����ƃI�u�W�F�N�g���̍��Z
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

//���e�N�j�b�N�FDefaultSpriteSetTechnique��
//�y�@�\�z
//GgafDxSpriteSetModel�p�W���V�F�[�_�[
//�y�T�v�z
//�|���i�[���X�v���C�g�j��`�悷��B���C�g�Ȃǂ̉A�e�͖����B
technique DefaultSpriteSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSpriteSet();
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
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSpriteSet();
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
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSpriteSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
