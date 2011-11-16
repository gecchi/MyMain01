#include "GgafEffectConst.fxh" 
////////////////////////////////////////////////////////////////////////////////
// レーザーチップ用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////
/* 
レーザーチップは次のようなメッシュであることが前提

 Mesh {
  8;
  0.000100;0.000000;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000100;0.000000;-1.000000;,
  0.000100;-1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.000100;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;;
  4;
  3;0,1,2;,
  3;3,4,5;,
  3;2,1,6;,
  3;5,4,7;;

  MeshNormals {
   2;
   0.000000;-1.000000;0.000000;,
   0.000000;0.000000;-1.000000;;
   4;
   3;0,0,0;,
   3;1,1,1;,
   3;0,0,0;,
   3;1,1,1;;
  }

  MeshTextureCoords {
   8;
   0.532110;0.000000;,
   0.500000;0.000000;,
   0.533110;0.999000;,
   0.532110;0.000000;,
   0.500000;0.000000;,
   0.533110;0.999000;,
   0.501000;0.999000;,
   0.501000;0.999000;;
  }

  MeshMaterialList {
   1;
   4;
   0,
   0,
   0,
   0;

   Material {
    0.588235;0.588235;0.588235;1.000000;;
    0.100000;
    0.900000;0.900000;0.900000;;
    0.000000;0.000000;0.000000;;

    TextureFilename {
     "MyOptionWateringLaserChip001.png";
    }
   }
  }
*/
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
float g_specular;
float g_specular_power;




float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//int g_kind; //チップ種類 1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）
int g_kind001;
int g_kind002;
int g_kind003;
int g_kind004;
int g_kind005;
int g_kind006;
int g_kind007;
int g_kind008;
int g_kind009;
int g_kind010;
int g_kind011;
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
float4x4 g_matWorld_front001;
float4x4 g_matWorld_front002;
float4x4 g_matWorld_front003;
float4x4 g_matWorld_front004;
float4x4 g_matWorld_front005;
float4x4 g_matWorld_front006;
float4x4 g_matWorld_front007;
float4x4 g_matWorld_front008;
float4x4 g_matWorld_front009;
float4x4 g_matWorld_front010;
float4x4 g_matWorld_front011;

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_vecLightDirection; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//レーザーチップ頂点シェーダー
OUT_VS GgafDxVS_LaserChip(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,    // PSIZEではなくてなんとモデルの頂点番号
      float3 prm_normal : NORMAL,        
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {

	OUT_VS out_vs = (OUT_VS)0;

	int index = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	float4x4 matWorld_front;
	int kind;

	if (index == 0) {
		matWorld = g_matWorld001;
		matWorld_front = g_matWorld_front001;
		kind = g_kind001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		matWorld_front = g_matWorld_front002;
		kind = g_kind002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		matWorld_front = g_matWorld_front003;
		kind = g_kind003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		matWorld_front = g_matWorld_front004;
		kind = g_kind004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		matWorld_front = g_matWorld_front005;
		kind = g_kind005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		matWorld_front = g_matWorld_front006;
		kind = g_kind006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		matWorld_front = g_matWorld_front007;
		kind = g_kind007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		matWorld_front = g_matWorld_front008;
		kind = g_kind008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		matWorld_front = g_matWorld_front009;
		kind = g_kind009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		matWorld_front = g_matWorld_front010;
		kind = g_kind010;
	} else {
		matWorld = g_matWorld011;
		matWorld_front = g_matWorld_front011;
		kind = g_kind011;
	} 
	float4 posWorld;
	if (prm_pos.x > 0.0) {    
//TODO:20090806アイディア
//現在先頭のチップは何も表示されないので
//２倍して90度回転して、先頭専用テクスチャをを張れば、先を丸く見せれるのではないか
//・・・単に２倍90度回転してだめだった、風車になるだけ

//		if (kind == 4) {  //3ではないよ
//         x =  cos90*_Xorg + sin90*_Yorg  = 0*_Xorg + 1*_Yorg   =  Y
//         y = -sin90*_Xorg + cos90*_Yorg  = -1*_Xorg + 0*_Yorg  = -X

//			sin
//		   ナインか
//		}
		//頂点計算
//		if (kind == 4) {  //3ではないよ
//			float tmpy = prm_pos.y;
//			prm_pos.y = -8.0 * prm_pos.z;
//			prm_pos.z = 8.0 * tmpy;
//		}

		prm_pos.x = 0;		
		if (kind == 4) {  //3ではないよ
			prm_pos.y = 0;
			prm_pos.z = 0;
		} 
		// 一つ前方のチップ座標へくっつける
		posWorld = mul( prm_pos, matWorld_front );      // World変換
	} else {
//		if (kind == 1) {  
//			prm_pos.x = 0;
//			prm_pos.y = 0;
//			prm_pos.z = 0;
//		} 
		//頂点計算
		posWorld = mul( prm_pos, matWorld );        // World変換
	}
	out_vs.pos = mul(mul(posWorld, g_matView), g_matProj);  // View変換射影変換

	//UV設定
    //レーザーチップ種別 について。
    //
    //      -==========<>            レーザーは
    //
    //      -= === === === <>        こんなふうに分断されています。
    //
    //    | -=|===|===|===|<> |     左図はレーザーをオブジェクトで区切ったつもりの図
    //
    //    <--><--><--><--><-->^
    //    ^   ^   ^   ^   ^   |
    //    |   |   |   |   |   |
    //    |   |   |   |   |    `----- 4:先端チップ(非表示で、中間先頭チップを表示するためだけに存在)
    //    |   |   |   |    `----- 3:中間先頭チップ(表示される実質の先頭)
    //    |   |   |    `----- 2:中間チップ
    //    |   |    `----- 2:中間チップ
    //    |    `----- 2:中間チップ
    //     `----- 1:末尾チップ
    //
    //先頭と先端という言葉で区別しています。
	if (kind == 2) {
		//中間チップ
		out_vs.uv = prm_uv;  
	} else if (kind == 1) {
		//末尾チップ
		out_vs.uv.x = prm_uv.x < 0.51f ? 0.0f : prm_uv.x;
		out_vs.uv.y = prm_uv.y;
	} else if (kind == 3) {
		//中間先頭チップ
		out_vs.uv.x = prm_uv.x > 0.51f ? 1.0f : prm_uv.x;
		out_vs.uv.y = prm_uv.y;
	} else {
		//先端チップ
		//何も描画したくない
		out_vs.uv.x = 0;
		out_vs.uv.y = 1;
	}
	//αフォグ
    float c = 1.25-(((out_vs.pos.z)/g_zf)*2);
	out_vs.color = (c < 0.2  ? 0.2 : c);
    out_vs.color.a = out_vs.color.a*g_alpha_master;
//	out_vs.color = c < 0.2  ? 2.0 : c;//1.0-((out_vs.pos.z/g_zf)*2) ;//float4((out_vs.pos.z/g_zf), (out_vs.pos.z/g_zf), (out_vs.pos.z/g_zf), 1.0-(out_vs.pos.z/g_zf));
//    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
//    }

//	if (out_vs.pos.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.color.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}

	//簡易フォグ
//	out_vs.color.a = 1.0/((g_zf*0.9)*0.5))*out_vs.pos.z - 1.0; // 1/2 より奥の場合徐々に透明に
	//out_vs.color.a = 1.0/(g_zf - (g_zf*0.75))*out_vs.pos.z - 3.0;  // 3/4 より奥の場合徐々に透明に
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}

float4 GgafDxPS_LaserChip_ONE( 
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {
	float4 out_color = float4(1,1,1,1);
	return out_color;
}

float4 GgafDxPS_LaserChip_SHADOW( 
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {
    //レーザーの影
	float4 out_color = tex2D( MyTextureSampler, prm_uv) * prm_color;
	out_color.rgba *= 0.2;
	return out_color;
}

float4 GgafDxPS_LaserChip( 
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {

	float4 out_color = tex2D( MyTextureSampler, prm_uv) * prm_color;
	out_color.rgba *= 0.9;
	return out_color;
}



technique LaserChipTechnique
{
 	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha; 
        DestBlend = InvSrcAlpha;
        SrcBlendAlpha = One;     //default
        DestBlendAlpha = One;    //default
		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
    }

// 	pass P1 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha; 
//        DestBlend = ONE;
//        SrcBlendAlpha = One;      //default
//        DestBlendAlpha = ZERO;    //default
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
//    }
//

//    pass P1 {
//    	AlphaBlendEnable = true;
//    	SrcBlend  = SrcAlpha; 
//          DestBlend = DestAlpha;
//    	VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//    	PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
//    }
//	pass P3 {
//		AlphaBlendEnable = true;
//		SrcBlend  = InvDestColor; 
//        DestBlend = ZERO;
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip_ONE();
//	}
//	pass P4 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha; 
//        DestBlend = One;
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
//	}


//	pass P0 {
//		AlphaBlendEnable = true;
////通常合成
//		SrcBlend  = SrcAlpha;
////		DestBlend = InvSrcAlpha;
//
//        BlendFactor = {1,1,1,1};
//		DestBlend =  BlendFactor;
//
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip_SHADOW();
////		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
////		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip_SHADOW();
//	}
//	pass P1 {
//		AlphaBlendEnable = true;
////加算合成
//		SrcBlend  = SrcAlpha; 
////		DestBlend = One;
//
////通常合成
////		SrcBlend  = SrcAlpha;
////		DestBlend = InvSrcAlpha;
////Zero/One/SrcColor/InvSrcColor/SrcAlpha/InvSrcAlpha/DestColor/InvDestColor/DestAlpha/InvDestAlpha
////SrcBlend  = SrcAlpha; 
////		DestBlend = One;
//		//SrcBlend  = SrcAlphaSat;
//                         // AARRGGBB
////        BlendFactor     = 0x11111111;//0xffffffff;
//        BlendFactor = {1,1,1,1};
//		DestBlend =  BlendFactor;
////DestBlend = One;
//        //BlendOp = Min;
//        //BlendOpAlpha = Max;
// //BlendOpAlpha = Add;
////BlendOp=Max ;       BlendOpとBlendOpAlphaはおなじようだ
////BlendOpAlpha= Add ;
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
//	}
//BlendOp=REVSUBTRACT, SrcBlend=SRCALPHA, DestBlend=ON

}



