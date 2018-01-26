#ifndef VS_VERSION
  #define VS_VERSION vs_3_0
#endif 

#ifndef PS_VERSION
  #define PS_VERSION ps_3_0
#endif 

#define FLUSH_COLOR float4(7.0, 7.0, 7.0, 7.0)
#define POWER_OF_LIGHT_AMBIENT (0.4f)

//�����_�����O�^�[�Q�b�g�̉���(px)
float g_dbd_offset_x;
//�����_�����O�^�[�Q�b�g�̏c��(px)
float g_dbd_offset_y;

//dot by dot �l��
float4 adjustDotByDot(float4 pos) {
	pos.x += g_dbd_offset_x*pos.w;
	pos.y += g_dbd_offset_y*pos.w;
	return pos;
}