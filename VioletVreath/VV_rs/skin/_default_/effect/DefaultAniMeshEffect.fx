#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::AniMeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////

//float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列


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
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
float4x4 g_matWorld020;
float4x4 g_matWorld021;
float4x4 g_matWorld022;
float4x4 g_matWorld023;
float4x4 g_matWorld024;
float4x4 g_matWorld025;
float4x4 g_matWorld026;
float4x4 g_matWorld027;
float4x4 g_matWorld028;
float4x4 g_matWorld029;
float4x4 g_matWorld030;

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）
float g_alpha_master;
float g_zf;
float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_tex_blink_power;
float g_tex_blink_threshold;


//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS VS_DefaultAniMesh(
      float4 prm_posModel_Local    : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法線
      float  prm_index           : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;

    //頂点計算
    float4x4 matWorld;

    if (index == 0) {
        matWorld = g_matWorld001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
    } else if (index == 14) {
        matWorld = g_matWorld015;
    } else if (index == 15) {
        matWorld = g_matWorld016;
    } else if (index == 16) {
        matWorld = g_matWorld017;
    } else if (index == 17) {
        matWorld = g_matWorld018;
    } else if (index == 18) {
        matWorld = g_matWorld019;
    } else if (index == 19) {
        matWorld = g_matWorld020;
    } else if (index == 20) {
        matWorld = g_matWorld021;
    } else if (index == 21) {
        matWorld = g_matWorld022;
    } else if (index == 22) {
        matWorld = g_matWorld023;
    } else if (index == 23) {
        matWorld = g_matWorld024;
    } else if (index == 24) {
        matWorld = g_matWorld025;
    } else if (index == 25) {
        matWorld = g_matWorld026;
    } else if (index == 26) {
        matWorld = g_matWorld027;
    } else if (index == 27) {
        matWorld = g_matWorld028;
    } else if (index == 28) {
        matWorld = g_matWorld029;
    } else { //if (index == 29) {
        matWorld = g_matWorld030;
    }
    //頂点計算
    const float4 posModel_World = mul(prm_posModel_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UVはそのまま
    out_vs.uv = prm_uv;

    //頂点カラー計算
    //法線を World 変換して正規化
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse;
    //αフォグ
    out_vs.color.a = g_colMaterialDiffuse.a;
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_DefaultAniMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;
    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
    }
    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_DefaultAniMesh2(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;

    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
    }
    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}


technique DefaultAniMeshTechnique
{
    //pass P0「メッシュ標準シェーダー」
    //メッシュを描画する
    //【考慮される要素】
    //--- VS ---
    //・頂点を World、View、射影 変換
    //・法線を World変換
    //--- PS ---
    //・Diffuseライト色
    //・Ambientライト色
    //・ライト方向
    //・オブジェクトのマテリアルのDiffuse反射（色はAmbient反射と共通）
    //・オブジェクトのテクスチャ
    //・半透明α（Diffuse反射αとテクスチャαの乗算）
    //【使用条件】
    //・テクスチャが存在しs0レジスタにバインドされていること。
    //【設定パラメータ】
    // float4x4 g_matWorld		:	World変換行列
    // float4x4 g_matView		:	View変換行列
    // float4x4 g_matProj		:	射影変換行列
    // float3 g_vecLightFrom_World	:	ライトの方向
    // float4 g_colLightAmbient	:	Ambienライト色（入射色）
    // float4 g_colLightDiffuse	:	Diffuseライト色（入射色）
    // float4 g_colMaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
    // s0レジスタ				:	2Dテクスチャ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultAniMesh();
    }
}

technique DefaultAniMeshTechnique2
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultAniMesh2();
    }
}


