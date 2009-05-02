////////////////////////////////////////////////////////////////////////////////
// レーザーチップ用シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

int g_kind; //チップ種類 1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）

float g_X; //一つ前を行くチップX
float g_Y; //一つ前を行くチップY
float g_Z; //一つ前を行くチップZ

float4x4 g_matWorld;  //自身のWorld変換行列
float4x4 g_matWorld_front;  //一つ前を行くチップのWorld変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//レーザーチップ頂点シェーダー
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
//
	if (g_X - g_matWorld._41 < 0) {
		prm_pos.z = -prm_pos.z;
	}
//
//	if (g_Y - g_matWorld._42 < 0) {
//		prm_pos.y = -prm_pos.y;
//	}
//
	if (abs(g_Z - g_matWorld._43) < 1.5) {
		if (abs(g_Y - g_matWorld._42) < 1.0) {
			prm_pos.z = 0;
		}
	}

	float4 posWorld;
	if (prm_pos.x > 0) {        
		float4x4 matWorld = g_matWorld_front;
		matWorld._41 = g_X;  // 一つ前方のチップ座標へ
		matWorld._42 = g_Y;  
		matWorld._43 = g_Z;  
		posWorld = mul( prm_pos, matWorld );  // World変換
	} else {
		//頂点計算
		posWorld = mul( prm_pos, g_matWorld );        // World変換
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View変換
	out_vs.pos          = mul(posWorldView, g_matProj);  // 射影変換

	//UV
	if (g_kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (g_kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		out_vs.uv = prm_uv;
	}
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One;

		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}



