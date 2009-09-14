////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MorphMeshModel用シェーダー
// author : Masatoshi Tsuge
// date:2009/05/12 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
int g_morph_target_num;  //メッシュパターン数(モーフターゲット数）、現在未使用
float g_weight1; //モーフターゲット１の重み
float g_weight2; //モーフターゲット２の重み
float g_weight3; //モーフターゲット３の重み
float g_weight4; //モーフターゲット４の重み
float g_weight5; //モーフターゲット５の重み
float g_weight6; //モーフターゲット６の重み
float g_weight7; //モーフターゲット７の重み
float g_weight8; //モーフターゲット８の重み
float g_weight9; //モーフターゲット９の重み

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

//モーフターゲットなし
OUT_VS GgafDx9VS_DefaultMorphMesh0(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0       // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
//	float4 posWorld = mul( prm_pos0, g_matWorld );               // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul( mul(mul( prm_pos0, g_matWorld ), g_matView ), g_matProj);//
    //法線計算
    out_vs.normal = normalize(mul(prm_normal0, g_matWorld)); 	//法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv0;
	return out_vs;
}

//モーフターゲット１つ
OUT_VS GgafDx9VS_DefaultMorphMesh1(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1         // モデルのモーフターゲット1頂点の法線

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	//頂点出力設定
//	float4 posWorld = mul( pos, g_matWorld );                   // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
	//法線出力設定
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv0;

	return out_vs;
}


//モーフターゲット２つ
OUT_VS GgafDx9VS_DefaultMorphMesh2(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2         // モデルのモーフターゲット2頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	//頂点出力設定
//	float4 posWorld = mul( pos, g_matWorld );                   // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
	//法線出力設定
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット３つ
OUT_VS GgafDx9VS_DefaultMorphMesh3(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3         // モデルのモーフターゲット3頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}
	//頂点出力設定
//	float4 posWorld = mul( pos, g_matWorld );                   // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
	//法線出力設定
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット４つ
OUT_VS GgafDx9VS_DefaultMorphMesh4(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_pos4    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_normal4 : NORMAL4         // モデルのモーフターゲット4頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}
	if (g_weight4 != 0 ) {
		pos += ((prm_pos4 - prm_pos0) * g_weight4);
		normal = lerp(normal, prm_normal4, g_weight4);
	}
	//頂点出力設定
//	float4 posWorld = mul( pos, g_matWorld );                   // World変換
//	float4 posWorldView = mul(posWorld, g_matView );            // View変換
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
	//法線出力設定
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
	//UVはそのまま
	out_vs.uv = prm_uv0;

	return out_vs;
}


//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_DefaultMorphMesh(
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
	//α計算、αは法線およびライト方向に依存しない事とするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 

	return out_color;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_DefaultMorphMesh2(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//求める色
	float4 out_color; 
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	out_color = g_MaterialDiffuse * tex_color;
	//α計算、αは法線およびライト方向に依存しない事とするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 

	return out_color;
}



technique DefaultMorphMeshTechnique
{
	//「メッシュ標準シェーダー」
	//メッシュを描画する
	//【考慮される要素】
	//--- VS ---
	//・頂点を World、View、射影 変換
	//・法線を World変換
	//--- PS ---
	//・Diffuseライト色(α色は無視)
	//・Ambientライト色(α色は無視)
	//・平行光ライト方向
	//・環境光ライト
	//・オブジェクトのマテリアルのDiffuse反射（Ambient反射と共通）
	//・オブジェクトのテクスチャ
	//・オブジェクトのマテリアル半透明α（Diffuse反射αとテクスチャαの乗算）
	//【使用条件】
	//・テクスチャが存在しs0レジスタにバインドされていること。
	//【設定パラメータ】
	// float g_weight1～9       :   重み1～9(必要なターゲット分だけ)
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列   
	// float3 g_LightDirection	:	ライトの方向
	// float4 g_LightAmbient	:	Ambienライト色（入射色）
	// float4 g_LightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				:	2Dテクスチャ

	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh4();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	//以下同様に P9 まで拡張可能。
	//でも、そんなに必要ないので省略。

}


technique DefaultMorphMeshTechnique2
{

	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh2();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh2();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh2();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh2();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh4();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh2();
	}

	//以下同様に P9 まで拡張可能。
	//でも、そんなに必要ないので省略。

}

