#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxSpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
float g_alpha; //α
float g_offset_u; //テクスチャU座標増分
float g_offset_v; //テクスチャV座標増分
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;
float g_far_rate;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS GgafDxVS_DefaultSprite(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posModel_World = mul( prm_posModel_Local, g_matWorld );               // World変換
	float4 posWorldView = mul(posModel_World, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.posModel_Proj = posWorldViewProj;                              // 出力に設定
    if (g_far_rate > 0.0) {
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {   
            out_vs.posModel_Proj.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
        }
    } 

	//UVのオフセット(パターン番号による増分)加算
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}


//スプライト標準ピクセルシェーダー
float4 GgafDxPS_DefaultSprite(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//求める色
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
	}         
	out_color.a = tex_color.a * g_alpha * g_alpha_master;
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 out_color = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
	out_color.a = out_color.a * g_alpha * g_alpha_master;
	return out_color;
}

//＜テクニック：DefaultSpriteTechnique＞
//【機能】
//GgafDxSpriteModel用標準シェーダー
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
// float g_alpha			:	α値
// float g_offset_u			:	テクスチャU座標増分
// float g_offset_v			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique DefaultSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSprite();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultSprite();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;
		VertexShader = compile VS_VERSION GgafDxVS_DefaultSprite();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
