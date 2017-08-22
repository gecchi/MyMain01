#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxEnclosedBoardModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2017/08/21
////////////////////////////////////////////////////////////////////////////////
float g_game_buffer_width; //画面幅(px)
float g_game_buffer_height; //画面高さ(px)
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;


float g_offset_u001;
float g_offset_u002;
float g_offset_u003;
float g_offset_u004;
float g_offset_u005;
float g_offset_u006;
float g_offset_u007;
float g_offset_u008;
float g_offset_u009;


float g_offset_v001;
float g_offset_v002;
float g_offset_v003;
float g_offset_v004;
float g_offset_v005;
float g_offset_v006;
float g_offset_v007;
float g_offset_v008;
float g_offset_v009;



                                                         
float g_unit_width;
float g_unit_height;

float g_top_edge_size_rate;
float g_center_height_rate;
float g_bottom_edge_size_rate;

float g_left_edge_size_rate;
float g_center_width_rate;
float g_right_edge_size_rate;

float g_alpha;
    
float g_x;
float g_y;
float g_z;
float g_rz;                         

float g_local_offset_x;
float g_local_offset_y;
//s0レジスタのサンプラを使う(＝固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float4 color            : COLOR0;
	float2 uv               : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//GgafDxEnclosedBoardModel標準頂点シェーダー
OUT_VS GgafDxVS_DefaultEnclosedBoard(
      float4 prm_posModel_Local    : POSITION,     // モデルの頂点
	  float  prm_index             : PSIZE ,       // モデル番号
      float2 prm_uv                : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	const int index = (int)prm_index;
	float offsetU; //テクスチャU座標増分
	float offsetV; //テクスチャV座標増分
	float x; //変換済みX座標(px)
	float y; //変換済みY座標(px)
	float depthZ; //深度Z (0 ～ +1)
	float alpha; //α
                            
    //    ┌─┬─┬─┐
    //    │０│１│２│
    //    ├─┼─┼─┤
    //    │３│４│５│
    //    ├─┼─┼─┤
    //    │６│７│８│
    //    └─┴─┴─┘
	if (index == 0) {
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u001;
		offsetV = g_offset_v001;
	} else if (index == 1) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u002;
		offsetV = g_offset_v002;
	} else if (index == 2) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = prm_posModel_Local.y * g_top_edge_size_rate;
		offsetU = g_offset_u003;
		offsetV = g_offset_v003;
	} else if (index == 3) {
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u004;
		offsetV = g_offset_v004;
	} else if (index == 4) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u005;
		offsetV = g_offset_v005;
	} else if (index == 5) {
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + prm_posModel_Local.y * g_center_height_rate;
		offsetU = g_offset_u006;
		offsetV = g_offset_v006;
	} else if (index == 6) {	
		x = prm_posModel_Local.x * g_left_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u007;
		offsetV = g_offset_v007;
	} else if (index == 7) {	
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u008;
		offsetV = g_offset_v008;
	} else if (index == 8) {	
		x = g_unit_width * g_left_edge_size_rate + prm_posModel_Local.x * g_center_width_rate + prm_posModel_Local.x * g_right_edge_size_rate;
		y = g_unit_height * g_top_edge_size_rate + g_unit_height * g_center_height_rate + prm_posModel_Local.y * g_bottom_edge_size_rate;
		offsetU = g_offset_u009;
		offsetV = g_offset_v009;

	}
	//X座標Y座標をを -1 ～ +1 に押し込める。
	out_vs.posModel_Proj.x = - 1 + ((2*x + 2*g_local_offset_x - 1) / g_game_buffer_width);
	out_vs.posModel_Proj.y =   1 - ((2*y + 2*g_local_offset_y - 1) / g_game_buffer_height);
	out_vs.posModel_Proj.z = g_z;
	out_vs.posModel_Proj.w = 1.0;
	//UVのオフセットを加算
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
	out_vs.color.a = g_alpha;
	return out_vs;
}


//GgafDxEnclosedBoardModel標準ピクセルシェーダー
float4 GgafDxPS_DefaultEnclosedBoard(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//求める色
	float4 colOut = tex2D( MyTextureSampler, prm_uv); 
	if (colOut.r >= g_tex_blink_threshold || colOut.g >= g_tex_blink_threshold || colOut.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
	}          
	//α考慮
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}

float4 PS_Flush(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * FLUSH_COLOR;                
	//α考慮
	colOut.a = colOut.a * prm_color.a * g_alpha_master; 
	return colOut;
}


//＜テクニック：DefaultEnclosedBoardTechnique＞
//【機能】
//GgafDxEnclosedBoardModel用標準シェーダー
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
// float g_transformed_x		: 	変換済みX座標(px)
// float g_transformed_y		:	変換済みY座標(px)
// float g_depth_z			:	深度Z (0 ～ +1)
// float g_game_buffer_width		:	画面幅(px)
// float g_game_buffer_height		:	画面高さ(px)
// float g_offset_u			:	テクスチャU座標増分
// float g_offset_v			:	テクスチャV座標増分
// s0レジスタ				:	2Dテクスチャ
technique DefaultEnclosedBoardTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultEnclosedBoard();
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
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION GgafDxPS_DefaultEnclosedBoard();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
		VertexShader = compile VS_VERSION GgafDxVS_DefaultEnclosedBoard();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
