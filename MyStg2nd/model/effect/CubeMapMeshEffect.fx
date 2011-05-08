#include "GgafEffectConst.fx" 
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */

//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
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
/** モデルのテクスチャ点滅機能(GgafDx9TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;   
/** モデルのテクスチャ点滅機能(GgafDx9TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** アルファカーテン(フェードイン・アウト)機能(GgafDx9AlphaCurtain参照)のマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
/** 頂点シェーダー、出力構造体 */
struct OUT_VS {                   
    float4 pos   : POSITION;      
    float3 normal: TEXCOORD0;    	// ワールド空間の法線
    float3 viewVecW: TEXCOORD1;  	// ワールド空間での視線ベクトル
    float4 col : COLOR0;
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
OUT_VS GgafDx9VS_CubeMapMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL   
) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
	out_vs.pos = mul(prm_pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
	float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
	//拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse * float4(2.0, 2.0, 2.0, 1.0); //全体的に明るくする;
    //αフォグ
	out_vs.col.a = g_colMaterialDiffuse.a;
	if (out_vs.pos.z > (g_zf*0.9)*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
	} 
	//マスターα
	out_vs.col.a *= g_alpha_master;

	return out_vs;
}

/**
 * 通常ピクセルシェーダー（テクスチャ有り）
 */
float4 GgafDx9PS_CubeMapMesh(
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_col    : COLOR0
) : COLOR  {
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_col;
    //Blinkerを考慮
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
    return out_color;
}

float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_col    : COLOR0
) : COLOR  {                         
	//テクスチャをサンプリングして色取得（原色を取得）
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);;
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
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

