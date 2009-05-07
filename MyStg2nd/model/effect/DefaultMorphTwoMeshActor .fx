////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MorphTwoMeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/05/07 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
float　g_weight; //重み

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
OUT_VS GgafDx9VS_DefaultMorphTwoMesh(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv      : TEXCOORD0.      // モデルの頂点のUV

      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット頂点
      float4 prm_normal1 : NORMAL1         // モデルのモーフターゲット頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点ブレンド＆変換
	float4 pos = lerp(prm_pos0, prm_pos1, g_weight );           // ブレンド
	float4 posWorld = mul( pos, g_matWorld );                   // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                              // 出力に設定
    //法線ブレンド＆変換
	float3 normal = lerp(prm_normal0, prm_normal1, g_weight );  //ブレンド
    out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_DefaultMorphTwoMesh(
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
	//α計算、αは法線およびライト方向に依存しないとするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 

	return out_color;
}

technique DefaultMorphTwoMeshTechnique
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
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphTwoMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphTwoMesh();
	}
}

