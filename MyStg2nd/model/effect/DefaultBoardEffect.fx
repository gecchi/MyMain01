////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9BoardModel�p�V�F�[�_�[
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
float g_view_width; //��ʕ�(px)
float g_view_height; //��ʍ���(px)
float g_sx;
float g_sy;
float g_PowerBlink;   
float g_BlinkThreshold;

//s0���W�X�^�̃T���v�����g��(���Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDx9BoardModel�W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultBoard(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//X���WY���W���� -1 �` +1 �ɉ������߂�B
	out_vs.pos.x = - 1 + ((2*prm_pos.x*g_sx + 2*g_transformedX - 1) / g_view_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y*g_sy + 2*g_transformedY - 1) / g_view_height);
	out_vs.pos.z = g_depthZ;
	out_vs.pos.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;

	return out_vs;
}


float4 GgafDx9PS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
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
	//���l��
	out_color.a = out_color.a * g_alpha; 
	return out_color;
}



float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//���l��
	out_color.a = out_color.a * g_alpha; 
	return out_color * float4(7.0, 7.0, 7.0, 1.0);
}






//���e�N�j�b�N�FDefaultBoardTechnique��
//�y�@�\�z
//GgafDx9BoardModel�p�W���V�F�[�_�[
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
technique DefaultBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoard();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}