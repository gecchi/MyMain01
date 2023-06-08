#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// author : Masatoshi Tsuge
// date:2010/12/24
////////////////////////////////////////////////////////////////////////////////

//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
float g_reflectance;

float g_specular;
float g_specular_power;


float g_tex_blink_power;
float g_tex_blink_threshold;
// ライトの方向
float3 g_vecLightFrom_World;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）
float4 g_colLightDiffuse;
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
//float4 g_colMaterialDiffuse016;

//テクスチャのサンプラ(s0レジスタ)
//sampler MyTextureSampler : register(s0);
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);

struct OUT_VS {
    float4 posModel_Proj   : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   // ワールド変換した法線
    float3 vecEye_World    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS VS_CubeMapMeshSet(
      float4 prm_posModel_Local    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;

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
//	} else {
//		matWorld = g_matWorld016;
//		colMaterialDiffuse = g_colMaterialDiffuse016;
//	}

    //頂点計算
    const float4 posModel_World = mul(prm_posModel_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま
    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_CubeMapMeshSet(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique CubeMapMeshSetTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_CubeMapMeshSet();
        PixelShader  = compile PS_VERSION PS_CubeMapMeshSet();
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
        VertexShader = compile VS_VERSION VS_CubeMapMeshSet();
        PixelShader  = compile PS_VERSION PS_CubeMapMeshSet();
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
        VertexShader = compile VS_VERSION VS_CubeMapMeshSet();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
