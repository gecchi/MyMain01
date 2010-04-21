////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9BoardSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_view_width; //��ʕ�(px)
float g_view_height; //��ʍ���(px)
float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;

//float g_offsetU; //�e�N�X�`��U���W����
//float g_offsetV; //�e�N�X�`��V���W����
//float g_transformedX; //�ϊ��ς�X���W(px)
//float g_transformedY; //�ϊ��ς�Y���W(px)
//float g_depthZ; //�[�xZ (0 �` +1)
//float g_alpha; //��
//

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
float g_offsetU019;
float g_offsetU020;
float g_offsetU021;
float g_offsetU022;
float g_offsetU023;
float g_offsetU024;
float g_offsetU025;
float g_offsetU026;
float g_offsetU027;
float g_offsetU028;

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
float g_offsetV019;
float g_offsetV020;
float g_offsetV021;
float g_offsetV022;
float g_offsetV023;
float g_offsetV024;
float g_offsetV025;
float g_offsetV026;
float g_offsetV027;
float g_offsetV028;

float g_transformedX001;
float g_transformedX002;
float g_transformedX003;
float g_transformedX004;
float g_transformedX005;
float g_transformedX006;
float g_transformedX007;
float g_transformedX008;
float g_transformedX009;
float g_transformedX010;
float g_transformedX011;
float g_transformedX012;
float g_transformedX013;
float g_transformedX014;
float g_transformedX015;
float g_transformedX016;
float g_transformedX017;
float g_transformedX018;
float g_transformedX019;
float g_transformedX020;
float g_transformedX021;
float g_transformedX022;
float g_transformedX023;
float g_transformedX024;
float g_transformedX025;
float g_transformedX026;
float g_transformedX027;
float g_transformedX028;

float g_transformedY001;

float g_depthZ001;

float g_alpha001;


//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDx9BoardSetModel�W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_StringBoard(
      float4 prm_pos    : POSITION,     // ���f���̒��_
	  float  prm_index  : PSIZE ,    // ���f���ԍ�
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	float offsetU; //�e�N�X�`��U���W����
	float offsetV; //�e�N�X�`��V���W����
	float transformedX;
	if (index == 0) {
		transformedX = g_transformedX001;
		offsetU  = g_offsetU001;
		offsetV  = g_offsetV001;
	} else if (index == 1) {
		transformedX = g_transformedX002;
		offsetU  = g_offsetU002;
		offsetV  = g_offsetV002;
	} else if (index == 2) {
		transformedX = g_transformedX003;
		offsetU  = g_offsetU003;
		offsetV  = g_offsetV003;
	} else if (index == 3) {
		transformedX = g_transformedX004;
		offsetU  = g_offsetU004;
		offsetV  = g_offsetV004;
	} else if (index == 4) {
		transformedX = g_transformedX005;
		offsetU  = g_offsetU005;
		offsetV  = g_offsetV005;
	} else if (index == 5) {
		transformedX = g_transformedX006;
		offsetU  = g_offsetU006;
		offsetV  = g_offsetV006;
	} else if (index == 6) {	
		transformedX = g_transformedX007;
		offsetU  = g_offsetU007;
		offsetV  = g_offsetV007;
	} else if (index == 7) {	
		transformedX = g_transformedX008;
		offsetU  = g_offsetU008;
		offsetV  = g_offsetV008;
	} else if (index == 8) {	
		transformedX = g_transformedX009;
		offsetU  = g_offsetU009;
		offsetV  = g_offsetV009;
	} else if (index == 9) {	
		transformedX = g_transformedX010;
		offsetU  = g_offsetU010;
		offsetV  = g_offsetV010;
	} else if (index == 10) {	
		transformedX = g_transformedX011;
		offsetU  = g_offsetU011;
		offsetV  = g_offsetV011;
	} else if (index == 11) {	
		transformedX = g_transformedX012;
		offsetU  = g_offsetU012;
		offsetV  = g_offsetV012;
	} else if (index == 12) {	
		transformedX = g_transformedX013;
		offsetU  = g_offsetU013;
		offsetV  = g_offsetV013;
	} else if (index == 13) {	
		transformedX = g_transformedX014;
		offsetU  = g_offsetU014;
		offsetV  = g_offsetV014;
	} else if (index == 14) {	
		transformedX = g_transformedX015;
		offsetU  = g_offsetU015;
		offsetV  = g_offsetV015;
	} else if (index == 15) {	
		transformedX = g_transformedX016;
		offsetU  = g_offsetU016;
		offsetV  = g_offsetV016;
	} else if (index == 16) {	
		transformedX = g_transformedX017;
		offsetU  = g_offsetU017;
		offsetV  = g_offsetV017;
	} else if (index == 17) {	
		transformedX = g_transformedX018;
		offsetU  = g_offsetU018;
		offsetV  = g_offsetV018;
	} else if (index == 18) {	
		transformedX = g_transformedX019;
		offsetU  = g_offsetU019;
		offsetV  = g_offsetV019;
	} else if (index == 19) {	
		transformedX = g_transformedX020;
		offsetU  = g_offsetU020;
		offsetV  = g_offsetV020;
	} else if (index == 20) {	
		transformedX = g_transformedX021;
		offsetU  = g_offsetU021;
		offsetV  = g_offsetV021;
	} else if (index == 21) {	
		transformedX = g_transformedX022;
		offsetU  = g_offsetU022;
		offsetV  = g_offsetV022;
	} else if (index == 22) {	
		transformedX = g_transformedX023;
		offsetU  = g_offsetU023;
		offsetV  = g_offsetV023;
	} else if (index == 23) {	
		transformedX = g_transformedX024;
		offsetU  = g_offsetU024;
		offsetV  = g_offsetV024;
	} else if (index == 24) {	
		transformedX = g_transformedX025;
		offsetU  = g_offsetU025;
		offsetV  = g_offsetV025;
	} else if (index == 25) {	
		transformedX = g_transformedX026;
		offsetU  = g_offsetU026;
		offsetV  = g_offsetV026;
	} else if (index == 26) {	
		transformedX = g_transformedX027;
		offsetU  = g_offsetU027;
		offsetV  = g_offsetV027;
	} else {	
		transformedX = g_transformedX028;
		offsetU  = g_offsetU028;
		offsetV  = g_offsetV028;
	} 

	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.pos.x = - 1 + ((2*prm_pos.x + 2*transformedX - 1) / g_view_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y + 2*g_transformedY001 - 1) / g_view_height);
	out_vs.pos.z = g_depthZ001;
	out_vs.pos.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = g_alpha001;
	return out_vs;
}


//GgafDx9BoardSetModel�W���s�N�Z���V�F�[�_�[
float4 GgafDx9PS_StringBoard(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//���߂�F
	float4 out_color; 
	if (tex_color.r >= g_BlinkThreshold || tex_color.g >= g_BlinkThreshold || tex_color.b >= g_BlinkThreshold) {
		out_color = tex_color * g_PowerBlink; //+ (tex_color * g_PowerBlink);
	} else {
		out_color = tex_color;
	}               
	out_color.a = out_color.a * prm_col.a * g_MasterAlpha; 
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * float4(7.0, 7.0, 7.0, 1.0);                
	//���l��
	out_color.a = out_color.a * prm_col.a * g_MasterAlpha; 
	return out_color;
}


//���e�N�j�b�N�FStringBoardTechnique��
//�y�@�\�z
//GgafDx9BoardSetModel�p�W���V�F�[�_�[
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
// float g_view_width		:	��ʕ�(px)
// float g_view_height		:	��ʍ���(px)
// float g_offsetU			:	�e�N�X�`��U���W����
// float g_offsetV			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique StringBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_StringBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_StringBoard();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_StringBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_StringBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_StringBoard();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

