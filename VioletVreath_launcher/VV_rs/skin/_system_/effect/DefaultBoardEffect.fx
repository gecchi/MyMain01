#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::BoardModel用シェーダー
//【概要】
// D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
// 画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
// プリミティブ（板ポリ）の基点は左上隅になります。
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float4 g_colMaterialDiffuse;
float g_offset_u; //テクスチャU座標増分
float g_offset_v; //テクスチャV座標増分
float g_transformed_x; //アラインメント未考慮、変換済みX座標(px)
float g_transformed_y; //アラインメント未考慮、変換済みY座標(px)
float g_local_left_top_x;  //ローカル左上変換済みX座標(px)
float g_local_left_top_y;  //ローカル左上変換済みY座標(px)
float g_depth_z; //深度Z (0 ～ +1)
float g_sx; //X軸方向拡大率(1.0で等倍)
float g_sy; //Y軸方向拡大率(1.0で等倍)
float g_rz; //Z軸回転角（ラジアン）0～2π
float g_tex_blink_power;
float g_tex_blink_threshold;
//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float2 uv            : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//BoardModel標準頂点シェーダー
OUT_VS VS_DefaultBoard(
      float4 prm_posModel_Local : POSITION,  // モデルの頂点
      float2 prm_uv             : TEXCOORD0  // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    if (g_rz == 0.0f) {
        //X座標Y座標をを -1 ～ +1 に押し込める。
        out_vs.posModel_Proj.x = - 1 + ( (2*( ((prm_posModel_Local.x + g_local_left_top_x)*g_sx) + g_transformed_x) ) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( ((prm_posModel_Local.y + g_local_left_top_y)*g_sy) + g_transformed_y) ) * g_inv_game_buffer_height);
    } else {
        //拡大縮小
        const float lx = (prm_posModel_Local.x + g_local_left_top_x) * g_sx;
        const float ly = (prm_posModel_Local.y + g_local_left_top_y) * g_sy;
        //回転 ＆ X座標Y座標をを -1 ～ +1 に押し込める。
        out_vs.posModel_Proj.x = - 1 + ( (2*( (lx * cos(g_rz) - ly * sin(g_rz))                  + g_transformed_x) ) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( (lx * sin(g_rz) + ly * cos(g_rz))                  + g_transformed_y) ) * g_inv_game_buffer_height);
    }
    out_vs.posModel_Proj.z = g_depth_z;
    out_vs.posModel_Proj.w = 1.0;
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UVのオフセットを加算
    out_vs.uv.x = prm_uv.x + g_offset_u;
    out_vs.uv.y = prm_uv.y + g_offset_v;

    return out_vs;
}


float4 PS_DefaultBoard(
    float2 prm_uv      : TEXCOORD0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv);
    if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
    }
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv      : TEXCOORD0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    colOut *= g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

//＜テクニック：DefaultBoardTechnique＞
//BoardModel用標準シェーダー
technique DefaultBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultBoard();
        PixelShader  = compile PS_VERSION PS_DefaultBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultBoard();
        PixelShader  = compile PS_VERSION PS_DefaultBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
