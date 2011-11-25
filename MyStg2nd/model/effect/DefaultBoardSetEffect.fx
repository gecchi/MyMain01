#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxBoardSetModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
float g_game_buffer_width; //画面幅(px)
float g_game_buffer_height; //画面高さ(px)
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
//float g_offsetU; //テクスチャU座標増分
//float g_offsetV; //テクスチャV座標増分
//float g_transformedX; //変換済みX座標(px)
//float g_transformedY; //変換済みY座標(px)
//float g_depthZ; //深度Z (0 ～ +1)
//float g_alpha; //α
//

float g_offsetU001;
float g_offsetU002;
float g_offsetU003;
float g_offsetU004;
float g_offsetU005;
float g_offsetU006;
float g_offsetU007;
float g_offsetU008;
float g_offsetU009;
float g_offsetU010;
float g_offsetU011;
float g_offsetU012;
float g_offsetU013;
float g_offsetU014;
float g_offsetU015;
float g_offsetU016;
float g_offsetU017;
float g_offsetU018;
float g_offsetU019;
float g_offsetU020;
float g_offsetU021;
float g_offsetU022;
float g_offsetU023;
float g_offsetU024;
float g_offsetU025;
float g_offsetU026;
float g_offsetU027;
float g_offsetU028;

float g_offsetV001;
float g_offsetV002;
float g_offsetV003;
float g_offsetV004;
float g_offsetV005;
float g_offsetV006;
float g_offsetV007;
float g_offsetV008;
float g_offsetV009;
float g_offsetV010;
float g_offsetV011;
float g_offsetV012;
float g_offsetV013;
float g_offsetV014;
float g_offsetV015;
float g_offsetV016;
float g_offsetV017;
float g_offsetV018;
float g_offsetV019;
float g_offsetV020;
float g_offsetV021;
float g_offsetV022;
float g_offsetV023;
float g_offsetV024;
float g_offsetV025;
float g_offsetV026;
float g_offsetV027;
float g_offsetV028;

float g_transformedX001;
float g_transformedX002;
float g_transformedX003;
float g_transformedX004;
float g_transformedX005;
float g_transformedX006;
float g_transformedX007;
float g_transformedX008;
float g_transformedX009;
float g_transformedX010;
float g_transformedX011;
float g_transformedX012;
float g_transformedX013;
float g_transformedX014;
float g_transformedX015;
float g_transformedX016;
float g_transformedX017;
float g_transformedX018;
float g_transformedX019;
float g_transformedX020;
float g_transformedX021;
float g_transformedX022;
float g_transformedX023;
float g_transformedX024;
float g_transformedX025;
float g_transformedX026;
float g_transformedX027;
float g_transformedX028;

float g_transformedY001;
float g_transformedY002;
float g_transformedY003;
float g_transformedY004;
float g_transformedY005;
float g_transformedY006;
float g_transformedY007;
float g_transformedY008;
float g_transformedY009;
float g_transformedY010;
float g_transformedY011;
float g_transformedY012;
float g_transformedY013;
float g_transformedY014;
float g_transformedY015;
float g_transformedY016;
float g_transformedY017;
float g_transformedY018;
float g_transformedY019;
float g_transformedY020;
float g_transformedY021;
float g_transformedY022;
float g_transformedY023;
float g_transformedY024;
float g_transformedY025;
float g_transformedY026;
float g_transformedY027;
float g_transformedY028;

float g_depthZ001;
float g_depthZ002;
float g_depthZ003;
float g_depthZ004;
float g_depthZ005;
float g_depthZ006;
float g_depthZ007;
float g_depthZ008;
float g_depthZ009;
float g_depthZ010;
float g_depthZ011;
float g_depthZ012;
float g_depthZ013;
float g_depthZ014;
float g_depthZ015;
float g_depthZ016;
float g_depthZ017;
float g_depthZ018;
float g_depthZ019;
float g_depthZ020;
float g_depthZ021;
float g_depthZ022;
float g_depthZ023;
float g_depthZ024;
float g_depthZ025;
float g_depthZ026;
float g_depthZ027;
float g_depthZ028;

float g_alpha001;
float g_alpha002;
float g_alpha003;
float g_alpha004;
float g_alpha005;
float g_alpha006;
float g_alpha007;
float g_alpha008;
float g_alpha009;
float g_alpha010;
float g_alpha011;
float g_alpha012;
float g_alpha013;
float g_alpha014;
float g_alpha015;
float g_alpha016;
float g_alpha017;
float g_alpha018;
float g_alpha019;
float g_alpha020;
float g_alpha021;
float g_alpha022;
float g_alpha023;
float g_alpha024;
float g_alpha025;
float g_alpha026;
float g_alpha027;
float g_alpha028;

//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 color    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxBoardSetModel標準頂点シェーダー
OUT_VS GgafDxVS_DefaultBoardSet(
      float4 prm_pos    : POSITION,     // モデルの頂点
	  float  prm_index  : PSIZE ,    // モデル番号
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;
	float offsetU; //テクスチャU座標増分
	float offsetV; //テクスチャV座標増分
	float transformedX; //変換済みX座標(px)
	float transformedY; //変換済みY座標(px)
	float depthZ; //深度Z (0 ～ +1)
	float alpha; //α

	if (index == 0) {
		transformedX = g_transformedX001;
		transformedY = g_transformedY001;
		depthZ = g_depthZ001;

		offsetU = g_offsetU001;
		offsetV = g_offsetV001;
		alpha = g_alpha001;
	} else if (index == 1) {
		transformedX = g_transformedX002;
		transformedY = g_transformedY002;
		depthZ = g_depthZ002;
		offsetU = g_offsetU002;
		offsetV = g_offsetV002;
		alpha = g_alpha002;
	} else if (index == 2) {
		transformedX = g_transformedX003;
		transformedY = g_transformedY003;
		depthZ = g_depthZ003;
		offsetU = g_offsetU003;
		offsetV = g_offsetV003;
		alpha = g_alpha003;
	} else if (index == 3) {
		transformedX = g_transformedX004;
		transformedY = g_transformedY004;
		depthZ = g_depthZ004;
		offsetU = g_offsetU004;
		offsetV = g_offsetV004;
		alpha = g_alpha004;
	} else if (index == 4) {
		transformedX = g_transformedX005;
		transformedY = g_transformedY005;
		depthZ = g_depthZ005;
		offsetU = g_offsetU005;
		offsetV = g_offsetV005;
		alpha = g_alpha005;
	} else if (index == 5) {
		transformedX = g_transformedX006;
		transformedY = g_transformedY006;
		depthZ = g_depthZ006;
		offsetU = g_offsetU006;
		offsetV = g_offsetV006;
		alpha = g_alpha006;
	} else if (index == 6) {	
		transformedX = g_transformedX007;
		transformedY = g_transformedY007;
		depthZ = g_depthZ007;
		offsetU = g_offsetU007;
		offsetV = g_offsetV007;
		alpha = g_alpha007;
	} else if (index == 7) {	
		transformedX = g_transformedX008;
		transformedY = g_transformedY008;
		depthZ = g_depthZ008;
		offsetU = g_offsetU008;
		offsetV = g_offsetV008;
		alpha = g_alpha008;
	} else if (index == 8) {	
		transformedX = g_transformedX009;
		transformedY = g_transformedY009;
		depthZ = g_depthZ009;
		offsetU = g_offsetU009;
		offsetV = g_offsetV009;
		alpha = g_alpha009;
	} else if (index == 9) {	
		transformedX = g_transformedX010;
		transformedY = g_transformedY010;
		depthZ = g_depthZ010;
		offsetU = g_offsetU010;
		offsetV = g_offsetV010;
		alpha = g_alpha010;
	} else if (index == 10) {	
		transformedX = g_transformedX011;
		transformedY = g_transformedY011;
		depthZ = g_depthZ011;
		offsetU = g_offsetU011;
		offsetV = g_offsetV011;
		alpha = g_alpha011;
	} else if (index == 11) {	
		transformedX = g_transformedX012;
		transformedY = g_transformedY012;
		depthZ = g_depthZ012;
		offsetU = g_offsetU012;
		offsetV = g_offsetV012;
		alpha = g_alpha012;
	} else if (index == 12) {	
		transformedX = g_transformedX013;
		transformedY = g_transformedY013;
		depthZ = g_depthZ013;
		offsetU = g_offsetU013;
		offsetV = g_offsetV013;
		alpha = g_alpha013;
	} else if (index == 13) {	
		transformedX = g_transformedX014;
		transformedY = g_transformedY014;
		depthZ = g_depthZ014;
		offsetU = g_offsetU014;
		offsetV = g_offsetV014;
		alpha = g_alpha014;
	} else if (index == 14) {	
		transformedX = g_transformedX015;
		transformedY = g_transformedY015;
		depthZ = g_depthZ015;
		offsetU = g_offsetU015;
		offsetV = g_offsetV015;
		alpha = g_alpha015;
	} else if (index == 15) {	
		transformedX = g_transformedX016;
		transformedY = g_transformedY016;
		depthZ = g_depthZ016;
		offsetU = g_offsetU016;
		offsetV = g_offsetV016;
		alpha = g_alpha016;
	} else if (index == 16) {	
		transformedX = g_transformedX017;
		transformedY = g_transformedY017;
		depthZ = g_depthZ017;
		offsetU = g_offsetU017;
		offsetV = g_offsetV017;
		alpha = g_alpha017;
	} else if (index == 17) {	
		transformedX = g_transformedX018;
		transformedY = g_transformedY018;
		depthZ = g_depthZ018;
		offsetU = g_offsetU018;
		offsetV = g_offsetV018;
		alpha = g_alpha018;
	} else if (index == 18) {	
		transformedX = g_transformedX019;
		transformedY = g_transformedY019;
		depthZ = g_depthZ019;
		offsetU = g_offsetU019;
		offsetV = g_offsetV019;
		alpha = g_alpha019;
	} else if (index == 19) {	
		transformedX = g_transformedX020;
		transformedY = g_transformedY020;
		depthZ = g_depthZ020;
		offsetU = g_offsetU020;
		offsetV = g_offsetV020;
		alpha = g_alpha020;
	} else if (index == 20) {	
		transformedX = g_transformedX021;
		transformedY = g_transformedY021;
		depthZ = g_depthZ021;
		offsetU = g_offsetU021;
		offsetV = g_offsetV021;
		alpha = g_alpha021;
	} else if (index == 21) {	
		transformedX = g_transformedX022;
		transformedY = g_transformedY022;
		depthZ = g_depthZ022;
		offsetU = g_offsetU022;
		offsetV = g_offsetV022;
		alpha = g_alpha022;
	} else if (index == 22) {	
		transformedX = g_transformedX023;
		transformedY = g_transformedY023;
		depthZ = g_depthZ023;
		offsetU = g_offsetU023;
		offsetV = g_offsetV023;
		alpha = g_alpha023;
	} else if (index == 23) {	
		transformedX = g_transformedX024;
		transformedY = g_transformedY024;
		depthZ = g_depthZ024;
		offsetU = g_offsetU024;
		offsetV = g_offsetV024;
		alpha = g_alpha024;
	} else if (index == 24) {	
		transformedX = g_transformedX025;
		transformedY = g_transformedY025;
		depthZ = g_depthZ025;
		offsetU = g_offsetU025;
		offsetV = g_offsetV025;
		alpha = g_alpha025;
	} else if (index == 25) {	
		transformedX = g_transformedX026;
		transformedY = g_transformedY026;
		depthZ = g_depthZ026;
		offsetU = g_offsetU026;
		offsetV = g_offsetV026;
		alpha = g_alpha026;
	} else if (index == 26) {	
		transformedX = g_transformedX027;
		transformedY = g_transformedY027;
		depthZ = g_depthZ027;
		offsetU = g_offsetU027;
		offsetV = g_offsetV027;
		alpha = g_alpha027;
	} else {	
		transformedX = g_transformedX028;
		transformedY = g_transformedY028;
		depthZ = g_depthZ028;
		offsetU = g_offsetU028;
		offsetV = g_offsetV028;
		alpha = g_alpha028;
	} 

	//X座標Y座標をを -1 ～ +1 に押し込める。
	out_vs.pos.x = - 1 + ((2*prm_pos.x + 2*transformedX - 1) / g_game_buffer_width);
	out_vs.pos.y =   1 - ((2*prm_pos.y + 2*transformedY - 1) / g_game_buffer_height);
	out_vs.pos.z = depthZ;
	out_vs.pos.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color = alpha;
	return out_vs;
}


//GgafDxBoardSetModel標準ピクセルシェーダー
float4 GgafDxPS_DefaultBoardSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv); 
	//求める色
	float4 out_color = tex_color; 
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	}          
	//α考慮
	out_color.a = out_color.a * prm_color.a * g_alpha_master; 
	return out_color;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;                
	//α考慮
	out_color.a = out_color.a * prm_color.a * g_alpha_master; 
	return out_color;
}


//＜テクニック：DefaultBoardSetTechnique＞
//【機能】
//GgafDxBoardSetModel用標準シェーダー
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
// float g_hAlpha			:	α値
// float g_transformedX		: 	変換済みX座標(px)
// float g_transformedY		:	変換済みY座標(px)
// float g_depthZ			:	深度Z (0 ～ +1)
// float g_game_buffer_width		:	画面幅(px)
// float g_game_buffer_height		:	画面高さ(px)
// float g_offsetU			:	テクスチャU座標増分
// float g_offsetV			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique DefaultBoardSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoardSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultBoardSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultBoardSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
