////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����p�A�{�[�h�W���V�F�[�_�[
//
// Auther:Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_alpha; //��
float g_offsetU; //�e�N�X�`��U���W����
float g_offsetV; //�e�N�X�`��V���W����
float g_view_width_half ; //��ʕ��̔���
float g_view_height_half ; //��ʍ����̔���
float g_x; //X���W
float g_y; //Y���W

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//�{�[�h�W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultBoard(
      float4 prm_pos    : POSITION,     // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
    //World�ϊ��͍s�Ȃ�Ȃ��B
	//View�ϊ��͒P�ʍs��i�������j
	//�����Đ��ˉe�ϊ�
    out_vs.pos.x = (prm_pos.x / g_view_width_half) - g_view_width_half;
	out_vs.pos.y = (-prm_pos.y / g_view_height_half) + g_view_width_half;
	out_vs.pos.w = 1.0;
	//UV�̃I�t�Z�b�g�����Z
	out_vs.uv.x = prm_uv.x + 0.2;//g_offsetU;
	out_vs.uv.y = prm_uv.y + 0;//g_offsetV;

	return out_vs;
}


//�{�[�h�W���s�N�Z���V�F�[�_�[
float4 GgafDx9PS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//���v�Z�A�e�N�X�`�����ƈ������̍��Z
	out_color.a = g_alpha * out_color.a ; 
	return out_color;
}


technique DefaultBoardTechnique
{
	//pass P0�u�{�[�h�W���V�F�[�_�[�v
	//D3DFVF_XYZRHW �ŕ`�悵���悤�Ȏd�l�łQ�c�\�����܂��B
	//��ʍ������(0,0)�ŉ�ʉE�������i��ʕ�(px), ��ʍ���(px))�ƂȂ���W�n��
	//�v���~�e�B�u�̊�_�͔|��������ɂȂ�܂��B
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//--- PS ---
	//�E�I�u�W�F�N�g�̃e�N�X�`��
	//�E���������i���p�����[�^�ƃe�N�X�`�����̏�Z�j
	//�y�g�p�����z
	//�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
	//�y�ݒ�p�����[�^�z
	// float g_hAlpha			:	���l
	// float g_view_width_half	:	��ʂ̕��̔���(px)
	// float g_view_height_half	:	��ʂ̍����̔���(px)
	// float g_offsetU			:	�e�N�X�`��U���W����
	// float g_offsetV			:	�e�N�X�`��V���W����
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoard();
	}
}


