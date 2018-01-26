#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDxBoardSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_game_buffer_width; //��ʕ�(px)
float g_game_buffer_height; //��ʍ���(px)
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
//float g_offset_u; //�e�N�X�`��U���W����
//float g_offset_v; //�e�N�X�`��V���W����
//float g_transformed_x; //�ϊ��ς�X���W(px)
//float g_transformed_y; //�ϊ��ς�Y���W(px)
//float g_depth_z; //�[�xZ (0 �` +1)
//float g_alpha; //��
//

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
float g_offset_u019;
float g_offset_u020;
float g_offset_u021;
float g_offset_u022;
float g_offset_u023;
float g_offset_u024;
float g_offset_u025;
float g_offset_u026;
float g_offset_u027;
float g_offset_u028;

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
float g_offset_v019;
float g_offset_v020;
float g_offset_v021;
float g_offset_v022;
float g_offset_v023;
float g_offset_v024;
float g_offset_v025;
float g_offset_v026;
float g_offset_v027;
float g_offset_v028;

float g_transformed_X001;
float g_transformed_X002;
float g_transformed_X003;
float g_transformed_X004;
float g_transformed_X005;
float g_transformed_X006;
float g_transformed_X007;
float g_transformed_X008;
float g_transformed_X009;
float g_transformed_X010;
float g_transformed_X011;
float g_transformed_X012;
float g_transformed_X013;
float g_transformed_X014;
float g_transformed_X015;
float g_transformed_X016;
float g_transformed_X017;
float g_transformed_X018;
float g_transformed_X019;
float g_transformed_X020;
float g_transformed_X021;
float g_transformed_X022;
float g_transformed_X023;
float g_transformed_X024;
float g_transformed_X025;
float g_transformed_X026;
float g_transformed_X027;
float g_transformed_X028;

float g_transformed_Y001;
float g_transformed_Y002;
float g_transformed_Y003;
float g_transformed_Y004;
float g_transformed_Y005;
float g_transformed_Y006;
float g_transformed_Y007;
float g_transformed_Y008;
float g_transformed_Y009;
float g_transformed_Y010;
float g_transformed_Y011;
float g_transformed_Y012;
float g_transformed_Y013;
float g_transformed_Y014;
float g_transformed_Y015;
float g_transformed_Y016;
float g_transformed_Y017;
float g_transformed_Y018;
float g_transformed_Y019;
float g_transformed_Y020;
float g_transformed_Y021;
float g_transformed_Y022;
float g_transformed_Y023;
float g_transformed_Y024;
float g_transformed_Y025;
float g_transformed_Y026;
float g_transformed_Y027;
float g_transformed_Y028;

float g_depth_Z001;
float g_depth_Z002;
float g_depth_Z003;
float g_depth_Z004;
float g_depth_Z005;
float g_depth_Z006;
float g_depth_Z007;
float g_depth_Z008;
float g_depth_Z009;
float g_depth_Z010;
float g_depth_Z011;
float g_depth_Z012;
float g_depth_Z013;
float g_depth_Z014;
float g_depth_Z015;
float g_depth_Z016;
float g_depth_Z017;
float g_depth_Z018;
float g_depth_Z019;
float g_depth_Z020;
float g_depth_Z021;
float g_depth_Z022;
float g_depth_Z023;
float g_depth_Z024;
float g_depth_Z025;
float g_depth_Z026;
float g_depth_Z027;
float g_depth_Z028;

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
float g_alpha019;
float g_alpha020;
float g_alpha021;
float g_alpha022;
float g_alpha023;
float g_alpha024;
float g_alpha025;
float g_alpha026;
float g_alpha027;
float g_alpha028;

//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float4 color    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxBoardSetModel�W�����_�V�F�[�_�[
OUT_VS GgafDxVS_DefaultBoardSet(
      float4 prm_posModel_Local    : POSITION,     // ���f���̒��_
	  float  prm_index  : PSIZE ,    // ���f���ԍ�
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	const int index = (int)prm_index;
	float offsetU; //�e�N�X�`��U���W����
	float offsetV; //�e�N�X�`��V���W����
	float transformedX; //�ϊ��ς�X���W(px)
	float transformedY; //�ϊ��ς�Y���W(px)
	float depthZ; //�[�xZ (0 �` +1)
	float alpha; //��

	if (index == 0) {
		transformedX = g_transformed_X001;
		transformedY = g_transformed_Y001;
		depthZ = g_depth_Z001;
		offsetU = g_offset_u001;
		offsetV = g_offset_v001;
		alpha = g_alpha001;
	} else if (index == 1) {
		transformedX = g_transformed_X002;
		transformedY = g_transformed_Y002;
		depthZ = g_depth_Z002;
		offsetU = g_offset_u002;
		offsetV = g_offset_v002;
		alpha = g_alpha002;
	} else if (index == 2) {
		transformedX = g_transformed_X003;
		transformedY = g_transformed_Y003;
		depthZ = g_depth_Z003;
		offsetU = g_offset_u003;
		offsetV = g_offset_v003;
		alpha = g_alpha003;
	} else if (index == 3) {
		transformedX = g_transformed_X004;
		transformedY = g_transformed_Y004;
		depthZ = g_depth_Z004;
		offsetU = g_offset_u004;
		offsetV = g_offset_v004;
		alpha = g_alpha004;
	} else if (index == 4) {
		transformedX = g_transformed_X005;
		transformedY = g_transformed_Y005;
		depthZ = g_depth_Z005;
		offsetU = g_offset_u005;
		offsetV = g_offset_v005;
		alpha = g_alpha005;
	} else if (index == 5) {
		transformedX = g_transformed_X006;
		transformedY = g_transformed_Y006;
		depthZ = g_depth_Z006;
		offsetU = g_offset_u006;
		offsetV = g_offset_v006;
		alpha = g_alpha006;
	} else if (index == 6) {	
		transformedX = g_transformed_X007;
		transformedY = g_transformed_Y007;
		depthZ = g_depth_Z007;
		offsetU = g_offset_u007;
		offsetV = g_offset_v007;
		alpha = g_alpha007;
	} else if (index == 7) {	
		transformedX = g_transformed_X008;
		transformedY = g_transformed_Y008;
		depthZ = g_depth_Z008;
		offsetU = g_offset_u008;
		offsetV = g_offset_v008;
		alpha = g_alpha008;
	} else if (index == 8) {	
		transformedX = g_transformed_X009;
		transformedY = g_transformed_Y009;
		depthZ = g_depth_Z009;
		offsetU = g_offset_u009;
		offsetV = g_offset_v009;
		alpha = g_alpha009;
	} else if (index == 9) {	
		transformedX = g_transformed_X010;
		transformedY = g_transformed_Y010;
		depthZ = g_depth_Z010;
		offsetU = g_offset_u010;
		offsetV = g_offset_v010;
		alpha = g_alpha010;
	} else if (index == 10) {	
		transformedX = g_transformed_X011;
		transformedY = g_transformed_Y011;
		depthZ = g_depth_Z011;
		offsetU = g_offset_u011;
		offsetV = g_offset_v011;
		alpha = g_alpha011;
	} else if (index == 11) {	
		transformedX = g_transformed_X012;
		transformedY = g_transformed_Y012;
		depthZ = g_depth_Z012;
		offsetU = g_offset_u012;
		offsetV = g_offset_v012;
		alpha = g_alpha012;
	} else if (index == 12) {	
		transformedX = g_transformed_X013;
		transformedY = g_transformed_Y013;
		depthZ = g_depth_Z013;
		offsetU = g_offset_u013;
		offsetV = g_offset_v013;
		alpha = g_alpha013;
	} else if (index == 13) {	
		transformedX = g_transformed_X014;
		transformedY = g_transformed_Y014;
		depthZ = g_depth_Z014;
		offsetU = g_offset_u014;
		offsetV = g_offset_v014;
		alpha = g_alpha014;
	} else if (index == 14) {	
		transformedX = g_transformed_X015;
		transformedY = g_transformed_Y015;
		depthZ = g_depth_Z015;
		offsetU = g_offset_u015;
		offsetV = g_offset_v015;
		alpha = g_alpha015;
	} else if (index == 15) {	
		transformedX = g_transformed_X016;
		transformedY = g_transformed_Y016;
		depthZ = g_depth_Z016;
		offsetU = g_offset_u016;
		offsetV = g_offset_v016;
		alpha = g_alpha016;
	} else if (index == 16) {	
		transformedX = g_transformed_X017;
		transformedY = g_transformed_Y017;
		depthZ = g_depth_Z017;
		offsetU = g_offset_u017;
		offsetV = g_offset_v017;
		alpha = g_alpha017;
	} else if (index == 17) {	
		transformedX = g_transformed_X018;
		transformedY = g_transformed_Y018;
		depthZ = g_depth_Z018;
		offsetU = g_offset_u018;
		offsetV = g_offset_v018;
		alpha = g_alpha018;
	} else if (index == 18) {	
		transformedX = g_transformed_X019;
		transformedY = g_transformed_Y019;
		depthZ = g_depth_Z019;
		offsetU = g_offset_u019;
		offsetV = g_offset_v019;
		alpha = g_alpha019;
	} else if (index == 19) {	
		transformedX = g_transformed_X020;
		transformedY = g_transformed_Y020;
		depthZ = g_depth_Z020;
		offsetU = g_offset_u020;
		offsetV = g_offset_v020;
		alpha = g_alpha020;
	} else if (index == 20) {	
		transformedX = g_transformed_X021;
		transformedY = g_transformed_Y021;
		depthZ = g_depth_Z021;
		offsetU = g_offset_u021;
		offsetV = g_offset_v021;
		alpha = g_alpha021;
	} else if (index == 21) {	
		transformedX = g_transformed_X022;
		transformedY = g_transformed_Y022;
		depthZ = g_depth_Z022;
		offsetU = g_offset_u022;
		offsetV = g_offset_v022;
		alpha = g_alpha022;
	} else if (index == 22) {	
		transformedX = g_transformed_X023;
		transformedY = g_transformed_Y023;
		depthZ = g_depth_Z023;
		offsetU = g_offset_u023;
		offsetV = g_offset_v023;
		alpha = g_alpha023;
	} else if (index == 23) {	
		transformedX = g_transformed_X024;
		transformedY = g_transformed_Y024;
		depthZ = g_depth_Z024;
		offsetU = g_offset_u024;
		offsetV = g_offset_v024;
		alpha = g_alpha024;
	} else if (index == 24) {	
		transformedX = g_transformed_X025;
		transformedY = g_transformed_Y025;
		depthZ = g_depth_Z025;
		offsetU = g_offset_u025;
		offsetV = g_offset_v025;
		alpha = g_alpha025;
	} else if (index == 25) {	
		transformedX = g_transformed_X026;
		transformedY = g_transformed_Y026;
		depthZ = g_depth_Z026;
		offsetU = g_offset_u026;
		offsetV = g_offset_v026;
		alpha = g_alpha026;
	} else if (index == 26) {	
		transformedX = g_transformed_X027;
		transformedY = g_transformed_Y027;
		depthZ = g_depth_Z027;
		offsetU = g_offset_u027;
		offsetV = g_offset_v027;
		alpha = g_alpha027;
	} else {	
		transformedX = g_transformed_X028;
		transformedY = g_transformed_Y028;
		depthZ = g_depth_Z028;
		offsetU = g_offset_u028;
		offsetV = g_offset_v028;
		alpha = g_alpha028;
	} 

	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.posModel_Proj.x = - 1 + ((2*prm_posModel_Local.x + 2*transformedX - 1) / g_game_buffer_width);
	out_vs.posModel_Proj.y =   1 - ((2*prm_posModel_Local.y + 2*transformedY - 1) / g_game_buffer_height);
	out_vs.posModel_Proj.z = depthZ;
	out_vs.posModel_Proj.w = 1.0;
	//dot by dot�l��
	//out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color = alpha;
	return out_vs;
}


//GgafDxBoardSetModel�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_DefaultBoardSet(
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


//���e�N�j�b�N�FDefaultBoardSetTechnique��
//�y�@�\�z
//GgafDxBoardSetModel�p�W���V�F�[�_�[
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
technique DefaultBoardSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoardSet();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoardSet();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
