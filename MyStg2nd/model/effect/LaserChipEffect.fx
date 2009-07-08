////////////////////////////////////////////////////////////////////////////////
// レーザーチップ用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

//int g_kind; //チップ種類 1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先）

//float g_X; //一つ前を行くチップX
//float g_Y; //一つ前を行くチップY
//float g_Z; //一つ前を行くチップZ

//bool g_RevPosZ; //Z座標を反転するかどうか

int g_nVertexs;

//float4x4 g_matWorld;  //自身のWorld変換行列
//float4x4 g_matWorld_front;  //一つ前を行くチップのWorld変換行列
bool g_RevPosZ001;
bool g_RevPosZ002;
bool g_RevPosZ003;
bool g_RevPosZ004;
bool g_RevPosZ005;
bool g_RevPosZ006;
bool g_RevPosZ007;
bool g_RevPosZ008;
//bool g_RevPosZ009;
//bool g_RevPosZ010;
//bool g_RevPosZ011;
//bool g_RevPosZ012;
//bool g_RevPosZ013;
//bool g_RevPosZ014;
//bool g_RevPosZ015;
//bool g_RevPosZ016;
int g_kind001;
int g_kind002;
int g_kind003;
int g_kind004;
int g_kind005;
int g_kind006;
int g_kind007;
int g_kind008;
//int g_kind009;
//int g_kind010;
//int g_kind011;
//int g_kind012;
//int g_kind013;
//int g_kind014;
//int g_kind015;
//int g_kind016;
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
//float4x4 g_matWorld009;
//float4x4 g_matWorld010;
//float4x4 g_matWorld011;
//float4x4 g_matWorld012;
//float4x4 g_matWorld013;
//float4x4 g_matWorld014;
//float4x4 g_matWorld015;
//float4x4 g_matWorld016;
float4x4 g_matWorld_front001;
float4x4 g_matWorld_front002;
float4x4 g_matWorld_front003;
float4x4 g_matWorld_front004;
float4x4 g_matWorld_front005;
float4x4 g_matWorld_front006;
float4x4 g_matWorld_front007;
float4x4 g_matWorld_front008;
//float4x4 g_matWorld_front009;
//float4x4 g_matWorld_front010;
//float4x4 g_matWorld_front011;
//float4x4 g_matWorld_front012;
//float4x4 g_matWorld_front013;
//float4x4 g_matWorld_front014;
//float4x4 g_matWorld_front015;
//float4x4 g_matWorld_front016;

float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色

//soレジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//レーザーチップ頂点シェーダー
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,    // モデルの頂点番号
      float3 prm_normal : NORMAL,        // 法線ではなくてなんと、x要素に頂点番号！
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV
) {

	OUT_VS out_vs = (OUT_VS)0;

	int g_cnt_vertec = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	float4x4 matWorld_front;
	int kind;
	bool revPosZ;



	if (64 > g_cnt_vertec) {
		if (32 > g_cnt_vertec) {
			if (16 > g_cnt_vertec) {
				matWorld = g_matWorld001;
				matWorld_front = g_matWorld_front001;
				kind = g_kind001;
				revPosZ = g_RevPosZ001;
			} else {
				matWorld = g_matWorld002;
				matWorld_front = g_matWorld_front002;
				kind = g_kind002;
				revPosZ = g_RevPosZ002;
			}
		} else {
			if (48 > g_cnt_vertec) {
				matWorld = g_matWorld003;
				matWorld_front = g_matWorld_front003;
				kind = g_kind003;
				revPosZ = g_RevPosZ003;
			} else {
				matWorld = g_matWorld004;
				matWorld_front = g_matWorld_front004;
				kind = g_kind004;
				revPosZ = g_RevPosZ004;
			}
		}
	} else {
		if (96 > g_cnt_vertec) {
			if (80 > g_cnt_vertec) {
				matWorld = g_matWorld005;
				matWorld_front = g_matWorld_front005;
				kind = g_kind005;
				revPosZ = g_RevPosZ005;
			} else {
				matWorld = g_matWorld006;
				matWorld_front = g_matWorld_front006;
				kind = g_kind006;
				revPosZ = g_RevPosZ006;
			}
		} else {
			if (112 > g_cnt_vertec) {
				matWorld = g_matWorld007;
				matWorld_front = g_matWorld_front007;
				kind = g_kind007;
				revPosZ = g_RevPosZ007;
			} else {
				matWorld = g_matWorld008;
				matWorld_front = g_matWorld_front008;
				kind = g_kind008;
				revPosZ = g_RevPosZ008;
			}
		}
	}



	//float4 posWorld = mul( prm_pos, matWorld );               // World変換







//
	if (revPosZ == true) {
		prm_pos.z = -prm_pos.z;
	}
//
//	if (g_Y - g_matWorld._42 < 0) {
//		prm_pos.y = -prm_pos.y;
//	}
//
	//ほぼ真横なら羽はいらない TODO
//	if (abs(g_Z - matWorld._43) < 1.5) {
//		if (abs(g_Y - matWorld._42) < 1.0) {
//			prm_pos.z = 0;
//		}
//	}

	float4 posWorld;
	if (prm_pos.x > 0) {
//		float4x4 matWorld_tmp = g_matWorld_front; 
//		matWorld_tmp._41 = matWorld_front._41;  // 一つ前方のチップ座標へくっつける
//		matWorld_tmp._42 = matWorld_front._42; 
//		matWorld_tmp._43 = matWorld_front._43; 
		posWorld = mul( prm_pos, matWorld_front );      // World変換
	} else {
		//頂点計算
		posWorld = mul( prm_pos, matWorld );        // World変換
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View変換
	out_vs.pos          = mul(posWorldView, g_matProj);  // 射影変換

	//UV
	if (kind == 2) {
		out_vs.uv = prm_uv;
	} else if (kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		//何も描画したくない
		out_vs.uv.x = 0.1;
		out_vs.uv.y = 0.1;
	}
	//g_cnt_vertec++;
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {

	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   //加算合成
		DestBlend = One;
		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}



