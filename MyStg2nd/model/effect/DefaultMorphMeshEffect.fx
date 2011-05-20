#include "GgafEffectConst.fx" 
////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MorphMeshModel用シェーダー
// author : Masatoshi Tsuge
// date:2009/05/12 
////////////////////////////////////////////////////////////////////////////////


/** スペキュラーの範囲（ハーフベクトル・法線内積のg_specular乗） */
float g_specular;
/** スペキュラーの強度 */
float g_specular_power;
/** カメラ（視点）の位置ベクトル */
float3 g_posCam;


float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列
int g_morph_target_num;  //メッシュパターン数(モーフターゲット数）、現在未使用
float g_weight1; //モーフターゲット１の重み
float g_weight2; //モーフターゲット２の重み
float g_weight3; //モーフターゲット３の重み
float g_weight4; //モーフターゲット４の重み
float g_weight5; //モーフターゲット５の重み
float g_weight6; //モーフターゲット６の重み
//float g_weight7; //モーフターゲット７の重み

float3 g_vecLightDirection; // ライトの方向
float4 g_colLightAmbient;   // Ambienライト色（入射色）
float4 g_colLightDiffuse;   // Diffuseライト色（入射色）

float4 g_colMaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
float g_zf;

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
	float3 normal : TEXCOORD1;   // ワールド変換した法線
    float3 cam    : TEXCOORD2;   //頂点 -> 視点 ベクトル

};


///////////////////////////////////////////////////////////////////////////

//モーフターゲットなし
OUT_VS GgafDx9VS_DefaultMorphMesh0(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0       // モデルの頂点のUV

) {
    OUT_VS out_vs = (OUT_VS)0;
    //頂点計算
    float4 posWorld = mul(prm_pos0, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*射影
    //UV計算
    out_vs.uv = prm_uv0;  //そのまま

    //頂点カラー計算
    //法線を World 変換して正規化
    out_vs.normal = normalize(mul(prm_normal0, g_matWorld));     
    //法線と、拡散光方向の内積からライト入射角を求め、面に対する拡散光の減衰率を求める。
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //拡散光色に減衰率を乗じ、環境光色を加算し、全体をマテリアル色を掛ける。
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //「頂点→カメラ視点」方向ベクトル                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //αはマテリアルαを最優先とする（上書きする）
    out_vs.color.a = g_colMaterialDiffuse.a;
    //αフォグ
    if (out_vs.pos.z > (g_zf*0.9)*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
        out_vs.color.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
    } 
    //マスターα
    out_vs.color.a *= g_alpha_master;
	return out_vs;
}

//モーフターゲット１つ
OUT_VS GgafDx9VS_DefaultMorphMesh1(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1         // モデルのモーフターゲット1頂点の法線

) {
//	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}

    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}


//モーフターゲット２つ
OUT_VS GgafDx9VS_DefaultMorphMesh2(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2         // モデルのモーフターゲット2頂点の法線
) {
//	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}

//モーフターゲット３つ
OUT_VS GgafDx9VS_DefaultMorphMesh3(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3         // モデルのモーフターゲット3頂点の法線
) {
	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}

    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}

//モーフターゲット４つ
OUT_VS GgafDx9VS_DefaultMorphMesh4(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_pos4    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_normal4 : NORMAL4         // モデルのモーフターゲット4頂点の法線
) {
	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}
	if (g_weight4 != 0 ) {
		pos += ((prm_pos4 - prm_pos0) * g_weight4);
		normal = lerp(normal, prm_normal4, g_weight4);
	}
    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}

//モーフターゲット５つ
OUT_VS GgafDx9VS_DefaultMorphMesh5(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_pos4    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_normal4 : NORMAL4,        // モデルのモーフターゲット4頂点の法線
      float4 prm_pos5    : POSITION5,      // モデルのモーフターゲット5頂点
      float3 prm_normal5 : NORMAL5         // モデルのモーフターゲット5頂点の法線
) {
	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}
	if (g_weight4 != 0 ) {
		pos += ((prm_pos4 - prm_pos0) * g_weight4);
		normal = lerp(normal, prm_normal4, g_weight4);
	}
	if (g_weight5 != 0 ) {
		pos += ((prm_pos5 - prm_pos0) * g_weight5);
		normal = lerp(normal, prm_normal5, g_weight5);
	}
    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}

//モーフターゲット６つ
OUT_VS GgafDx9VS_DefaultMorphMesh6(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
      float3 prm_normal3 : NORMAL3,        // モデルのモーフターゲット3頂点の法線
      float4 prm_pos4    : POSITION4,      // モデルのモーフターゲット4頂点
      float3 prm_normal4 : NORMAL4,        // モデルのモーフターゲット4頂点の法線
      float4 prm_pos5    : POSITION5,      // モデルのモーフターゲット5頂点
      float3 prm_normal5 : NORMAL5,        // モデルのモーフターゲット5頂点の法線
      float4 prm_pos6    : POSITION6,      // モデルのモーフターゲット6頂点
      float3 prm_normal6 : NORMAL6         // モデルのモーフターゲット6頂点の法線

) {
	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}
	if (g_weight2 != 0 ) {
		pos += ((prm_pos2 - prm_pos0) * g_weight2);
		normal = lerp(normal, prm_normal2, g_weight2);
	}
	if (g_weight3 != 0 ) {
		pos += ((prm_pos3 - prm_pos0) * g_weight3);
		normal = lerp(normal, prm_normal3, g_weight3);
	}
	if (g_weight4 != 0 ) {
		pos += ((prm_pos4 - prm_pos0) * g_weight4);
		normal = lerp(normal, prm_normal4, g_weight4);
	}
	if (g_weight5 != 0 ) {
		pos += ((prm_pos5 - prm_pos0) * g_weight5);
		normal = lerp(normal, prm_normal5, g_weight5);
	}
	if (g_weight6 != 0 ) {
		pos += ((prm_pos6 - prm_pos0) * g_weight6);
		normal = lerp(normal, prm_normal6, g_weight6);
	}
    return GgafDx9VS_DefaultMorphMesh0(pos, normal, prm_uv0);
}


float4 GgafDx9PS_DefaultMorphMesh(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //頂点 -> 視点 ベクトル
) : COLOR  {
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //スペキュラ成分
    if (g_specular_power != 0) {
        //ハーフベクトル（「頂点→カメラ視点」方向ベクトル と、「頂点→ライト」方向ベクトルの真ん中の方向ベクトル）
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //ハーフベクトルと法線の内積よりスペキュラ具合を計算
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + s;
    //Blinkerを考慮
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 
    out_color.a = prm_color.a; 
	return out_color;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color  : COLOR0
) : COLOR  {
    float4 colTex2D  = tex2D( MyTextureSampler, prm_uv);
    float4 out_color = colTex2D * prm_color * float4(7.0, 7.0, 7.0, 1.0);
	return 	out_color;
}

technique DefaultMorphMeshTechnique
{
	//「メッシュ標準シェーダー」
	//メッシュを描画する
	//【考慮される要素】
	//--- VS ---
	//・頂点を World、View、射影 変換
	//・法線を World変換
	//--- PS ---
	//・Diffuseライト色(α色は無視)
	//・Ambientライト色(α色は無視)
	//・平行光ライト方向
	//・環境光ライト
	//・オブジェクトのマテリアルのDiffuse反射（Ambient反射と共通）
	//・オブジェクトのテクスチャ
	//・オブジェクトのマテリアル半透明α（Diffuse反射αとテクスチャαの乗算）
	//【使用条件】
	//・テクスチャが存在しs0レジスタにバインドされていること。
	//【設定パラメータ】
	// float g_weight1〜9       :   重み1〜9(必要なターゲット分だけ)
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列   
	// float3 g_vecLightDirection	:	ライトの方向
	// float4 g_colLightAmbient	:	Ambienライト色（入射色）
	// float4 g_colLightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_colMaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				:	2Dテクスチャ

	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh4();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh5();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh6();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}
}


technique DestBlendOne
{
	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh4();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh5();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh6();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMorphMesh();
	}

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //加算合成
//		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_DestBlendOne();
//	}

}

technique Flush
{
	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh4();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh5();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh6();
		PixelShader  = compile PS_VERSION PS_Flush();
	}

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //加算合成
//		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMorphMesh7();
//		PixelShader  = compile PS_VERSION PS_Flush();
//	}

}