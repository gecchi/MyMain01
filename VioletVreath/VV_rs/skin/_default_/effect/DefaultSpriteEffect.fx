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
float4 g_colMaterialDiffuse;
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
	float4 posModel_World = mul(prm_posModel_Local, g_matWorld ); // World変換
	float4 posModel_View = mul(posModel_World, g_matView );       // View変換
	float4 posModel_Proj = mul(posModel_View, g_matProj);         // 射影変換
	out_vs.posModel_Proj = posModel_Proj;                         // 出力に設定
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
	//求める色
	float4 colOut = tex2D( MyTextureSampler, prm_uv) ; 
	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
	}   
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 colOut = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master; 
	return colOut;
}

//＜テクニック：DefaultSpriteTechnique＞
//【機能】
//GgafDxSpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
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
