
float4x4 g_matWorld;  //ワールド変換行列
float4x4 g_matView;   //VIEW変換行列
float4x4 g_matPro;    //射影変換行列

float3 g_LD = float3( 1, 0, 0 );      // ライトの方向
float4 g_LC = float4( 1, 1, 1, 1 );   // ライトカラー（入射色）

texture g_diffuseMap;
sampler MyTextureSampler = sampler_state {
	texture = <g_diffuseMap>;
};

//texture	Tex1;		//テクスチャ
//sampler TextureSampler = sampler_state
//{
//    Texture = <Tex1>;
//	//フィルタ設定
//    MinFilter = LINEAR;
//    MagFilter = LINEAR;
//    MipFilter = LINEAR;    
//    //テクスチャラッピング
//    AddressU = Wrap;
//    AddressV = Wrap;
//};
// 
//頂点シェーダー出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
    float2 uv     : TEXCOORD0;
    float3 normal : TEXCOORD1; // ピクセルシェーダーに法線情報を渡すために TEXCOORD1 とする
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,       // モデルの頂点
      float2 prm_uv     : TEXCOORD0,      // モデルの頂点のUV
      float3 prm_normal : NORMAL         // モデルの頂点の法線
) {

	//頂点計算
	float4 pos;   // 出力頂点座標
	pos = mul( prm_pos, g_matWorld );   // ワールド変換
	pos = mul( pos, g_matView );    // ビュー変換
	pos = mul( pos, g_matPro );    // 射影変換

    //法線計算
	float3 normal;
	normal = mul( prm_normal, g_matWorld );  //法線をワールド変換

	//UV計算


	//出力へ代入
	OUT_VS out_vs = (OUT_VS)0;
	out_vs.pos    = pos;
	out_vs.uv     = prm_uv; //ピクセルシェーダーへ
	out_vs.normal = normal; //ピクセルシェーダーへ
	return out_vs;
}

// ピクセルシェーダ
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,  //頂点シェーダーでワールド変換済みの法線
    float4 prm_color : COLOR0 
) : COLOR  {
	//テクスチャ処理
	prm_color = tex2D( MyTextureSampler, prm_uv ) * prm_color;
    return prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
