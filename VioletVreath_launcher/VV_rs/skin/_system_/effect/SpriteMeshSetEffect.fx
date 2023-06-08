#include "GgafDx_World3DimEffect.fxh"
// author : Masatoshi Tsuge
// date:2009/03/06

//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
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

float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;
float g_offset_u010;
float g_offset_u011;
float g_offset_u012;
float g_offset_u013;
float g_offset_u014;
float g_offset_u015;
//float g_offset_u016;

float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;
float g_offset_v010;
float g_offset_v011;
float g_offset_v012;
float g_offset_v013;
float g_offset_v014;
float g_offset_v015;
//float g_offset_v016;

//テクスチャのサンプラ(s0レジスタ)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
    float2 uv     : TEXCOORD0;
    float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS VS_SpriteMeshSet(
    float4 prm_posModel_Local  : POSITION,  // モデルの頂点
    float  prm_index           : PSIZE ,    // モデルのインデックス（何個目のオブジェクトか？）
    float3 prm_vecNormal_Local : NORMAL,    // モデルの頂点の法線
    float2 prm_uv              : TEXCOORD0  // モデルの頂点のUV
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;

    //頂点計算
    float4x4 matWorld;
    float offsetU;
    float offsetV;
    float4 colMaterialDiffuse;

    if (index == 0) {
        matWorld = g_matWorld001;
        colMaterialDiffuse = g_colMaterialDiffuse001;
        offsetU  = g_offset_u001;
        offsetV  = g_offset_v001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
        colMaterialDiffuse = g_colMaterialDiffuse002;
        offsetU  = g_offset_u002;
        offsetV  = g_offset_v002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
        colMaterialDiffuse = g_colMaterialDiffuse003;
        offsetU  = g_offset_u003;
        offsetV  = g_offset_v003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
        colMaterialDiffuse = g_colMaterialDiffuse004;
        offsetU  = g_offset_u004;
        offsetV  = g_offset_v004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
        colMaterialDiffuse = g_colMaterialDiffuse005;
        offsetU  = g_offset_u005;
        offsetV  = g_offset_v005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
        colMaterialDiffuse = g_colMaterialDiffuse006;
        offsetU  = g_offset_u006;
        offsetV  = g_offset_v006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
        colMaterialDiffuse = g_colMaterialDiffuse007;
        offsetU  = g_offset_u007;
        offsetV  = g_offset_v007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
        colMaterialDiffuse = g_colMaterialDiffuse008;
        offsetU  = g_offset_u008;
        offsetV  = g_offset_v008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
        colMaterialDiffuse = g_colMaterialDiffuse009;
        offsetU  = g_offset_u009;
        offsetV  = g_offset_v009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
        colMaterialDiffuse = g_colMaterialDiffuse010;
        offsetU  = g_offset_u010;
        offsetV  = g_offset_v010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
        colMaterialDiffuse = g_colMaterialDiffuse011;
        offsetU  = g_offset_u011;
        offsetV  = g_offset_v011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
        colMaterialDiffuse = g_colMaterialDiffuse012;
        offsetU  = g_offset_u012;
        offsetV  = g_offset_v012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
        colMaterialDiffuse = g_colMaterialDiffuse013;
        offsetU  = g_offset_u013;
        offsetV  = g_offset_v013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
        colMaterialDiffuse = g_colMaterialDiffuse014;
        offsetU  = g_offset_u014;
        offsetV  = g_offset_v014;
    } else { //if (index == 14) {
        matWorld = g_matWorld015;
        colMaterialDiffuse = g_colMaterialDiffuse015;
        offsetU  = g_offset_u015;
        offsetV  = g_offset_v015;
    }
//	else {
//		matWorld = g_matWorld016;
//		colMaterialDiffuse = g_colMaterialDiffuse016;
//		offsetU  = g_offset_u016;
//		offsetV  = g_offset_v016;
//	}
    //World*View*射影変換
    out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);
    //法線計算
    //out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	//法線を World 変換して正規化
    //UVはそのまま
    out_vs.uv.x = prm_uv.x + offsetU;
    out_vs.uv.y = prm_uv.y + offsetV;
    //頂点カラー計算

    //法線を World 変換して正規化
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * colMaterialDiffuse;
    //αフォグ
    out_vs.color.a = colMaterialDiffuse.a;
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_SpriteMeshSet(
    float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0
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

float4 PS_Flush(
    float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    const float4 colOut = colTex * prm_color * FLUSH_COLOR;
    return colOut;
}

technique SpriteMeshSetTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_SpriteMeshSet();
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
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_SpriteMeshSet();
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
        VertexShader = compile VS_VERSION VS_SpriteMeshSet();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
