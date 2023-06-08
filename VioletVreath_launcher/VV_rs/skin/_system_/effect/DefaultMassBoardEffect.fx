#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::MassBoardModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
float g_tex_blink_power;
float g_tex_blink_threshold;

//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float4 color            : COLOR0;
    float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//MassBoardModel標準頂点シェーダー
OUT_VS VS_DefaultMassBoard(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線(未使用)
      float2 prm_uv               : TEXCOORD0,     // モデルの頂点のUV

      float3 prm_pos              : TEXCOORD1,     // px_x, px_y, depth_z
      float2 prm_loc              : TEXCOORD2,     // local_px_x, local_px_y
      float3 prm_sc               : TEXCOORD3,     // r_sx, r_sy, rad_rz
      float2 prm_offset_uv        : TEXCOORD4,     // offset_u, offset_v
      float4 prm_color            : TEXCOORD5      // r, g, b, a
) {
    OUT_VS out_vs = (OUT_VS)0;
    float px_x = prm_pos.x; //変換済みX座標(px)
    float px_y = prm_pos.y; //変換済みY座標(px)
    float depthZ = prm_pos.z;  //深度Z (0 ～ +1)
    float local_px_x = prm_loc.x; //ローカルX座標（X座標のオフセット）
    float local_px_y = prm_loc.y; //ローカルY座標（Y座標のオフセット）
    float r_sx = prm_sc.x;     //X軸方向拡大率
    float r_sy = prm_sc.y;     //Y軸方向拡大率
    float rad_rz = prm_sc.z;   //Z回転角度

    if (rad_rz == 0.0f) {
        //X座標Y座標をを -1 ～ +1 に押し込める。
        out_vs.posModel_Proj.x = - 1 + ( (2*( ((prm_posModel_Local.x + local_px_x)*r_sx) + px_x)) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( ((prm_posModel_Local.y + local_px_y)*r_sy) + px_y)) * g_inv_game_buffer_height);
    } else {
        //拡大縮小
        const float lx = (prm_posModel_Local.x + local_px_x) * r_sx;
        const float ly = (prm_posModel_Local.y + local_px_y) * r_sy;
        //回転 ＆ X座標Y座標をを -1 ～ +1 に押し込める。
        out_vs.posModel_Proj.x = - 1 + ( (2*( (lx * cos(rad_rz) - ly * sin(rad_rz))      + px_x)) * g_inv_game_buffer_width);
        out_vs.posModel_Proj.y =   1 - ( (2*( (lx * sin(rad_rz) + ly * cos(rad_rz))      + px_y)) * g_inv_game_buffer_height);
    }
    out_vs.posModel_Proj.z = depthZ;
    out_vs.posModel_Proj.w = 1.0;
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);

    //UVのオフセットを加算
    out_vs.uv.x = prm_uv.x + prm_offset_uv.x;
    out_vs.uv.y = prm_uv.y + prm_offset_uv.y;
    out_vs.color = prm_color;
    return out_vs;
}


//MassBoardModel標準ピクセルシェーダー
float4 PS_DefaultMassBoard(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
//	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
//		colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
//	}
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

//＜テクニック：DefaultMassBoardTechnique＞
//【機能】
//MassBoardModel用標準シェーダー
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
technique DefaultMassBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassBoard();
        PixelShader  = compile PS_VERSION PS_DefaultMassBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultMassBoard();
        PixelShader  = compile PS_VERSION PS_DefaultMassBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultMassBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
