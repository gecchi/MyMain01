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

float3 g_LightDirection = normalize(float3( -1, -1, 1 ));      // ライトの方向

float4 g_LightAmbient = float4( 0.3f, 0.3f, 0.3f, 1.0f );   // Ambienライト色（入射色）
float4 g_LightDiffuse = float4( 1.0f, 1.0f, 1.0f, 1.0f );           // Diffuseライト色（入射色）

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
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ワールド変換した法線
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	float4 posWorld = mul( prm_pos, g_matWorld );               // World変換
	float4 posWorldView = mul(posWorld, g_matView );            // View変換
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // 射影変換
	out_vs.pos = posWorldViewProj;                            // 出力に設定

    //法線計算
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); //法線を World 変換し、正規化

//	//カラー計算(光源計算)し、出力に設定
//	out_vs.color = (g_LightDiffuse * g_MaterialDiffuse * max( dot(g_LightDirection, normal), 0)) +
//                   (g_LightAmbient * g_MaterialAmbient);

	//UV
	out_vs.uv = prm_uv;

	return out_vs;
}


// ピクセルシェーダ
//テクスチャ色、Diffuseライト色、Ambientライト色、ライト方向を考慮して
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	// 色を算出
	float4 out_color; //求める色


    //Diffuse色計算
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          //法線と、Diffuseライト方向の内積を計算し、face に対するライト方向の入射角による減衰具合を求める。
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                //テクスチャ原色を取得
//	out_color = tex_color;
	out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; //ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色の完成！。              

	//Ambient色を加算
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  //マテリアルのAmbien反射色は、マテリアルのDiffuse反射色と同じ色とする。

	//α計算
	out_color.a = g_LightDiffuse.a * g_LightAmbient.a * g_MaterialDiffuse.a * tex_color.a ; //但しαは法線、ライト方向が関係ないので別計算、全部掛ける。

	return out_color;   // 反射色

	//return float4( 1, 1, 1, 1 );//prm_color;

	//テクスチャ処理
	//return tex2D( MyTextureSampler, prm_uv );// * prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
