#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// author : Masatoshi Tsuge
// date:2010/12/24
////////////////////////////////////////////////////////////////////////////////

//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
float g_reflectance;

float g_specular;
float g_specular_power;



/** カメラのWorld位置 */
//float3 pos_camera; 

float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ライトの方向
float3 g_vecLightDirection;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）  
float4 g_colLightDiffuse;  
//View変換行列
float4x4 g_matView; 
//射影変換行列  
float4x4 g_matProj;  
//ワールド変換行列
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
//float4x4 g_matWorld016;
//オブジェクトのマテリアル色（Diffuse反射色と、Ambien反射色共通）
float4 g_colMaterialDiffuse001;
float4 g_colMaterialDiffuse002;
float4 g_colMaterialDiffuse003;
float4 g_colMaterialDiffuse004;
float4 g_colMaterialDiffuse005;
float4 g_colMaterialDiffuse006;
float4 g_colMaterialDiffuse007;
float4 g_colMaterialDiffuse008;
float4 g_colMaterialDiffuse009;
float4 g_colMaterialDiffuse010;
float4 g_colMaterialDiffuse011;
float4 g_colMaterialDiffuse012;
float4 g_colMaterialDiffuse013;
float4 g_colMaterialDiffuse014;
float4 g_colMaterialDiffuse015;
//float4 g_colMaterialDiffuse016;

//テクスチャのサンプラ(s0レジスタ)
//sampler MyTextureSampler : register(s0);
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);

struct OUT_VS {
    float4 pos   : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
    float3 normal : TEXCOORD1;   // ワールド変換した法線
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS GgafDxVS_CubeMapMeshSet(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	float4 colorMaterialDiffuse;

	if (index == 0) {
		matWorld = g_matWorld001;
		colorMaterialDiffuse = g_colMaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colorMaterialDiffuse = g_colMaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colorMaterialDiffuse = g_colMaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colorMaterialDiffuse = g_colMaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colorMaterialDiffuse = g_colMaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colorMaterialDiffuse = g_colMaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colorMaterialDiffuse = g_colMaterialDiffuse007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		colorMaterialDiffuse = g_colMaterialDiffuse008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		colorMaterialDiffuse = g_colMaterialDiffuse009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		colorMaterialDiffuse = g_colMaterialDiffuse010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		colorMaterialDiffuse = g_colMaterialDiffuse011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		colorMaterialDiffuse = g_colMaterialDiffuse012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		colorMaterialDiffuse = g_colMaterialDiffuse013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		colorMaterialDiffuse = g_colMaterialDiffuse014;
	} else { //if (index == 14) {
		matWorld = g_matWorld015;
		colorMaterialDiffuse = g_colMaterialDiffuse015;
	}
//	} else {
//		matWorld = g_matWorld016;
//		colorMaterialDiffuse = g_colMaterialDiffuse016;
//	}








	//頂点計算
    float4 posWorld = mul(prm_pos, matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま
    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.normal = normalize(mul(prm_normal, matWorld));     
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * colorMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = colorMaterialDiffuse.a;
    //αフォグ
    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;


//	//World*View*射影変換
//	out_vs.pos = mul(prm_pos, matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
//    out_vs.normal = normalize(mul(prm_normal, matWorld)); 
//	//UVはそのまま
////	out_vs.uv = prm_uv;
//
//    //頂点カラー計算
//
//	//法線を World 変換して正規化
//    //float3 normal = normalize(mul(prm_normal, matWorld)); 	
//    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
//	float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
//	//Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。      
//	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * colorMaterialDiffuse * float4(2.0, 2.0, 2.0, 1.0); //全体的に明るくする;
//	//αフォグ
//	out_vs.color.a = colorMaterialDiffuse.a;
//    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
//    }
//
//	//マスターα
//	out_vs.color.a *= g_alpha_master;
//	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDxPS_CubeMapMeshSet(       
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {


	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_cam, prm_normal));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * g_alpha_master; 
	return out_color;









//
//	//テクスチャをサンプリングして色取得（原色を取得）
//	float3 vReflect = reflect( prm_viewVecW, prm_normal );
//    float4 tex_color = texCUBE(MyTextureSampler, vReflect);        
//	float4 out_color = tex_color * prm_color;
//
//    //Blinkerを考慮
//	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
//		out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
//	} 
//	return out_color;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
	return out_color;
}

technique CubeMapMeshSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMeshSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMeshSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;      //default
        DestBlendAlpha = Zero;    //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMeshSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
