////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9SpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
float g_hAlpha; //α
float g_offsetU; //テクスチャU座標増分
float g_offsetV; //テクスチャV座標増分

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultSprite(
      float4 prm_pos    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
	//UVのオフセット(パターン番号による増分)加算
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;
	return out_vs;
}

//ビルボード頂点シェーダー
OUT_VS GgafDx9VS_BillBoardSprite(
      float4 prm_pos    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + g_offsetU;
	out_vs.uv.y = prm_uv.y + g_offsetV;
	return out_vs;
}


//スプライト標準ピクセルシェーダー
float4 GgafDx9PS_DefaultSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv);
	//α計算、テクスチャαと引数αの合算
	out_color.a = g_hAlpha * out_color.a ; 
	return out_color;
}

//＜テクニック：DefaultSpriteTechnique＞
//【機能】
//GgafDx9SpriteModel用標準シェーダー
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
technique DefaultSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultSprite();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultSprite();
	}
}


