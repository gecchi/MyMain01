#include "GgafEffectConst.fxh" 
/**
 * GgafLib::DefaultMeshActor 用シェーダー .
 * 静的モデル１つを描画する標準的なシェーダー。
 * 頂点バッファフォーマットは
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
 * を、前提とする。
 * @author Masatoshi Tsuge
 * @since 2009/03/06 
 */

/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのView変換行列 */
float4x4 g_matView;
/** モデルの射影変換行列 */
float4x4 g_matProj;
/** ライトの方向ベクトル（正規化済み） */
float3 g_vecLightDirection;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam;
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
/** モデルのテクスチャ色点滅機能(GgafDxTextureBlinker参照)の点滅強度 */
float g_tex_blink_power;   
/** モデルのテクスチャ色点滅機能(GgafDxTextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** フェードイン・アウト機能(GgafDxAlphaCurtain参照)のためのマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** -1.0 or 0.999 。遠くでも表示を強制したい場合に0.999 が代入される。*/ 
float g_far_rate;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler BumpMapTextureSampler : register(s2);  

/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 pos    : POSITION;    //座標
    float2 uv     : TEXCOORD0;   //テクスチャUV
    float4 color  : COLOR0;      //頂点カラー
    float3 normal : TEXCOORD1;   //オブジェクトの法線ベクトル
    float3 eye    : TEXCOORD2;   //頂点 -> 視点 ベクトル
    float3 light  : TEXCOORD3;   
};

/**
 * GgafLib::DefaultMeshActor 用の標準頂点シェーダー .
 * 頂点を World > View > 射影 変換した後、
 * モデルのマテリアル色付を頂点カラーの設定で行う。
 * マテリアル色付とは具体位的に
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、の事。
 * @param prm_pos    頂点のローカル座標
 * @param prm_normal 頂点の法線
 * @param prm_uv     頂点のUV座標
 */
OUT_VS GgafDxVS_DefaultMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0,
      float3 prm_tangent  : TANGENT,
      float3 prm_binormal : BINORMAL 
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld); //World変換
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影

    //UV計算
    out_vs.uv = prm_uv;  //そのまま

    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.normal = normalize(mul(prm_normal, g_matWorld));  

    float3 L = -g_vecLightDirection;
	out_vs.light.x = dot(L,prm_tangent);
	out_vs.light.y = dot(L,prm_binormal);
	out_vs.light.z = dot(L,prm_normal);
    out_vs.light =  normalize(out_vs.light);
   

    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル（スペキュラで使用）                                                        
    //out_vs.eye = normalize(g_posCam.xyz - posWorld.xyz);
    float3 E = g_posCam.xyz - posWorld.xyz;
    out_vs.eye.x = dot(E, prm_tangent);
	out_vs.eye.y = dot(E, prm_binormal);
	out_vs.eye.z = dot(E, prm_normal);
    out_vs.eye =  normalize(out_vs.eye);

    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;

    //遠方時の表示方法。
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //マスターα
    out_vs.color.a *= g_alpha_master;

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor 用の標準ピクセルシェーダー .
 * @param prm_uv     ピクセルでのUV座標
 * @param prm_color  ピクセルでの色（頂点カラーによる）
 * @param prm_normal ピクセルでの法線
 * @param prm_eye    ピクセルでの座標 -> 視点 ベクトル
 */
float4 GgafDxPS_DefaultMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_eye    : TEXCOORD2,   //頂点 -> 視点 ベクトル
    float3 prm_light    : TEXCOORD3   
) : COLOR  {

    float3 new_normal = 2.0f * tex2D( BumpMapTextureSampler, prm_uv).xyz-1.0;// 法線マップからの法線

    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(new_normal, -prm_light ), 0);      


    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_eye + (-prm_light));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(new_normal, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
    //テクスチャ色に        
    float4 out_color = tex_color * prm_color * power + s;
    //Blinkerを考慮
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    } 
    //マスターα
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * GgafLib::DefaultMeshActor 用の閃光ピクセルシェーダー .
 * テクスチャ原色を FLUSH_COLOR 倍して設定。
 * @param prm_uv     ピクセルでのUV座標
 * @param prm_color  ピクセルでの色（頂点カラーによる）
 */
float4 PS_Flush( 
    float2 prm_uv  : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {                         
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
    float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * 通常テクニック .
 */
technique DefaultMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

/**
 * 加算合成テクニック .
 */
technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;   
        DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

/**
 * 閃光テクニック .
 */
technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

