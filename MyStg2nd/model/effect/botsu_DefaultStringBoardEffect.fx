////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9BoardSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_view_width; //��ʕ�(px)
float g_view_height; //��ʍ���(px)

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

float g_offsetV001;
float g_offsetV002;
float g_offsetV003;
float g_offsetV004;
float g_offsetV005;
float g_offsetV006;
float g_offsetV007;
float g_offsetV008;
uint string001

float g_transformedX;
float g_transformedY;
float g_depthZ;
float g_alpha;


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
OUT_VS GgafDx9VS_DefaultBoardSet(
      float4 prm_pos    : POSITION,     // ���f���̒��_
	  float  prm_index  : PSIZE ,    // ���f���ԍ�
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	float offsetU; //�e�N�X�`��U���W����
	float offsetV; //�e�N�X�`��V���W����
	float transformedX; //�ϊ��ς�X���W(px)
	float transformedY; //�ϊ��ς�Y���W(px)
	float depthZ; //�[�xZ (0 �` +1)
	float alpha; //��

	if (index == 0) {
		transformedX = g_transformedX001;
		transformedY = g_transformedY001;
		depthZ = g_depthZ001;

		offsetU  = g_offsetU001;
		offsetV  = g_offsetV001;
		alpha   = g_alpha001;
	} else if (index == 1) {
		transformedX = g_transformedX002;
		transformedY = g_transformedY002;
		depthZ = g_depthZ002;
		offsetU  = g_offsetU002;
		offsetV  = g_offsetV002;
		alpha   = g_alpha002;
	} else if (index == 2) {
		transformedX = g_transformedX003;
		transformedY = g_transformedY003;
		depthZ = g_depthZ003;
		offsetU  = g_offsetU003;
		offsetV  = g_offsetV003;
		alpha   = g_alpha003;
	} else if (index == 3) {
		transformedX = g_transformedX004;
		transformedY = g_transformedY004;
		depthZ = g_depthZ004;
		offsetU  = g_offsetU004;
		offsetV  = g_offsetV004;
		alpha   = g_alpha004;
	} else if (index == 4) {
		transformedX = g_transformedX005;
		transformedY = g_transformedY005;
		depthZ = g_depthZ005;
		offsetU  = g_offsetU005;
		offsetV  = g_offsetV005;
		alpha   = g_alpha005;
	} else if (index == 5) {
		transformedX = g_transformedX006;
		transformedY = g_transformedY006;
		depthZ = g_depthZ006;
		offsetU  = g_offsetU006;
		offsetV  = g_offsetV006;
		alpha   = g_alpha006;
	} else if (index == 6) {
		transformedX = g_transformedX007;
		transformedY = g_transformedY007;
		depthZ = g_depthZ007;
		offsetU  = g_offsetU007;
		offsetV  = g_offsetV007;
		alpha   = g_alpha007;
	} else {
		transformedX = g_transformedX008;
		transformedY = g_transformedY008;
		depthZ = g_depthZ008;
		offsetU  = g_offsetU008;
		offsetV  = g_offsetV008;
		alpha   = g_alpha008;
	}






	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.pos.x = - 1 + ((2*prm_pos.x + 2*transformedX - 1) / g_view_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y + 2*transformedY - 1) / g_view_height);
	//out_vs.pos.x = - 1 + 2 * ((prm_pos.x + g_transformedX- 0.5) / g_view_width);
	//out_vs.pos.y =   1 - 2 * ((prm_pos.y + g_transformedY- 0.5) / g_view_height);
//	out_vs.pos.x = (2 * prm_pos.x  / g_view_width ) - 1 + (2 * g_transformedX / g_view_width);
//	out_vs.pos.y = (2 * -prm_pos.y / g_view_height) + 1 - (2 * g_transformedY / g_view_height);
	out_vs.pos.z = depthZ;
	out_vs.pos.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = alpha;
	return out_vs;
}


//GgafDx9BoardSetModel�W���s�N�Z���V�F�[�_�[
float4 GgafDx9PS_DefaultBoardSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//���l��
	out_color.a = out_color.a * prm_col.a; 
	return out_color;
}



//���e�N�j�b�N�FDefaultBoardSetTechnique��
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
technique DefaultBoardSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoardSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoardSet();
	}
}


