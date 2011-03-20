/**
 * GgafDx9MeshModel用シェーダー .
 * 静的モデル１つを描画する標準的シェーダー。
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
/** モデルのテクスチャ点滅機能(GgafDx9TextureBlinker参照)の対象となるRGBのしきい値(0.0〜1.0) */
float g_tex_blink_threshold;
/** アルファカーテン(フェードイン・アウト)機能(GgafDx9AlphaCurtain参照)のマスターアルファ値(0.0〜1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
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
OUT_VS GgafDx9VS_DefaultMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*射影変換

	//UV計算
	out_vs.uv = prm_uv;  //そのまま

    //頂点カラー計算
	//法線を World 変換して正規化
    float3 normal = normalize(mul(prm_normal, g_matWorld)); 	
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
	float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;

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
float4 GgafDx9PS_DefaultMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinkerを考慮
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
	return out_color;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {                         
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);
	return out_color;
}


/**
 * 通常テクニック
 */
technique DefaultMeshTechnique
{
	//pass P0「メッシュ標準シェーダー」
	//メッシュを描画する
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

