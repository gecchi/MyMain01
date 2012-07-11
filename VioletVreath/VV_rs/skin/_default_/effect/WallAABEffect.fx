#include "GgafEffectConst.fxh" 

////////////////////////////////////////////////////////////////////////////////
// WallAABActor用シェーダー
// 【概要】
// 外壁ブロックの描画を行う。
// 頂点バッファに、外壁ブロック情報が、２０個分繰り返し詰め込んである。
// ステートやレジスタの更新を行わず、１回の 描画で、最大
// 20オブジェクトまで描画。高速化を狙う。
// author : Masatoshi Tsuge
// date:2010/10/20
////////////////////////////////////////////////////////////////////////////////
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ライトの方向
float3 g_vecLightFrom_World;
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
float4x4 g_matWorld016;
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
//float4x4 g_matWorld020;

//テクスチャのサンプラ(s0レジスタ)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS GgafDxVS_WallAAB(
    float4 prm_posModel_Local  : POSITION, // モデルの頂点
    float  prm_object_index    : PSIZE ,   // モデルのインデックス（何個目のオブジェクトか）
    float3 prm_vecNormal_Local : NORMAL,   // モデルの頂点の法線
    float2 prm_uv              : TEXCOORD0 // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;
	//ワールド変換行列を割り当てる
	int index = (int)prm_object_index; 
	float4x4 matWorld;
	if (index == 0) {
		matWorld = g_matWorld001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
	} else if (index == 14) {
		matWorld = g_matWorld015;
	} else if (index == 15) {
		matWorld = g_matWorld016;
	} else if (index == 16) {
		matWorld = g_matWorld017;
	} else if (index == 17) {
		matWorld = g_matWorld018;
//	} else if (index == 18) {
//		matWorld = g_matWorld019;
	} else {
		matWorld = g_matWorld019;
	} 
    //描画面番号情報が、ワールド変換行列のmatWorld._14 に埋め込まれている
	int draw_face = matWorld._14;
    matWorld._14 = 0; //元の行列値に戻しておく

    //UVによりどの面の頂点か判断し、
    //描画不要な面の頂点の場合は何とかする（ジオメトリシェーダー使いたい；）

    //draw_faceは壁部分にビットが立っている
    //&b 00abcdef
    //
    //下図はBOXの展開した状態の図
    //
    //                   ^y
    //              z┌  | 
    //                 \ | 
    //                  c| 
    // ----自機＞--- a b d f ---- -> x
    //                   |e
    //                   | \
    //                   |  \   
	//  u v
	// (0,0)      0.25                     →u
	//       +------+------+------+------+
	//       |      |        Z+          |
	//       |      |       面c          |
	//  0.25 +  X+  +--------------------+
	//       | 面f  |        Y-          |
	//       |      |       面d          |
	//   0.5 +------+--------------------+
	//       |      |        Y+          |
	//       |      |       面a          |
	//  0.75 +  X-  +--------------------+
	//       | 面b  |        Z-          |
	//       |      |       面e          |
	//       +------+------+------+------+
	//    ↓                                (1,1)
	//    v

    //                          00abcdef
  	if (draw_face >= 32) {  //&b00100000
        draw_face -= 32;
    } else {
        //上面(面a)が描画不要の場合
        if (0.25 < prm_uv.x && 
            0.5  < prm_uv.y && prm_uv.y < 0.75 ) 
		{
            return out_vs;
        }
    }

    //                          00abcdef
  	if (draw_face >= 16) {  //&b00010000
        draw_face -= 16;
    } else {
        //正面(面b)が描画不要の場合
        if (                   prm_uv.x < 0.25 &&
            0.5  < prm_uv.y                       ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 8) {   //&b00001000
        draw_face -= 8;
    } else {
        //左側面(面c)が描画不要の場合
        if (0.25 < prm_uv.x && 
                               prm_uv.y < 0.25 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
   	if (draw_face >= 4) {   //&b00000100
        draw_face -= 4;
    } else {
        //底面(面d)が描画不要の場合
        if (0.25 < prm_uv.x &&
            0.25 < prm_uv.y && prm_uv.y < 0.5 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 2) {   //&b00000010
        draw_face -= 2;
    } else {
        //右側面(面e)が描画不要の場合
        if (0.25 < prm_uv.x &&
            0.75 < prm_uv.y                    ) 
		{
            return out_vs;
        } 
    }
    //                          00abcdef
  	if (draw_face >= 1) {   //&b00000001
       // draw_face -= 1;
    } else {
        //向こう正面(面f)が描画不要の場合
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    ) 
		{
            return out_vs;
        }
    }

	//World*View*射影変換
	out_vs.posModel_Proj = mul(mul(mul( prm_posModel_Local, matWorld ), g_matView ), g_matProj);

	//UVはそのまま
	out_vs.uv = prm_uv;

    //頂点カラー計算

	//法線を World 変換して正規化
    float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	
    vecNormal_World.x+=0.5; //値0.5は壁面にも無理やり光を当てるため
                   //ライトベクトルは XYZ=0.819232,-0.573462,0
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(vecNormal_World, float3(-0.819232,0.573462,0)), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向 を考慮したカラー作成。      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power));// * マテリアル色無しcolMaterialDiffuse;
	//αフォグ
	//out_vs.color.a = colMaterialDiffuse.a;
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
    //自機より手前はα
	if ( out_vs.posModel_Proj.z < g_distance_AlphaTarget) {
		out_vs.color.a = (out_vs.posModel_Proj.z + 1.0)  / (g_distance_AlphaTarget*2);
	}
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {   
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDxPS_WallAAB(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {
    if (prm_color.a == 0) {
        return 0;
    }
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
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color * FLUSH_COLOR;
	return colOut;
}

technique WallAABTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_WallAAB();
		PixelShader  = compile PS_VERSION GgafDxPS_WallAAB();
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
		VertexShader = compile VS_VERSION GgafDxVS_WallAAB();
		PixelShader  = compile PS_VERSION GgafDxPS_WallAAB();
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
		VertexShader = compile VS_VERSION GgafDxVS_WallAAB();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
