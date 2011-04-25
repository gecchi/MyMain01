////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MorphMeshModel用シェーダー
// author : Masatoshi Tsuge
// date:2009/05/12 
////////////////////////////////////////////////////////////////////////////////
/** カメラのWorld位置 */
float3 pos_camera;

//エラーが出るのでとりあえず宣言 
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
//struct OUT_VS
//{
//    float4 pos    : POSITION;
//	float2 uv     : TEXCOORD0;
//	float3 normal : TEXCOORD1;   // ワールド変換した法線
//};

struct OUT_VS {                   
    float4 pos   : POSITION;      
    float3 normal: TEXCOORD0;    	// ワールド空間の法線
    float3 viewVecW: TEXCOORD1;  	// ワールド空間での視線ベクトル
};  

///////////////////////////////////////////////////////////////////////////

//モーフターゲットなし
OUT_VS GgafDx9VS_CubeMapMorphMesh0(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0       // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	out_vs.pos = mul(prm_pos0, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(prm_normal0, g_matWorld)); 

//	//頂点計算
//	out_vs.pos = mul( mul(mul( prm_pos0, g_matWorld ), g_matView ), g_matProj);//
//    //法線計算
//    out_vs.normal = normalize(mul(prm_normal0, g_matWorld)); 	//法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;
	return out_vs;
}

//モーフターゲット１つ
OUT_VS GgafDx9VS_CubeMapMorphMesh1(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1         // モデルのモーフターゲット1頂点の法線

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点＆法線ブレンド
	float4 pos = prm_pos0;
	float3 normal = prm_normal0;
	if (g_weight1 != 0 ) {
		pos += ((prm_pos1 - prm_pos0) * g_weight1);
		normal = lerp(normal, prm_normal1, g_weight1);
	}

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 

//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}


//モーフターゲット２つ
OUT_VS GgafDx9VS_CubeMapMorphMesh2(
      float4 prm_pos0    : POSITION0,      // モデルの頂点
      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
      float3 prm_normal2 : NORMAL2         // モデルのモーフターゲット2頂点の法線
) {
	OUT_VS out_vs = (OUT_VS)0;

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

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 


//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット３つ
OUT_VS GgafDx9VS_CubeMapMorphMesh3(
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
	OUT_VS out_vs = (OUT_VS)0;

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

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 

//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット４つ
OUT_VS GgafDx9VS_CubeMapMorphMesh4(
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
	OUT_VS out_vs = (OUT_VS)0;

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

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 

//
//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット５つ
OUT_VS GgafDx9VS_CubeMapMorphMesh5(
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
	OUT_VS out_vs = (OUT_VS)0;

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

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 



//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}

//モーフターゲット６つ
OUT_VS GgafDx9VS_CubeMapMorphMesh6(
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
	OUT_VS out_vs = (OUT_VS)0;

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

	//頂点計算
	out_vs.pos = mul(pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*射影変換
    out_vs.normal = normalize(mul(normal, g_matWorld)); 


//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;

	return out_vs;
}

////モーフターゲット７つ
//OUT_VS GgafDx9VS_CubeMapMorphMesh7(
//      float4 prm_pos0    : POSITION0,      // モデルの頂点
//      float3 prm_normal0 : NORMAL0,        // モデルの頂点の法線
//      float2 prm_uv0     : TEXCOORD0,      // モデルの頂点のUV
//      float4 prm_pos1    : POSITION1,      // モデルのモーフターゲット1頂点
//      float3 prm_normal1 : NORMAL1,        // モデルのモーフターゲット1頂点の法線
//      float4 prm_pos2    : POSITION2,      // モデルのモーフターゲット2頂点
//      float3 prm_normal2 : NORMAL2,        // モデルのモーフターゲット2頂点の法線
//      float4 prm_pos3    : POSITION3,      // モデルのモーフターゲット3頂点
//      float3 prm_normal3 : NORMAL3,        // モデルのモーフターゲット3頂点の法線
//      float4 prm_pos4    : POSITION4,      // モデルのモーフターゲット4頂点
//      float3 prm_normal4 : NORMAL4,        // モデルのモーフターゲット4頂点の法線
//      float4 prm_pos5    : POSITION5,      // モデルのモーフターゲット5頂点
//      float3 prm_normal5 : NORMAL5,        // モデルのモーフターゲット5頂点の法線
//      float4 prm_pos6    : POSITION6,      // モデルのモーフターゲット6頂点
//      float3 prm_normal6 : NORMAL6,        // モデルのモーフターゲット6頂点の法線
//      float4 prm_pos7    : POSITION7,      // モデルのモーフターゲット7頂点
//      float3 prm_normal7 : NORMAL7         // モデルのモーフターゲット7頂点の法線
//) {
//	OUT_VS out_vs = (OUT_VS)0;
//
//	//頂点＆法線ブレンド
//	float4 pos = prm_pos0;
//	float3 normal = prm_normal0;
//	if (g_weight1 != 0 ) {
//		pos += ((prm_pos1 - prm_pos0) * g_weight1);
//		normal = lerp(normal, prm_normal1, g_weight1);
//	}
//	if (g_weight2 != 0 ) {
//		pos += ((prm_pos2 - prm_pos0) * g_weight2);
//		normal = lerp(normal, prm_normal2, g_weight2);
//	}
//	if (g_weight3 != 0 ) {
//		pos += ((prm_pos3 - prm_pos0) * g_weight3);
//		normal = lerp(normal, prm_normal3, g_weight3);
//	}
//	if (g_weight4 != 0 ) {
//		pos += ((prm_pos4 - prm_pos0) * g_weight4);
//		normal = lerp(normal, prm_normal4, g_weight4);
//	}
//	if (g_weight5 != 0 ) {
//		pos += ((prm_pos5 - prm_pos0) * g_weight5);
//		normal = lerp(normal, prm_normal5, g_weight5);
//	}
//	if (g_weight6 != 0 ) {
//		pos += ((prm_pos6 - prm_pos0) * g_weight6);
//		normal = lerp(normal, prm_normal6, g_weight6);
//	}
//	if (g_weight7 != 0 ) {
//		pos += ((prm_pos7 - prm_pos0) * g_weight7);
//		normal = lerp(normal, prm_normal7, g_weight7);
//	}
//	//頂点出力設定
//	out_vs.pos = mul(mul(mul( pos, g_matWorld ), g_matView ), g_matProj); //World*View*射影変換
//	//法線出力設定
//	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //法線を World 変換して正規化
//	//UVはそのまま
//	out_vs.uv = prm_uv0;
//
//	return out_vs;
//}

float4 GgafDx9PS_CubeMapMorphMesh(
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1
) : COLOR  {
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(prm_normal, -g_vecLightDirection ), 0);          

 	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);

	//ライト方向、ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	float4 out_color = g_colLightDiffuse * g_colMaterialDiffuse * tex_color * power; 
	//Ambient色を加算。マテリアルのAmbien反射色は、マテリアルのDiffuse反射色と同じ色とする。
	out_color =  (g_colLightAmbient * g_colMaterialDiffuse * tex_color) + out_color;  
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power;
	} 
	//α計算、αは法線およびライト方向に依存しない事とするので別計算。固定はライトα色も考慮するが、本シェーダーはライトαは無し。
	out_color.a = g_colMaterialDiffuse.a * tex_color.a * g_alpha_master; 

	return out_color * float4(2.0, 2.0, 2.0, 1.0); //全体的に明るくする;
}

float4 PS_DestBlendOne( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1
) : COLOR  {
 	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	tex_color.a = tex_color.a * g_alpha_master; 
	return 	tex_color;
}

float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1
) : COLOR  {
 	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect) * float4(7.0, 7.0, 7.0, 1.0);
	tex_color.a = tex_color.a * g_alpha_master; 
	return 	tex_color;
}

technique CubeMapMorphMeshTechnique
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
	// float g_weight1～9       :   重み1～9(必要なターゲット分だけ)
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
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh0();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh1();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh2();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh3();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh4();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh5();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh6();
		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
	}

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = InvSrcAlpha;
//		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile ps_2_0 GgafDx9PS_CubeMapMorphMesh();
//	}
}


technique DestBlendOne
{
	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh0();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh1();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh2();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh3();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh4();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh5();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh6();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //加算合成
//		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile ps_2_0 PS_DestBlendOne();
//	}

}

technique Flush
{
	//モーフターゲット無し
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh0();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット１つ
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh1();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット２つ
	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh2();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット３つ
	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh3();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット４つ
	pass P4 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh4();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット５つ
	pass P5 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh5();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

	//モーフターゲット６つ
	pass P6 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh6();
		PixelShader  = compile ps_2_0 PS_Flush();
	}

//	//モーフターゲット７つ
//	pass P7 {
//		AlphaBlendEnable = true;
//		SrcBlend  = SrcAlpha;
//		DestBlend = One; //加算合成
//		VertexShader = compile vs_2_0 GgafDx9VS_CubeMapMorphMesh7();
//		PixelShader  = compile ps_2_0 PS_Flush();
//	}

}