#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、FontBoardActor用シェーダー
//
// author : Masatoshi Tsuge
// date:2016/03/14
////////////////////////////////////////////////////////////////////////////////
float g_tex_blink_power;
float g_tex_blink_threshold;

//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float4 color         : COLOR0;
    float2 uv            : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//FontBoardActor標準頂点シェーダー
OUT_VS VS_FontBoard(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線(未使用)
      float2 prm_uv               : TEXCOORD0,     // モデルの頂点のUV

      float3 prm_pos              : TEXCOORD1,     // px_x, px_y, depth_z
      float3 prm_info             : TEXCOORD2      // offset_u, offset_v, alpha
) {
    OUT_VS out_vs = (OUT_VS)0;
    float px_x = prm_pos.x; //変換済みX座標(px)
    float px_y = prm_pos.y; //変換済みY座標(px)
    float depthZ = prm_pos.z; //深度Z (0 ～ +1)
    float offset_u = prm_info.x; //テクスチャU座標増分
    float offset_v = prm_info.y; //テクスチャV座標増分
    float alpha = prm_info.z; //α

    //X座標Y座標をを -1 ～ +1 に押し込める。
    out_vs.posModel_Proj.x = - 1 + ((2*prm_posModel_Local.x + 2*px_x) * g_inv_game_buffer_width);
    out_vs.posModel_Proj.y =   1 - ((2*prm_posModel_Local.y + 2*px_y) * g_inv_game_buffer_height);
    out_vs.posModel_Proj.z = depthZ;
    out_vs.posModel_Proj.w = 1.0;
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    //UVのオフセットを加算
    out_vs.uv.x = prm_uv.x + offset_u;
    out_vs.uv.y = prm_uv.y + offset_v;
    out_vs.color.a = alpha;
    return out_vs;
}


//FontBoardActor標準ピクセルシェーダー
float4 PS_FontBoard(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv);
    if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power;
    }
    //α考慮
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR * prm_color;
    //α考慮
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;

}

//＜テクニック：FontBoardTechnique＞
//【機能】
//FontBoardActor用標準シェーダー
//【概要】
//D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
//画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
//プリミティブ（板ポリ）の基点は左上隅になります。
//--- VS ---
//・頂点を -1 ～ +1へ押し込み(＝正射影変換)、Y座標反転
//--- PS ---
//・オブジェクトのテクスチャ
//・半透明α
//
//【設定グローバル】
// float g_alpha			:	α値
// float g_px_x		: 	変換済みX座標(px)
// float g_px_y		:	変換済みY座標(px)
// float g_depth_z			:	深度Z (0 ～ +1)
// float g_game_buffer_width		:	画面幅(px)
// float g_game_buffer_height		:	画面高さ(px)
// float g_offset_u			:	テクスチャU座標増分
// float g_offset_v			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique FontBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_FontBoard();
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
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_FontBoard();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_FontBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
