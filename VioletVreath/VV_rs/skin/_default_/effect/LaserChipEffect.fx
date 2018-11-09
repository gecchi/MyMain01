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
float3 g_posCam_World;
float g_specular;
float g_specular_power;
float g_tex_blink_power;
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 posModel_Proj : POSITION;
    float2 uv            : TEXCOORD0;
    float4 color         : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//レーザーチップ頂点シェーダー
OUT_VS GgafDxVS_LaserChip(
      float4 prm_posModel_Local  : POSITION,  // モデルの頂点
      float  prm_index           : PSIZE ,    // PSIZEではなくてなんとモデルの頂点番号
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv              : TEXCOORD0,  // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float4 prm_infront_world0   : TEXCOORD5,
      float4 prm_infront_world1   : TEXCOORD6,
      float4 prm_infront_world2   : TEXCOORD7,
      float4 prm_infront_world3   : TEXCOORD8,
      float4 prm_info             : TEXCOORD9 //チップ種別,強制α,火力率,前方チップ火力率

) {
    OUT_VS out_vs = (OUT_VS)0;

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    float4x4 matWorld_infront = {prm_infront_world0, prm_infront_world1, prm_infront_world2, prm_infront_world3};
    int kind_t = (int)(prm_info.x);
    float force_alpha = prm_info.y;
    float power;
    float4 posModel_World;
    if (prm_posModel_Local.x > 0.0) {
//TODO:20090806アイディア
//現在先頭のチップは何も表示されないので
//２倍して90度回転して、先頭専用テクスチャをを張れば、先を丸く見せれるのではないか
//・・・単に２倍90度回転してだめだった、風車になるだけ

//		if (kind_t == 4) {  //3ではないよ
//         x =  cos90*_Xorg + sin90*_Yorg  = 0*_Xorg + 1*_Yorg   =  Y
//         y = -sin90*_Xorg + cos90*_Yorg  = -1*_Xorg + 0*_Yorg  = -X

//			sin
//		   ナインか
//		}
        //頂点計算
//		if (kind_t == 4) {  //3ではないよ
//			float tmpy = prm_posModel_Local.y;
//			prm_posModel_Local.y = -8.0 * prm_posModel_Local.z;
//			prm_posModel_Local.z = 8.0 * tmpy;
//		}

        prm_posModel_Local.x = 0;
        if (kind_t == 4) {  //3ではないよ
            prm_posModel_Local.y = 0;
            prm_posModel_Local.z = 0;
        }
        // 一つ前方のチップ座標へくっつける
        posModel_World = mul( prm_posModel_Local, matWorld_infront );      // World変換
        power = prm_info.w;
    } else {
//		if (kind_t == 1) {
//			prm_posModel_Local.x = 0;
//			prm_posModel_Local.y = 0;
//			prm_posModel_Local.z = 0;
//		}
        //頂点計算
        posModel_World = mul( prm_posModel_Local, matWorld );        // World変換
        out_vs.posModel_Proj = mul(mul(posModel_World, g_matView), g_matProj);  // View変換射影変換
        power = prm_info.z;
    }
    out_vs.posModel_Proj = mul(mul(posModel_World, g_matView), g_matProj);  // View変換射影変換

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
    if (kind_t == 2) {
        //中間チップ
        out_vs.uv = prm_uv;
    } else if (kind_t == 1) {
        //末尾チップ
        out_vs.uv.x = prm_uv.x < 0.51f ? 0.0f : prm_uv.x;
        out_vs.uv.y = prm_uv.y;
    } else if (kind_t == 3) {
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
	const float c = (1.25-(((out_vs.posModel_Proj.z)/g_zf)*2));
	out_vs.color = (c < 0.2  ? 0.2 : c) ; //powerが大きいほど白く輝く
    if (force_alpha > out_vs.color.a) {
        out_vs.color.a = force_alpha*g_alpha_master;
    } else {
        out_vs.color.a = out_vs.color.a*g_alpha_master;
    }
    out_vs.color.rgb *= power;
//	out_vs.color = c < 0.2  ? 2.0 : c;//1.0-((out_vs.posModel_Proj.z/g_zf)*2) ;//float4((out_vs.posModel_Proj.z/g_zf), (out_vs.posModel_Proj.z/g_zf), (out_vs.posModel_Proj.z/g_zf), 1.0-(out_vs.posModel_Proj.z/g_zf));
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }

//	if (out_vs.posModel_Proj.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.color.a *= (-1.0/(g_zf*0.25)*out_vs.posModel_Proj.z + 4.0);
//	}

    //簡易フォグ
//	out_vs.color.a = 1.0/((g_zf*0.9)*0.5))*out_vs.posModel_Proj.z - 1.0; // 1/2 より奥の場合徐々に透明に
    //out_vs.color.a = 1.0/(g_zf - (g_zf*0.75))*out_vs.posModel_Proj.z - 3.0;  // 3/4 より奥の場合徐々に透明に
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }

//射影変換とは
//右面がX軸+1.0、左面がX軸-1.0
//上面がY軸+1.0、下面がY軸-1.0
//前面（手前の面）がZ軸0.0、背面（奥の面）がZ軸+1.0
//g_zf:現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn
//    _zn = 0.1f;
//    _zf = -_cameraZ_org*(_dep+1.0);
//今 w =  _zf だから
//
    return out_vs;
}

float4 GgafDxPS_LaserChip_ZERO(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    const float4 colOut = float4(1,1,1,1);
    return colOut;
}

//float4 GgafDxPS_LaserChip_SHADOW(
//	float2 prm_uv	  : TEXCOORD0,
//	float4 prm_color    : COLOR0
//) : COLOR  {
//    //レーザーの影
//	float4 colOut = tex2D( MyTextureSampler, prm_uv) * prm_color;
////colOut.r = 1-colOut.r;
////colOut.g = 1-colOut.g;
////colOut.b = 1-colOut.b;
////colOut.a = 1-colOut.a;
//
////    colOut.rgb = 1;
//    colOut.a = 1-colOut.a;
//    //colOut.a = 1-colOut.a;
//	return colOut;
//}

float4 GgafDxPS_LaserChip(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    return tex2D( MyTextureSampler, prm_uv) * prm_color;
}

technique LaserChipTechnique
{
     pass P0 {
        AlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        //BlendOp = Add;    //default
        VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
        PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
    }

// 	pass P1 {
//		AlphaBlendEnable = true;
//        SeparateAlphaBlendEnable = false;
//		SrcBlend  = Zero;
//        DestBlend = DestAlpha;
//		BlendOp = Add;       //default
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip();
//    }
//
//
//    pass P1 {
//		AlphaBlendEnable = true;
//        //SeparateAlphaBlendEnable = true;
//		SrcBlend  = Zero;
//        DestBlend = DestAlpha;
//        //SrcBlendAlpha = One;      //default
//        DestBlendAlpha = One;    //default
//		BlendOpAlpha = Revsubtract;       //default
//		VertexShader = compile VS_VERSION GgafDxVS_LaserChip();
//		PixelShader  = compile PS_VERSION GgafDxPS_LaserChip_SHADOW();
//   }
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
//BlendOpにMin,Maxはきかない？
//BlendOp=REVSUBTRACT, SrcBlend=SRCALPHA, DestBlend=ON

}



