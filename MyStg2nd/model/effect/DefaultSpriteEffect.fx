////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9SpriteModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
float g_hAlpha; //��
float g_offsetU; //�e�N�X�`��U���W����
float g_offsetV; //�e�N�X�`��V���W����

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
OUT_VS GgafDx9VS_DefaultSprite(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	//UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;
	return out_vs;
}

//�r���{�[�h���_�V�F�[�_�[
OUT_VS GgafDx9VS_BillBoardSprite(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;
	return out_vs;
}


//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 GgafDx9PS_DefaultSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv);
	//���v�Z�A�e�N�X�`�����ƈ������̍��Z
	out_color.a = g_hAlpha * out_color.a ; 
	return out_color;
}

//���e�N�j�b�N�FDefaultSpriteTechnique��
//�y�@�\�z
//GgafDx9SpriteModel�p�W���V�F�[�_�[
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
// float g_hAlpha			:	���l
// float g_offsetU			:	�e�N�X�`��U���W����
// float g_offsetV			:	�e�N�X�`��V���W����
// s0���W�X�^				:	2D�e�N�X�`��
technique DefaultSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultSprite();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultSprite();
	}
}


