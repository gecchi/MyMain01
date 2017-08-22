#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxEnclosedBoardModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2017/08/21
////////////////////////////////////////////////////////////////////////////////
float g_game_buffer_width; //��ʕ�(px)
float g_game_buffer_height; //��ʍ���(px)
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;


float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;


float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;



                                                         
float g_unit_width;
float g_unit_height;

float g_top_edge_size_rate;
float g_center_height_rate;
float g_bottom_edge_size_rate;

float g_left_edge_size_rate;
float g_center_width_rate;
float g_right_edge_size_rate;

float g_alpha;
    
float g_x;
float g_y;
float g_z;
float g_rz;                         

float g_local_offset_x;
float g_local_offset_y;
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

//GgafDxEnclosedBoardModel�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultEnclosedBoard(
      float4 prm_posModel_Local    : POSITION,     // ���f���̒��_
	  float  prm_index             : PSIZE ,       // ���f���ԍ�
      float2 prm_uv                : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	const int index = (int)prm_index;
	float offsetU; //�e�N�X�`��U���W����
	float offsetV; //�e�N�X�`��V���W����
	float x; //�ϊ��ς�X���W(px)
	float y; //�ϊ��ς�Y���W(px)
	float depthZ; //�[�xZ (0 �` +1)
	float alpha; //��
                            
    //    ��������������
    //    ���O���P���Q��
    //    ��������������
    //    ���R���S���T��
    //    ��������������
    //    ���U���V���W��
    //    ��������������
	if (index == 0) {
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u001;
		offsetV = g_offset_v001;
	} else if (index == 1) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u002;
		offsetV = g_offset_v002;
	} else if (index == 2) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u003;
		offsetV = g_offset_v003;
	} else if (index == 3) {
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u004;
		offsetV = g_offset_v004;
	} else if (index == 4) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u005;
		offsetV = g_offset_v005;
	} else if (index == 5) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u006;
		offsetV = g_offset_v006;
	} else if (index == 6) {	
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u007;
		offsetV = g_offset_v007;
	} else if (index == 7) {	
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u008;
		offsetV = g_offset_v008;
	} else if (index == 8) {	
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u009;
		offsetV = g_offset_v009;

	}
	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.posModel_Proj.x = - 1 + ((2*x + 2*g_local_offset_x - 1) / g_game_buffer_width);
	out_vs.posModel_Proj.y =   1 - ((2*y + 2*g_local_offset_y - 1) / g_game_buffer_height);
	out_vs.posModel_Proj.z = g_z;
	out_vs.posModel_Proj.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color.a = g_alpha;
	return out_vs;
}


//GgafDxEnclosedBoardModel�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultEnclosedBoard(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//���߂�F
	float4 colOut = tex2D( MyTextureSampler, prm_uv); 
	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
	}          
	//���l��
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;                
	//���l��
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}


//���e�N�j�b�N�FDefaultEnclosedBoardTechnique��
//�y�@�\�z
//GgafDxEnclosedBoardModel�p�W���V�F�[�_�[
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
// float g_alpha			:	���l
// float g_transformed_x		: 	�ϊ��ς�X���W(px)
// float g_transformed_y		:	�ϊ��ς�Y���W(px)
// float g_depth_z			:	�[�xZ (0 �` +1)
// float g_game_buffer_width		:	��ʕ�(px)
// float g_game_buffer_height		:	��ʍ���(px)
// float g_offset_u			:	�e�N�X�`��U���W����
// float g_offset_v			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique DefaultEnclosedBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultEnclosedBoard();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultEnclosedBoard();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
