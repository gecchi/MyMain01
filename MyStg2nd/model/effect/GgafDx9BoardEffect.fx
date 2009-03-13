////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9BoardModel用シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_alpha; //α
float g_offsetU; //テクスチャU座標増分
float g_offsetV; //テクスチャV座標増分
float g_transformedX; //変換済みX座標(px)
float g_transformedY; //変換済みY座標(px)
float g_depthZ; //深度Z (0 ～ +1)
float g_view_width; //画面幅(px)
float g_view_height; //画面高さ(px)

//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDx9BoardModel標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultBoard(
      float4 prm_pos    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//X座標Y座標をを -1 ～ +1 に押し込める。
    out_vs.pos.x = (2 * prm_pos.x  / g_view_width ) - 1 + (2 * g_transformedX / g_view_width);
	out_vs.pos.y = (2 * -prm_pos.y / g_view_height) + 1 - (2 * g_transformedY / g_view_height);
	out_vs.pos.z = g_depthZ;
	out_vs.pos.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;

	return out_vs;
}


//GgafDx9BoardModel標準ピクセルシェーダー
float4 GgafDx9PS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//α考慮
	out_color.a = g_alpha * out_color.a ; 
	return out_color;
}



//＜テクニック：DefaultBoardTechnique＞
//【機能】
//GgafDx9BoardModel用標準シェーダー
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
technique DefaultBoardTechnique
{
	pass P0 {
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoard();
	}
}


