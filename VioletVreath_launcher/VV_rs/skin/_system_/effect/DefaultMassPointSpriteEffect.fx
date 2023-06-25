#include "GgafDx_World3DimEffect.fxh"
// author : Masatoshi Tsuge
// date:2016/05/17

float g_dist_CamZ_default;
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_InvTextureSplitRowcol;

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float  psize         : PSIZE;
    float4 color         : COLOR0;
    float4 uv_pos        : COLOR1;  //スペキュラを潰して表示したいUV座標左上の情報をPSに渡す
};

OUT_VS VS_DefaultMassPointSprite(
    float4 prm_posModel_Local : POSITION,  //ポイントスプライトのポイント群
    float  prm_psize_rate     : PSIZE,     //PSIZEでは無くて、スケールの率(0.0～N (1.0=等倍)) が入ってくる
    float4 prm_p_color        : COLOR0,     //オブジェクトのカラー
    float2 prm_ptn_no         : TEXCOORD0 , //UVでは無くて、prm_ptn_no.xには、表示したいアニメーションパターン番号が埋め込んである

    float4 prm_world0         : TEXCOORD1,
    float4 prm_world1         : TEXCOORD2,
    float4 prm_world2         : TEXCOORD3,
    float4 prm_world3         : TEXCOORD4,
    float4 prm_color          : TEXCOORD5,
    float prm_pattno_uvflip_now  : TEXCOORD6
) {
    OUT_VS out_vs = (OUT_VS)0;
    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    const float4 posModel_View = mul(mul(prm_posModel_Local, matWorld), g_matView);
    const float dep = posModel_View.z + 1.0; //+1.0の意味は
                                    //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                    //距離に加える。
    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //射影変換
    out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;

    //psizeは画面上のポイント スプライトの幅 (ピクセル単位)
    //スペキュラセマンテックス(COLOR1)を潰して表示したいUV座標左上の情報をPSに渡す
    int ptnno = prm_ptn_no.x + prm_pattno_uvflip_now;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_pos.x = fmod(ptnno, g_TextureSplitRowcol) / g_TextureSplitRowcol;
    out_vs.uv_pos.y = trunc(ptnno / g_TextureSplitRowcol) / g_TextureSplitRowcol;

    out_vs.color = prm_p_color * prm_color;
    out_vs.color.a = prm_p_color.a * prm_color.a;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
    }
    return out_vs;
}

float4 PS_DefaultMassPointSprite (
    float2 prm_uv_pointsprite	  : TEXCOORD0,  //(0.0, 0.0), (0.0, 1.0), (1.0, 0.0), (1.0, 1.0) の範囲で来る
    float4 prm_color              : COLOR0,
    float4 prm_uv_pos             : COLOR1      //スペキュラでは無くて、表示したいUV座標左上の情報が入っている
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.x,
                        prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color;
    colOut.a *= g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv_pointsprite : TEXCOORD0,
    float4 prm_color          : COLOR0,
    float4 prm_uv_pos         : COLOR1
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.x,
                        prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_pos.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique DefaultMassPointSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassPointSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultMassPointSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultMassPointSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

