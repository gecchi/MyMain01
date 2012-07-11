#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxBoardModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float g_alpha; //α
float g_offset_u; //テクスチャU座標増分
float g_offset_v; //テクスチャV座標増分
float g_transformed_X; //変換済みX座標(px)
float g_transformed_Y; //変換済みY座標(px)
float g_depth_Z; //深度Z (0 ～ +1)
float g_game_buffer_width; //画面幅(px)
float g_game_buffer_height; //画面高さ(px)
float g_sx;
float g_sy;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxBoardModel標準頂点シェーダー
OUT_VS GgafDxVS_DefaultBoard(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//X座標Y座標をを -1 ～ +1 に押し込める。
	out_vs.posModel_Proj.x = - 1 + ((2*prm_posModel_Local.x*g_sx + 2*g_transformed_X - 1) / g_game_buffer_width);
	out_vs.posModel_Proj.y =   1 - ((2*prm_posModel_Local.y*g_sy + 2*g_transformed_Y - 1) / g_game_buffer_height);
	out_vs.posModel_Proj.z = g_depth_Z;
	out_vs.posModel_Proj.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;

	return out_vs;
}


float4 GgafDxPS_DefaultBoard(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colTex = tex2D( MyTextureSampler, prm_uv); 
	//求める色
	float4 colOut = colTex; 
	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
	}    
	//α考慮
	colOut.a = colOut.a * g_alpha * g_alpha_master; 
	return colOut;
}



float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;                
	//α考慮
	colOut.a = colOut.a * g_alpha * g_alpha_master; 
	return colOut;
}






//＜テクニック：DefaultBoardTechnique＞
//【機能】
//GgafDxBoardModel用標準シェーダー
//【概要】
//D3DFVF_XYZRHW で描画したような仕様で２Ｄ表示します。
//画面左上隅が(0,0)で画面右下隅が（画面幅(px), 画面高さ(px))となる座標系で
//プリミティブ（板ポリ）の基点は左上隅になります。
//--- VS ---
//・頂点を -1 ～ +1へ押し込み(＝正射影変換)、Y座標反転
//--- PS ---
//・オブジェクトのテクスチャ
//・半透明α
//
//【設定グローバル】
// float g_alpha			:	α値
// float g_transformed_X		: 	変換済みX座標(px)
// float g_transformed_Y		:	変換済みY座標(px)
// float g_depth_Z			:	深度Z (0 ～ +1)
// float g_game_buffer_width		:	画面幅(px)
// float g_game_buffer_height		:	画面高さ(px)
// float g_offset_u			:	テクスチャU座標増分
// float g_offset_v			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique DefaultBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoard();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}