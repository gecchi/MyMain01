#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxBoardModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_alpha; //��
float g_offsetU; //�e�N�X�`��U���W����
float g_offsetV; //�e�N�X�`��V���W����
float g_transformedX; //�ϊ��ς�X���W(px)
float g_transformedY; //�ϊ��ς�Y���W(px)
float g_depthZ; //�[�xZ (0 �` +1)
float g_game_buffer_width; //��ʕ�(px)
float g_game_buffer_height; //��ʍ���(px)
float g_sx;
float g_sy;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxBoardModel�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultBoard(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.pos.x = - 1 + ((2*prm_pos.x*g_sx + 2*g_transformedX - 1) / g_game_buffer_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y*g_sy + 2*g_transformedY - 1) / g_game_buffer_height);
	out_vs.pos.z = g_depthZ;
	out_vs.pos.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;

	return out_vs;
}


float4 GgafDxPS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//���߂�F
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	}    
	//���l��
	out_color.a = out_color.a * g_alpha * g_alpha_master; 
	return out_color;
}



float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;                
	//���l��
	out_color.a = out_color.a * g_alpha * g_alpha_master; 
	return out_color;
}






//���e�N�j�b�N�FDefaultBoardTechnique��
//�y�@�\�z
//GgafDxBoardModel�p�W���V�F�[�_�[
//�y�T�v�z
//D3DFVF_XYZRHW �ŕ`�悵���悤�Ȏd�l�łQ�c�\�����܂��B
//��ʍ������(0,0)�ŉ�ʉE�������i��ʕ�(px), ��ʍ���(px))�ƂȂ���W�n��
//�v���~�e�B�u�i�|���j�̊�_�͍�����ɂȂ�܂��B
//--- VS ---
//�E���_�� -1 �` +1�։�������(�����ˉe�ϊ�)�AY���W���]
//--- PS ---
//�E�I�u�W�F�N�g�̃e�N�X�`��
//�E��������
//
//�y�ݒ�O���[�o���z
// float g_hAlpha			:	���l
// float g_transformedX		: 	�ϊ��ς�X���W(px)
// float g_transformedY		:	�ϊ��ς�Y���W(px)
// float g_depthZ			:	�[�xZ (0 �` +1)
// float g_game_buffer_width		:	��ʕ�(px)
// float g_game_buffer_height		:	��ʍ���(px)
// float g_offsetU			:	�e�N�X�`��U���W����
// float g_offsetV			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique DefaultBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoard();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}