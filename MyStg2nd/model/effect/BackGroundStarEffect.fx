////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、BackGroundStar001用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_vecLightDirection; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）
float g_alpha_master;   



float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

float g_tex_blink_power;   
float g_tex_blink_threshold;

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS BackGroundStarVS_DefaultMesh(
      float4 prm_pos    : POSITION      // モデルの頂点

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 BackGroundStarPS_DefaultMesh(
) : COLOR  {
	//求める色
	return float4( 1, 1, 1, 0.9 );
}


technique BackGroundStarTechnique
{
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 BackGroundStarVS_DefaultMesh();
		PixelShader  = compile ps_2_0 BackGroundStarPS_DefaultMesh();
	}
}

