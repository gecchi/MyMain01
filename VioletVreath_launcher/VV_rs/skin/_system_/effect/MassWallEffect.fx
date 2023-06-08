#include "GgafDx_World3DimEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// MassWallActor用シェーダー
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
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //壁ブロックの長さ（X座標軸長さ）
float g_wall_height; //壁ブロックの高さ（Y座標軸長さ）
float g_wall_width;  //壁ブロックの幅（Z座標軸長さ)

float g_ah_POS_ZX;
float g_fh_POS_ZX;
float g_ah_POS_YZ;
float g_fh_POS_YZ;
float g_ah_POS_XY;
float g_fh_POS_XY;

float g_tex_blink_power;
float g_tex_blink_threshold;
// ライトの方向
float3 g_vecLightFrom_World;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）
float4 g_colLightDiffuse;


//プリズム姿勢(位置)定数
#define POS_PRISM_XY_NN   17
#define POS_PRISM_XY_NP   18
#define POS_PRISM_XY_PN   20
#define POS_PRISM_XY_PP   24
#define POS_PRISM_YZ_NN   33
#define POS_PRISM_YZ_NP   34
#define POS_PRISM_YZ_PN   36
#define POS_PRISM_YZ_PP   40
#define POS_PRISM_ZX_NN   65
#define POS_PRISM_ZX_NP   66
#define POS_PRISM_ZX_PN   68
#define POS_PRISM_ZX_PP   72

#define POS_PRISM_xx_NN    1
#define POS_PRISM_xx_NP    2
#define POS_PRISM_xx_PN    4
#define POS_PRISM_xx_PP    8
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

#define POS_PYRAMID_NNN   32768
#define POS_PYRAMID_NNP   33024
#define POS_PYRAMID_NPN   33280
#define POS_PYRAMID_NPP   33536
#define POS_PYRAMID_PNN   33792
#define POS_PYRAMID_PNP   34048
#define POS_PYRAMID_PPN   34304
#define POS_PYRAMID_PPP   34560

#define POS_PYRAMID_xxP   256
#define POS_PYRAMID_xPx   512
#define POS_PYRAMID_xPP   768
#define POS_PYRAMID_Pxx   1024
#define POS_PYRAMID_PxP   1280
#define POS_PYRAMID_PPx   1536

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
OUT_VS VS_MassWall(
      float4 prm_posModel_Local   : POSITION,      // モデルの頂点
      float3 prm_vecNormal_Local  : NORMAL,        // モデルの頂点の法線
      float2 prm_uv               : TEXCOORD0 ,    // モデルの頂点のUV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float4 prm_color            : TEXCOORD5,
      float2 prm_info             : TEXCOORD6
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
    } else if (POS_PRISM_XY_NN <= pos_info && pos_info <= POS_PRISM_ZX_PP) {
        //プリズムの場合

        if (pos_info >= POS_PRISM_ZX_xx) {
            //BOXの１面を無理やり閉じてプリズム型に変形させる
            //＋X -X の面がプリズムの斜め面にならないようにする
            // ZX は XZ平面と見る
            pos_info -= POS_PRISM_ZX_xx;
            if (pos_info == POS_PRISM_xx_PP) {
                prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
            } else if (pos_info == POS_PRISM_xx_PN) {
                prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
            } else if (pos_info == POS_PRISM_xx_NP) {
                prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
            } else { //if (pos_info == POS_PRISM_xx_NN) {
                prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
            }
        } else if (pos_info >= POS_PRISM_YZ_xx) {
            //＋Z -Z の面がプリズムの斜め面にならないようにする
            pos_info -= POS_PRISM_YZ_xx;
            if (pos_info == POS_PRISM_xx_PP) {
                prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
            } else if (pos_info == POS_PRISM_xx_PN) {
                prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
            } else if (pos_info == POS_PRISM_xx_NP) {
                prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
            } else { //if (pos_info == POS_PRISM_xx_NN) {
                prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
            }
        } else { //if (pos_info >= POS_PRISM_XY_xx) {
            pos_info -= POS_PRISM_XY_xx;
            //＋X -X の面がプリズムの斜め面にならないようにする
            if (pos_info == POS_PRISM_xx_PP) {
                prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
            } else if (pos_info == POS_PRISM_xx_PN) {
                prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
            } else if (pos_info == POS_PRISM_xx_NP) {
                prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
            } else { //if (pos_info == POS_PRISM_xx_NN) {
                prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
            }
        }
        //メモ  □→⊿
        // g_wall_dep = 20      幅
        // fh = 20 / 2 = 10     幅(20)の半分
        // ah = 1.0 * 0.5 = 0.5 傾き(1)の半分
        // prm_posModel_Local.x = -10 ～ 10

        //(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   ・・・ 先端をキュッとまとめる計算
        //
        // 		//                 y
        //                ^
        //                |
        //                |
        //                |
        //         +------+------+-
        //         |      |      |
        //         |      |      |
        //   ------+------+------+---->x
        //      -10|     0|      |10
        //         |      |      |
        //         +------+------+-
        //                |
        //                |
        //                |
        //
        //         <------------->
        //  r=    0.0             1.0
        //  r = (prm_posModel_Local.x+fh)/g_wall_dep)
        //
        // その後
        //  - ((fh-prm_posModel_Local.x)*ah);   ・・・ 先端を水平にする計算

    } else {
        //ピラミッドの場合
        pos_info -= POS_PYRAMID_NNN;
        if (pos_info >= POS_PYRAMID_Pxx) {
            // Pxx
            pos_info -= POS_PYRAMID_Pxx;
            if (pos_info >= POS_PYRAMID_xPx) {
                // PPx
                pos_info -= POS_PYRAMID_xPx;
                if (pos_info >= POS_PYRAMID_xxP) {
                    // PPP
                    prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
                } else {
                    // PPN
                    prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
                }
            } else {
                // PNx
                if (pos_info >= POS_PYRAMID_xxP) {
                    // PNP
                    prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
                } else {
                    // PNN
                    prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
                }
            }
        } else {
            // Nxx
            pos_info -= POS_PYRAMID_Pxx;
            if (pos_info >= POS_PYRAMID_xPx) {
                // NPx
                pos_info -= POS_PYRAMID_xPx;
                if (pos_info >= POS_PYRAMID_xxP) {
                    // NPP
                    prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);

                } else {
                    // NPN
                    prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
                }
            } else {
                // NNx
                if (pos_info >= POS_PYRAMID_xxP) {
                    // NNP
                    prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
                } else {
                    // NNN
                    prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
                    prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
                }
            }
        }
    }

    float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};

    const float4 posModel_View = mul(mul( prm_posModel_Local, matWorld ), g_matView ); //World*View
    out_vs.posModel_Proj = mul(posModel_View, g_matProj); //射影変換

    //UVはそのまま
    out_vs.uv = prm_uv;
    //法線を World 変換して正規化
    float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    vecNormal_World.x+=0.5; //値0.5は壁面にも無理やり光を当てるため
                   //ライトベクトルは XYZ=0.819232,-0.573462,0
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
    float refl_power = dot(vecNormal_World, float3(-0.819232,0.573462,0));
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambientライト色、Diffuseライト色、Diffuseライト方向 を考慮したカラー作成。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * prm_color;
    out_vs.color.a = prm_color.a;
    //自機より手前はα
    if (posModel_View.z < g_distance_AlphaTarget) {
        //out_vs.color.a *= ((posModel_View.z  / (g_distance_AlphaTarget*2)) + 0.5f); //1.0～0.5
        out_vs.color.a *= (posModel_View.z  / g_distance_AlphaTarget); //1.0～0.0
    }
    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w; //描画外のZでも、描画を強制するために上書き、
    }
    //メモ：posModel_Proj.w = 1.0 の場合 posModel_Proj ＝ X座標Y座標 -1 ～ +1、深度Z  0 ～ +1

    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_MassWall(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    if (prm_color.a == 0) {
        discard;
    }
    //テクスチャをサンプリングして色取得（原色を取得）
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
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
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique MassWallTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_MassWall();
        PixelShader  = compile PS_VERSION PS_MassWall();
    }
}

technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One; //加算合成
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_MassWall();
        PixelShader  = compile PS_VERSION PS_MassWall();
    }
}

technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_MassWall();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
