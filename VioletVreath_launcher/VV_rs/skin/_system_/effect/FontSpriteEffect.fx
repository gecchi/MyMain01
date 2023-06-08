#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::MassSpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2016/03/30
////////////////////////////////////////////////////////////////////////////////
float g_tex_blink_power;
float g_tex_blink_threshold;

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
OUT_VS VS_FontSprite(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線
      float2 prm_uv               : TEXCOORD0,     // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float2 prm_local            : TEXCOORD5,     // local_x, local_y
      float2 prm_offset_uv        : TEXCOORD6,     // offset_u, offset_v
      float4 prm_color            : TEXCOORD7      // r, g, b, a
) {
    OUT_VS out_vs = (OUT_VS)0;
    //頂点計算
    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    prm_posModel_Local.x += prm_local.x;
    prm_posModel_Local.y += prm_local.y;

    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // 出力に設定
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UVのオフセット(パターン番号による増分)加算
    out_vs.uv.x = prm_uv.x + prm_offset_uv.x;
    out_vs.uv.y = prm_uv.y + prm_offset_uv.y;
    out_vs.color = prm_color;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 PS_FontSprite(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color  : COLOR0
) : COLOR  {

    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
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
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;
    //α計算、テクスチャαとオブジェクトαの合算
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//＜テクニック：FontSpriteTechnique＞
//【機能】
//MassSpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique FontSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontSprite();
        PixelShader  = compile PS_VERSION PS_FontSprite();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontSprite();
        PixelShader  = compile PS_VERSION PS_FontSprite();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
