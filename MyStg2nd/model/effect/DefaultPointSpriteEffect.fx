////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、GgafDx9MeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float g_default_DcamZ;
float g_Dist_VpPlnFront; //ほぼ視点からの距離
float g_zn;
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_offsetU; //テクスチャU座標増分
float g_offsetV; //テクスチャV座標増分
float g_UvFlipPtnNo;

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_PowerBlink;   
float g_BlinkThreshold;

//s0レジスタのサンプラを使う(固定パイプラインにセットされたテクスチャをシェーダーで使う)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//頂点シェーダー、出力構造体
struct OUT_VS
{
    float4 pos    : POSITION;
	float  psize  : PSIZE;
	float4 col    : COLOR0;
	float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//メッシュ標準頂点シェーダー
OUT_VS GgafDx9VS_DefaultPointSprite(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float  prm_psize  : PSIZE,
      float2 prm_uv     : TEXCOORD0,
      float4 prm_col    : COLOR0

) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	out_vs.pos = mul(prm_pos    , g_matWorld);  //World
	out_vs.pos = mul(out_vs.pos , g_matView);  //View
	float dep = out_vs.pos.z + 1.0; //+1.0の意味は
                                    //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                    //距離に加える。
    //float dep = g_zn + g_Dist_VpPlnFront;//(0,0,0)の距離
	out_vs.pos = mul(out_vs.pos , g_matProj);  //射影変換

	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_default_DcamZ / dep) * prm_psize;


    int ptnno = ((int)(prm_uv.x + g_UvFlipPtnNo)) % (g_TextureSplitRowcol*g_TextureSplitRowcol);
    float u = ((int)(ptnno % g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);
    float v = ((int)(ptnno / g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);


	// colorに、uv座標を無理やり埋め込む（ポイントスプライトはUV固定になるため）
	out_vs.col.r = u;
	out_vs.col.g = v;

    int rg = (int)(prm_col.r*255) + ((int)(prm_col.g*255))*1000;
    int ba = (int)(prm_col.b*255) + ((int)(prm_col.a*255))*1000;
	out_vs.col.b = rg;
	out_vs.col.a = ba;
	//out_vs.uv = prm_uv;//何でも同じfloat2(0.5, 0.5);
	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 GgafDx9PS_DefaultPointSprite(
	float2 prm_uv	  : TEXCOORD0,     
	float4 prm_col    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float2 uv = (float2)0; // * 0.5;//左上1/4


	uv.x = prm_uv.x * (1.0 / g_TextureSplitRowcol) + prm_col.r;
	uv.y = prm_uv.y * (1.0 / g_TextureSplitRowcol) + prm_col.g;
	int rg = (int)prm_col.b;
	int ba = (int)prm_col.a;
	//float4 color = float4((float)((rg%1000) / 255.0), (float)(((int)(rg/1000)) / 255.0), (float)((ba%1000) / 255.0), (float)(((int)(ba/1000)) / 255.0));        

    float4 out_color =  tex2D( MyTextureSampler, uv);
	out_color.r = out_color.r * (float)((rg%1000) / 255.0);
	out_color.g = out_color.g * (float)(((int)(rg/1000)) / 255.0);
	out_color.b = out_color.b * (float)((ba%1000) / 255.0);
	out_color.a = out_color.a * (float)(((int)(ba/1000)) / 255.0);
//	uv.x = prm_uv.x * (1.0 / g_TextureSplitRowcol) + prm_col.x + g_offsetU;
//	uv.y = prm_uv.y * (1.0 / g_TextureSplitRowcol) + prm_col.y + g_offsetV;
	return out_color;
}

float4 PS_DestBlendOne( 
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	return tex2D( MyTextureSampler, prm_uv) * g_MaterialDiffuse;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	return tex2D( MyTextureSampler, prm_uv) * g_MaterialDiffuse * float4(7.0, 7.0, 7.0, 1.0);
}

technique DefaultPointSpriteTechnique
{
	//pass P0「メッシュ標準シェーダー」
	//メッシュを描画する
	//【考慮される要素】
	//--- VS ---
	//・頂点を World、View、射影 変換
	//・法線を World変換
	//--- PS ---
	//・Diffuseライト色
	//・Ambientライト色
	//・ライト方向
	//・オブジェクトのマテリアルのDiffuse反射（色はAmbient反射と共通）
	//・オブジェクトのテクスチャ
	//・半透明α（Diffuse反射αとテクスチャαの乗算）
	//【使用条件】
	//・テクスチャが存在しs0レジスタにバインドされていること。
	//【設定パラメータ】
	// float4x4 g_matWorld		:	World変換行列
	// float4x4 g_matView		:	View変換行列
	// float4x4 g_matProj		:	射影変換行列   
	// float3 g_LightDirection	:	ライトの方向
	// float4 g_LightAmbient	:	Ambienライト色（入射色）
	// float4 g_LightDiffuse	:	Diffuseライト色（入射色）
	// float4 g_MaterialDiffuse	:	マテリアルのDiffuse反射（Ambient反射と共通）
	// s0レジスタ				:	2Dテクスチャ
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultPointSprite();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 PS_DestBlendOne();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_DefaultPointSprite();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

