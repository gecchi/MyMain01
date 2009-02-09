// ワールドビュー射影変換行列宣言
float4x4 matWorldViewProj;


// 頂点シェーダ
float4 BasicTransform( float4 LocalPos : POSITION ) : POSITION
{
   // ローカル座標にある頂点をワールドビュー射影変換で
   // 一気にスクリーン座標にしてしまう
   return mul( LocalPos, matWorldViewProj );
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