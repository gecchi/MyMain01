////////////////////////////////////////////////////////////////////////////////
// レーザーチップ用シェーダー
//
// Auther:Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

float g_X; //一つ前を行くチップX
float g_Y; //一つ前を行くチップY
float g_Z; //一つ前を行くチップZ

float4x4 g_matWorld;  //自身のWorld変換行列
float4x4 g_matWorld_front;  //一つ前を行くチップのWorld変換行列
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
      float2 prm_uv     : TEXCOORD0     // モデルの頂点のUV

) {
	OUT_VS out_vs = (OUT_VS)0;

	//αブレンドの影が出ないように（手前から描画されないように）、
	//傾きによって頂点のy,zを反転
	//
	//【頂点バッファ（デフォルト）の描画順】
	//
	//         ↑ｙ軸
	//         │
	//
	//          ＼
	//         │ ＼   
	//         │�C ＼ 
	//  (0,0,0)│    ┃        ｚ軸
	// ────┘----┃─   ─→
	//  ＼ �A  ：＼  ┃   ＼  
	//    ＼   ：  ＼┃  �B ＼ 
	//       ━━━━╋━━━━
	//         │    ┃
	//          ＼ �@┃  ＼   
	//            ＼ ┃    ＼ ｘ軸（方向）
	//               ┃      ┘
	//
	if (abs(g_Y - g_matWorld._42) < 1) {
		prm_pos.z = 0;
    } else {
		if (g_Z < g_matWorld._43) {      //奥から手前   
			if (g_Y > g_matWorld._42) {      //下から上
				if (g_X > g_matWorld._41) {      //左から右
					//奥から手前で、下から上で、左から右
					//
					//                                ─┐
					//                           方向 ／│ 
					//                              ／  
					//                    ┃
					//                 ／ ┃
					//               ／ �@┃
					//              │    ┃
					//            ━━━━╋━━━━
					//         ／   ：  ／┃  �A ／
					//       ／ �B  ：／  ┃   ／
					//      ────┐----┃─
					//              │    ┃
					//              │�C ／
					//    y         │ ／
					//   ↑          ／
					// ─┼→x
					//   │
					prm_pos.y = -prm_pos.y;
					prm_pos.z = -prm_pos.z;

				} else {
					//奥から手前で、下から上で、右から左
					//
					// ┌─     
					// │＼ 方向
					//     ＼   
					//               ┃
					//               ┃ ＼
					//               ┃�@ ＼
					//               ┃    │
					//       ━━━━╋━━━━
					//        ＼ �A  ┃＼  ：   ＼
					//          ＼   ┃  ＼：  �B ＼
					//             ─┃----┌────
					//               ┃    │
					//                ＼ �C│
					//    y             ＼ │
					//   ↑               ＼
					// ─┼→x
					//   │
					prm_pos.y = -prm_pos.y;

				}
			} else {                          //上から下
				if (g_X > g_matWorld._41) {
					//奥から手前で、上から下で、左から右
					//
					//          ＼
					//         │ ＼   
					//         │�C ＼ 
					//         │    ┃   
					// ────┘----┃─
					//  ＼ �B  ：＼  ┃   ＼  
					//    ＼   ：  ＼┃  �A ＼ 
					//       ━━━━╋━━━━
					//         │    ┃
					//          ＼ �@┃
					//    y       ＼ ┃     ＼ 方向  
					//   ↑          ┃       ＼│
					// ─┼→x                ─┘
					//   │
					prm_pos.z = -prm_pos.z;

				} else {
					//奥から手前で、上から下で、右から左
					//
					//                      ／
					//                    ／ │
					//                  ／ �C│
					//                 ┃    │
					//               ─┃----└────
					//            ／   ┃  ／：  �B ／
					//          ／ �A  ┃／  ：   ／
					//         ━━━━╋━━━━
					//                 ┃    │
					//            ／   ┃�@ ／
					//     方向 ／     ┃ ／
					//      │／       ┃
					//    y └─
					//   ↑ 
					// ─┼→x
					//   │ 
	                //そのままで描画順変更不用

				}
			}
		} else {                        //手前から奥 
			if (g_Y > g_matWorld._42) {      //下から上
				if (g_X > g_matWorld._41) {      //左から右
					//手前から奥で、下から上で、左から右
					//
					//                                ─┐
					//                           方向 ／│
					//                              ／  
					//                  ／        ／
					//       ｙ       ／ │ 
					//       ∧     ／ �C│
					//       ┃    ┃    │
					//       ┃  ─┃----└────
					//       ┃    ┃  ／：  �B ／
					//     ／┃�A  ┃／  ：   ／
					//     ━┃━━╋━━━━
					//       ┃    ┃    │
					//       ┃    ┃�@ ／
					// ━━━╋━━━━━━━＞ｘ
					//       ┃    ┃ 
					//       ┃    
					//       ┃
					//
					prm_pos.z = -prm_pos.z;

				} else {
					//手前から奥で、下から上で、右から左
	                //
					//          ｙ
					//          ∧
					//  方向┌─┃
					//      │＼┃    │
					//          ┃    │ ＼
					//          ┃＼  │�C ＼
					//          ┃    │    ┃
					//        ─┃──┘----┃─
					//        ＼┃ �B ：＼  ┃   ＼
					//          ┃、  ：  ＼┃  �A ＼
					//          ┃  ━━━━╋━━━━
					//          ┃    │    ┃
					//          ┃     ＼ �@┃
					//  ━━━━╋━━━━━━━━━＞ｘ
					//          ┃          ┃
					//          ┃
					//          ┃
					//そのままで描画順変更不用

				}
			} else {
				if (g_X > g_matWorld._41) {
					//手前から奥で、上から下で、左から右
					//
					//       ｙ    ┃
					//       ∧    ┃ ＼
					//       ┃    ┃�@ ＼
					//       ┃    ┃    │
					//     ━┃━━╋━━━━
					//     ＼┃ �A ┃＼  ：   ＼
					//       ┃、  ┃  ＼：  �B ＼
					//       ┃  ─┃----┌────
					//       ┃    ┃    │
					//       ┃     ＼ �C│ ＼
					// ━━━╋━━━━━━━━━＞ｘ
					//       ┃         ＼      ＼
					//       ┃                   ＼│方向
					//       ┃                   ─┘
					prm_pos.y = -prm_pos.y;
					prm_pos.z = -prm_pos.z;

				} else {
					//手前から奥で、上から下で、右から左
					//
					//                      ┃
					//          ｙ       ／ ┃
					//          ∧     ／ �@┃
					//          ┃    │    ┃
					//          ┃／━━━━╋━━━━
					//          ┃    ：  ／┃ �A  ／
					//        ／┃�B  ：／  ┃   ／
					//        ─┃──┐----┃─
					//          ┃    │    ┃
					//          ┃／  │�C ／
					//    ━━━╋━━━━━━━━＞ｘ
					//      │／┃     |／ 
					//  方向└─┃    
					//          ┃
					//
					prm_pos.y = -prm_pos.y;

				}
			}
		}
	}

	float4 posWorld;
	if (prm_pos.x > 0) {        
		float4x4 matWorld = g_matWorld_front;
		matWorld._41 = g_X;  // 一つ前方のチップ座標へ
		matWorld._42 = g_Y;  
		matWorld._43 = g_Z;  
		posWorld = mul( prm_pos, matWorld );  // World変換
	} else {
		//頂点計算
		posWorld = mul( prm_pos, g_matWorld );        // World変換
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View変換
	out_vs.pos          = mul(posWorldView, g_matProj);  // 射影変換

	//UVはそのまま
	out_vs.uv = prm_uv;
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
		SrcBlend  = SrcAlpha;
		DestBlend = One;

		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}

}



