////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


int g_nVertexs;

float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse001;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse002;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse003;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse004;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse005;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse006;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse007;  //マテリアルのDiffuse反射色と、Ambien反射色
float4 g_MaterialDiffuse008;  //マテリアルのDiffuse反射色と、Ambien反射色

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
	float4 col    : COLOR0;
	float3 normal : TEXCOORD1;   // ワールド変換した法線
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultMeshSet(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,    // モデルの頂点番号
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	float4 colorMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

	if (index == 0) {
		matWorld = g_matWorld001;
		colorMaterialDiffuse = g_MaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colorMaterialDiffuse = g_MaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colorMaterialDiffuse = g_MaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colorMaterialDiffuse = g_MaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colorMaterialDiffuse = g_MaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colorMaterialDiffuse = g_MaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colorMaterialDiffuse = g_MaterialDiffuse007;
	} else {
		matWorld = g_matWorld008;
		colorMaterialDiffuse = g_MaterialDiffuse008;
	} 

//	float4 posWorld = mul( prm_pos, matWorld );               // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul( mul(mul( prm_pos, matWorld ), g_matView ), g_matProj); //World*View*射影変換
    //法線計算
    out_vs.normal = normalize(mul(prm_normal, matWorld)); 	//法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv;
	out_vs.col = colorMaterialDiffuse;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_DefaultMeshSet(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_col    : COLOR0
) : COLOR  {
	//求める色
	float4 out_color; 
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	out_color =  g_LightDiffuse * prm_col * tex_color * power; 
	//Ambient色を加算。本シェーダーではマテリアルのAmbien反射色は、マテリアルのDiffuse反射色と同じ色とする。
	out_color =  (g_LightAmbient * prm_col * tex_color) + out_color;  
	//α計算、αは法線およびライト方向に依存しないとするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = prm_col.a * tex_color.a ;    // tex_color.a はマテリアルα＊テクスチャα

	return out_color;
}

float4 GgafDx9PS_DefaultMeshSet2(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_col    : COLOR0
) : COLOR  {
	//求める色
	float4 out_color; 
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	out_color =  g_LightDiffuse * prm_col * tex_color; 
	//α計算、αは法線およびライト方向に依存しないとするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = prm_col.a * tex_color.a ;    // tex_color.a はマテリアルα＊テクスチャα

	return out_color;
}

technique DefaultMeshSetTechnique
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
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列   
	// float3 g_LightDirection	:	ライトの方向
	// float4 g_LightAmbient	:	Ambienライト色（入射色）
	// float4 g_LightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMeshSet();
	}
}


technique DefaultMeshSetTechnique2
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMeshSet2();
	}
}

