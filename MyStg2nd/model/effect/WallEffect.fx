////////////////////////////////////////////////////////////////////////////////
// WallActor用シェーダー
// 【概要】
// 外壁ブロックの描画を行う。
// 頂点バッファに、外壁ブロック情報が、２０個分繰り返し詰め込んである。
// ステートやレジスタの更新を行わず、１回の 描画で、最大
// 20オブジェクトまで描画。高速化を狙う。
// author : Masatoshi Tsuge
// date:2010/10/20
////////////////////////////////////////////////////////////////////////////////


float g_distance_AlphaTarget;
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
float4x4 g_matWorld018;
float4x4 g_matWorld019;
float4x4 g_matWorld020;

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
OUT_VS GgafDx9VS_Wall(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_object_index  : PSIZE , // モデルのインデックス（何個目のオブジェクトか）
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//ワールド変換行列を割り当てる
	float4x4 matWorld;
	if (prm_object_index == 0) {
		matWorld = g_matWorld001;
	} else if (prm_object_index == 1) {
		matWorld = g_matWorld002;
	} else if (prm_object_index == 2) {
		matWorld = g_matWorld003;
	} else if (prm_object_index == 3) {
		matWorld = g_matWorld004;
	} else if (prm_object_index == 4) {
		matWorld = g_matWorld005;
	} else if (prm_object_index == 5) {
		matWorld = g_matWorld006;
	} else if (prm_object_index == 6) {
		matWorld = g_matWorld007;
	} else if (prm_object_index == 7) {
		matWorld = g_matWorld008;
	} else if (prm_object_index == 8) {
		matWorld = g_matWorld009;
	} else if (prm_object_index == 9) {
		matWorld = g_matWorld010;
	} else if (prm_object_index == 10) {
		matWorld = g_matWorld011;
	} else if (prm_object_index == 11) {
		matWorld = g_matWorld012;
	} else if (prm_object_index == 12) {
		matWorld = g_matWorld013;
	} else if (prm_object_index == 13) {
		matWorld = g_matWorld014;
	} else if (prm_object_index == 14) {
		matWorld = g_matWorld015;
	} else if (prm_object_index == 15) {
		matWorld = g_matWorld016;
	} else if (prm_object_index == 16) {
		matWorld = g_matWorld017;
	} else if (prm_object_index == 17) {
		matWorld = g_matWorld018;
	} else if (prm_object_index == 18) {
		matWorld = g_matWorld019;
	} else {
		matWorld = g_matWorld020;
	} 
    //描画面番号情報が、ワールド変換行列のmatWorld._14 に埋め込まれている
	int draw_face = matWorld._14;
    matWorld._14 = 0; //元の行列値に戻しておく

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
            out_vs.col.a = 0;
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
            out_vs.col.a = 0;
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
            out_vs.col.a = 0;
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
            out_vs.col.a = 0;
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
            out_vs.col.a = 0;
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
            out_vs.col.a = 0;
            return out_vs;
        }
    }

	//World*View*射影変換
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);

	//UVはそのまま
	out_vs.uv = prm_uv;

    //頂点カラー計算

	//法線を World 変換して正規化
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    normal.x+=0.5; //値0.5は壁面にも無理やり光を当てるため
                   //ライトベクトルは XYZ=0.819232,-0.573462,0
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(normal, float3(-0.819232,0.573462,0)), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向 を考慮したカラー作成。      
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power));// * マテリアル色無しcolMaterialDiffuse;
	//αフォグ
	//out_vs.col.a = colMaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
    //自機より手前はα
	if ( out_vs.pos.z < g_distance_AlphaTarget) {
		out_vs.col.a = (out_vs.pos.z + 1.0)  / (g_distance_AlphaTarget*2);
	}
	//マスターα
	out_vs.col.a *= g_alpha_master;
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_Wall(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {
    if (prm_col.a == 0) {
        return 0;
    }
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

technique WallTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_Wall();
		PixelShader  = compile ps_2_0 GgafDx9PS_Wall();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_Wall();
		PixelShader  = compile ps_2_0 GgafDx9PS_Wall();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_Wall();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}
