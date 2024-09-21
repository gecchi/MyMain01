#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::SpriteSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;

float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
float g_offset_u010;
float g_offset_u011;
float g_offset_u012;
float g_offset_u013;
float g_offset_u014;
float g_offset_u015;
float g_offset_u016;
float g_offset_u017;
float g_offset_u018;

float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;
float g_offset_v010;
float g_offset_v011;
float g_offset_v012;
float g_offset_v013;
float g_offset_v014;
float g_offset_v015;
float g_offset_v016;
float g_offset_v017;
float g_offset_v018;

float g_alpha001;
float g_alpha002;
float g_alpha003;
float g_alpha004;
float g_alpha005;
float g_alpha006;
float g_alpha007;
float g_alpha008;
float g_alpha009;
float g_alpha010;
float g_alpha011;
float g_alpha012;
float g_alpha013;
float g_alpha014;
float g_alpha015;
float g_alpha016;
float g_alpha017;
float g_alpha018;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float4 color    : COLOR0;
    float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS VS_DefaultSpriteSet(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法
      float  prm_index  : PSIZE ,    // モデル番号
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;
    //頂点計算
    float4x4 matWorld;
    float offsetU;
    float offsetV;
    float alpha;
    if (index == 0) {
        matWorld = g_matWorld001;
        offsetU  = g_offset_u001;
        offsetV  = g_offset_v001;
        alpha   = g_alpha001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
        offsetU  = g_offset_u002;
        offsetV  = g_offset_v002;
        alpha   = g_alpha002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
        offsetU  = g_offset_u003;
        offsetV  = g_offset_v003;
        alpha   = g_alpha003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
        offsetU  = g_offset_u004;
        offsetV  = g_offset_v004;
        alpha   = g_alpha004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
        offsetU  = g_offset_u005;
        offsetV  = g_offset_v005;
        alpha   = g_alpha005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
        offsetU  = g_offset_u006;
        offsetV  = g_offset_v006;
        alpha   = g_alpha006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
        offsetU  = g_offset_u007;
        offsetV  = g_offset_v007;
        alpha   = g_alpha007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
        offsetU  = g_offset_u008;
        offsetV  = g_offset_v008;
        alpha   = g_alpha008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
        offsetU  = g_offset_u009;
        offsetV  = g_offset_v009;
        alpha   = g_alpha009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
        offsetU  = g_offset_u010;
        offsetV  = g_offset_v010;
        alpha   = g_alpha010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
        offsetU  = g_offset_u011;
        offsetV  = g_offset_v011;
        alpha   = g_alpha011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
        offsetU  = g_offset_u012;
        offsetV  = g_offset_v012;
        alpha   = g_alpha012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
        offsetU  = g_offset_u013;
        offsetV  = g_offset_v013;
        alpha   = g_alpha013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
        offsetU  = g_offset_u014;
        offsetV  = g_offset_v014;
        alpha   = g_alpha014;
    } else if (index == 14) {
        matWorld = g_matWorld015;
        offsetU  = g_offset_u015;
        offsetV  = g_offset_v015;
        alpha   = g_alpha015;
    } else if (index == 15) {
        matWorld = g_matWorld016;
        offsetU  = g_offset_u016;
        offsetV  = g_offset_v016;
        alpha   = g_alpha016;
    } else if (index == 16) {
        matWorld = g_matWorld017;
        offsetU  = g_offset_u017;
        offsetV  = g_offset_v017;
        alpha   = g_alpha017;
    } else {
        matWorld = g_matWorld018;
        offsetU  = g_offset_u018;
        offsetV  = g_offset_v018;
        alpha   = g_alpha018;
    }

    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);  // 出力に設定

    //UVのオフセット(パターン番号による増分)加算
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;
    out_vs.color.a  = alpha;
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }

    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

//スプライト標準ピクセルシェーダー
float4 PS_DefaultSpriteSet(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv);
    //Blinkerを考慮
    colOut = getBlinkColor(colOut);
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    //α計算、テクスチャαとオブジェクトαの合算
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//＜テクニック：DefaultSpriteSetTechnique＞
//【機能】
//SpriteSetModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultSpriteSetTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSpriteSet();
        PixelShader  = compile PS_VERSION PS_DefaultSpriteSet();
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
        VertexShader = compile VS_VERSION VS_DefaultSpriteSet();
        PixelShader  = compile PS_VERSION PS_DefaultSpriteSet();
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
        VertexShader = compile VS_VERSION VS_DefaultSpriteSet();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
