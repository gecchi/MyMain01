#include "GgafEffectConst.fxh" 
/**
 * GgafLib::DefaultMeshActor 用シェーダー .
 * 静的モデル１つを描画する標準的なシェーダー。
 * 頂点バッファフォーマットは
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
 * を、前提とする。
 * @author Masatoshi Tsuge
 * @since 2009/03/06 
 */

/** モデルのWorld変換行列 */
float4x4 g_matWorld;
/** モデルのView変換行列 */
float4x4 g_matView;
/** モデルの射影変換行列 */
float4x4 g_matProj;
/** ライトの方向ベクトル（正規化済み） */
float3 g_vecLightDirection;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam;
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
/** モデルのテクスチャ色点滅機能(GgafDxTextureBlinker参照)の点滅強度 */
float g_tex_blink_power;   
/** モデルのテクスチャ色点滅機能(GgafDxTextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** フェードイン・アウト機能(GgafDxAlphaCurtain参照)のためのマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** -1.0 or 0.999 。遠くでも表示を強制したい場合に0.999 が代入される。*/ 
float g_far_rate;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler BumpMapTextureSampler : register(s2);  
/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 pos    : POSITION;    //座標
    float2 uv     : TEXCOORD0;   //テクスチャUV
    float4 color  : COLOR0;      //頂点カラー
    float3 normal : TEXCOORD1;   //オブジェクトの法線ベクトル
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};    
/** 頂点シェーダー、出力構造体(バンプマッピング用) */
struct OUT_VS_BM {
    float4 pos    : POSITION;    //座標
    float2 uv     : TEXCOORD0;   //テクスチャUV
    float4 color  : COLOR0;      //頂点カラー
    float3 normal : TEXCOORD1;   //オブジェクトの法線ベクトル
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル
	float4 lightTangentDirect : TEXCOORD3;
	float4 harfTangentDirect : TEXCOORD4;

};

/**
 * ローカル→接空間変換 行列を返す .
 * 接空間とはメッシュサーフェイス上のある点において、
 * テクスチャu方向ベクトル, テクスチャv方向ベクトル, 法線ベクトル の
 * ３軸で表現される座標系の事。３軸は直交している。
 * @param prm_tangent  接ベクトル(u方向単位ベクトル)
 * @param prm_binormal 従法線ベクトル(v方向単位ベクトル)
 * @param prm_normal   法線ベクトル
 **/
float4x4 InvTangentMatrix(
	float3 prm_tangent,
	float3 prm_binormal,
	float3 prm_normal )
{
	float4x4 mat = { float4(prm_tangent , 0.0f), 
                     float4(prm_binormal, 0.0f), 
                     float4(prm_normal  , 0.0f)  , 
                     {  0.0f, 0.0f, 0.0f, 1.0f } };
	return transpose( mat );  // 転置(∵正規直交系の行列の逆行列は転置行列で良いから)
}


/**
 * GgafLib::DefaultMeshActor 用の標準頂点シェーダー .
 * 頂点を World > View > 射影 変換した後、
 * モデルのマテリアル色付を頂点カラーの設定で行う。
 * マテリアル色付とは具体位的に
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、の事。
 * @param prm_pos    頂点のローカル座標
 * @param prm_normal 頂点の法線
 * @param prm_uv     頂点のUV座標
 */
OUT_VS GgafDxVS_DefaultMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
    OUT_VS out_vs = (OUT_VS)0;

    //頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld); //World変換
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影

    //UV計算
    out_vs.uv = prm_uv;  //そのまま

    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.normal = normalize(mul(prm_normal, g_matWorld));     
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル（スペキュラで使用）                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;

    //遠方時の表示方法。
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //マスターα
    out_vs.color.a *= g_alpha_master;

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor 用の標準ピクセルシェーダー .
 * @param prm_uv     ピクセルでのUV座標
 * @param prm_color  ピクセルでの色（頂点カラーによる）
 * @param prm_normal ピクセルでの法線
 * @param prm_cam    ピクセルでの座標 -> 視点 ベクトル
 */
float4 GgafDxPS_DefaultMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
    //テクスチャ色に        
    float4 out_color = tex_color * prm_color + s;
    //Blinkerを考慮
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    } 
    //マスターα
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * GgafLib::DefaultMeshActor 用の標準頂点シェーダー .
 * 頂点を World > View > 射影 変換した後、
 * モデルのマテリアル色付を頂点カラーの設定で行う。
 * マテリアル色付とは具体位的に
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、の事。
 * @param prm_pos    頂点のローカル座標
 * @param prm_normal 頂点の法線
 * @param prm_uv     頂点のUV座標
 * @param prm_tangent  接ベクトル(u方向単位ベクトル)
 * @param prm_binormal 従法線ベクトル(v方向単位ベクトル)
 */
OUT_VS_BM GgafDxVS_BumpMapping(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0,
      float3 prm_tangent  : TEXCOORD1,
      float3 prm_binormal : TEXCOORD2  
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld); //World変換
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影

    //UV計算
    out_vs.uv = prm_uv;  //そのまま

	// 接空間行列の逆行列を算出
	float4x4 invTangentMat = InvTangentMatrix(prm_tangent, prm_binormal, prm_normal );
	// ライトベクトルを接空間に移す
	out_vs.lightTangentDirect = mul( -g_vecLightDirection, invTangentMat );


    if (g_specular_power != 0) {
        //「頂点→カメラ視点」方向ベクトル（スペキュラで使用）                                                        
        out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(out_vs.cam + (-g_vecLightDirection));
        //ハーフベクトルを接空間に移す
        out_vs.harfTangentDirect =  mul(vecHarf, invTangentMat );
    }

    //頂点カラー計算(拡散光色,マテリアル色)
    out_vs.color = g_colMaterialDiffuse;


    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;

    //遠方時の表示方法。
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //本来視野外のZでも、描画を強制するため g_zf*0.999 に上書き、
        }
    } else {
        //αフォグ
        if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //マスターα
    out_vs.color.a *= g_alpha_master;

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor 用の標準ピクセルシェーダー .
 * @param prm_uv     ピクセルでのUV座標
 * @param prm_color  ピクセルでの色（頂点カラーによる）
 * @param prm_normal ピクセルでの法線
 * @param prm_cam    ピクセルでの座標 -> 視点 ベクトル
 */
float4 GgafDxPS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2,   //頂点 -> 視点 ベクトル
    float3 inLightTangentDirect : TEXCOORD3,  //接空間座標系に変換された拡散光方向ベクトル
    float3 inHarfTangentDirect : TEXCOORD4
) : COLOR  {
    float a = prm_color.a; //α保持

	float3 normalVec = 2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz-1.0; //法線マップからの法線
	normalVec = normalize( normalVec );//法線正規化
    //法線(法線マップの法線、つまり接空間座標系の法線になる）と、
    //拡散光方向ベクトル(頂点シェーダーで接空間座標系に予め変換済み) の内積から
    //ライト入射角を求め、面に対する拡散光の減衰率(power)を求める
    float power = max(dot(normalVec, normalize(inLightTangentDirect) ), 0); 


    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトルで
        //接空間座標系に予め変換済み）と法線(法線マップの法線、つまり接空間座標系の法線)の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(normalVec, inHarfTangentDirect)), g_specular ) * g_specular_power;
    }



    //環境光色、テクスチャ色、頂点カラー、減衰率、スペキュラ を考慮した色作成  
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
//tex_color * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * g_colMaterialDiffuse ) + s;
//tex・mate・(amb + (light・p))  + s

    float4 out_color = tex_color * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * prm_color ) + s; //prm_color == g_colMaterialDiffuse
    //Blinkerを考慮
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //あえてαも倍率を掛ける。点滅を目立たせる。
    } 
    //マスターα
    out_color.a = a * g_alpha_master;
    return out_color;
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
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
    float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * 通常テクニック .
 */
technique DefaultMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

technique BumpMapping
{
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

/**
 * 加算合成テクニック .
 */
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

/**
 * 閃光テクニック .
 */
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

