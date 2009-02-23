//今回は、ライトの向きと法線の内積と0を比べて数値の大きな方をテクスチャの色に乗算して影をつけているという処理をしています。


// 
//			Xファイル+テクスチャ
//			Created by TAKAHASHI Masafumi
// 
// グローバル変数
float4x4 mWVP;		// ローカルから射影空間への座標変換
float4	Dir;		// ライトの向き
float4	Diffuse;	//ディフューズ色
float4	Ambient;	//アンビエント
texture	Tex1;		//テクスチャ
sampler TextureSampler = sampler_state
{
    Texture = <Tex1>;
	//フィルタ設定
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;    
    //テクスチャラッピング
    AddressU = Wrap;
    AddressV = Wrap;
};
// バーテックスシェーダ出力
struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float4 Col  : COLOR0;
    float2 TexUV	: TEXCOORD0;
};
// バーテックスシェーダプログラム
VS_OUTPUT VS(
      float4 Pos    : POSITION,          // モデルの頂点
      float3 Normal : NORMAL,	         // モデルの法線
      float2 TexUV	: TEXCOORD0
){
	float3	dir={Dir.x,Dir.y,Dir.z};	//ライトの向きセット
	VS_OUTPUT Out = (VS_OUTPUT)0;        // 出力データ  
	Out.Pos = mul(Pos, mWVP);			// 座標変換 
	Out.TexUV = TexUV;					//UV取得
	Out.Col = max( dot(dir, Normal), 0);//光源計算  
	return Out;
}

// ピクセルシェーダプログラム
float4 PS(
	float2 TexUV	: TEXCOORD0,
    	float4 Col  : COLOR0 ) : COLOR
{
	//テクスチャ処理
	Col = tex2D( TextureSampler, TexUV ) * Col;
    return Col;
}
// テクニック
technique TShader
{
    pass P0
    {
        VertexShader = compile vs_1_1 VS();
        PixelShader  = compile ps_1_1 PS();
    }
}




//
//
//// ワールドビュー射影変換行列宣言
//float4x4 g_worldMat;
//float4x4 g_viewMat;
//float4x4 g_projMat;
////float4 pos : POSITION;
//
//
//struct VS_OUT {
//	float4 pos    : POSITION;
//	float4 uv     : TEXCOORD0;
//	float3 normal : TEXCOORD1;
//};
//
//VS_OUT Specular_VS( float4 inLocalPos : POSITION, float3 inLocalNormal : NORMAL, float4 inUV : TEXCOORD0 )
//{
//	VS_OUT Out = (VS_OUT)0;
//	Out.pos = mul( inLocalPos, g_worldMat );
//	Out.pos = mul( Out.pos, g_viewMat );
//	Out.pos = mul( Out.pos, g_projMat );
//
//	// 法線ベクトルをワールドへ？
//	Out.normal = inLocalNormal;
////mul( inLocalNormal, g_worldView );
//	
//	Out.uv     = inUV;
//	return Out;
//}
//
////
////// 頂点シェーダ
////float4 BasicTransform( float4 inLocalPos : POSITION ) : POSITION
////{
////
////	pos = mul( inLocalPos, g_worldMat );
////	pos = mul( pos, g_viewMat );
////	pos = mul( pos, g_projMat );
////	return pos;
////}
////
//// ピクセルシェーダ
//float4 NoWorkingPixelShader( float4 ScreenColor : COLOR ) : COLOR
//{
//   // 入力されたスクリーンピクセルの色をそのままスルー
//   return ScreenColor;
//}
//
//
//technique BasicTec
//{
//   pass P0
//   {
//      VertexShader = compile vs_2_0 Specular_VS();
//      PixelShader = compile ps_2_0 NoWorkingPixelShader();
//   }
//}
