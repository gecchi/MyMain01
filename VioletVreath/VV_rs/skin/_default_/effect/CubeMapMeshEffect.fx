#include "GgafEffectConst.fxh"
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam_World;
float g_reflectance;
float g_specular;
float g_specular_power;

/** カメラのWorld位置 */
float3 pos_camera;



/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのView変換行列 */
float4x4 g_matView;
/** モデルの射影変換行列 */
float4x4 g_matProj;
/** モデルのWorld変換行列の逆行列 */
float4x4 g_matInvWorld;
/** ライトの方向 */
float3 g_vecLightFrom_World;
/** 環境光色（入射色）*/
float4 g_colLightAmbient;
/** 拡散光色（入射色）*/
float4 g_colLightDiffuse;
/** モデルのマテリアル色（表面色）。いわゆる拡散光反射色で環境光反射色も兼ねる */
float4 g_colMaterialDiffuse;
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の対象となるRGBのしきい値(0.0〜1.0) */
float g_tex_blink_threshold;
/** アルファカーテン(フェードイン・アウト)機能(GgafDxAlphaCurtain参照)のマスターアルファ値(0.0〜1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
sampler BumpMapTextureSampler : register(s2);

/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //最終的な頂点座標(ワールド・ビュー・射影変換済み)
    float2 uv              : TEXCOORD0;   //頂点テクスチャUV
    float4 color           : COLOR0;      //頂点カラー
    float3 vecNormal_World : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_World    : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
};

/** バンプマッピング用頂点シェーダー、出力構造体 */
struct OUT_VS_BM {
    float4 posModel_Proj    : POSITION;    //最終的な頂点座標(ワールド・ビュー・射影変換済み)
    float2 uv               : TEXCOORD0;   //頂点テクスチャUV
    float4 color            : COLOR0;      //頂点カラー
    float3 vecNormal_World  : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_Tangent   : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
    float4 vecLight_Tangent : TEXCOORD3;   //頂点のライトベクトル(ローカルの接空間座標系)
    float4 vecHarf_Tangent  : TEXCOORD4;   //頂点のハーフベクトル(ローカルの接空間座標系)
};

/**
 * 標準的な頂点シェーダー .
 * 頂点バッファには、
 * 頂点を World > View > 射影 変換し、頂点カラーの設定を行っている。
 * モデルのマテリアル色付、つまり
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、は
 * 速度重視のためピクセルシェーダーで行わず、頂点カラーで実現している。
 * @param prm_posModel_Local    モデル頂点のローカル座標
 * @param prm_vecNormal_Local モデル頂点の法線
 * @param prm_vecNormal_Local モデル頂点のUV座標
 */
OUT_VS GgafDxVS_CubeMapMesh(
      float4 prm_posModel_Local  : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv              : TEXCOORD0
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    float4 posModel_World = mul(prm_posModel_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま
    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(out_vs.vecNormal_World, -g_vecLightFrom_World ), 0);
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}

/**
 * 通常ピクセルシェーダー（テクスチャ有り）
 */
float4 GgafDxPS_CubeMapMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_vecEye_World, prm_vecNormal_World));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
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

/**
 * ローカル→接空間変換 行列を返す .
 * 接空間とはメッシュサーフェイス上のある点において、
 * テクスチャu方向ベクトル, テクスチャv方向ベクトル, 法線ベクトル の
 * ３軸で表現される座標系の事。３軸は直交している。<BR>
 * 『マルペケつくろーどっとコム』の記事 <BR>
 * http://marupeke296.com/DXPS_S_No5_NormalMap.html<BR>
 * から引用させて頂きました。<BR>
 * @param prm_vecTangent  接ベクトル(u方向単位ベクトル)
 * @param prm_vecBinormal 従法線ベクトル(v方向単位ベクトル)
 * @param prm_vecNormal   法線ベクトル
 **/
float4x4 getInvTangentMatrix(
    float3 prm_vecTangent,
    float3 prm_vecBinormal,
    float3 prm_vecNormal )
{
    float4x4 mat = { float4(prm_vecTangent , 0.0f),
                     float4(prm_vecBinormal, 0.0f),
                     float4(prm_vecNormal  , 0.0f)  ,
                     {  0.0f, 0.0f, 0.0f, 1.0f } };
    return transpose( mat );  // 転置(∵正規直交系の行列の逆行列は転置行列で良いから)
}


OUT_VS_BM GgafDxVS_BumpMapping(
      float4 prm_posModel_Local    : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv     : TEXCOORD0,
      float3 prm_vecTangent_Local  : TEXCOORD1,
      float3 prm_vecBinormal_Local : TEXCOORD2
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //頂点計算
    float4 posModel_World = mul(prm_posModel_Local, g_matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま

    // 接空間行列の逆行列を算出
    float4x4 matTangent = getInvTangentMatrix(prm_vecTangent_Local, prm_vecBinormal_Local, prm_vecNormal_Local );

    // Worldライトベクトルを接空間に移す
    float3 vecLight_Local = mul(-g_vecLightFrom_World, g_matInvWorld); //ローカルに戻して（TODO:ここは予め計算できる…）
    out_vs.vecLight_Tangent = mul(vecLight_Local, matTangent);         //接空間座標系へ

    //ワールド視点「頂点→カメラ視点」方向ベクトルを接空間に移す（スペキュラで使用）
    float3 vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
    float3 vecEye_Local = mul(vecEye_World, g_matInvWorld);  //ローカルに戻して
    out_vs.vecEye_Tangent  = mul(vecEye_Local, matTangent);  //接空間座標系へ

    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf_World = normalize(vecEye_World + (-g_vecLightFrom_World));
        //Worldハーフベクトルを接空間に移す
        float3 vecHarf_Local = mul(vecHarf_World, g_matInvWorld); //ローカルに戻して
        out_vs.vecHarf_Tangent = mul(vecHarf_Local, matTangent ); //接空間座標系へ
    }

    out_vs.color = g_colMaterialDiffuse;
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.posModel_Proj.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
    }
//    if (out_vs.posModel_Proj.z > g_zf*0.98) {
//        out_vs.posModel_Proj.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
    return out_vs;
}


float4 GgafDxPS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 vecEye_Tangent   : TEXCOORD2,  //接空間座標系に変換された頂点 -> 視点 ベクトル
    float3 vecLight_Tangent : TEXCOORD3,  //接空間座標系に変換された拡散光方向ベクトル
    float3 vecHarf_Tangent  : TEXCOORD4   //接空間座標系に変換されたハーフベクトル
) : COLOR  {
    float a = prm_color.a; //α保持
    //法線マップからの法線
    float3 vecNormal_Tangent = normalize(2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz - 1.0);
    //法線(法線マップの法線、つまり接空間座標系の法線になる）と、
    //拡散光方向ベクトル(頂点シェーダーで接空間座標系に予め変換済み) の内積から
    //ライト入射角を求め、面に対する拡散光の減衰率(power)を求める
    float power = max(dot(vecNormal_Tangent, normalize(vecLight_Tangent) ), 0);

    float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-vecEye_Tangent, vecNormal_Tangent));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトルで
        //接空間座標系に予め変換済み）と法線(法線マップの法線、つまり接空間座標系の法線)の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(vecNormal_Tangent, vecHarf_Tangent)), g_specular ) * g_specular_power;
    }

    //色計算
    float4 colOut = colTex2D * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * prm_color ) + (colTexCube*g_reflectance) +s; //prm_color == g_colMaterialDiffuse
    //TODO:↑色計算もうちょっと頂点シェーダで処理できないものか・・・
    //float4 colOut = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
    if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
    }

    colOut.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master;
    return colOut;
}


float4 PS_Flush(
     float3 prm_vecNormal_World: TEXCOORD0,
    float3 prm_viewVecW: TEXCOORD1,
     float4 prm_color    : COLOR0
) : COLOR  {
    //テクスチャをサンプリングして色取得（原色を取得）
    float3 vReflect = reflect( prm_viewVecW, prm_vecNormal_World );
    float4 colTex = texCUBE(MyTextureSampler, vReflect);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}


/**
 * 通常テクニック
 */
technique CubeMapMeshTechnique
{
    //pass P0「メッシュ標準シェーダー」
    //メッシュを描画する
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
    }
}

technique BumpMapping
{
    //pass P0「メッシュ標準シェーダー」
    //メッシュを描画する
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
        //BlendOpAlpha = Add;       //default
        VertexShader = compile VS_VERSION GgafDxVS_BumpMapping();
        PixelShader  = compile PS_VERSION GgafDxPS_BumpMapping();
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
        VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
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
        VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

