#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxMassBoardModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_game_buffer_width; //��ʕ�(px)
float g_game_buffer_height; //��ʍ���(px)
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;


//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float4 color            : COLOR0;
	float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxMassBoardModel�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultMassBoard(
      float4 prm_posModel_Local   : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,        // ���f���̒��_�̖@��(���g�p)
      float2 prm_uv               : TEXCOORD0,     // ���f���̒��_��UV

      float3 prm_pos              : TEXCOORD1,     // px_x, px_y, depth_z   
      float2 prm_loc              : TEXCOORD2,     // local_px_x, local_px_y
      float3 prm_sc               : TEXCOORD3,     // r_sx, r_sy, rad_rz
      float2 prm_offset_uv        : TEXCOORD4,     // offset_u, offset_v   
      float4 prm_color            : TEXCOORD5      // r, g, b, a 
) {
	OUT_VS out_vs = (OUT_VS)0;
	float px_x = prm_pos.x; //�ϊ��ς�X���W(px)
	float px_y = prm_pos.y; //�ϊ��ς�Y���W(px)
	float depthZ = prm_pos.z;  //�[�xZ (0 �` +1)
    float local_px_x = prm_loc.x; //���[�J��X���W�iX���W�̃I�t�Z�b�g�j
    float local_px_y = prm_loc.y; //���[�J��Y���W�iY���W�̃I�t�Z�b�g�j
    float r_sx = prm_sc.x;     //X�������g�嗦
    float r_sy = prm_sc.y;     //Y�������g�嗦
    float rad_rz = prm_sc.z;   //Z��]�p�x

    if (rad_rz == 0.0f) {
        //X���WY���W���� -1 �` +1 �ɉ������߂�B
        out_vs.posModel_Proj.x = - 1 + ( (2*( ((prm_posModel_Local.x + local_px_x)*r_sx) + px_x) - 1) / g_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( ((prm_posModel_Local.y + local_px_y)*r_sy) + px_y) - 1) / g_game_buffer_height);
    } else {
        //�g��k��
        const float lx = (prm_posModel_Local.x + local_px_x) * r_sx;
        const float ly = (prm_posModel_Local.y + local_px_y) * r_sy;
        //��] �� X���WY���W���� -1 �` +1 �ɉ������߂�B
        out_vs.posModel_Proj.x = - 1 + ( (2*( (lx * cos(rad_rz) - ly * sin(rad_rz))      + px_x) - 1) / g_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( (lx * sin(rad_rz) + ly * cos(rad_rz))      + px_y) - 1) / g_game_buffer_height);
    }
	out_vs.posModel_Proj.z = depthZ;
	out_vs.posModel_Proj.w = 1.0;
	//dot by dot�l��
	//out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + prm_offset_uv.x;
	out_vs.uv.y = prm_uv.y + prm_offset_uv.y;
	out_vs.color = prm_color;
	return out_vs;
}


//GgafDxMassBoardModel�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultMassBoard(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color  : COLOR0 
) : COLOR  {
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
//	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
//		colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
//	}          
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;                
	//���l��
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;

}

//���e�N�j�b�N�FDefaultMassBoardTechnique��
//�y�@�\�z
//GgafDxMassBoardModel�p�W���V�F�[�_�[
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
technique DefaultMassBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultMassBoard();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultMassBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
