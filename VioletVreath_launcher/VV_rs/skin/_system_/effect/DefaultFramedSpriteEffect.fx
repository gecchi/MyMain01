#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

/**
 * GgafLib::DefaultFramedSpriteActor 用シェーダー .
 * 板ポリゴンにテクスチャを貼り付けた擬似スプライトを１つ描画する標準的なシェーダー。
 * 頂点バッファフォーマットは、以下のような GgafLib::FramedSpriteModel に定義されているものを前提としています。
 * {
 *     float x, y, z;             // 座標(ローカル座標系)
 *     float nx, ny, nz;          // 法線ベクトル(ローカル座標系)
 *     DWORD color;               // 頂点カラー（現在未使用）
 *     float tu, tv;              // テクスチャ座標
 * };
 *
 * DWORD FramedSpriteModel::FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
 *
 * @author Masatoshi Tsuge
 * @since 2022/2/8
 */

/** モデルのWorld変換行列 */
float4x4 g_matWorldRotMv;
/** モデルのマテリアル色(ライトによる拡散反射時のモデルの色) */
float4 g_colMaterialDiffuse;

/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;

/** テクスチャU座標増分（パターンNoにより増減） */
float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
/** テクスチャV座標増分（パターンNoにより増減） */
float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;

float g_center_width;
float g_center_height;

float g_frame_width;
float g_frame_height;

float g_frame_sx;
float g_center_sy;

float g_frame_sy;
float g_center_sx;

float g_local_offset_x;
float g_local_offset_y;

float g_alpha;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler MyTextureSampler_frame : register(s1);

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
OUT_VS VS_DefaultFramedSprite(
      float4 prm_posModel_Local : POSITION, // モデルの頂点
      float  prm_index          : PSIZE ,       // モデル番号
      float2 prm_uv             : TEXCOORD0 // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;
    float offsetU; //テクスチャU座標増分
    float offsetV; //テクスチャV座標増分
    float x; //X座標(dxcoord)
    float y; //Y座標(dxcoord)
    float center_flg = 0.0f;
//center_flg = 1.0f;
    //    ┌─┬─┬─┐
    //    │０│１│２│
    //    ├─┼─┼─┤
    //    │３│４│５│
    //    ├─┼─┼─┤
    //    │６│７│８│
    //    └─┴─┴─┘
    float center_width = g_center_width * g_center_sx;
    float center_height = g_center_height * g_center_sy;
    float frame_width = g_frame_width * g_frame_sx;
    float frame_height = g_frame_height * g_frame_sy;
    if (index < 3) {
        y = (center_height + frame_height) * 0.5;
        prm_posModel_Local.y *= g_frame_sy;
        if (index == 0) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u001;
            offsetV = g_offset_v001;
        } else if (index == 1) {
            x = 0;
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u002;
            offsetV = g_offset_v002;
        } else { //index == 2
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u003;
            offsetV = g_offset_v003;
        }
    } else if (index < 6) {
        y = 0;
        prm_posModel_Local.y *= g_center_sy;
        if (index == 3) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u004;
            offsetV = g_offset_v004;
        } else if (index == 4) {
            x = 0;
            center_flg = 1.0f; //中心パネルであることのフラグ
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u005;
            offsetV = g_offset_v005;
        } else { //index == 5
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u006;
            offsetV = g_offset_v006;
        }
    } else { // index >= 6
        y = -(center_height + frame_height) * 0.5;
        prm_posModel_Local.y *= g_frame_sy;
        if (index == 6) {
            x = -(center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u007;
            offsetV = g_offset_v007;
        } else if (index == 7) {
            x = 0;
            prm_posModel_Local.x *= g_center_sx;
            offsetU = g_offset_u008;
            offsetV = g_offset_v008;
        } else { // index == 8
            x = (center_width + frame_width) * 0.5;
            prm_posModel_Local.x *= g_frame_sx;
            offsetU = g_offset_u009;
            offsetV = g_offset_v009;
        }
    }

    prm_posModel_Local.x += (x + g_local_offset_x);
    prm_posModel_Local.y += (y + g_local_offset_y);
    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, g_matWorldRotMv ), g_matView ), g_matProj);  // 出力に設定
    //遠方時の表示方法。
    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }

    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UVのオフセット（パターン番号による増分）を加算
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;

    //マテリアル色として頂点カラーに設定
    out_vs.color.r = center_flg;  //中心パネルである事の情報を color.r （頂点カラーを潰して）埋め込む
    out_vs.color.a = g_alpha;
    return out_vs;
}

/**
 * GgafLib::DefaultFramedSpriteActor 用の疑似スプライト標準ピクセルシェーダー .
 * @param prm_uv    UV座標
 * @param prm_color 色（マテリアル、αフォグ考慮済み）
 */
float4 PS_DefaultFramedSprite(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    float4 colOut;
    if (prm_color.r == 0.0f) { //color.rは中心パネル情報
        colOut = tex2D( MyTextureSampler_frame, prm_uv);
    } else {
        colOut = tex2D( MyTextureSampler, prm_uv);
    }

    //求める色
    //float4 colTex = tex2D( MyTextureSampler, prm_uv); //テクスチャから色取得
    //テクスチャ色にマテリアルカラーとスペキュラーを考慮
    colOut = colOut * g_colMaterialDiffuse;
    //Blinkerを考慮
    if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }

    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    float4 colOut;
    if (prm_color.r == 0.0f) { //color.rは中心パネル情報
        colOut = tex2D( MyTextureSampler_frame, prm_uv)* FLUSH_COLOR;
    } else {
        colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    }
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//＜テクニック：DefaultFramedSpriteTechnique＞
//【機能】
//FramedSpriteModel用標準シェーダー
//【概要】
//板ポリ（擬似スプライト）を描画する。ライトなどの陰影は無し。
technique DefaultFramedSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_DefaultFramedSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_DefaultFramedSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
