////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshSetModel用シェーダー
// 【概要】
// 頂点バッファに、同じモデルキャラの頂点情報が、複数個分繰り返し詰め込んである。
// ステートやレジスタの更新を行わず、１回の 描画で、最大
// 16オブジェクトまで描画。高速化を狙う。
// 大量の同じ敵や弾には、このシェーダーで描画することとする。
// 但し、１オブジェクトにつきマテリアル設定は１つだけという制限がある。
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


int g_vertexs_num;
float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ライトの方向
float3 g_vecLightDirection;
// Ambienライト色（入射色）
float4 g_colLightAmbient;
// Diffuseライト色（入射色）  
float4 g_colLightDiffuse;  
//View変換行列
float4x4 g_matView; 
//射影変換行列  
float4x4 g_matProj;  

float g_box_dep;
float g_box_width;
float g_box_height;

int g_draw_face001;
int g_draw_face002;
int g_draw_face003;
int g_draw_face004;
int g_draw_face005;
int g_draw_face006;
int g_draw_face007;
int g_draw_face008;
int g_draw_face009;
int g_draw_face010;
int g_draw_face011;
int g_draw_face012;
int g_draw_face013;
int g_draw_face014;
int g_draw_face015;
int g_draw_face016;

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
//オブジェクトのマテリアル色（Diffuse反射色と、Ambien反射色共通）
//float4 g_colMaterialDiffuse001;
//float4 g_colMaterialDiffuse002;
//float4 g_colMaterialDiffuse003;
//float4 g_colMaterialDiffuse004;
//float4 g_colMaterialDiffuse005;
//float4 g_colMaterialDiffuse006;
//float4 g_colMaterialDiffuse007;
//float4 g_colMaterialDiffuse008;
//float4 g_colMaterialDiffuse009;
//float4 g_colMaterialDiffuse010;
//float4 g_colMaterialDiffuse011;
//float4 g_colMaterialDiffuse012;
//float4 g_colMaterialDiffuse013;
//float4 g_colMaterialDiffuse014;
//float4 g_colMaterialDiffuse015;
//float4 g_colMaterialDiffuse016;

//テクスチャのサンプラ(s0レジスタ)
sampler MyTextureSampler : register(s0);

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//頂点シェーダー
OUT_VS GgafDx9VS_GroundBox(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_index  : PSIZE ,        // モデルのインデックス（何個目のオブジェクトか？）
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//頂点計算
	float4x4 matWorld;
	int draw_face;

	if (index == 0) {
		matWorld = g_matWorld001;
		draw_face = g_colMaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		draw_face = g_colMaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		draw_face = g_colMaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		draw_face = g_colMaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		draw_face = g_colMaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		draw_face = g_colMaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		draw_face = g_colMaterialDiffuse007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		draw_face = g_colMaterialDiffuse008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		draw_face = g_colMaterialDiffuse009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		draw_face = g_colMaterialDiffuse010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		draw_face = g_colMaterialDiffuse011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		draw_face = g_colMaterialDiffuse012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		draw_face = g_colMaterialDiffuse013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		draw_face = g_colMaterialDiffuse014;
	} else { //if (index == 14) {
		matWorld = g_matWorld015;
		draw_face = g_colMaterialDiffuse015;
	}
//	} else {
//		matWorld = g_matWorld016;
//		draw_face = g_colMaterialDiffuse016;
//	}
//float g_box_dep;
//float g_box_width;
//float g_box_height;

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
          
    //                              00abcdef
  	if (draw_face & 32 == 0) {  //&b00100000
        //上面(面a)が描画不要の場合
        if (prm_pos.y > g_box_height/2) {
            prm_pos = 0;
            prm_uv = 0;
        }
    }
    //                              00abcdef
  	if (draw_face & 16 == 0) {  //&b00010000
        //正面(面b)が描画不要の場合
        if (prm_pos.x < -g_box_dep/2) {
            prm_pos = 0;
            prm_uv = 0;
        }
    }
    //                              00abcdef
  	if (draw_face & 8 == 0) {   //&b00001000
        //左側面(面c)が描画不要の場合
        if (prm_pos.z > g_box_width/2) {
            prm_pos = 0;
            prm_uv = 0;
        }
    }
    //                              00abcdef
   	if (draw_face & 4 == 0) {   //&b00000100
        //底面(面d)が描画不要の場合
        if (prm_pos.y < -g_box_height/2) {
            prm_pos = 0;
            prm_uv = 0;
        }
    }
    //                              00abcdef
  	if (draw_face & 2 == 0) {   //&b00000010
        //右側面(面e)が描画不要の場合
        if (prm_pos.z < -g_box_width/2) {
            prm_pos = 0;
            prm_uv = 0;
        }   
    }
    //                              00abcdef
  	if (draw_face & 1 == 0) {   //&b00000001
        //向こう正面(面f)が描画不要の場合
        if (prm_pos.x > g_box_dep/2) {
            prm_pos = 0;
            prm_uv = 0;
        }
    }

//    float4 colMaterialDiffuse = float4(1.0, 1.0, 1.0, 1.0);

	//World*View*射影変換
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);
	//UVはそのまま
	out_vs.uv = prm_uv;

    //頂点カラー計算

	//法線を World 変換して正規化
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(normal, -g_vecLightDirection ), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。      
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power));// * colMaterialDiffuse;
	//αフォグ
	//out_vs.col.a = colMaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//マスターα
	out_vs.col.a *= g_alpha_master;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_GroundBox(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinkerを考慮
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
	return out_color;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);
	return out_color;
}

technique GroundBoxTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundBox();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundBox();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_GroundBox();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}
