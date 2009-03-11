////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ用、ボード標準シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_alpha; //α
float g_offsetU; //テクスチャU座標増分
float g_offsetV; //テクスチャV座標増分
float g_view_width_half ; //画面幅の半分
float g_view_height_half ; //画面高さの半分
float g_x; //X座標
float g_y; //Y座標

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//ボード標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultBoard(
      float4 prm_pos    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
    //World変換は行なわない。
	//View変換は単位行列（＝無し）
	//そして正射影変換
    out_vs.pos.x = (prm_pos.x / g_view_width_half) - g_view_width_half;
	out_vs.pos.y = (-prm_pos.y / g_view_height_half) + g_view_width_half;
	out_vs.pos.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + 0.2;//g_offsetU;
	out_vs.uv.y = prm_uv.y + 0;//g_offsetV;

	return out_vs;
}


//ボード標準ピクセルシェーダー
float4 GgafDx9PS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);                
	//α計算、テクスチャαと引数αの合算
	out_color.a = g_alpha * out_color.a ; 
	return out_color;
}


technique DefaultBoardTechnique
{
	//pass P0「ボード標準シェーダー」
	//D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
	//画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
	//プリミティブの基点は板ポリ左上隅になります。
	//【考慮される要素】
	//--- VS ---
	//・頂点を World、View、射影 変換
	//--- PS ---
	//・オブジェクトのテクスチャ
	//・半透明α（αパラメータとテクスチャαの乗算）
	//【使用条件】
	//・テクスチャが存在しs0レジスタにバインドされていること。
	//【設定パラメータ】
	// float g_hAlpha			:	α値
	// float g_view_width_half	:	画面の幅の半分(px)
	// float g_view_height_half	:	画面の高さの半分(px)
	// float g_offsetU			:	テクスチャU座標増分
	// float g_offsetV			:	テクスチャV座標増分
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultBoard();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultBoard();
	}
}


