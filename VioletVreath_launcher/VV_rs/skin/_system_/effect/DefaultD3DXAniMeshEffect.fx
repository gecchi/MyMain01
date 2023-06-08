#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::AniMeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）
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
OUT_VS VS_DefaultD3DXAniMesh(
      float4 prm_posModel_Local    : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
    //UVはそのまま
    out_vs.uv = prm_uv;

    //頂点カラー計算

    //法線を World 変換して正規化
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
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
float4 PS_DefaultD3DXAniMesh(
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

float4 PS_DefaultD3DXAniMesh2(
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


technique DefaultD3DXAniMeshTechnique
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
        VertexShader = compile VS_VERSION VS_DefaultD3DXAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultD3DXAniMesh();
    }
}

technique DefaultD3DXAniMeshTechnique2
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultD3DXAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultD3DXAniMesh2();
    }
}


