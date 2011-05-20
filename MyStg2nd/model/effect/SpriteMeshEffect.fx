#include "GgafEffectConst.fx" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
float g_specular;
float g_specular_power;


float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_vecLightDirection; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

float g_offset_u;
float g_offset_v;

//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
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
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS GgafDx9VS_SpriteMesh(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
    //UV
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;

	//法線を World 変換して正規化
    float3 normal = normalize(mul(prm_normal, g_matWorld)); 	
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
	//αフォグ
	out_vs.color.a = g_colMaterialDiffuse.a;
	if (out_vs.pos.z > (g_zf*0.9)*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.color.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.color.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//マスターα
	out_vs.color.a *= g_alpha_master;

	return out_vs;
}

OUT_VS VS_NoLight(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
    //UV
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;
	//、マテリアル色 を考慮したカラー作成。      
	out_vs.color = g_colMaterialDiffuse;
	//マスターα
	out_vs.color.a *= g_alpha_master;
	return out_vs;
}


//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_SpriteMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color;

    //Blinkerを考慮
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
	} 
	return out_color;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color * float4(7.0, 7.0, 7.0, 1.0);;
	return out_color;
}

float4 PS_NoLight(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color;
    //Blinkerを考慮
//	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
//		out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
//	} 
	return out_color;
}

technique SpriteMeshTechnique
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
	// float3 g_vecLightDirection	:	ライトの方向
	// float4 g_colLightAmbient	:	Ambienライト色（入射色）
	// float4 g_colLightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_colMaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				    D3DXHANDLE _h_cnt_vertec;:	2Dテクスチャ
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile VS_VERSION GgafDx9VS_SpriteMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_SpriteMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_SpriteMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_SpriteMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_SpriteMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

technique NoLight
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION VS_NoLight();
		PixelShader  = compile PS_VERSION PS_NoLight();
	}
}

