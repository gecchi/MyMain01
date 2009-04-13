////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshModel用シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_X; //一つ前を行くチップX
float g_Y; //一つ前を行くチップX
float g_Z; //一つ前を行くチップX



float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ワールド変換した法線
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	if (prm_pos.x > 0) {
		out_vs.pos.x = g_X;  // 出力に設定
		out_vs.pos.y = g_Y;  // 出力に設定
		out_vs.pos.z = g_Z;  // 出力に設定
	} else {

		//頂点計算
		float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
		float4 posWorldView = mul(posWorld, g_matView );            // View変換
		float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
		out_vs.pos = posWorldViewProj;                              // 出力に設定
	}
	//法線計算
	out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 	//法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_LaserChip(
	float4 prm_in_color : COLOR0,
	float2 prm_uv	    : TEXCOORD0,
	float3 prm_normal   : TEXCOORD1
) : COLOR  {
	//求める色
	float4 out_color; 

	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                

	if (prm_in_color.a < tex_color.a) {
		out_color.a = tex_color.a;               
	} else {
		out_color.a = prm_in_color.a;
	}

	if (prm_in_color.r < tex_color.r) {
		out_color.r = tex_color.r;               
	} else {
		out_color.r = prm_in_color.r;               
	}

	if (prm_in_color.g < tex_color.g) {
		out_color.g = tex_color.g;               
	} else {
		out_color.g = prm_in_color.g;               
	}

	if (prm_in_color.a < tex_color.b) {
		out_color.b = tex_color.b;               
	} else {
		out_color.b = prm_in_color.b;               
	}

	//α計算、
	out_color.a = g_MaterialDiffuse.a * out_color.a ; 

	return out_color;
}

technique LaserChipTechnique
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
	//・オブジェクトのマテリアルのDiffuse反射（Ambient反射と共通）
	//・オブジェクトのテクスチャ
	//・半透明α（Diffuse反射αとテクスチャαの乗算）
	//【使用条件】
	//・テクスチャが存在しs0レジスタにバインドされていること。
	//【設定パラメータ】
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列   
	// float3 g_LightDirection	:	ライトの方向
	// float4 g_LightAmbient	:	Ambienライト色（入射色）
	// float4 g_LightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}
}



