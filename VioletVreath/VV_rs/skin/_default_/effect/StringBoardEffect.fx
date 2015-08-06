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

float4 g_colMaterialDiffuse;  //�}�e���A���̐F

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

float g_depth_Z001;



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
OUT_VS GgafDxVS_StringBoard(
    float4 prm_posModel_Local : POSITION,     // ���f���̒��_
	float  prm_index          : PSIZE ,    // ���f���ԍ�
    float2 prm_uv             : TEXCOORD0     // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;
	const int index = (int)prm_index;
	float offsetU; //�e�N�X�`��U���W����
	float offsetV; //�e�N�X�`��V���W����
	float transformedX;
	if (index == 0) {
		transformedX = g_transformed_X001;
		offsetU  = g_offset_u001;
		offsetV  = g_offset_v001;
	} else if (index == 1) {
		transformedX = g_transformed_X002;
		offsetU  = g_offset_u002;
		offsetV  = g_offset_v002;
	} else if (index == 2) {
		transformedX = g_transformed_X003;
		offsetU  = g_offset_u003;
		offsetV  = g_offset_v003;
	} else if (index == 3) {
		transformedX = g_transformed_X004;
		offsetU  = g_offset_u004;
		offsetV  = g_offset_v004;
	} else if (index == 4) {
		transformedX = g_transformed_X005;
		offsetU  = g_offset_u005;
		offsetV  = g_offset_v005;
	} else if (index == 5) {
		transformedX = g_transformed_X006;
		offsetU  = g_offset_u006;
		offsetV  = g_offset_v006;
	} else if (index == 6) {	
		transformedX = g_transformed_X007;
		offsetU  = g_offset_u007;
		offsetV  = g_offset_v007;
	} else if (index == 7) {	
		transformedX = g_transformed_X008;
		offsetU  = g_offset_u008;
		offsetV  = g_offset_v008;
	} else if (index == 8) {	
		transformedX = g_transformed_X009;
		offsetU  = g_offset_u009;
		offsetV  = g_offset_v009;
	} else if (index == 9) {	
		transformedX = g_transformed_X010;
		offsetU  = g_offset_u010;
		offsetV  = g_offset_v010;
	} else if (index == 10) {	
		transformedX = g_transformed_X011;
		offsetU  = g_offset_u011;
		offsetV  = g_offset_v011;
	} else if (index == 11) {	
		transformedX = g_transformed_X012;
		offsetU  = g_offset_u012;
		offsetV  = g_offset_v012;
	} else if (index == 12) {	
		transformedX = g_transformed_X013;
		offsetU  = g_offset_u013;
		offsetV  = g_offset_v013;
	} else if (index == 13) {	
		transformedX = g_transformed_X014;
		offsetU  = g_offset_u014;
		offsetV  = g_offset_v014;
	} else if (index == 14) {	
		transformedX = g_transformed_X015;
		offsetU  = g_offset_u015;
		offsetV  = g_offset_v015;
	} else if (index == 15) {	
		transformedX = g_transformed_X016;
		offsetU  = g_offset_u016;
		offsetV  = g_offset_v016;
	} else if (index == 16) {	
		transformedX = g_transformed_X017;
		offsetU  = g_offset_u017;
		offsetV  = g_offset_v017;
	} else if (index == 17) {	
		transformedX = g_transformed_X018;
		offsetU  = g_offset_u018;
		offsetV  = g_offset_v018;
	} else if (index == 18) {	
		transformedX = g_transformed_X019;
		offsetU  = g_offset_u019;
		offsetV  = g_offset_v019;
	} else if (index == 19) {	
		transformedX = g_transformed_X020;
		offsetU  = g_offset_u020;
		offsetV  = g_offset_v020;
	} else if (index == 20) {	
		transformedX = g_transformed_X021;
		offsetU  = g_offset_u021;
		offsetV  = g_offset_v021;
	} else if (index == 21) {	
		transformedX = g_transformed_X022;
		offsetU  = g_offset_u022;
		offsetV  = g_offset_v022;
	} else if (index == 22) {	
		transformedX = g_transformed_X023;
		offsetU  = g_offset_u023;
		offsetV  = g_offset_v023;
	} else if (index == 23) {	
		transformedX = g_transformed_X024;
		offsetU  = g_offset_u024;
		offsetV  = g_offset_v024;
	} else if (index == 24) {	
		transformedX = g_transformed_X025;
		offsetU  = g_offset_u025;
		offsetV  = g_offset_v025;
	} else if (index == 25) {	
		transformedX = g_transformed_X026;
		offsetU  = g_offset_u026;
		offsetV  = g_offset_v026;
	} else if (index == 26) {	
		transformedX = g_transformed_X027;
		offsetU  = g_offset_u027;
		offsetV  = g_offset_v027;
	} else {	
		transformedX = g_transformed_X028;
		offsetU  = g_offset_u028;
		offsetV  = g_offset_v028;
	} 

	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.posModel_Proj.x = - 1 + ((2*prm_posModel_Local.x + 2*transformedX - 1) / g_game_buffer_width);
	out_vs.posModel_Proj.y =   1 - ((2*prm_posModel_Local.y + 2*g_transformed_Y001 - 1) / g_game_buffer_height);
	out_vs.posModel_Proj.z = g_depth_Z001;
	out_vs.posModel_Proj.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color  = g_colMaterialDiffuse;
	return out_vs;
}


//GgafDxBoardSetModel�W���s�N�Z���V�F�[�_�[
float4 GgafDxPS_StringBoard(
	float2 prm_uv	 : TEXCOORD0,
	float4 prm_color : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	const float4 colTex = tex2D( MyTextureSampler, prm_uv); 
	//���߂�F
	float4 colOut = colTex * prm_color; 
	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	}        
	colOut.a *= g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;                
	//���l��
	colOut.a *= g_alpha_master; 
	return colOut;
}


//���e�N�j�b�N�FStringBoardTechnique��
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
technique StringBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_StringBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_StringBoard();
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
		VertexShader = compile VS_VERSION GgafDxVS_StringBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_StringBoard();
	}
}

technique Flush
{
	pass P0 {
        //SeparateAlphaBlendEnable = true;
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_StringBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

