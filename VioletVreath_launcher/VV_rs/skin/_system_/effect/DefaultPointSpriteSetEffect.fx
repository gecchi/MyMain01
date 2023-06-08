#include "GgafDx_World3DimEffect.fxh"
#include "GgafDx_IPlaneEffect.fxh"

//float4x4 g_matWorld;  //World変換行列

float g_dist_CamZ_default;
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_InvTextureSplitRowcol;
float g_UvFlipPtnNo;

//ワールド変換行列
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
//float4x4 g_matWorld016;
//オブジェクトのマテリアル色（Diffuse反射色と、Ambien反射色共通）
float4 g_colMaterialDiffuse001;
float4 g_colMaterialDiffuse002;
float4 g_colMaterialDiffuse003;
float4 g_colMaterialDiffuse004;
float4 g_colMaterialDiffuse005;
float4 g_colMaterialDiffuse006;
float4 g_colMaterialDiffuse007;
float4 g_colMaterialDiffuse008;
float4 g_colMaterialDiffuse009;
float4 g_colMaterialDiffuse010;
float4 g_colMaterialDiffuse011;
float4 g_colMaterialDiffuse012;
float4 g_colMaterialDiffuse013;
float4 g_colMaterialDiffuse014;
float4 g_colMaterialDiffuse015;


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

OUT_VS VS_DefaultPointSpriteSet(
    float4 prm_posModel_Local : POSITION,  //ポイントスプライトのポイント群
    float  prm_psize_rate     : PSIZE,     //PSIZEでは無くて、スケールの率(0.0～N (1.0=等倍)) が入ってくる
    float4 prm_color          : COLOR0,    //オブジェクトのカラー
    float2 prm_val            : TEXCOORD0 //UVでは無くて、prm_ini_ptn_no.xには、その頂点スプライトの表示したい初期アニメーションパターン番号が埋め込んである
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int ini_ptn_no = (int)prm_val.x;
    const int index = (int)prm_val.y;

    //頂点計算
    float4x4 matWorld;
    float4 colMaterialDiffuse;

    if (index == 0) {
        matWorld = g_matWorld001;
        colMaterialDiffuse = g_colMaterialDiffuse001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
        colMaterialDiffuse = g_colMaterialDiffuse002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
        colMaterialDiffuse = g_colMaterialDiffuse003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
        colMaterialDiffuse = g_colMaterialDiffuse004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
        colMaterialDiffuse = g_colMaterialDiffuse005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
        colMaterialDiffuse = g_colMaterialDiffuse006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
        colMaterialDiffuse = g_colMaterialDiffuse007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
        colMaterialDiffuse = g_colMaterialDiffuse008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
        colMaterialDiffuse = g_colMaterialDiffuse009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
        colMaterialDiffuse = g_colMaterialDiffuse010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
        colMaterialDiffuse = g_colMaterialDiffuse011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
        colMaterialDiffuse = g_colMaterialDiffuse012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
        colMaterialDiffuse = g_colMaterialDiffuse013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
        colMaterialDiffuse = g_colMaterialDiffuse014;
    } else { //if (index == 14) {
        matWorld = g_matWorld015;
        colMaterialDiffuse = g_colMaterialDiffuse015;
    }
    int active_flip_ptn_no = (int)matWorld._14;   //ワールド変換行列の._14には、そのオブジェクトのアクティブなUVパターンが埋め込まれている
    matWorld._14 = 0.0f;         //元の行列値に戻しておく

    const float4 posModel_View = mul(mul(prm_posModel_Local, matWorld), g_matView);
    const float dep = posModel_View.z + 1.0; //+1.0の意味は
                                    //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                    //距離に加える。
    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //射影変換
//	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;
    out_vs.psize = (g_TexSize*g_dist_CamZ_default*prm_psize_rate) / (g_TextureSplitRowcol*dep);
    //psizeは画面上のポイント スプライトの幅 (ピクセル単位)

    //スペキュラセマンテックス(COLOR1)を潰して表示したいUV座標左上の情報をPSに渡す
    int ptnno = ini_ptn_no + active_flip_ptn_no;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) * g_InvTextureSplitRowcol;
    out_vs.uv_ps.y = trunc(ptnno * g_InvTextureSplitRowcol) * g_InvTextureSplitRowcol;

    out_vs.color = prm_color * colMaterialDiffuse;
    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
    }
    //dot by dot考慮
    out_vs.posModel_Proj = adjustDotByDot(out_vs.posModel_Proj);
    return out_vs;
}

float4 PS_DefaultPointSpriteSet(
    float2 prm_uv_pointsprite	  : TEXCOORD0,   //(0.F, 0.F), (0.F, 1.F), (1.F, 0.F), (1.F, 1.F)が来る
    float4 prm_color              : COLOR0,
    float4 prm_uv_ps              : COLOR1  //スペキュラでは無くて、表示したいUV座標左上の情報が入っている
) : COLOR  {
    float2 uv = (float2)0;
    uv.x = prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x;
    uv.y = prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y;
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color;
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
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique DefaultPointSpriteSetTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultPointSpriteSet();
        PixelShader  = compile PS_VERSION PS_DefaultPointSpriteSet();
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
        VertexShader = compile VS_VERSION VS_DefaultPointSpriteSet();
        PixelShader  = compile PS_VERSION PS_DefaultPointSpriteSet();
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
        VertexShader = compile VS_VERSION VS_DefaultPointSpriteSet();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

