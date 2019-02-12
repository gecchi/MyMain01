#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、MorphMeshModel用シェーダー
// author : Masatoshi Tsuge
// date:2009/05/12
////////////////////////////////////////////////////////////////////////////////

//エラーが出るのでとりあえず宣言
/** スペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
float g_specular;
/** スペキュラーの強度 */
float g_specular_power;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam_World;

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
int g_morph_target_num;  //メッシュパターン数(モーフターゲット数）、現在未使用
float g_weight1; //モーフターゲット１の重み
float g_weight2; //モーフターゲット２の重み
float g_weight3; //モーフターゲット３の重み
float g_weight4; //モーフターゲット４の重み
float g_weight5; //モーフターゲット５の重み
float g_weight6; //モーフターゲット６の重み
//float g_weight7; //モーフターゲット７の重み

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
//sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s0);

//struct OUT_VS {
//    float4 posModel_Proj   : POSITION;
//	float2 uv     : TEXCOORD0;
//	float4 color    : COLOR0;
//    float3 vecNormal_World : TEXCOORD1;   // ワールド変換した法線
//    float3 vecEye_World    : TEXCOORD2;   //頂点 -> 視点 ベクトル
//    //float3 viewVecW: TEXCOORD1;  	// ワールド空間での視線ベクトル
//};

struct OUT_VS {
    float4 posModel_Proj    : POSITION;
    float4 color  : COLOR0;
    float3 vecNormal_World : TEXCOORD0;   // ワールド変換した法線
    //float3 viewVecW: TEXCOORD1;  	// ワールド空間での視線ベクトル
};


///////////////////////////////////////////////////////////////////////////

//モーフターゲットなし
OUT_VS VS_WorldBound0(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0//, //,        // モデルの頂点の法線
      //float2 prm_uv0     : TEXCOORD0       // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    const float4 posModel_World = mul(prm_posPrimary_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UV計算
    //out_vs.uv = prm_uv0;  //そのまま
    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormalPrimary_Local, g_matWorld));
    out_vs.color = g_colMaterialDiffuse;
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    //float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0);
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    //out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル
    //out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    //out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
//    if (out_vs.posModel_Proj.z > (g_zf*0.9)*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
//        out_vs.color.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.posModel_Proj.z + 2.0);
//    }
    return out_vs;
}

//モーフターゲット１つ
OUT_VS VS_WorldBound1(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1         // モデルのモーフターゲット1頂点の法線

) {
//    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}


//モーフターゲット２つ
OUT_VS VS_WorldBound2(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_posMorphTarget2_Local    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_vecNormal2_Local : NORMAL2         // モデルのモーフターゲット2頂点の法線
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal2_Local, g_weight2);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}

//モーフターゲット３つ
OUT_VS VS_WorldBound3(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_posMorphTarget2_Local    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_vecNormal2_Local : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_posMorphTarget3_Local    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_vecNormal3_Local : NORMAL3         // モデルのモーフターゲット3頂点の法線
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal3_Local, g_weight3);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}

//モーフターゲット４つ
OUT_VS VS_WorldBound4(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_posMorphTarget2_Local    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_vecNormal2_Local : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_posMorphTarget3_Local    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_vecNormal3_Local : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_posMorphTarget4_Local    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_vecvecNormal4_Local : NORMAL4         // モデルのモーフターゲット4頂点の法線
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_World = lerp(vecNormal_World, prm_vecvecNormal4_Local, g_weight4);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}

//モーフターゲット５つ
OUT_VS VS_WorldBound5(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_posMorphTarget2_Local    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_vecNormal2_Local : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_posMorphTarget3_Local    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_vecNormal3_Local : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_posMorphTarget4_Local    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_vecvecNormal4_Local : NORMAL4,        // モデルのモーフターゲット4頂点の法線
      float4 prm_posMorphTarget5_Local    : POSITION5,      // モデルのモーフターゲット5頂点
      float3 prm_vecNormal5_Local : NORMAL5         // モデルのモーフターゲット5頂点の法線
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_World = lerp(vecNormal_World, prm_vecvecNormal4_Local, g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget5_Local - prm_posPrimary_Local) * g_weight5);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal5_Local, g_weight5);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}

//モーフターゲット６つ
OUT_VS VS_WorldBound6(
      float4 prm_posPrimary_Local    : POSITION0,      // モデルの頂点
      float3 prm_vecNormalPrimary_Local : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_posMorphTarget1_Local    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_vecNormal1_Local : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_posMorphTarget2_Local    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_vecNormal2_Local : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_posMorphTarget3_Local    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_vecNormal3_Local : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_posMorphTarget4_Local    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_vecvecNormal4_Local : NORMAL4,        // モデルのモーフターゲット4頂点の法線
      float4 prm_posMorphTarget5_Local    : POSITION5,      // モデルのモーフターゲット5頂点
      float3 prm_vecNormal5_Local : NORMAL5,        // モデルのモーフターゲット5頂点の法線
      float4 prm_posMorphTarget6_Local    : POSITION6,      // モデルのモーフターゲット6頂点
      float3 prm_vecNormal6_Local : NORMAL6         // モデルのモーフターゲット6頂点の法線

) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点＆法線ブレンド
    float4 posModel_Proj = prm_posPrimary_Local;
    float3 vecNormal_World = prm_vecNormalPrimary_Local;
    if (g_weight1 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget1_Local - prm_posPrimary_Local) * g_weight1);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal1_Local, g_weight1);
    }
    if (g_weight2 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget2_Local - prm_posPrimary_Local) * g_weight2);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal2_Local, g_weight2);
    }
    if (g_weight3 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget3_Local - prm_posPrimary_Local) * g_weight3);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal3_Local, g_weight3);
    }
    if (g_weight4 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget4_Local - prm_posPrimary_Local) * g_weight4);
        vecNormal_World = lerp(vecNormal_World, prm_vecvecNormal4_Local, g_weight4);
    }
    if (g_weight5 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget5_Local - prm_posPrimary_Local) * g_weight5);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal5_Local, g_weight5);
    }
    if (g_weight6 != 0 ) {
        posModel_Proj += ((prm_posMorphTarget6_Local - prm_posPrimary_Local) * g_weight6);
        vecNormal_World = lerp(vecNormal_World, prm_vecNormal6_Local, g_weight6);
    }
    return VS_WorldBound0(posModel_Proj, vecNormal_World);
}


float4 PS_WorldBound(
    //float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD0
    //float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    //float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, -prm_vecNormal_World));
    const float4 colTexCube = texCUBE(CubeMapTextureSampler, -prm_vecNormal_World);

//    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

//    float s = 0.0f; //スペキュラ成分
//    if (g_specular_power != 0) {
//        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
//        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
//        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
//        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
//    }

    float4 colOut = (colTexCube * prm_color);// colTexCube; //(colTex2D * prm_color) + (colTexCube*0.2); // + s;
//    //Blinkerを考慮
    if (colTexCube.r >= g_tex_blink_threshold || colTexCube.g >= g_tex_blink_threshold || colTexCube.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }
//
//    colOut.a = prm_color.a;
    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}
float4 PS_Flush(
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_Local : TEXCOORD0
//	float2 prm_uv	  : TEXCOORD0,
//	float4 prm_color    : COLOR0,
//    float3 prm_vecNormal_Local : TEXCOORD1,
//    float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {

//	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, -prm_vecNormal_Local));
    const float4 colTexCube = texCUBE(CubeMapTextureSampler, -prm_vecNormal_Local);
    float4 colOut = colTexCube * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return 	colOut;
}

technique WorldBoundTechnique
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound0();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット１つ
    pass P1 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound1();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット２つ
    pass P2 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound2();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット３つ
    pass P3 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound3();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット４つ
    pass P4 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound4();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット５つ
    pass P5 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound5();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット６つ
    pass P6 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound6();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;
//		VertexShader = compile VS_VERSION VS_WorldBound7();
//		PixelShader  = compile PS_VERSION PS_WorldBound();
//	}
}


technique DestBlendOne
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound0();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット１つ
    pass P1 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound1();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット２つ
    pass P2 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound2();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット３つ
    pass P3 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound3();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット４つ
    pass P4 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound4();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット５つ
    pass P5 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound5();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }

    //モーフターゲット６つ
    pass P6 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound6();
        PixelShader  = compile PS_VERSION PS_WorldBound();
    }
}

technique Flush
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット１つ
    pass P1 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット２つ
    pass P2 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //SeparateAlphaBlendEnable = true;
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット３つ
    pass P3 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット４つ
    pass P4 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット５つ
    pass P5 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound5();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

    //モーフターゲット６つ
    pass P6 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_WorldBound6();
        PixelShader  = compile PS_VERSION PS_Flush();
    }

}
