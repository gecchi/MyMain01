#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxMassSpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2016/02/25 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float4 color            : COLOR0;
	float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS GgafDxVS_DefaultMassSprite(                              
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線
      float2 prm_uv               : TEXCOORD0,     // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float3 prm_info             : TEXCOORD5
) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
    float4x4 matWorld;
    matWorld._11_12_13_14 = prm_world0; 
    matWorld._21_22_23_24 = prm_world1;
    matWorld._31_32_33_34 = prm_world2;
    matWorld._41_42_43_44 = prm_world3; 

	float offsetU = prm_info.x;
	float offsetV = prm_info.y;
	float alpha   = prm_info.z;

	//World*View*射影変換
	out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // 出力に設定
	//UVのオフセット(パターン番号による増分)加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color.a  = alpha;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 GgafDxPS_DefaultMassSprite(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color  : COLOR0 
) : COLOR  {

	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colOut = tex2D( MyTextureSampler, prm_uv); 
	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
	}           
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0 ,
	float4 prm_color  : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
	//α計算、テクスチャαとオブジェクトαの合算
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

//＜テクニック：DefaultMassSpriteTechnique＞
//【機能】
//GgafDxMassSpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultMassSpriteTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultMassSprite();
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
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassSprite();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultMassSprite();
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
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_DefaultMassSprite();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
