#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::SpriteModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float4x4 g_matWorld;  //World変換行列
float4 g_colMaterialDiffuse;
float g_offset_u; //テクスチャU座標増分
float g_offset_v; //テクスチャV座標増分
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_sin_rz;
float g_cos_rz;
float g_u_center;
float g_v_center;
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
OUT_VS VS_DefaultRegularPolygonSprite(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    float x = prm_posModel_Local.x;
    float y = prm_posModel_Local.y;
    prm_posModel_Local.x = (x*g_cos_rz + y*-g_sin_rz);
    prm_posModel_Local.y = (x*g_sin_rz + y*g_cos_rz);
    //頂点計算
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld ); // World変換
    const float4 posModel_View = mul(posModel_World, g_matView );       // View変換
    const float4 posModel_Proj = mul(posModel_View, g_matProj);         // 射影変換
    out_vs.posModel_Proj = posModel_Proj;                         // 出力に設定
    //遠方時の表示方法。
    /*
    if (g_far_rate > 0.0) {
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {
            out_vs.posModel_Proj.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
        }
    }

    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }

    */
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    //UVのオフセット(パターン番号による増分)加算
    x = prm_uv.x - g_u_center;
    y = prm_uv.y - g_v_center;
    out_vs.uv.x = (x*g_cos_rz + y*g_sin_rz);
    out_vs.uv.y = (x*-g_sin_rz + y*g_cos_rz);
    out_vs.uv.x += (g_u_center + g_offset_u);
    out_vs.uv.y += (g_v_center + g_offset_v);
    return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 PS_DefaultRegularPolygonSprite(
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

//＜テクニック：DefaultRegularPolygonSpriteTechnique＞
//【機能】
//SpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultRegularPolygonSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_DefaultRegularPolygonSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultRegularPolygonSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
