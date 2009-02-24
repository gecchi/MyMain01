float4x4 g_matWorld;  //ワールド変換行列
float4x4 g_matView;   //VIEW変換行列
float4x4 g_matPro;    //射影変換行列

// バーテックスシェーダ
struct OUT_VS
{
    float4 pos    : POSITION;
    float2 uv     : TEXCOORD0;
};



OUT_VS Default_VS(
      float4 prm_pos    : POSITION,          // モデルの頂点
      float2 prm_uv     : TEXCOORD0          // モデルのUV
) {

	//頂点計算
	float4 pos;   // 出力頂点座標
	pos = mul( prm_pos, g_matWorld );   // ワールド変換
	pos = mul( pos, g_matView );    // ビュー変換
	pos = mul( pos, g_matPro );    // 射影変換

    //法線計算


	//UV計算


	//出力へ代入
	OUT_VS out_vs = (OUT_VS)0;
	out_vs.pos = pos;
	out_vs.uv = prm_uv;

	return out_vs;
}

// ピクセルシェーダプログラム
float4 Default_PS(
	float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0 
) : COLOR  {
	//テクスチャ処理
//	prm_color = tex2D( TextureSampler, prm_uv ) * prm_color;
    return prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
