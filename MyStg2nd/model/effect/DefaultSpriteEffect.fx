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
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

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


//スプライト標準ピクセルシェーダー
float4 GgafDx9PS_DefaultSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//求める色
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	}         
	out_color.a = tex_color.a * g_hAlpha * g_alpha_master;
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * g_hAlpha * float4(7.0, 7.0, 7.0, 1.0);
	out_color.a = out_color.a * g_alpha_master; 
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

		VertexShader = compile vs_3_0  GgafDx9VS_DefaultSprite();
		PixelShader  = compile ps_3_0  GgafDx9PS_DefaultSprite();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_3_0  GgafDx9VS_DefaultSprite();
		PixelShader  = compile ps_3_0  GgafDx9PS_DefaultSprite();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_3_0  GgafDx9VS_DefaultSprite();
		PixelShader  = compile ps_3_0  PS_Flush();
	}
}