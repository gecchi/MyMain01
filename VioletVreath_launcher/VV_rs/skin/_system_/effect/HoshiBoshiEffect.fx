#include "GgafDx_World3DimEffect.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ライブラリ、MeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列

float g_fX_MyShip;
float g_fY_MyShip;
float g_fZ_MyShip;
float g_far_rate;

float g_dist_CamZ_default;
float g_dist_VpInfrontPlane; //ほぼ視点からの距離
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_InvTextureSplitRowcol;
float g_offset_u;        //テクスチャU座標増分
float g_offset_v;         //テクスチャV座標増分
int g_UvFlipPtnNo;

float3 g_vecLightFrom_World; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
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
    float  psize  : PSIZE;
    float4 color    : COLOR0;
    float4 uv_ps  : COLOR1;  //スペキュラを潰して表示したいUV座標左上の情報をPSに渡す
};


///////////////////////////////////////////////////////////////////////////
////http://wlog.flatlib.jp/?blogid=1&query=dxgi
//// パックされたカラーを展開する
//float3 pf_to_float3( float pf )
//{
//    uint    data= asint( pf );
//    float3  rcol;
//    const float tof= 1.0f/255.0f;
//    rcol.x= ( data      & 255) * tof;
//    rcol.y= ((data>> 8) & 255) * tof;
//    rcol.z= ((data>>16) & 255) * tof;
//    return  rcol;
//}
//
//// カラーを float1 に圧縮する
//float float3_to_pf( float3 color )
//{
//    uint3   bcol= (uint3)( color * 255.0f ) & 255;
//    return  asfloat( (bcol.z << 16) + (bcol.y << 8) + bcol.x );
//}


//メッシュ標準頂点シェーダー
OUT_VS VS_HoshiBoshi(
      float4 prm_posModel_Local : POSITION,  //ポイントスプライトのポイント群
      float  prm_psize_rate     : PSIZE,     //PSIZEはポイントサイズでは無く、スケールの率(0.0～N (1.0=等倍)) が入ってくる
      float2 prm_ptn_no         : TEXCOORD0, //UVでは無くて、prm_ptn_no.xには、表示したいアニメーションパターン番号が埋め込んである
      float4 prm_color          : COLOR0     //オブジェクトのカラー
) {
    OUT_VS out_vs = (OUT_VS)0;

    out_vs.color = prm_color;
    //out_vs.posModel_Proj = mul(prm_posModel_Local, g_matWorld);  //World
    float4 posModel_World = mul(prm_posModel_Local, g_matWorld);  //

    const float w_zf = g_zf * g_far_rate;
    //カメラの最大視野範囲(-_zf ～ _zf, -_zf ～ _zf, -_zf ～ _zf)
    //を超えている場合、ループする。
    if (posModel_World.x > w_zf) {
        posModel_World.x = posModel_World.x - (w_zf*2);
    }
    if (posModel_World.x < -w_zf) {
        posModel_World.x = posModel_World.x + (w_zf*2);
    }
    if (posModel_World.y > w_zf) {
        posModel_World.y = posModel_World.y - (w_zf*2);
    }
    if (posModel_World.y < -w_zf) {
        posModel_World.y = posModel_World.y + (w_zf*2);
    }
    if (posModel_World.z > w_zf) {
        posModel_World.z = posModel_World.z - (w_zf*2);
    }
    if (posModel_World.z < -w_zf) {
        posModel_World.z = posModel_World.z + (w_zf*2);
    }

// 自機の周りにある星々を滑らかに透明にしたい。
//
// 自機座標を(X,Y,Z)とした場合。
// f(x,y,z) = abs(X-x)+abs(Y-y)+abs(Z-z)　と置くと
// f(x,y,z) = D を満たす(x,y,z)は、距離がDのラミエルな領域となる。
// f(x,y,z) = g_dist_CamZ_default はつまり ① のような範囲である。（g_dist_CamZ_defaultは自機からカメラの初期距離）
// ①を式変形して
// {abs(X-x)+abs(Y-y)+abs(Z-z)} / g_dist_CamZ_default = 1.0 … ①
// これより、以下の範囲を考える
// {abs(X-x)/15 + abs(Y-y)/2 + abs(Z-z)/2} / g_dist_CamZ_default = 1.0 …②
// {abs(X-x)/15 + abs(Y-y)/2 + abs(Z-z)/2} / g_dist_CamZ_default = 2.0 …③
// [真上からのイメージ（図の比率がオカシイが；）]
//
//      Z
//     ^
//     |
//     |
//     |
//     |
//     |                                            ＝＿
//     |                       (dCamZ,0)              ￣＝＿        ●                                  ●
//     |                     ／ ＼                        ￣＝＿
//     |                   ／     ＼                        ②￣＝＿             ●   ￣＝＿
//     |                 ／       ①＼                            ￣＝＿                ③￣＝＿
//     |               ／             ＼                              ￣＝＿                  ￣＝＿
//     |             ／                 ＼                                ￣＝＿                  ￣＝＿
// ----+--------------------- 自機→ --------------------------------------------------------------------------------> X
//    0|   (-dCamZ,0)＼        ^        ／  (dCamZ,0)                     ＿＝￣ (15*dCamZ,0)     ＿＝￣(30*dCamZ,0)
//     |               ＼      |dCamZ ／                              ＿＝￣                  ＿＝￣
//     |                 ＼    |    ／      この領域(A領域)では   ＿＝￣                  ＿＝￣
//     |                   ＼  |  ／        星は非表示        ＿＝￣        ●        ＿＝￣                    ●
//     |                     ＼v／                        ＿＝￣                  ＿＝￣
// ￣＝＿                     Cam (dCamZ,0)           ＿＝￣                  ＿＝￣
//     ￣＝＿                  ^                  ＿＝￣この領域(B領域)   ＿＝￣
//     |   ￣＝＿              |              ＿＝￣     星が薄まる   ＿＝￣  ●(posModel_World.x, posModel_World.y, posModel_World.z)
//     |       ￣＝＿          |          ＿＝￣                  ＿＝￣      星
//     |           ￣＝＿      |      ＿＝￣                  ＿＝￣
//     |               ￣＝＿  v  ＿＝￣                  ＿＝￣
// ￣＝＿                  ￣＝ ＝￣                  ＿＝￣
//     ￣＝＿                  ^ (2*dCamZ,0)      ＿＝￣
//     |   ￣＝＿              |              ＿＝￣
//     |       ￣＝＿          |          ＿＝￣                           ●
//     |           ￣＝＿      |      ＿＝￣
//     |               ￣＝＿  v  ＿＝￣
//     |                   ￣＝ ＝￣
//                             (4*dCamZ,0)
//
// ここで (x,y,z) に星の座標を代入して、③→②へ移動中にアルファを減らそうとした。

    const float r2 = ( abs(posModel_World.x-g_fX_MyShip)/15.0 +
                       abs(posModel_World.y-g_fY_MyShip)/2.0 +
                       abs(posModel_World.z-g_fZ_MyShip)/2.0  ) / g_dist_CamZ_default;
    // r2 < 1.0         がA領域
    // 1.0 < r2 < 2.0   がB領域  となる

    if (r2 < 1.0) {
        //A領域の場合、星を非表示
        out_vs.color.a = 0;
    } else {
        //A領域外側の場合、星を距離に応じて半透明
        out_vs.color.a = r2 - 1.0;
    }
    const float4 posModel_View = mul(posModel_World, g_matView);

    const float dep = posModel_View.z  + 1.0; //+1.0の意味は
                                          //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                          //距離に加える。
//    if (dep > g_zf) {
//        dep = g_zf;
//    }

    out_vs.posModel_Proj = mul(posModel_View, g_matProj);  //射影変換

    if (out_vs.posModel_Proj.z > g_zf*0.98) {
        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZ座標でも、描画を強制するため0.9以内に上書き、
    }

    //奥ほど小さく表示するために縮小率計算
    //out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep) * prm_psize_rate;  //prm_psize_rate=Xファイルの、通常時縮小率
    out_vs.psize = (g_TexSize*g_dist_CamZ_default*prm_psize_rate) / (g_TextureSplitRowcol*dep);  //prm_psize_rate=Xファイルの、通常時縮小率
    //psizeは画面上のポイント スプライトの幅 (ピクセル単位)
    if (out_vs.psize < 2.5) {
        //2.5pix x 2.5pix より小さい場合、星としての描画を強制するため2.5x2.5を維持。
        out_vs.psize = 2.5;
    }
//out_vs.psize = (g_TexSize / g_TextureSplitRowcol);


 //   out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_dist_CamZ_default / dep ) * prm_psize_rate + (-(g_dist_CamZ_default - dep) * 0.001);
    //通常の奥行きの縮小率では、星がもともと小さいため、遠くの星はほとんど見えなくなってしまう。
    //そこで (-(g_dist_CamZ_default - dep) * 0.001) を縮小率に加算し、奥行きに対する縮小率を緩やかにし、
    //遠くの星でも存在が解るようにした。
 //out_vs.psize =(g_TexSize / g_TextureSplitRowcol)*prm_psize_rate;
    //スペキュラセマンテックス(COLOR1)を潰して表示したいUV座標左上の情報をPSに渡す
    int ptnno = prm_ptn_no.x + g_UvFlipPtnNo;
    if (ptnno >= g_TextureSplitRowcol*g_TextureSplitRowcol) {
        ptnno -= (g_TextureSplitRowcol*g_TextureSplitRowcol);
    }
    out_vs.uv_ps.x = fmod(ptnno, g_TextureSplitRowcol) * g_InvTextureSplitRowcol;
    out_vs.uv_ps.y = trunc(ptnno * g_InvTextureSplitRowcol) * g_InvTextureSplitRowcol;

    return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_HoshiBoshi(
    float2 prm_uv_pointsprite : TEXCOORD0,
    float4 prm_color          : COLOR0,
    float4 prm_uv_ps          : COLOR1  //スペキュラでは無くて、表示したいUV座標左上の情報が入っている
) : COLOR  {
    float2 uv = (float2)0;
    float4 color = prm_color;
    color.a = 1.0;
    uv.x = prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x;
    uv.y = prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y;
    float4 colOut = tex2D( MyTextureSampler, uv) * color * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}


float4 PS_Flush(
    float2 prm_uv_pointsprite	  : TEXCOORD0,
    float4 prm_color                : COLOR0,
    float4 prm_uv_ps              : COLOR1
) : COLOR  {
    float2 uv = (float2)0;
    uv.x = prm_uv_pointsprite.x * g_InvTextureSplitRowcol + prm_uv_ps.x;
    uv.y = prm_uv_pointsprite.y * g_InvTextureSplitRowcol + prm_uv_ps.y;
    float4 colOut = tex2D( MyTextureSampler, uv) * prm_color * FLUSH_COLOR * g_colMaterialDiffuse;
    colOut.a *= g_alpha_master;
    return colOut;
}

technique HoshiBoshiTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_HoshiBoshi();
        PixelShader  = compile PS_VERSION PS_HoshiBoshi();
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
        VertexShader = compile VS_VERSION VS_HoshiBoshi();
        PixelShader  = compile PS_VERSION PS_HoshiBoshi();
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
        VertexShader = compile VS_VERSION VS_HoshiBoshi();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

