// ワールドビュー射影変換行列宣言
float4x4 g_worldMat;
float4x4 g_viewMat;
float4x4 g_projMat;
float4 pos : POSITION;

// 頂点シェーダ
float4 BasicTransform( float4 inLocalPos : POSITION ) : POSITION
{

	pos = mul( inLocalPos, g_worldMat );
	pos = mul( pos, g_viewMat );
	pos = mul( pos, g_projMat );
	return pos;
}

// ピクセルシェーダ
float4 NoWorkingPixelShader( float4 ScreenColor : COLOR ) : COLOR
{
   // 入力されたスクリーンピクセルの色をそのままスルー
   return ScreenColor;
}


technique BasicTec
{
   pass P0
   {
      VertexShader = compile vs_2_0 BasicTransform();
      PixelShader = compile ps_2_0 NoWorkingPixelShader();
   }
}