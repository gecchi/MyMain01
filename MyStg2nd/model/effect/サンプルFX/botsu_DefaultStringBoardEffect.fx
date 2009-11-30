////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9BoardSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_view_width; //画面幅(px)
float g_view_height; //画面高さ(px)

//float g_offsetU; //テクスチャU座標増分
//float g_offsetV; //テクスチャV座標増分
//float g_transformedX; //変換済みX座標(px)
//float g_transformedY; //変換済みY座標(px)
//float g_depthZ; //深度Z (0 ～ +1)
//float g_alpha; //α
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


//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDx9BoardSetModel標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultBoardSet(
      float4 prm_pos    : POSITION,     // モデルの頂点
	  float  prm_index  : PSIZE ,    // モデル番号
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	float offsetU; //テクスチャU座標増分
	float offsetV; //テクスチャV座標増分
	float transformedX; //変換済みX座標(px)
	float transformedY; //変換済みY座標(px)
	float depthZ; //深度Z (0 ～ +1)
	float alpha; //α

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






	//X座標Y座標をを -1 ～ +1 に押し込める。
	out_vs.pos.x = - 1 + ((2*prm_pos.x + 2*transformedX - 1) / g_view_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y + 2*transformedY - 1) / g_view_height);
	//out_vs.pos.x = - 1 + 2 * ((prm_pos.x + g_transformedX- 0.5) / g_view_width);
	//out_vs.pos.y =   1 - 2 * ((prm_pos.y + g_transformedY- 0.5) / g_view_height);
//	out_vs.pos.x = (2 * prm_pos.x  / g_view_width ) - 1 + (2 * g_transformedX / g_view_width);
//	out_vs.pos.y = (2 * -prm_pos.y / g_view_height) + 1 - (2 * g_transformedY / g_view_height);
	out_vs.pos.z = depthZ;
	out_vs.pos.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.col  = alpha;
	return out_vs;
}


//GgafDx9BoardSetModel標準ピクセルシェーダー
float4 GgafDx9PS_DefaultBoardSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//α考慮
	out_color.a = out_color.a * prm_col.a; 
	return out_color;
}



//＜テクニック：DefaultBoardSetTechnique＞
//【機能】
//GgafDx9BoardSetModel用標準シェーダー
//【概要】
//D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
//画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
//プリミティブ（板ポリ）の基点は左上隅になります。
//--- VS ---
//・頂点を -1 ～ +1へ押し込み(＝正射影変換)、Y座標反転
//--- PS ---
//・オブジェクトのテクスチャ
//・半透明α
//
//【設定グローバル】
// float g_hAlpha			:	α値
// float g_transformedX		: 	変換済みX座標(px)
// float g_transformedY		:	変換済みY座標(px)
// float g_depthZ			:	深度Z (0 ～ +1)
// float g_view_width		:	画面幅(px)
// float g_view_height		:	画面高さ(px)
// float g_offsetU			:	テクスチャU座標増分
// float g_offsetV			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
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


