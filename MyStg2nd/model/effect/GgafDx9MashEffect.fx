////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ用、メッシュ標準シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/02/04 
////////////////////////////////////////////////////////////////////////////////

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
OUT_VS GgafDx9VS_DefaultMesh(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
    //法線計算
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 	//法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー
float4 GgafDx9PS_DefaultMesh(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//求める色
	float4 out_color; 

    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; 
	//Ambient色を加算。マテリアルのAmbien反射色は、マテリアルのDiffuse反射色と同じ色とする。
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  
	//α計算、αは法線、ライト方向が関係なしにするので別計算。本来ライトα色も掛けるが、ライトは省略。
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 
	return out_color;
}

//メッシュ標準ピクセルシェーダー（テクスチャ無し）
float4 GgafDx9PS_NoTexMesh(
	float2 prm_uv     : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//求める色
	float4 out_color; 

    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//ライト方向、ライト色、マテリアル色、を考慮した色作成。              
	out_color = g_LightDiffuse * g_MaterialDiffuse * power; 
	//Ambient色を加算。マテリアルのAmbien反射色は、マテリアルのDiffuse反射色と同じ色とする。
	out_color =  (g_LightAmbient * g_MaterialDiffuse) + out_color;  
	//マテリアルα。
	out_color.a = g_MaterialDiffuse.a; 
	return out_color;
}

technique DefaultMeshTechnique
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
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMesh();
	}
}

technique NoTexMeshTechnique {
	//pass P1「メッシュ標準シェーダー（テクスチャ無し）」
	//【考慮される要素】
	//--- VS ---
	//・頂点を World、View、射影 変換
	//・法線を World変換
	//--- PS ---
	//・Diffuseライト色
	//・Ambientライト色
	//・ライト方向
	//・オブジェクトのマテリアルのDiffuse反射（Ambient反射と共通）
	//・半透明α（マテリアルDiffuse反射αのみ）
	//【使用条件】
	//【設定パラメータ】
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列
	// float3 g_LightDirection	:	ライトの方向
	// float4 g_LightAmbient	:	Ambienライト色（入射色）
	// float4 g_LightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	pass P1 {
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_NoTexMesh();
	}


}
