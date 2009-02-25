////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ用、標準シェーダー
// 
// 概要：World、View、射影変換して、マテリアルとテクスチャだけを考慮してレンダリング
//
// パラメータ:
// float4x4 g_matWorld		:	World変換行列
// float4x4 g_matView		:	View変換行列
// float4x4 g_matProj		:	射影変換行列
// float4 g_MaterialAmbient	:	マテリアルのAmbien反射色
// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射色
//
// Auther:Masatoshi Tsuge
// date:2009/02/04 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_LightDirection = float3( -0.577, 0.577, -0.577 );      // ライトの方向

float4 g_LightAmbient = float4( 0.2, 0.2, 0.2, 0.2 );   // Ambienライト色（入射色）
float4 g_LightDiffuse = float4( 1, 1, 1, 1 );           // Diffuseライト色（入射色）

float4 g_MaterialAmbient;  //マテリアルのAmbien反射色
float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色


texture g_diffuseMap;
sampler MyTextureSampler = sampler_state {
	texture = <g_diffuseMap>;
};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 color  : COLOR0;
    float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float2 prm_uv     : TEXCOORD0,     // モデルの頂点のUV
      float3 prm_normal : NORMAL         // モデルの頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定

    //法線計算
    float3 normal = normalize(mul(prm_normal, posWorldView)); //法線を World 変換

	//カラー計算(光源計算)し、出力に設定
	out_vs.color = (g_LightDiffuse * g_MaterialDiffuse * max( dot(g_LightDirection, normal), 0)) +
                   (g_LightAmbient * g_MaterialAmbient);

	//αは別でせっていするのがいいのではないのか

	//UV計算を出力に設定
	out_vs.uv = prm_uv;

	return out_vs;
}

// ピクセルシェーダ
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0 
) : COLOR  {
	//テクスチャ処理
	return tex2D( MyTextureSampler, prm_uv );// * prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
