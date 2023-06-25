#ifndef VS_VERSION
  #define VS_VERSION vs_3_0
#endif

#ifndef PS_VERSION
  #define PS_VERSION ps_3_0
#endif

#define FLUSH_COLOR float4(7.0, 7.0, 7.0, 7.0)

/** �A���t�@�J�[�e��(�t�F�[�h�C���E�A�E�g)�@�\(GgafDx::AlphaCurtain�Q��)�̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;


float4 getBlinkColor(float4 prm_colOut  : COLOR, 
                     float4 prm_colTex  : COLOR
) : COLOR {
	if (prm_colTex.r >= 0.4 || prm_colTex.g >= 0.4  || prm_colTex.b >= 0.4 ) {
		return (prm_colOut *= g_tex_blink_power); //�����ă����{�����|����B�_�ł�ڗ�������B);
	} else {
		return prm_colOut; //�_�łȂ�
	}
}

float4 getBlinkColor(float4 prm_colTex  : COLOR) : COLOR {
	if (prm_colTex.r >= 0.4 || prm_colTex.g >= 0.4  || prm_colTex.b >= 0.4 ) {
		return (prm_colTex *= g_tex_blink_power); //�����ă����{�����|����B�_�ł�ڗ�������B);
	} else {
		return prm_colTex; //�_�łȂ�
	}
}

