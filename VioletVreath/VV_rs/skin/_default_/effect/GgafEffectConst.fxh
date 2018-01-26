#ifndef VS_VERSION
  #define VS_VERSION vs_3_0
#endif 

#ifndef PS_VERSION
  #define PS_VERSION ps_3_0
#endif 

#define FLUSH_COLOR float4(7.0, 7.0, 7.0, 7.0)
#define POWER_OF_LIGHT_AMBIENT (0.4f)

//レンダリングターゲットの横幅(px)
float g_dbd_offset_x;
//レンダリングターゲットの縦幅(px)
float g_dbd_offset_y;

//dot by dot 考慮
float4 adjustDotByDot(float4 pos) {
	pos.x += g_dbd_offset_x*pos.w;
	pos.y += g_dbd_offset_y*pos.w;
	return pos;
}