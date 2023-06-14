#include "GgafDx_World3DimEffect.fxh"
/**
 * GgafLib::DefaultMeshActor 用シェーダー .
 * 静的モデル１つを描画する標準的なシェーダー。
 * 頂点バッファフォーマットは、以下のような GgafLib::MeshModel に定義されているものを前提としています。
 *
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
 *                                                        D3DFVF_TEXCOORDSIZE2(0) |     // テクスチャ座標
 *                                                        D3DFVF_TEXCOORDSIZE3(1) |     // 接ベクトル
 *                                                        D3DFVF_TEXCOORDSIZE3(2)   )   // 従法線ベクトル
 * {
 *     float x, y, z;             // 座標(ローカル座標系)
 *     float nx, ny, nz;          // 法線ベクトル(ローカル座標系)
 *     DWORD color;               // 頂点カラー
 *     float tu, tv;              // テクスチャ座標
 *     float tan_x, tan_y, tan_z; // 接ベクトル(u方向単位ベクトル、バンプマッピング時に使用) (ローカル座標系)
 *     float bin_x, bin_y, bin_z; // 従法線ベクトル(v方向単位ベクトル、バンプマッピング時に使用) (ローカル座標系)
 * };
 *
 * @author Masatoshi Tsuge
 * @since 2009/03/06
 */

/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのWorld変換行列の逆行列 */
float4x4 g_matInvWorld;
/** ライトの方向ベクトル（正規化済み） */
float3 g_vecLightFrom_World;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam_World;
/** 環境光の色 */
float4 g_colLightAmbient;
/** ライトの色(ライトの拡散反射時のライト自身の色) */
float4 g_colLightDiffuse;
/** モデルのマテリアル色(ライトによる拡散反射時のモデルの色) */
float4 g_colMaterialDiffuse;
/** スペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
float g_specular;
/** スペキュラーの強度 */
float g_specular_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の点滅強度 */
float g_tex_blink_power;
/** モデルのテクスチャ色点滅機能(GgafDx::TextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;

float g_lambert_flg;


/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
/** 法線マップテクスチャのサンプラー(s2 レジスタにセットされたテクスチャを使う) */
sampler BumpMapTextureSampler : register(s2);

/** 頂点シェーダー出力構造体 */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //最終的な頂点座標(ワールド・ビュー・射影変換後)
    float2 uv              : TEXCOORD0;   //頂点テクスチャUV
    float4 color           : COLOR0;      //頂点カラー
    float3 vecNormal_World : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_World    : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
};

/**
 * GgafLib::DefaultMeshActor 用の標準頂点シェーダー .
 * 頂点を World > View > 射影 変換した後、
 * モデルに以下の色をブレンドし、頂点カラーとしての設定する
 * ・ライトの色（拡散光色）
 * ・モデルのマテリアル色（拡散光反射色）
 * ・環境光色を加算
 *  （※以上の色とモデル表面の法線とライト入射角との差を計算し、ライトの色を減衰を考慮）
 * ・遠方描画時のαフォグ
 * @param prm_posModel_Local  頂点のローカル座標
 * @param prm_vecNormal_Local ローカル頂点での法線ベクトル
 * @param prm_uv              頂点のUV座標
 * @return OUT_VS 頂点シェーダー出力構造体。上記の説明を参照
 */
OUT_VS VS_DefaultMesh(
      float4 prm_posModel_Local  : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv              : TEXCOORD0
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld);        //World変換
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影

    //UV計算
    out_vs.uv = prm_uv;  //そのまま

    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光反射率を求める。
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    if (g_lambert_flg > 0) {
        //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
        refl_power = refl_power * 0.5f + 0.5f;
        refl_power *= refl_power;
    } else {
        //通常のランバート反射、内積の負の値をカット
        refl_power = max(refl_power, 0);
    }
    //拡散光色に反射率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color.rgb = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse.rgb;
    //αはライトに関係なくマテリアルαを優先とする
    out_vs.color.a = g_colMaterialDiffuse.a;
    //「頂点→カメラ視点」方向ベクトル。ピクセルシェーダーのスペキュラー計算で使用。
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

    //遠方時の表示方法。
    if (g_fog_starts_far_rate < 0.0) {
        //負の場合、どんな遠方でも表示する
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //本来視野外のZでも、描画を強制するため、射影後のZ座標を上書き、
            out_vs.posModel_Proj.z = g_zf*0.999; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor 用の標準ピクセルシェーダー .
 * 各ピクセルに、頂点カラーで設定された色にと下記の色をブレンドする。
 * ・テクスチャの色
 * ・スペキュラーの強さを加算
 * ・Blinker（特定の閾値より大きい色について点滅効果）を考慮
 * ・マスターα
 * @param prm_uv              UV座標
 * @param prm_color           色（マテリアル、ライト、αフォグ考慮済み）
 * @param prm_vecNormal_World 法線ベクトル(ワールド座標系)
 * @param prm_vecEye_World    視線(頂点 -> 視点)ベクトル(ワールド座標系)
 */
float4 PS_DefaultMesh(
    float2 prm_uv              : TEXCOORD0,
    float4 prm_color           : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2
) : COLOR  {
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    //出力色にテクスチャ色にマテリアルカラーを考慮
    float4 colOut = colTex * prm_color;
    //スペキュラ成分計算
    float s = 0.0f;
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }
    //出力色にスペキュラーを考慮
    colOut.rgb += s;
    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }
    //マスターα
    colOut.a *= g_alpha_master;
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


/** バンプマッピング用頂点シェーダー、出力構造体 */
struct OUT_VS_BM {
    float4 posModel_Proj    : POSITION;    //最終的な頂点座標(ワールド・ビュー・射影変換後)
    float2 uv               : TEXCOORD0;   //頂点テクスチャUV
    float4 color            : COLOR0;      //頂点カラー
    float3 vecNormal_World  : TEXCOORD1;   //頂点の法線ベクトル(ワールド座標系)
    float3 vecEye_World     : TEXCOORD2;   //頂点の視線(頂点->視点)ベクトル(ワールド座標系)
    float4 vecLight_Tangent : TEXCOORD3;   //頂点のライトベクトル(ローカルの接空間座標系)
    float4 vecHarf_Tangent  : TEXCOORD4;   //頂点のハーフベクトル(ローカルの接空間座標系)
};

/**
 * GgafLib::DefaultMeshActor バンプマッピング用の頂点シェーダー .
 * 頂点を World > View > 射影 変換した後、
 * モデルに以下の色をブレンドし、頂点カラーとしての設定する
 * ・モデルのマテリアル色（拡散光反射色）
 * ・遠方描画時のαフォグ。
 * @param prm_posModel_Local    モデル頂点(ローカル座標系)
 * @param prm_vecNormal_Local   頂点の法線(ローカル座標系)
 * @param prm_uv                頂点のUV座標
 * @param prm_vecTangent_Local  頂点の接ベクトル(u方向単位ベクトル)(ローカル座標系)
 * @param prm_vecBinormal_Local 頂点の従法線ベクトル(v方向単位ベクトル)(ローカル座標系)
 */
OUT_VS_BM VS_BumpMapping(
      float4 prm_posModel_Local    : POSITION,
      float3 prm_vecNormal_Local   : NORMAL,
      float2 prm_uv                : TEXCOORD0,
      float3 prm_vecTangent_Local  : TEXCOORD1,
      float3 prm_vecBinormal_Local : TEXCOORD2
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //頂点計算
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld); //World変換
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*射影

    //UV計算
    out_vs.uv = prm_uv;  //そのまま

    // 接空間行列の逆行列を算出
    const float4x4 matTangent = getInvTangentMatrix(prm_vecTangent_Local, prm_vecBinormal_Local, prm_vecNormal_Local );
    // Worldライトベクトルを接空間に移す
    const float3 vecLight_Local = mul(-g_vecLightFrom_World, g_matInvWorld); //ローカルに戻して（TODO:ここは予め計算できる…）
    out_vs.vecLight_Tangent = mul(vecLight_Local, matTangent);         //接空間座標系へ

    if (g_specular_power != 0) {
        //「頂点→カメラ視点」方向ベクトル（スペキュラで使用）
        out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
        //Worldハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf_World = normalize(out_vs.vecEye_World + (-g_vecLightFrom_World));
        //Worldハーフベクトルを接空間に移す
        float3 vecHarf_Local = mul(vecHarf_World, g_matInvWorld); //ローカルに戻して
        out_vs.vecHarf_Tangent = mul(vecHarf_Local, matTangent ); //接空間座標系へ
    }

    //頂点カラーにマテリアル色を設定しておく、
    //ライトの拡散光色計算は、バンプマッピングの計算のピクセルシェーダーで行う
    out_vs.color = g_colMaterialDiffuse;

    //遠方時の表示方法。
    if (g_fog_starts_far_rate < 0.0) {
        //負の場合、どんな遠方でも表示する
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //本来視野外のZでも、描画を強制するため、射影後のZ座標を上書き、
            out_vs.posModel_Proj.z = g_zf*0.999; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor バンプマッピング用のピクセルシェーダー .
 * 法線マップから得た法線を考慮し拡散光の減衰率を計算し、
 * 疑似的に表面に凹凸があるようにみせる。
 * 各ピクセルに、頂点カラーで設定された色にと下記の色をブレンドする。
 * ・ライトの色（拡散光色）
 * ・モデルのマテリアル色（拡散光反射色）
 * ・環境光色を加算
 * ・環境光色をブレンド
 * ・スペキュラーの強さを加算
 *  （※以上の色について、モデル表面の法線とライト入射角との差を計算し、ライトの色を減衰を考慮する
 *      その際、モデル表面の法線については、法線マップから得た法線を考慮する）
 * ・Blinker（特定の閾値より大きい色について点滅効果）を考慮
 * ・マスターαをブレンド
 * @param prm_uv               UV座標
 * @param prm_color            色（頂点カラーによるマテリアル色が設定済）
 * @param prm_vecNormal_World  法線ベクトル(World座標系)
 * @param prm_vecEye_World     視線(頂点->視点)ベクトル(World座標系)
 * @param prm_vecLight_Tangent 拡散光方向ベクトル(接空間座標系)
 * @param prm_vecHarf_Tangent  ハーフベクトル(接空間座標系)
 */
float4 PS_BumpMapping(
    float2 prm_uv               : TEXCOORD0,
    float4 prm_color            : COLOR0,
    float3 prm_vecNormal_World  : TEXCOORD1,
    float3 prm_vecEye_World     : TEXCOORD2,
    float3 prm_vecLight_Tangent : TEXCOORD3,
    float3 prm_vecHarf_Tangent  : TEXCOORD4
) : COLOR  {
    const float a = prm_color.a; //α保持

    //法線マップからの法線
    const float3 vecNormal_Tangent = normalize(2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz - 1.0);

    //法線(法線マップの法線、つまり接空間座標系の法線になる）と、
    //拡散光方向ベクトル(頂点シェーダーで接空間座標系に予め変換済み) の内積から
    //ライト入射角を求め、面に対する拡散光の減衰率(power)を求める
    float refl_power = dot(vecNormal_Tangent, normalize(prm_vecLight_Tangent));
    if (g_lambert_flg > 0) {
        //内積の負の値も使用して、ハーフ・ランバート で拡散光の回析を行う
        refl_power = refl_power * 0.5f + 0.5f;
        refl_power *= refl_power;
    } else {
        //通常のランバート反射、内積の負の値をカット
        refl_power = max(refl_power, 0);
    }

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトルで
        //接空間座標系に予め変換済み）と法線(法線マップの法線、つまり接空間座標系の法線)の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(vecNormal_Tangent, prm_vecHarf_Tangent)), g_specular ) * g_specular_power; //法線マップの凸凹を考慮。
    }

    const float4 colTex = tex2D( MyTextureSampler, prm_uv); //単純にUVから色取得、つまり法線マップの凸凹は未考慮。
    //環境光色、テクスチャ色、頂点カラー、減衰率、スペキュラ を考慮した色作成
    //tex・mate・(amb + (light・pow)) + spow
    float4 colOut = colTex * ((g_colLightAmbient + ( g_colLightDiffuse * refl_power)) * prm_color ) + s; //prm_color = g_colMaterialDiffuse
    //Blinkerを考慮
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    }
    colOut.a = a * g_alpha_master;
    return colOut;
}

/**
 * GgafLib::DefaultMeshActor 用の閃光ピクセルシェーダー .
 * テクスチャ原色を FLUSH_COLOR 倍して設定。
 * @param prm_uv     ピクセルでのUV座標
 * @param prm_color  ピクセルでの色（頂点カラーによる）
 */
float4 PS_Flush(
    float2 prm_uv  : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

/**
 * 通常エフェクトのTechnique .
 */
technique DefaultMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;

        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;

        //SrcBlendAlpha = One;    //default
        //DestBlendAlpha = Zero;  //default
        //BlendOpAlpha = Add;     //default

        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

/**
 * バンプマッピングエフェクトのテクニック .
 */
technique BumpMapping
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_BumpMapping();
        PixelShader  = compile PS_VERSION PS_BumpMapping();
    }
}

/**
 * 加算合成エフェクトのテクニック .
 */
technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

technique DestBlendOneMax
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Max;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

/**
 * 閃光エフェクトのテクニック .
 */
technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

