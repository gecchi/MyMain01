#include "GgafDx_World3DimEffect.fxh"
float4x4 g_matWorld;

float3 g_vecLightFrom_World;
float4 g_colLightAmbient;
float4 g_colLightDiffuse;

float4 g_colMaterialDiffuse;

float g_tex_blink_power;
float g_tex_blink_threshold;

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


OUT_VS VS_GroundMesh(
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

 //カメラの位置(0,0,-57.1259)
//実は世界は(-1.0f, -1.0f, 0 )という点から(1.0f, 1.0f, 1,0f)という点を対角線とする直方体の世界に収められてしまっています

//wは射影空間（視錐台空間）にある頂点座標をそれで割ることにより
//「頂点をスクリーンに投影するための立方体の領域（-1≦x≦1、-1≦y≦1そして0≦z≦1）に納める」
//という大切な役目をしています。wが「同次系」と呼ばれるのは、
//上の例のように視錐状にカメラの視線方向に広がっている頂点を同じXY座標に投影するためです。


    if ( out_vs.posModel_Proj.z < 60) {
        out_vs.color.a = (out_vs.posModel_Proj.z + 1.0)  / (57.1259*2);
//1 - (out_vs.posModel_Proj.z / 57.1259);
    }
    return out_vs;
}

float4 PS_GroundMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;

    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }
    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}


technique GroundMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_GroundMesh();
        PixelShader  = compile PS_VERSION PS_GroundMesh();
    }
}

