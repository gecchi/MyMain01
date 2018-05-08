#include "GgafEffectConst.fxh" 

////////////////////////////////////////////////////////////////////////////////
// CubeMapMassWallActor用シェーダー
// 【概要】
// 外壁プリズムの描画を行う。
// 頂点バッファに、外壁プリズム情報が、10個分繰り返し詰め込んである。
// ステートやレジスタの更新を行わず、１回の 描画で、最大
// 10オブジェクトまで描画。高速化を狙う。
// author : Masatoshi Tsuge
// date:2011/01/10
////////////////////////////////////////////////////////////////////////////////
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
float g_reflectance;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //壁ブロックの長さ（X座標軸長さ）
float g_wall_height; //壁ブロックの高さ（Y座標軸長さ）
float g_wall_width;  //壁ブロックの幅（Z座標軸長さ)

float g_ah_POS_PRISM_ZX;
float g_fh_POS_PRISM_ZX;
float g_ah_POS_PRISM_YZ;
float g_fh_POS_PRISM_YZ;
float g_ah_POS_PRISM_XY;
float g_fh_POS_PRISM_XY;


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

#define POS_PRISM_xx_NN    1 
#define POS_PRISM_xx_NP    2 
#define POS_PRISM_xx_PN    4 
#define POS_PRISM_xx_PP    8 
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

//テクスチャのサンプラ(s0レジスタ)
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
sampler BumpMapTextureSampler : register(s2);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj   : POSITION;
	float2 uv              : TEXCOORD0;
	float4 color           : COLOR0;
    float3 vecNormal_World : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_World    : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS GgafDxVS_CubeMapMassWall(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線
      float2 prm_uv               : TEXCOORD0 ,    // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float2 prm_info             : TEXCOORD5
) {
	OUT_VS out_vs = (OUT_VS)0;

	int draw_face = (int)(prm_info.x);
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

	int pos_info = (int)(prm_info.y);

	if (pos_info == 0) {
        //BOX
	} else if (pos_info >= POS_PRISM_ZX_xx) {   
        //BOXの１面を無理やり閉じてプリズム型に変形させる
		//＋X -X の面がプリズムの斜め面にならないようにする
		// ZX は XZ平面と見る
		pos_info -= POS_PRISM_ZX_xx;
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))       - ((prm_posModel_Local.x-g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))) + ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))       + ((prm_posModel_Local.x-g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)/g_wall_dep))) - ((prm_posModel_Local.x+g_fh_POS_PRISM_ZX)*g_ah_POS_PRISM_ZX);
		}
	} else if (pos_info >= POS_PRISM_YZ_xx) {   
		//＋Z -Z の面がプリズムの斜め面にならないようにする
		pos_info -= POS_PRISM_YZ_xx;
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))       - ((prm_posModel_Local.z-g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))) + ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))       + ((prm_posModel_Local.z-g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)/g_wall_width))) - ((prm_posModel_Local.z+g_fh_POS_PRISM_YZ)*g_ah_POS_PRISM_YZ);
		}
	} else { //if (pos_info >= POS_PRISM_XY_xx) {   
		pos_info -= POS_PRISM_XY_xx;
		//＋X -X の面がプリズムの斜め面にならないようにする
		if (pos_info == POS_PRISM_xx_PP) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))       - ((prm_posModel_Local.x-g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else if (pos_info == POS_PRISM_xx_PN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))       + ((prm_posModel_Local.x-g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else if (pos_info == POS_PRISM_xx_NP) { 
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))) + ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		} else { //if (pos_info == POS_PRISM_xx_NN) {
			prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_PRISM_XY)/g_wall_dep))) - ((prm_posModel_Local.x+g_fh_POS_PRISM_XY)*g_ah_POS_PRISM_XY);
		}
	}
	//メモ
	//(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   ・・・ 先端をキュッとまとめる計算
	//+ ((prm_posModel_Local.x-fh)*ah);                      ・・・ 先端を水平にする計算

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
	//World*View*射影変換
    const float4 posModel_World = mul(prm_posModel_Local, matWorld);        //World 変換
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //View*射影 変換
	//UVはそのまま
	out_vs.uv = prm_uv;
	//法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	
    out_vs.vecNormal_World.x+=0.5; //値0.5は壁面にも無理やり光を当てるため
                   //ライトベクトルは XYZ=0.819232,-0.573462,0 固定。とりあえず。
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(out_vs.vecNormal_World, float3(-0.819232,0.573462,0)), 0);      
// const float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0); //本来

	//Ambientライト色、Diffuseライト色、Diffuseライト方向 を考慮したカラー作成。      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power));// * マテリアル色無しcolMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

	//αフォグ
	//out_vs.color.a = colMaterialDiffuse.a;
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }
    
    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w;
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
float4 GgafDxPS_CubeMapMassWall(
	float2 prm_uv              : TEXCOORD0,
    float4 prm_color           : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    if (prm_color.a == 0) {
        discard;
    }

    const float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    const float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        const float3 vecHarf = normalize(prm_vecEye_World + float3(-0.819232,0.573462,0));
        //const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));  //本来
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;

	return colOut;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	const float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
	return colOut;
}

technique CubeMapMassWallTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMassWall();
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
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMassWall();
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
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMassWall();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
