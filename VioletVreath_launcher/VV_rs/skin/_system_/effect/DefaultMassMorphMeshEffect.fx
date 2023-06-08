#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::MassMorphMeshModel用シェーダー
// author : Masatoshi Tsuge
// date:2016/03/18
////////////////////////////////////////////////////////////////////////////////

/** スペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
float g_specular;
/** スペキュラーの強度 */
float g_specular_power;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam_World;

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

//float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_tex_blink_power;
float g_tex_blink_threshold;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj   : POSITION;
    float2 uv              : TEXCOORD0;
    float4 color           : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ワールド変換した法線
    float3 vecEye_World    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};


///////////////////////////////////////////////////////////////////////////

OUT_VS VS_DefaultMassMorphMesh(
    float4 prm_posPrimary_Local      ,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local,  // モデルの頂点の法線
    float2 prm_uv0                   ,  // モデルの頂点のUV

    float4 prm_world0,
    float4 prm_world1,
    float4 prm_world2,
    float4 prm_world3,
    float4 prm_color
) {
    OUT_VS out_vs = (OUT_VS)0;

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};

    //頂点計算
    const float4 posModel_World = mul(prm_posPrimary_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv0;  //そのまま

    //法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormalPrimary_Local, matWorld));
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * prm_color;
    //「頂点→カメラ視点」方向ベクトル
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = prm_color.a;
    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}


//モーフターゲットなし
OUT_VS VS_DefaultMassMorphMesh0(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // モデルの頂点の法線
    float2 prm_uv0                    : TEXCOORD0,  // モデルの頂点のUV
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World行列要素
    float4 prm_world1                 : TEXCOORD2,  // World行列要素
    float4 prm_world2                 : TEXCOORD3,  // World行列要素
    float4 prm_world3                 : TEXCOORD4,  // World行列要素
    float4 prm_color                  : TEXCOORD5   // マテリアルカラー
) {
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//モーフターゲット１つ
OUT_VS VS_DefaultMassMorphMesh1(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // モデルの頂点の法線
    float2 prm_uv0                    : TEXCOORD0,  // モデルの頂点のUV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // モデルのモーフターゲット1頂点
    float3 prm_vecNormal1_Local       : NORMAL1  ,  // モデルのモーフターゲット1頂点の法線
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World行列要素
    float4 prm_world1                 : TEXCOORD2,  // World行列要素
    float4 prm_world2                 : TEXCOORD3,  // World行列要素
    float4 prm_world3                 : TEXCOORD4,  // World行列要素
    float4 prm_color                  : TEXCOORD5   // マテリアルカラー
) {
    //重みを取り出して、元に戻す
    float weight1 = prm_world0[3];
    prm_world0[3] = 0;
    //頂点＆法線ブレンド
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0.0 ) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }

    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//モーフターゲット２つ
OUT_VS VS_DefaultMassMorphMesh2(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // モデルの頂点の法線
    float2 prm_uv0                    : TEXCOORD0,  // モデルの頂点のUV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // モデルのモーフターゲット1頂点
    float3 prm_vecNormal1_Local       : NORMAL1,    // モデルのモーフターゲット1頂点の法線
    float4 prm_posMorphTarget2_Local  : POSITION2,  // モデルのモーフターゲット2頂点
    float3 prm_vecNormal2_Local       : NORMAL2  ,  // モデルのモーフターゲット2頂点の法線
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World行列要素
    float4 prm_world1                 : TEXCOORD2,  // World行列要素
    float4 prm_world2                 : TEXCOORD3,  // World行列要素
    float4 prm_world3                 : TEXCOORD4,  // World行列要素
    float4 prm_color                  : TEXCOORD5   // マテリアルカラー
) {
    //重みを取り出して、元に戻す
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    //頂点＆法線ブレンド
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//モーフターゲット３つ
OUT_VS VS_DefaultMassMorphMesh3(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // モデルの頂点の法線
    float2 prm_uv0                    : TEXCOORD0,  // モデルの頂点のUV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // モデルのモーフターゲット1頂点
    float3 prm_vecNormal1_Local       : NORMAL1,    // モデルのモーフターゲット1頂点の法線
    float4 prm_posMorphTarget2_Local  : POSITION2,  // モデルのモーフターゲット2頂点
    float3 prm_vecNormal2_Local       : NORMAL2,    // モデルのモーフターゲット2頂点の法線
    float4 prm_posMorphTarget3_Local  : POSITION3,  // モデルのモーフターゲット3頂点
    float3 prm_vecNormal3_Local       : NORMAL3,    // モデルのモーフターゲット3頂点の法線
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World行列要素
    float4 prm_world1                 : TEXCOORD2,  // World行列要素
    float4 prm_world2                 : TEXCOORD3,  // World行列要素
    float4 prm_world3                 : TEXCOORD4,  // World行列要素
    float4 prm_color                  : TEXCOORD5   // マテリアルカラー
) {
    //重みを取り出して、元に戻す
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    float weight3 = prm_world2[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    prm_world2[3] = 0;
    //頂点＆法線ブレンド
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    if (weight3 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , weight3);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


//モーフターゲット４つ
OUT_VS VS_DefaultMassMorphMesh4(
    //vertex model
    float4 prm_posPrimary_Local       : POSITION0,  // モデルの頂点
    float3 prm_vecNormalPrimary_Local : NORMAL0,    // モデルの頂点の法線
    float2 prm_uv0                    : TEXCOORD0,  // モデルの頂点のUV
    float4 prm_posMorphTarget1_Local  : POSITION1,  // モデルのモーフターゲット1頂点
    float3 prm_vecNormal1_Local       : NORMAL1,    // モデルのモーフターゲット1頂点の法線
    float4 prm_posMorphTarget2_Local  : POSITION2,  // モデルのモーフターゲット2頂点
    float3 prm_vecNormal2_Local       : NORMAL2,    // モデルのモーフターゲット2頂点の法線
    float4 prm_posMorphTarget3_Local  : POSITION3,  // モデルのモーフターゲット3頂点
    float3 prm_vecNormal3_Local       : NORMAL3,    // モデルのモーフターゲット3頂点の法線
    float4 prm_posMorphTarget4_Local  : POSITION4,  // モデルのモーフターゲット4頂点
    float3 prm_vecNormal4_Local       : NORMAL4,    // モデルのモーフターゲット4頂点の法線
    //vertex instace data
    float4 prm_world0                 : TEXCOORD1,  // World行列要素
    float4 prm_world1                 : TEXCOORD2,  // World行列要素
    float4 prm_world2                 : TEXCOORD3,  // World行列要素
    float4 prm_world3                 : TEXCOORD4,  // World行列要素
    float4 prm_color                  : TEXCOORD5   // マテリアルカラー
) {
    //重みを取り出して、元に戻す
    float weight1 = prm_world0[3];
    float weight2 = prm_world1[3];
    float weight3 = prm_world2[3];
    float weight4 = prm_world3[3];
    prm_world0[3] = 0;
    prm_world1[3] = 0;
    prm_world2[3] = 0;
    prm_world3[3] = 1;
    //頂点＆法線ブレンド
    float4 posModel_Local = prm_posPrimary_Local;
    float3 vecNormal_Local = prm_vecNormalPrimary_Local;
    if (weight1 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget1_Local, weight1);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal1_Local     , weight1);
    }
    if (weight2 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget2_Local, weight2);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal2_Local     , weight2);
    }
    if (weight3 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget3_Local, weight3);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal3_Local     , weight3);
    }
    if (weight4 != 0) {
        posModel_Local  = lerp(posModel_Local , prm_posMorphTarget4_Local, weight4);
        vecNormal_Local = lerp(vecNormal_Local, prm_vecNormal4_Local     , weight4);
    }
    return VS_DefaultMassMorphMesh(posModel_Local, vecNormal_Local, prm_uv0,
                                         prm_world0,
                                         prm_world1,
                                         prm_world2,
                                         prm_world3,
                                         prm_color  );
}


float4 PS_DefaultMassMorphMesh(
    float2 prm_uv	           : TEXCOORD0,
    float4 prm_color           : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 colOut = (colTex2D * prm_color) + s;
    //Blinkerを考慮
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }
    colOut.a = prm_color.a * g_alpha_master;
    return colOut;
}

float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    const float4 colTex2D  = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex2D * prm_color * FLUSH_COLOR;
    colOut *= g_alpha_master;
    return 	colOut;
}

//////////////////////////////////////////////////////////////////////////////
technique DefaultMassMorphMeshTechnique0
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique1
{
    //モーフターゲット1つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique2
{
    //モーフターゲット2つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique3
{
    //モーフターゲット3つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DefaultMassMorphMeshTechnique4
{
    //モーフターゲット4つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

//////////////////////////////////////////////////////////////////////////////
technique DestBlendOne0
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne1
{
    //モーフターゲット1つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne2
{
    //モーフターゲット2つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne3
{
    //モーフターゲット3つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

technique DestBlendOne4
{
    //モーフターゲット4つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_DefaultMassMorphMesh();
    }
}

//////////////////////////////////////////////////////////////////////////////
technique Flush0
{
    //モーフターゲット無し
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh0();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush1
{
    //モーフターゲット1つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh1();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush2
{
    //モーフターゲット2つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh2();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush3
{
    //モーフターゲット3つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh3();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

technique Flush4
{
    //モーフターゲット3つ
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMassMorphMesh4();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

