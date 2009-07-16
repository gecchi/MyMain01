////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9SpriteSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��


float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;

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

float g_alpha001;
float g_alpha002;
float g_alpha003;
float g_alpha004;
float g_alpha005;
float g_alpha006;
float g_alpha007;
float g_alpha008;

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�X�v���C�g�W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultSpriteSet(                              
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float  prm_index  : PSIZE ,    // ���f���̒��_�ԍ�
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV
) {
	OUT_VS out_vs = (OUT_VS)0;
	int cnt_vertec = (int)prm_index;
	//���_�v�Z
	float4x4 matWorld;
	float offsetU;
	float offsetV;
	float alpah;

	if (16 > cnt_vertec) {
		if (8 > cnt_vertec) {
			if (4 > cnt_vertec) {
				matWorld = g_matWorld001;
				offsetU  = g_offsetU001;
				offsetV  = g_offsetV001;
				alpah   = g_alpha001;
			} else {
				matWorld = g_matWorld002;
				offsetU  = g_offsetU002;
				offsetV  = g_offsetV002;
				alpah   = g_alpha002;
			}
		} else {
			if (12 > cnt_vertec) {
				matWorld = g_matWorld003;
				offsetU  = g_offsetU003;
				offsetV  = g_offsetV003;
				alpah   = g_alpha003;
			} else {
				matWorld = g_matWorld004;
				offsetU  = g_offsetU004;
				offsetV  = g_offsetV004;
				alpah   = g_alpha004;
			}
		}
	} else {
		if (24 > cnt_vertec) {
			if (20 > cnt_vertec) {
				matWorld = g_matWorld005;
				offsetU  = g_offsetU005;
				offsetV  = g_offsetV005;
				alpah   = g_alpha005;
			} else {
				matWorld = g_matWorld006;
				offsetU  = g_offsetU006;
				offsetV  = g_offsetV006;
				alpah   = g_alpha006;
			}
		} else { 
			if (28 > cnt_vertec) {
				matWorld = g_matWorld007;
				offsetU  = g_offsetU007;
				offsetV  = g_offsetV007;
				alpah   = g_alpha007;
			} else {
				matWorld = g_matWorld008;
				offsetU  = g_offsetU008;
				offsetV  = g_offsetV008;
				alpah   = g_alpha008;
			}
		}
	}


	//���_�v�Z
	float4 posWorld = mul( prm_pos, matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	//UV�̃I�t�Z�b�g(�p�^�[���ԍ��ɂ�鑝��)���Z
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = alpah;
	return out_vs;
}

//�X�v���C�g�W���s�N�Z���V�F�[�_�[
float4 GgafDx9PS_DefaultSpriteSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv);
	//���v�Z�A�e�N�X�`�����ƃI�u�W�F�N�g���̍��Z
	//out_color.a = out_color.a * prm_col.a; 
	return out_color;
}

//���e�N�j�b�N�FDefaultSpriteSetTechnique��
//�y�@�\�z
//GgafDx9SpriteSetModel�p�W���V�F�[�_�[
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
technique DefaultSpriteSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultSpriteSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultSpriteSet();
	}
}


