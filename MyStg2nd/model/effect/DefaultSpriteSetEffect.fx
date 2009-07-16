////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9SpriteSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列


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

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultSpriteSet(                              
      float4 prm_pos    : POSITION,     // モデルの頂点
      float  prm_index  : PSIZE ,    // モデルの頂点番号
      float3 prm_normal : NORMAL,        // モデルの頂点の法
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;
	int cnt_vertec = (int)prm_index;
	//頂点計算
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


	//頂点計算
	float4 posWorld = mul( prm_pos, matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
	//UVのオフセット(パターン番号による増分)加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = alpah;
	return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 GgafDx9PS_DefaultSpriteSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);
	//α計算、テクスチャαとオブジェクトαの合算
	//out_color.a = out_color.a * prm_col.a; 
	return out_color;
}

//＜テクニック：DefaultSpriteSetTechnique＞
//【機能】
//GgafDx9SpriteSetModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
//【考慮される要素】
//--- VS ---
//・頂点を World、View、射影 変換
//・UVをパターン番号の位置へ
//--- PS ---
//・オブジェクトのテクスチャ
//・半透明α（αパラメータとテクスチャαの乗算）
//【使用条件】
//・テクスチャが存在しs0レジスタにバインドされていること。
//【設定パラメータ】
// float4x4 g_matWorld		:	World変換行列
// float4x4 g_matView		:	View変換行列
// float4x4 g_matProj		:	射影変換行列   
// float g_hAlpha			:	α値
// float g_offsetU			:	テクスチャU座標増分
// float g_offsetV			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
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


