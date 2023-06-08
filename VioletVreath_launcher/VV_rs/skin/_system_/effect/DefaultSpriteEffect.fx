#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

/**
 * GgafLib::DefaultSpriteActor 用シェーダー .
 * 板ポリゴンにテクスチャを貼り付けた擬似スプライトを１つ描画する標準的なシェーダー。
 * 頂点バッファフォーマットは、以下のような GgafLib::SpriteModel に定義されているものを前提としています。
 * {
 *     float x, y, z;             // 座標(ローカル座標系)
 *     float nx, ny, nz;          // 法線ベクトル(ローカル座標系)
 *     DWORD color;               // 頂点カラー（現在未使用）
 *     float tu, tv;              // テクスチャ座標
 * };
 *
 * DWORD SpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
 *
 * @author Masatoshi Tsuge
 * @since 2009/03/06
 */

/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのマテリアル色(ライトによる拡散反射時のモデルの色) */
float4 g_colMaterialDiffuse;
/** テクスチャU座標増分（パターンNoにより増減） */
float g_offset_u;
/** テクスチャV座標増分（パターンNoにより増減） */
float g_offset_v;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** -1.0 or 0.0～1.0。遠くでも表示を強制したい場合に 負の値 が代入される。*/
float g_far_rate;

/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);

/** 頂点シェーダー、出力構造体 */
struct OUT_VS
{
    float4 posModel_Proj : POSITION;  //最終的な頂点座標(ワールド・ビュー・射影変換後)
    float4 color         : COLOR0;    //頂点カラー
    float2 uv            : TEXCOORD0; //頂点テクスチャUV
};


/**
 * GgafLib::DefaultMeshActor 用の疑似スプライト標準頂点シェーダー .
 * 頂点を World > View > 射影 変換する。
 * モデルのマテリアル色付を頂点カラーの設定で行う。
 * テクスチャのパターン番号に伴い設定されたUV座標を設定。
 * @param prm_posModel_Local  頂点のローカル座標。左上、右上、左下、右下の順で4頂点が渡ってくる
 * @param prm_uv              頂点のUV座標
 */
OUT_VS VS_DefaultSprite(
      float4 prm_posModel_Local : POSITION, // モデルの頂点
      float2 prm_uv             : TEXCOORD0 // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;

    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, g_matWorld ), g_matView ), g_matProj);  // 出力に設定
    //遠方時の表示方法。
    if (g_far_rate < 0.0) {
        //負の場合、どんな遠方でも表示する
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //本来視野外のZでも、描画を強制するため、射影後のZ座標を上書き、
            out_vs.posModel_Proj.z = g_zf*0.999; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {   // 最遠の g_far_rate よりさらに奥の場合徐々に透明に
            //  z : g_far_rate*g_zf ～ 1.0*g_zf  → α : 1.0 ～ 0.0  となるようにするには
            //  α = ( (0-1)*z - (g_zf*0) + (1* (far_rate*g_zf)) ) / ((far_rate*g_zf)-g_zf)
            //  α = (far_rate*g_zf - z) / (far_rate*g_zf - g_zf)
            out_vs.color.a *= (  (g_far_rate*g_zf - out_vs.posModel_Proj.z) / ((g_far_rate-1.0)*g_zf) );
        }
    }
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UVのオフセット（パターン番号による増分）を加算
    out_vs.uv.x = prm_uv.x + g_offset_u;
    out_vs.uv.y = prm_uv.y + g_offset_v;

    //マテリアル色として頂点カラーに設定
    out_vs.color = g_colMaterialDiffuse;

    return out_vs;
}

/**
 * GgafLib::DefaultSpriteActor 用の疑似スプライト標準ピクセルシェーダー .
 * @param prm_uv    UV座標
 * @param prm_color 色（マテリアル、αフォグ考慮済み）
 */
float4 PS_DefaultSprite(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //求める色
    float4 colTex = tex2D( MyTextureSampler, prm_uv); //テクスチャから色取得
    //テクスチャ色にマテリアルカラーとスペキュラーを考慮
    float4 colOut = colTex * prm_color;
    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }

    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv : TEXCOORD0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv)  * FLUSH_COLOR;
//    colOut *= g_colMaterialDiffuse;
//    colOut.a *= g_alpha_master;
    return colOut;
}

//＜テクニック：DefaultSpriteTechnique＞
//【機能】
//SpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_DefaultSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_DefaultSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
