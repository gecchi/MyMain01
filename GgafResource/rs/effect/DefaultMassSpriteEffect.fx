#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::MassSpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2016/02/25
////////////////////////////////////////////////////////////////////////////////
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
OUT_VS VS_DefaultMassSprite(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線
      float2 prm_uv               : TEXCOORD0,     // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float2 prm_offset_uv        : TEXCOORD5,     // offset_u, offset_v
      float4 prm_color            : TEXCOORD6      // r, g, b, a
) {
    OUT_VS out_vs = (OUT_VS)0;
    //頂点計算
    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};

 //   prm_posModel_Local.x += prm_local.x;
 //   prm_posModel_Local.y += prm_local.y;

    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // 出力に設定

    //UVのオフセット(パターン番号による増分)加算
    out_vs.uv.x = prm_uv.x + prm_offset_uv.x;
    out_vs.uv.y = prm_uv.y + prm_offset_uv.y;
    out_vs.color = prm_color;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 PS_DefaultMassSprite(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color  : COLOR0
) : COLOR  {

    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
    //Blinkerを考慮
    colOut = getBlinkColor(colOut);
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

//＜テクニック：DefaultMassSpriteTechnique＞
//【機能】
//MassSpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultMassSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
