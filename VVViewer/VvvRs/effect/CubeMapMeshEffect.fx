#include "GgafEffectConst.fxh" 
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */
//エラー回避のためにとりあえず追加後でちゃんとする
float3 g_posCam;
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
/** ライトの方向 */
float3 g_vecLightDirection;
/** 環境光色（入射色）*/
float4 g_colLightAmbient;
/** 拡散光色（入射色）*/
float4 g_colLightDiffuse;
/** モデルのマテリアル色（表面色）。いわゆる拡散光反射色で環境光反射色も兼ねる */
float4 g_colMaterialDiffuse;
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の点滅強度 */
float g_tex_blink_power;   
/** モデルのテクスチャ点滅機能(GgafDxTextureBlinker参照)の対象となるRGBのしきい値(0.0～1.0) */
float g_tex_blink_threshold;
/** アルファカーテン(フェードイン・アウト)機能(GgafDxAlphaCurtain参照)のマスターアルファ値(0.0～1.0) */
float g_alpha_master;
/** 現在の射影変換行列要素のzf。カメラから遠くのクリップ面までの距離(どこまでの距離が表示対象か）> zn */
float g_zf;
/** テクスチャのサンプラー(s0 レジスタにセットされたテクスチャを使う) */
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
sampler BumpMapTextureSampler : register(s2);  

/** 頂点シェーダー、出力構造体 */
struct OUT_VS {
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color  : COLOR0;
    float3 normal : TEXCOORD1;   // ワールド変換した法線
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル
};

struct OUT_VS_BM {
    float4 pos    : POSITION;    //座標
    float2 uv     : TEXCOORD0;   //テクスチャUV
    float4 color  : COLOR0;      //頂点カラー
    float3 normal : TEXCOORD1;   //オブジェクトの法線ベクトル
    float3 camTangentDirect    : TEXCOORD2;   //頂点 -> 視点 ベクトル
	float4 lightTangentDirect : TEXCOORD3;
	float4 harfTangentDirect : TEXCOORD4;

};

/**
 * 標準的な頂点シェーダー .
 * 頂点バッファには、
 * 頂点を World > View > 射影 変換し、頂点カラーの設定を行っている。
 * モデルのマテリアル色付、つまり
 * 拡散光色、拡散光反射色、環境光色、マスターアルファ、フォグ、は
 * 速度重視のためピクセルシェーダーで行わず、頂点カラーで実現している。
 * @param prm_pos    モデル頂点のローカル座標
 * @param prm_normal モデル頂点の法線
 * @param prm_normal モデル頂点のUV座標
 */
OUT_VS GgafDxVS_CubeMapMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
 	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld);
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
    //「頂点→カメラ視点」方向ベクトル                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}

/**
 * 通常ピクセルシェーダー（テクスチャ有り）
 */
float4 GgafDxPS_CubeMapMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_cam, prm_normal));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master; 
	return out_color;
}

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


OUT_VS_BM GgafDxVS_BumpMapping(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0,
      float3 prm_tangent  : TEXCOORD1,
      float3 prm_binormal : TEXCOORD2  
) {
 	OUT_VS_BM out_vs = (OUT_VS_BM)0;

	//頂点計算
    float4 posWorld = mul(prm_pos, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv;  //そのまま

	// 接空間行列の逆行列を算出
	float4x4 invTangentMat = InvTangentMatrix(prm_tangent, prm_binormal, prm_normal );
	// ライトベクトルを接空間に移す
	out_vs.lightTangentDirect = mul( -g_vecLightDirection, invTangentMat );

        //「頂点→カメラ視点」方向ベクトル（スペキュラで使用）                                                        
    float3 cam = normalize(g_posCam.xyz - posWorld.xyz);
    out_vs.camTangentDirect  =  mul(cam, invTangentMat );

    if (g_specular_power != 0) {

        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(cam + (-g_vecLightDirection));
        //ハーフベクトルを接空間に移す
        out_vs.harfTangentDirect =  mul(vecHarf, invTangentMat );
    }






//    //頂点カラー計算
//    //法線を World 変換して正規化
//    out_vs.normal = normalize(mul(prm_normal, g_matWorld));     
//    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
//    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
//    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
//    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
//    //「頂点→カメラ視点」方向ベクトル                                                        
//    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);

    out_vs.color = g_colMaterialDiffuse;
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.pos.z > 0.6*g_zf) {   // 最遠の約 2/3 よりさらに奥の場合徐々に透明に
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //本来視野外のZでも、描画を強制するため0.9以内に上書き、
//    }
	return out_vs;
}


float4 GgafDxPS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 inCamTangentDirect    : TEXCOORD2,   //接空間座標系に変換された頂点 -> 視点 ベクトル
    float3 inLightTangentDirect : TEXCOORD3,  //接空間座標系に変換された拡散光方向ベクトル
    float3 inHarfTangentDirect : TEXCOORD4     //接空間座標系に変換されたハーフベクトル
) : COLOR  {
    float a = prm_color.a; //α保持

	float3 normalVec = 2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz-1.0; //法線マップからの法線
	normalVec = normalize( normalVec );//法線正規化
    //法線(法線マップの法線、つまり接空間座標系の法線になる）と、
    //拡散光方向ベクトル(頂点シェーダーで接空間座標系に予め変換済み) の内積から
    //ライト入射角を求め、面に対する拡散光の減衰率(power)を求める
    float power = max(dot(normalVec, normalize(inLightTangentDirect) ), 0); 

	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-inCamTangentDirect, normalVec));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);


    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトルで
        //接空間座標系に予め変換済み）と法線(法線マップの法線、つまり接空間座標系の法線)の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(normalVec, inHarfTangentDirect)), g_specular ) * g_specular_power;
    }



//    float s = 0.0f; //スペキュラ成分
//    if (g_specular_power != 0) {
//        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
//        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
//        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
//        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
//    }
    float4 out_color = colTex2D * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * prm_color ) + (colTexCube*g_reflectance) +s; //prm_color == g_colMaterialDiffuse

    //float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinkerを考慮
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master; 
	return out_color;
}







float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_color    : COLOR0
) : COLOR  {                         
	//テクスチャをサンプリングして色取得（原色を取得）
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
	return out_color;
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

