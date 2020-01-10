#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、GgafDx::SkinAniMeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
#define SkinAniMeshModel_MAX_BONE_WORLD_MATRIX (5)
/** モデルのWorld変換行列（フレーム毎） */
float4x4 g_matBone001;
float4x4 g_matBone002;
float4x4 g_matBone003;
float4x4 g_matBone004;
float4x4 g_matBone005;
float4x4 g_matBone006;
float4x4 g_matBone007;
float4x4 g_matBone008;
float4x4 g_matBone009;
float4x4 g_matBone010;
float4x4 g_matBone011;
float4x4 g_matBone012;
float4x4 g_matBone013;
float4x4 g_matBone014;
float4x4 g_matBone015;
float4x4 g_matBone016;
float4x4 g_matBone017;
float4x4 g_matBone018;
float4x4 g_matBone019;
float4x4 g_matBone020;
float4x4 g_matBone021;
float4x4 g_matBone022;
float4x4 g_matBone023;
float4x4 g_matBone024;
float4x4 g_matBone025;
float4x4 g_matBone026;
float4x4 g_matBone027;
float4x4 g_matBone028;
float4x4 g_matBone029;
float4x4 g_matBone030;


float4x4 g_matBoneOffset001;
float4x4 g_matBoneOffset002;
float4x4 g_matBoneOffset003;
float4x4 g_matBoneOffset004;
float4x4 g_matBoneOffset005;
float4x4 g_matBoneOffset006;
float4x4 g_matBoneOffset007;
float4x4 g_matBoneOffset008;
float4x4 g_matBoneOffset009;
float4x4 g_matBoneOffset010;
float4x4 g_matBoneOffset011;
float4x4 g_matBoneOffset012;
float4x4 g_matBoneOffset013;
float4x4 g_matBoneOffset014;
float4x4 g_matBoneOffset015;
float4x4 g_matBoneOffset016;
float4x4 g_matBoneOffset017;
float4x4 g_matBoneOffset018;
float4x4 g_matBoneOffset019;
float4x4 g_matBoneOffset020;
float4x4 g_matBoneOffset021;
float4x4 g_matBoneOffset022;
float4x4 g_matBoneOffset023;
float4x4 g_matBoneOffset024;
float4x4 g_matBoneOffset025;
float4x4 g_matBoneOffset026;
float4x4 g_matBoneOffset027;
float4x4 g_matBoneOffset028;
float4x4 g_matBoneOffset029;
float4x4 g_matBoneOffset030;


/** モデルのView変換行列 */
float4x4 g_matView;
/** モデルの射影変換行列 */
float4x4 g_matProj;
/** ライトの方向ベクトル（正規化済み） */
float3 g_vecLightFrom_World;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam_World;
/** 環境光の色 */
float4 g_colLightAmbient;
/** ライトの色(ライトの拡散反射時のライト自身の色) */
float4 g_colLightDiffuse;
/** モデルのマテリアル色(ライトによる拡散反射時のモデルの色) */
float4 g_colMaterialDiffuse;
/** スペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
float g_specular;
/** スペキュラーの強度 */
float g_specular_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** フェードイン・アウト機能(GgafDx::AlphaCurtain参照)のためのマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** -1.0 or 0.999 。遠くでも表示を強制したい場合に0.999 が代入される。*/
float g_far_rate;

//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

/** 頂点シェーダー出力構造体 */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //最終的な頂点座標(ワールド・ビュー・射影変換後)
    float2 uv              : TEXCOORD0;   //頂点テクスチャUV
    float4 color           : COLOR0;      //頂点カラー
    float3 vecNormal_World : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_World    : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
};
///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS VS_DefaultSkinAniMesh(
      float4 prm_posModel_Local  : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法線
      float  prm_index           : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float2 prm_uv              : TEXCOORD0 ,     // モデルの頂点のUV
      float4 infl_weight         : BLENDWEIGHT,
      int4   infl_bone_idx       : BLENDINDICES
) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = ((int)prm_index) % SkinAniMeshModel_MAX_BONE_WORLD_MATRIX;

    //頂点計算
    float4x4 matWorld;

    if (index == 0) {
        matWorld = g_matBone001;
    } else if (index == 1) {
        matWorld = g_matBone002;
    } else if (index == 2) {
        matWorld = g_matBone003;
    } else if (index == 3) {
        matWorld = g_matBone004;
    } else if (index == 4) {
        matWorld = g_matBone005;
    } else if (index == 5) {
        matWorld = g_matBone006;
    } else if (index == 6) {
        matWorld = g_matBone007;
    } else if (index == 7) {
        matWorld = g_matBone008;
    } else if (index == 8) {
        matWorld = g_matBone009;
    } else if (index == 9) {
        matWorld = g_matBone010;
    } else if (index == 10) {
        matWorld = g_matBone011;
    } else if (index == 11) {
        matWorld = g_matBone012;
    } else if (index == 12) {
        matWorld = g_matBone013;
    } else if (index == 13) {
        matWorld = g_matBone014;
    } else if (index == 14) {
        matWorld = g_matBone015;
    } else if (index == 15) {
        matWorld = g_matBone016;
    } else if (index == 16) {
        matWorld = g_matBone017;
    } else if (index == 17) {
        matWorld = g_matBone018;
    } else if (index == 18) {
        matWorld = g_matBone019;
    } else if (index == 19) {
        matWorld = g_matBone020;
    } else if (index == 20) {
        matWorld = g_matBone021;
    } else if (index == 21) {
        matWorld = g_matBone022;
    } else if (index == 22) {
        matWorld = g_matBone023;
    } else if (index == 23) {
        matWorld = g_matBone024;
    } else if (index == 24) {
        matWorld = g_matBone025;
    } else if (index == 25) {
        matWorld = g_matBone026;
    } else if (index == 26) {
        matWorld = g_matBone027;
    } else if (index == 27) {
        matWorld = g_matBone028;
    } else if (index == 28) {
        matWorld = g_matBone029;
    } else { //if (index == 29) {
        matWorld = g_matBone030;
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
    //拡散光色に反射率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color.rgb = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse.rgb;
    //αはライトに関係なくマテリアルαを優先とする
    out_vs.color.a = g_colMaterialDiffuse.a;

    //「頂点→カメラ視点」方向ベクトル。ピクセルシェーダーのスペキュラー計算で使用。
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

    //遠方時の表示方法。
    if (g_far_rate > 0.0) {
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {
            //本来視野外のZでも、描画を強制するため、射影後のZ座標を上書き、
            out_vs.posModel_Proj.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.posModel_Proj.z > 0.666f*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
            //  z : 0.666*g_zf ～ 1.0*g_zf  → α : 1.0 ～ 0.0  となるようにするには
            //  α = ( (0.0-1.0)*z - (0.666*g_zf*0.0) + (1.0*1.0*g_zf) ) / (1.0*g_zf-0.666*g_zf)
            //  α = (3.0*(g_zf-z))/g_zf = (3.0*g_zf - 3.0*z)/g_zf = 3.0 - 3.0*z/g_zf
            out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
        }
    }
    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_DefaultSkinAniMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2
) : COLOR  {
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    //出力色にテクスチャ色にマテリアルカラーを考慮
    float4 colOut = colTex * prm_color;
    //スペキュラ成分計算
    float s = 0.0f;
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }
    //出力色にスペキュラーを考慮
    colOut.rgb += s;
    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }
    //マスターα
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_DefaultSkinAniMesh2(
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


technique DefaultSkinAniMeshTechnique
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
    // float4x4 g_matBone		:	World変換行列
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
        VertexShader = compile VS_VERSION VS_DefaultSkinAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultSkinAniMesh();
    }
}

technique DefaultSkinAniMeshTechnique2
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSkinAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultSkinAniMesh2();
    }
}


