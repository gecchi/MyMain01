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
     "MyOptionWateringLaserChip2001.png";
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
OUT_VS VS_LaserChip2(
      float4 prm_posModel_Local   : POSITION,   // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,
      float2 prm_uv               : TEXCOORD0,  // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float4 prm_infront_world0   : TEXCOORD5,
      float4 prm_infront_world1   : TEXCOORD6,
      float4 prm_infront_world2   : TEXCOORD7,
      float4 prm_infront_world3   : TEXCOORD8,
      float4 prm_info             : TEXCOORD9   //x:チップ種別, y:強制α, z:火力率, w:前方チップ火力率

) {
    OUT_VS out_vs = (OUT_VS)0;

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
    float offset_u = matWorld._14; //ワールド変換行列の._14 u,v座標の u オフセット
    float offset_v = matWorld._24;  //ワールド変換行列の._14 u,v座標の u オフセット
    //元の行列値に戻しておく
    matWorld._14 = 0.0f;
    matWorld._24 = 0.0f;

    float4x4 matWorld_infront = {prm_infront_world0, prm_infront_world1, prm_infront_world2, prm_infront_world3};
    int kind_t = (int)(prm_info.x);
    float force_alpha = prm_info.y;
    float power;
    float4 posModel_infront_World;
    float4 posModel_own_World;
    float4 posModel_World;

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
    //    |   |   |   |   |    `----- 5:先端チップ(非表示で、中間先頭チップを表示するためだけに存在)
    //    |   |   |   |    `----- 4:中間先頭チップ(表示される実質の先頭)
    //    |   |   |    `----- 3:中間チップ
    //    |   |    `----- 3:中間チップ
    //    |    `----- 3:中間チップ
    //     `----- 1:末尾チップ
    //
    //先頭と先端という言葉で区別しています。
    if (prm_posModel_Local.x > 0.0) {

        if (kind_t == 5) {  //4ではないよ
            prm_posModel_Local.x = 0;
            prm_posModel_Local.y = 0;
            prm_posModel_Local.z = 0;
        }
        // 一つ前方のチップ座標へくっつける
        posModel_own_World = mul( prm_posModel_Local, matWorld );
        posModel_infront_World = mul( prm_posModel_Local, matWorld_infront );  //一つ前方のチップのWorld変換
        posModel_World = lerp( posModel_own_World, posModel_infront_World, prm_posModel_Local.x );  //prm_posModel_Local.x は 0.0 ～ 1.0 とする
        power = lerp(prm_info.z, prm_info.w, prm_posModel_Local.x ); //z 自身の火力率 w 前方チップ火力率
    } else { // prm_posModel_Local.x <= 0.0
        //頂点計算
        prm_posModel_Local.x = 0;
        posModel_World = mul( prm_posModel_Local, matWorld );  // World変換
        power = prm_info.z; //火力率
    }
    out_vs.posModel_Proj = mul(mul(posModel_World, g_matView), g_matProj);  // View変換・射影変換

    //UV設定
    if (kind_t == 3) {
        //中間チップ
        out_vs.uv = prm_uv;
    } else if (kind_t == 2) {
        //末尾チップ（先が丸い）
        if (prm_uv.x < 0.51f) {
            out_vs.uv.x = 0.0f;
        } else if (prm_uv.x > 0.51f) {
            out_vs.uv.x = 1.0f;
        } else {
            out_vs.uv.x = prm_uv.x;
        }
        out_vs.uv.y = prm_uv.y;
    } else if (kind_t == 1) {
        //末尾チップ
        out_vs.uv.x = prm_uv.x < 0.51f ? 0.0f : prm_uv.x;
        out_vs.uv.y = prm_uv.y;
    } else if (kind_t == 4) {
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
    out_vs.color = (c < 0.2  ? 0.2 : c) ;
    if (force_alpha > out_vs.color.a) {
        out_vs.color.a = force_alpha*g_alpha_master;
    } else {
        out_vs.color.a = out_vs.color.a*g_alpha_master;
    }
    out_vs.color.rgb *= power;  //powerが大きいほど白く輝く
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

float4 PS_LaserChip2(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0
) : COLOR  {
    return tex2D( MyTextureSampler, prm_uv) * prm_color;
}

technique LaserChip2Technique
{
     pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = true; //!!
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Max;
        SrcBlendAlpha = One;
        DestBlendAlpha = Zero;
        BlendOpAlpha = Add;
        VertexShader = compile VS_VERSION VS_LaserChip2();
        PixelShader  = compile PS_VERSION PS_LaserChip2();
    }
}


