////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshSetModel用シェーダー
// 【概要】
// 頂点バッファに、同じモデルキャラの頂点情報が、複数個分繰り返し詰め込んである。
// ステートやレジスタの更新を行わず、１回の DrawIndexedPrimitiveで、最大
// １２オブジェクトまで描画。高速化を狙う。
// 大量の同じ敵や弾には、このシェーダーで描画することとする。
// 但し、１オブジェクトにつきマテリアル設定は１つだけという制限がある。
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ライトの方向
float3 g_vecLightDirection;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）  
float4 g_colLightDiffuse;  
//View変換行列
float4x4 g_matView; 
//射影変換行列  
float4x4 g_matProj;  
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
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
float4x4 g_matWorld020;
float4x4 g_matWorld021;
float4x4 g_matWorld022;
float4x4 g_matWorld023;
float4x4 g_matWorld024;
float4x4 g_matWorld025;
float4x4 g_matWorld026;
float4x4 g_matWorld027;



//テクスチャのサンプラ(s0レジスタ)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS GgafDx9VS_SingleLaser(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	float4 colorMaterialDiffuse;

	if (index == 0) {		
		matWorld = g_matWorld001;	
	} else if (index == 1) {		
		matWorld = g_matWorld002;	
	} else if (index == 2) {		
		matWorld = g_matWorld003;	
	} else if (index == 3) {		
		matWorld = g_matWorld004;	
	} else if (index == 4) {		
		matWorld = g_matWorld005;	
	} else if (index == 5) {		
		matWorld = g_matWorld006;	
	} else if (index == 6) {		
		matWorld = g_matWorld007;	
	} else if (index == 7) {		
		matWorld = g_matWorld008;	
	} else if (index == 8) {		
		matWorld = g_matWorld009;	
	} else if (index == 9) {		
		matWorld = g_matWorld010;	
	} else if (index == 10) {		
		matWorld = g_matWorld011;	
	} else if (index == 11) {		
		matWorld = g_matWorld012;	
	} else if (index == 12) {		
		matWorld = g_matWorld013;	
	} else if (index == 13) {		
		matWorld = g_matWorld014;	
	} else if (index == 14) {		
		matWorld = g_matWorld015;	
	} else if (index == 15) {		
		matWorld = g_matWorld016;	
	} else if (index == 16) {		
		matWorld = g_matWorld017;	
	} else if (index == 17) {		
		matWorld = g_matWorld018;	
	} else if (index == 18) {		
		matWorld = g_matWorld019;	
	} else if (index == 19) {		
		matWorld = g_matWorld020;	
	} else if (index == 20) {		
		matWorld = g_matWorld021;	
	} else if (index == 21) {		
		matWorld = g_matWorld022;	
	} else if (index == 22) {		
		matWorld = g_matWorld023;	
	} else if (index == 23) {		
		matWorld = g_matWorld024;	
	} else if (index == 24) {		
		matWorld = g_matWorld025;	
	} else if (index == 25) {		
		matWorld = g_matWorld026;	
	} else if (index == 26) {		
		matWorld = g_matWorld027;	
	} 


	//World*View*射影変換
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);
	//UVはそのまま
	out_vs.uv = prm_uv;
	//αフォグ
	out_vs.col = float4(1.0, 1.0, 1.0, 1.0);
	if (out_vs.pos.z > g_zf*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
	out_vs.col.a *= g_alpha_master;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_SingleLaser(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {

	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	float4 out_color = tex_color * prm_col;
	return out_color;
}

technique SingleLaserTechnique
{
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //加算合成
		DestBlend = One;

//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_SingleLaser();
		PixelShader  = compile ps_2_0 GgafDx9PS_SingleLaser();
	}
}

