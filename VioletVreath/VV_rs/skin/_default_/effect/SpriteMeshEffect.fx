#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDxMeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
float g_specular;
float g_specular_power;


float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_vecLightFrom_World; // ライトの方向
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
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS GgafDxVS_SpriteMesh(
    float4 prm_posModel_Local  : POSITION, // モデルの頂点
    float3 prm_vecNormal_Local : NORMAL,   // モデルの頂点の法線
    float2 prm_uv              : TEXCOORD0 // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
    //UV
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;

	//法線を World 変換して正規化
    float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld)); 	
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(vecNormal_World, -g_vecLightFrom_World ), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
	//αフォグ
	out_vs.color.a = g_colMaterialDiffuse.a;
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}

OUT_VS VS_NoLight(
    float4 prm_posModel_Local  : POSITION,  // モデルの頂点
    float3 prm_vecNormal_Local : NORMAL,    // モデルの頂点の法線
    float2 prm_uv              : TEXCOORD0  // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;
	//頂点計算
	out_vs.posModel_Proj = mul( mul( mul(prm_posModel_Local, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
    //UV
	out_vs.uv.x = prm_uv.x + g_offset_u;
	out_vs.uv.y = prm_uv.y + g_offset_v;
	//、マテリアル色 を考慮したカラー作成。      
	out_vs.color = g_colMaterialDiffuse;
	return out_vs;
}


//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDxPS_SpriteMesh(
	float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color;
    //Blinkerを考慮
	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
	} 
	//マスターα
	colOut.a *= g_alpha_master;
	return colOut;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color * FLUSH_COLOR;
	colOut.a *= g_alpha_master;
	return colOut;
}

float4 PS_NoLight(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
    //Blinkerを考慮
//	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
//		colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
//	} 
	colOut.a *= g_alpha_master;
	return colOut;
}

technique SpriteMeshTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_SpriteMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_SpriteMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
        //SeparateAlphaBlendEnable = true;
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_SpriteMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_SpriteMesh();
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
		VertexShader = compile VS_VERSION GgafDxVS_SpriteMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

technique NoLight
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION VS_NoLight();
		PixelShader  = compile PS_VERSION PS_NoLight();
	}
}

