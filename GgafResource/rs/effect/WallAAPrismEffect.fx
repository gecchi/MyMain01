#include "GgafDx_World3DimEffect.fxh"

////////////////////////////////////////////////////////////////////////////////
// WallAAPrismActor用シェーダー
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
int g_pos_info;

// ライトの方向
float3 g_vecLightFrom_World;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）
float4 g_colLightDiffuse;

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
//float4x4 g_matWorld018;
//float4x4 g_matWorld019;
//float4x4 g_matWorld020;

#define POS_PRISM_xx_NN    1
#define POS_PRISM_xx_NP    2
#define POS_PRISM_xx_PN    4
#define POS_PRISM_xx_PP    8
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

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
OUT_VS VS_WallAAPrism(
      float4 prm_posModel_Local    : POSITION,      // モデルの頂点
      float  prm_object_index  : PSIZE , // モデルのインデックス（何個目のオブジェクトか）
      float3 prm_vecNormal_Local : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;
    //ワールド変換行列を割り当てる
    const int index = (int)prm_object_index;
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
//	} else if (index == 10) {
//		matWorld = g_matWorld011;
//	} else if (index == 11) {
//		matWorld = g_matWorld012;
//	} else if (index == 12) {
//		matWorld = g_matWorld013;
//	} else if (index == 13) {
//		matWorld = g_matWorld014;
//	} else if (index == 14) {
//		matWorld = g_matWorld015;
//	} else if (index == 15) {
//		matWorld = g_matWorld016;
//	} else if (index == 16) {
//		matWorld = g_matWorld017;
//	} else if (index == 17) {
//		matWorld = g_matWorld018;
//	} else if (index == 18) {
//		matWorld = g_matWorld019;
    } else {
        matWorld = g_matWorld011;
    }
    //描画面番号情報が、ワールド変換行列のmatWorld._14 に埋め込まれている
    int draw_face = matWorld._14;
    int pos_info = matWorld._24;
    //元の行列値に戻しておく
    matWorld._14 = 0;
    matWorld._24 = 0; //元の行列値に戻しておく

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

    //BOXの１面を無理やり閉じてプリズム型に変形させる
    float ah,fh;
    if (pos_info >= POS_PRISM_ZX_xx) {
        //＋X -X の面がプリズムの斜め面にならないようにする
        // ZX は XZ平面と見る
        pos_info -= POS_PRISM_ZX_xx;
        ah = g_wall_width / g_wall_dep / 2.0; //傾き z/x （傾き x/z ではなくて）
        //ah = g_wall_height / g_wall_dep / 2.0; //傾き y/x
        fh = g_wall_dep/2.0;
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+fh)/g_wall_dep))       - ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) + ((prm_posModel_Local.x+fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+fh)/g_wall_dep))       + ((prm_posModel_Local.x-fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) - ((prm_posModel_Local.x+fh)*ah);
        }
    } else if (pos_info >= POS_PRISM_YZ_xx) {
        //＋Z -Z の面がプリズムの斜め面にならないようにする
        pos_info -= POS_PRISM_YZ_xx;
        ah = g_wall_height / g_wall_width / 2.0; //傾き y/z
        fh = g_wall_width/2.0;                   //傾く軸
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+fh)/g_wall_width))       - ((prm_posModel_Local.z-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+fh)/g_wall_width))) + ((prm_posModel_Local.z+fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+fh)/g_wall_width))       + ((prm_posModel_Local.z-fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+fh)/g_wall_width))) - ((prm_posModel_Local.z+fh)*ah);
        }
    } else { //if (pos_info >= POS_PRISM_XY_xx) {
        //＋X -X の面がプリズムの斜め面にならないようにする
        pos_info -= POS_PRISM_XY_xx;
        ah = g_wall_height / g_wall_dep / 2.0; //傾き y/x
        fh = g_wall_dep/2.0;                   //傾く軸
        if (pos_info == POS_PRISM_xx_PP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))       - ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_PN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))       + ((prm_posModel_Local.x-fh)*ah);
        } else if (pos_info == POS_PRISM_xx_NP) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) + ((prm_posModel_Local.x+fh)*ah);
        } else { //if (pos_info == POS_PRISM_xx_NN) {
            prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+fh)/g_wall_dep))) - ((prm_posModel_Local.x+fh)*ah);
        }
    }
    //メモ
    //(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   ・・・ 先端をキュッとまとめる計算
    //+ ((prm_posModel_Local.x-fh)*ah);                      ・・・ 先端を水平にする計算

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
    float refl_power = dot(vecNormal_World, float3(-0.819232,0.573462,0));
    //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //Ambientライト色、Diffuseライト色、Diffuseライト方向 を考慮したカラー作成。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*refl_power));// * マテリアル色無しcolMaterialDiffuse;

    //αフォグ
    //out_vs.color.a = colMaterialDiffuse.a;
//    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
//        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
//    }

    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
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
float4 PS_WallAAPrism(
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
    colOut = getBlinkColor(colOut, colTex);
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

technique WallAAPrismTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_WallAAPrism();
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
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_WallAAPrism();
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
        VertexShader = compile VS_VERSION VS_WallAAPrism();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}
