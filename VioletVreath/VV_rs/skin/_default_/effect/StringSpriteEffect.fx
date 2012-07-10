#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxSpriteSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

float4x4 g_matWorld001;
//float4x4 g_matWorld002;
//float4x4 g_matWorld003;
//float4x4 g_matWorld004;
//float4x4 g_matWorld005;
//float4x4 g_matWorld006;
//float4x4 g_matWorld007;
//float4x4 g_matWorld008;
//float4x4 g_matWorld009;
//float4x4 g_matWorld010;
//float4x4 g_matWorld011;
//float4x4 g_matWorld012;
//float4x4 g_matWorld013;
//float4x4 g_matWorld014;
//float4x4 g_matWorld015;
//float4x4 g_matWorld016;
//float4x4 g_matWorld017;
//float4x4 g_matWorld018;

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

float g_X001;
float g_X002;
float g_X003;
float g_X004;
float g_X005;
float g_X006;
float g_X007;
float g_X008;
float g_X009;
float g_X010;
float g_X011;
float g_X012;
float g_X013;
float g_X014;
float g_X015;
float g_X016;
float g_X017;
float g_X018;

float g_Y001;
float g_Y002;
float g_Y003;
float g_Y004;
float g_Y005;
float g_Y006;
float g_Y007;
float g_Y008;
float g_Y009;
float g_Y010;
float g_Y011;
float g_Y012;
float g_Y013;
float g_Y014;
float g_Y015;
float g_Y016;
float g_Y017;
float g_Y018;

float g_alpha001;
//float g_alpha002;
//float g_alpha003;
//float g_alpha004;
//float g_alpha005;
//float g_alpha006;
//float g_alpha007;
//float g_alpha008;
//float g_alpha009;
//float g_alpha010;
//float g_alpha011;
//float g_alpha012;
//float g_alpha013;
//float g_alpha014;
//float g_alpha015;
//float g_alpha016;
//float g_alpha017;
//float g_alpha018;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float4 color  : COLOR0;
    float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//スプライト標準頂点シェーダー
OUT_VS GgafDxVS_StringSprite(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法
      float  prm_index  : PSIZE ,    // モデル番号
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    int index = (int)prm_index;
    //頂点計算
    float4x4 matWorld;
    float X;
    float Y;
    float offsetU;
    float offsetV;
    float alpha;

    if (index == 0) {
        X = g_X001;
        Y = g_Y001;
        offsetU  = g_offset_u001;
        offsetV  = g_offset_v001;
    } else if (index == 1) {
        X = g_X002;
        Y = g_Y002;
        offsetU  = g_offset_u002;
        offsetV  = g_offset_v002;
    } else if (index == 2) {
        X = g_X003;
        Y = g_Y003;
        offsetU  = g_offset_u003;
        offsetV  = g_offset_v003;
    } else if (index == 3) {
        X = g_X004;
        Y = g_Y004;
        offsetU  = g_offset_u004;
        offsetV  = g_offset_v004;
    } else if (index == 4) {
        X = g_X005;
        Y = g_Y005;
        offsetU  = g_offset_u005;
        offsetV  = g_offset_v005;
    } else if (index == 5) {
        X = g_X006;
        Y = g_Y006;
        offsetU  = g_offset_u006;
        offsetV  = g_offset_v006;
    } else if (index == 6) {
        X = g_X007;
        Y = g_Y007;
        offsetU  = g_offset_u007;
        offsetV  = g_offset_v007;
    } else if (index == 7) {
        X = g_X008;
        Y = g_Y008;
        offsetU  = g_offset_u008;
        offsetV  = g_offset_v008;
    } else if (index == 8) {
        X = g_X009;
        Y = g_Y009;
        offsetU  = g_offset_u009;
        offsetV  = g_offset_v009;
    } else if (index == 9) {
        X = g_X010;
        Y = g_Y010;
        offsetU  = g_offset_u010;
        offsetV  = g_offset_v010;
    } else if (index == 10) {
        X = g_X011;
        Y = g_Y011;
        offsetU  = g_offset_u011;
        offsetV  = g_offset_v011;
    } else if (index == 11) {
        X = g_X012;
        Y = g_Y012;
        offsetU  = g_offset_u012;
        offsetV  = g_offset_v012;
    } else if (index == 12) {
        X = g_X013;
        Y = g_Y013;
        offsetU  = g_offset_u013;
        offsetV  = g_offset_v013;
    } else if (index == 13) {
        X = g_X014;
        Y = g_Y014;
        offsetU  = g_offset_u014;
        offsetV  = g_offset_v014;
    } else if (index == 14) {
        X = g_X015;
        Y = g_Y015;
        offsetU  = g_offset_u015;
        offsetV  = g_offset_v015;
    } else if (index == 15) {
        X = g_X016;
        Y = g_Y016;
        offsetU  = g_offset_u016;
        offsetV  = g_offset_v016;
    } else if (index == 16) {
        X = g_X017;
        Y = g_Y017;
        offsetU  = g_offset_u017;
        offsetV  = g_offset_v017;
    } else {
        X = g_X018;
        Y = g_Y018;
        offsetU  = g_offset_u018;
        offsetV  = g_offset_v018;
    }
    alpha   = g_alpha001;
    matWorld = g_matWorld001;
    prm_posModel_Local.x += X;
    prm_posModel_Local.y += Y;
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
float4 GgafDxPS_StringSprite(
    float2 prm_uv     : TEXCOORD0 ,
    float4 prm_color  : COLOR0
) : COLOR  {

    //テクスチャをサンプリングして色取得（原色を取得）
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
    //求める色
    float4 out_color = tex_color;
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }
    out_color.a = out_color.a * prm_color.a * g_alpha_master;
    return out_color;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0 ,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 out_color = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    //α計算、テクスチャαとオブジェクトαの合算
    out_color.a = out_color.a * prm_color.a * g_alpha_master;
    return out_color;
}

//＜テクニック：StringSpriteTechnique＞
//【機能】
//GgafDxSpriteSetModel用標準シェーダー
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
technique StringSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION GgafDxVS_StringSprite();
        PixelShader  = compile PS_VERSION GgafDxPS_StringSprite();
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
        VertexShader = compile VS_VERSION GgafDxVS_StringSprite();
        PixelShader  = compile PS_VERSION GgafDxPS_StringSprite();
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
        VertexShader = compile VS_VERSION GgafDxVS_StringSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
