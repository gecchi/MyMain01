#ifndef VS_VERSION
  #define VS_VERSION vs_3_0
#endif

#ifndef PS_VERSION
  #define PS_VERSION ps_3_0
#endif

#define FLUSH_COLOR float4(7.0, 7.0, 7.0, 7.0)

/** アルファカーテン(フェードイン・アウト)機能(GgafDx::AlphaCurtain参照)のマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;


float4 getBlinkColor(float4 prm_colOut  : COLOR, 
                     float4 prm_colTex  : COLOR
) : COLOR {
	if (prm_colTex.r >= g_tex_blink_threshold || prm_colTex.g >= g_tex_blink_threshold  || prm_colTex.b >= g_tex_blink_threshold ) {
		return (prm_colOut *= g_tex_blink_power); //あえてαも倍率を掛ける。点滅を目立たせる。);
	} else {
		return prm_colOut; //点滅なし
	}
}

float4 getBlinkColor(float4 prm_colTex  : COLOR) : COLOR {
	if (prm_colTex.r >= g_tex_blink_threshold || prm_colTex.g >= g_tex_blink_threshold || prm_colTex.b >= g_tex_blink_threshold ) {
		return (prm_colTex *= g_tex_blink_power); //あえてαも倍率を掛ける。点滅を目立たせる。);
	} else {
		return prm_colTex; //点滅なし
	}
}

