#include "GgafEffectConst.fxh" 
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
float g_reflectance;
float g_specular;
float g_specular_power;

/** カメラのWorld位置 */
float3 pos_camera; 
/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのView変換行列 */
float4x4 g_matView;
/** モデルの射影変換行列 */
float4x4 g_matProj;
/** ライトの方向 */
float3 g_vecLightDirection;
/** 環境光色（入射色）*/
float4 g_colLightAmbient;
/** 拡散光色（入射色）*/
float4 g_colLightDiffuse;
/** モデルのマテリアル色（表面色）。いわゆる拡散光反射色で環境光反射色も兼ねる */
float4 g_colMaterialDiffuse;
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の点滅強度 */
float g_tex_blink_power;   
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の対象となるRGBのしきい値(0.0〜1.0) */
float g_tex_blink_threshold;
/** アルファカーテン(フェードイン・アウト)機能(GgafDxAlphaCurtain参照)のマスターアルファ値(0.0〜1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color  : COLOR0;
    float3 normal : TEXCOORD1;   // ワールド変換した法線
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};
/**
 * 標準的な頂点シェーダー .
 * 頂点バッファには、
 * 頂点を World > View > 射影 変換し、頂点カラーの設定を行っている。
 * モデルのマテリアル色付、つまり
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、は
 * 速度重視のためピクセルシェーダーで行わず、頂点カラーで実現している。
 * @param prm_pos    モデル頂点のローカル座標
 * @param prm_normal モデル頂点の法線
 * @param prm_normal モデル頂点のUV座標
 */
OUT_VS GgafDxVS_CubeMapMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
 	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま
    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.normal = normalize(mul(prm_normal, g_matWorld));     
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;


//	OUT_VS out_vs = (OUT_VS)0;
//	//頂点計算
//	out_vs.pos = mul(prm_pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
//    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
//    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
//	float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
//	//拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
//	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse * float4(2.0, 2.0, 2.0, 1.0); //全体的に明るくする;
//    //αフォグ
//	out_vs.color.a = g_colMaterialDiffuse.a;
//    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
//    }
//	//マスターα
//	out_vs.color.a *= g_alpha_master;
//
//	return out_vs;
}

/**
 * 通常ピクセルシェーダー（テクスチャ有り）
 */
float4 GgafDxPS_CubeMapMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_cam, prm_normal));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * g_alpha_master; 
	return out_color;




//	float3 vReflect = reflect( prm_viewVecW, prm_normal );
//    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
//	float4 out_color = tex_color * prm_color;
//    //Blinkerを考慮
//	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
//		out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
//	} 
//    return out_color;
}

float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_color    : COLOR0
) : COLOR  {                         
	//テクスチャをサンプリングして色取得（原色を取得）
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
	return out_color;
}


/**
 * 通常テクニック
 */
technique CubeMapMeshTechnique
{
	//pass P0「メッシュ標準シェーダー」
	//メッシュを描画する
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

