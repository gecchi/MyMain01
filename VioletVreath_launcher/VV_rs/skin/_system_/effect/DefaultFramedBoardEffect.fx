#include "GgafDx_Fix2DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::FramedBoardModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2017/08/21
////////////////////////////////////////////////////////////////////////////////
float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;

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

float g_alpha;

float g_x;
float g_y;
float g_z;
float g_rz;

float g_local_offset_x;
float g_local_offset_y;
//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);
sampler MyTextureSampler_frame : register(s1);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float4 color            : COLOR0;
    float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//FramedBoardModel標準頂点シェーダー
OUT_VS VS_DefaultFramedBoard(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float  prm_index             : PSIZE ,       // モデル番号
      float2 prm_uv                : TEXCOORD0     // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;
    float offsetU; //テクスチャU座標増分
    float offsetV; //テクスチャV座標増分
    float x; //変換済みX座標(px)
    float y; //変換済みY座標(px)
    float center_flg = 0.0f;

    //    ┌─┬─┬─┐
    //    │０│１│２│
    //    ├─┼─┼─┤
    //    │３│４│５│
    //    ├─┼─┼─┤
    //    │６│７│８│
    //    └─┴─┴─┘

    if (index < 3) {
        y = prm_posModel_Local.y * g_frame_sy;
        if (index == 0) {
            x = prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u001;
            offsetV = g_offset_v001;
        } else if (index == 1) {
            x = g_frame_width * g_frame_sx + prm_posModel_Local.x * g_center_sx;
            offsetU = g_offset_u002;
            offsetV = g_offset_v002;
        } else { //index == 2
            x = g_frame_width * g_frame_sx + g_center_width * g_center_sx + prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u003;
            offsetV = g_offset_v003;
        }
    } else if (index < 6) {
        y = g_frame_height * g_frame_sy + prm_posModel_Local.y * g_center_sy;
        if (index == 3) {
            x = prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u004;
            offsetV = g_offset_v004;
        } else if (index == 4) {
            x = g_frame_width * g_frame_sx + prm_posModel_Local.x * g_center_sx;
            offsetU = g_offset_u005;
            offsetV = g_offset_v005;
            center_flg = 1.0f; //中心パネルであることのフラグ
        } else { //index == 5
            x = g_frame_width * g_frame_sx + g_center_width * g_center_sx + prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u006;
            offsetV = g_offset_v006;
        }
    } else { // index >= 6
        y = g_frame_height * g_frame_sy + g_center_height * g_center_sy + prm_posModel_Local.y * g_frame_sy;
        if (index == 6) {
            x = prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u007;
            offsetV = g_offset_v007;
        } else if (index == 7) {
            x = g_frame_width * g_frame_sx + prm_posModel_Local.x * g_center_sx;
            offsetU = g_offset_u008;
            offsetV = g_offset_v008;
        } else { // index == 8
            x = g_frame_width * g_frame_sx + g_center_width * g_center_sx + prm_posModel_Local.x * g_frame_sx;
            offsetU = g_offset_u009;
            offsetV = g_offset_v009;
        }
    }
    //X座標Y座標をを -1 ～ +1 に押し込める。
    out_vs.posModel_Proj.x = - 1 + ((2*x + 2*g_local_offset_x + 2*g_x) * g_inv_game_buffer_width);
    out_vs.posModel_Proj.y =   1 - ((2*y + 2*g_local_offset_y + 2*g_y) * g_inv_game_buffer_height);
    out_vs.posModel_Proj.z = g_z;
    out_vs.posModel_Proj.w = 1.0;

    //UVのオフセットを加算
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;
    out_vs.color.r = center_flg;  //中心パネルである事の情報を color.r として埋め込む
    out_vs.color.a = g_alpha;
    
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}


//FramedBoardModel標準ピクセルシェーダー
float4 PS_DefaultFramedBoard(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //求める色
    float4 colOut;
    if (prm_color.r == 0.0f) { //color.rは中心パネル情報
        colOut = tex2D( MyTextureSampler_frame, prm_uv);
    } else {
        colOut = tex2D( MyTextureSampler, prm_uv);
    }
    //Blinkerを考慮
    colOut = getBlinkColor(colOut);
    //α考慮
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv    : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float4 colOut;
    if (prm_color.r == 1.0f) { //color.rは中心パネル情報
        colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;
    } else {
        colOut = tex2D( MyTextureSampler_frame, prm_uv) * FLUSH_COLOR;
    }
    //α考慮
    colOut.a = colOut.a * prm_color.a * g_alpha_master;
    return colOut;
}

//＜テクニック：DefaultFramedBoardTechnique＞
technique DefaultFramedBoardTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultFramedBoard();
        PixelShader  = compile PS_VERSION PS_DefaultFramedBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedBoard();
        PixelShader  = compile PS_VERSION PS_DefaultFramedBoard();
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
        VertexShader = compile VS_VERSION VS_DefaultFramedBoard();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
