#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

float4x4 g_matWorld;  //World変換行列

float g_dist_CamZ_default;
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_InvTextureSplitRowcol;
float g_UvFlipPtnNo;

//float3 g_vecLightFrom_World; // ライトの方向
//float4 g_colLightAmbient;   // Ambienライト色（入射色）
//float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float  psize         : PSIZE;
    float4 color         : COLOR0;
    float4 uv_ps         : COLOR1;  //スペキュラを潰して表示したいUV座標左上の情報をPSに渡す
};

OUT_VS VS_DefaultPointSprite(
    float4 prm_posModel_Local : POSITION,  //ポイントスプライトのポイント群
    float  prm_psize_rate     : PSIZE,     //PSIZEでは無くて、スケールの率(0.0～N (1.0=等倍)) が入ってくる
    float4 prm_color          : COLOR0,     //オブジェクトのカラー
    float1 prm_ptn_no         : TEXCOORD0 //UVでは無くて、prm_ptn_no.xには、表示したいアニメーションパターン番号が埋め込んである
) {
    OUT_VS out_vs = (OUT_VS)0;
    const float4 posModel_View = mul(mul(prm_posModel_Local, g_matWorld), g_matView);
    const float dep = posModel_View.z + 1.0; //+1.0の意味は
                                    //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                    //距離に加える。
    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //射影変換
//	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;
    out_vs.psize = (g_TexSize*g_dist_CamZ_default*prm_psize_rate) / (g_TextureSplitRowcol*dep) ;
    //psizeは画面上のポイント スプライトの幅 (ピクセル単位)

    //スペキュラセマンテックス(COLOR1)を潰して表示したいUV座標左上の情報をPSに渡す
    int ptnno = (int)prm_ptn_no.x + (int)g_UvFlipPtnNo;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) * g_InvTextureSplitRowcol;
    out_vs.uv_ps.y = trunc(ptnno * g_InvTextureSplitRowcol) * g_InvTextureSplitRowcol;

    out_vs.color = prm_color;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
    }
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

float4 PS_DefaultPointSprite(
    float2 prm_uv_pointsprite	  : TEXCOORD0,   //(0.F, 0.F), (0.F, 1.F), (1.F, 0.F), (1.F, 1.F)が来る
    float4 prm_color              : COLOR0,
    float4 prm_uv_ps              : COLOR1  //スペキュラでは無くて、表示したいUV座標左上の情報が入っている
) : COLOR  {
    float2 uv = (float2)0;
    uv.x = prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x;
    uv.y = prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y;
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv_pointsprite	  : TEXCOORD0,
    float4 prm_color                : COLOR0,
    float4 prm_uv_ps              : COLOR1
) : COLOR  {
    const float2 uv = { prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x,
                        prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y };
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique DefaultPointSpriteTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultPointSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_DefaultPointSprite();
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
        VertexShader = compile VS_VERSION VS_DefaultPointSprite();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

