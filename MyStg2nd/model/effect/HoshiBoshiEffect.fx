////////////////////////////////////////////////////////////////////////////////
// Ggafライブラリ、MeshModel用シェーダー
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World変換行列
float4x4 g_matView;   //View変換行列
float4x4 g_matProj;   //射影変換行列

float g_MyShip_fX;
float g_MyShip_fY;
float g_MyShip_fZ;


float g_default_DcamZ;
float g_Dist_VpPlnFront; //ほぼ視点からの距離
float g_zn;
float g_zf;
float g_TexSize;  //読み込んだテクスチャ（正方形が前提）の幅テクセル数
int g_TextureSplitRowcol; //テクスチャの縦横分割数。
                            //1：縦横１分割＝分割無し。
                            //2：縦横２分割＝４個のアニメパターン
                            //3：縦横３分割＝９個のアニメパターン
float g_offsetU;        //テクスチャU座標増分
float g_offsetV;         //テクスチャV座標増分
float g_UvFlipPtnNo;

float3 g_LightDirection; // ライトの方向
float4 g_LightAmbient;   // Ambienライト色（入射色）
float4 g_LightDiffuse;   // Diffuseライト色（入射色）

float4 g_MaterialDiffuse;  //マテリアルのDiffuse反射色と、Ambien反射色
float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;

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
	float4 uv_ps  : COLOR1;  //スペキュラを潰して表示したいUV座標左上の情報をPSに渡す
};


///////////////////////////////////////////////////////////////////////////
////http://wlog.flatlib.jp/?blogid=1&query=dxgi
//// パックされたカラーを展開する
//float3 pf_to_float3( float pf )
//{
//    uint    data= asint( pf );
//    float3  rcol;
//    const float tof= 1.0f/255.0f;
//    rcol.x= ( data      & 255) * tof;
//    rcol.y= ((data>> 8) & 255) * tof;
//    rcol.z= ((data>>16) & 255) * tof;
//    return  rcol;
//}
//
//// カラーを float1 に圧縮する
//float float3_to_pf( float3 color )
//{
//    uint3   bcol= (uint3)( color * 255.0f ) & 255;
//    return  asfloat( (bcol.z << 16) + (bcol.y << 8) + bcol.x );
//}


//メッシュ標準頂点シェーダー
OUT_VS VS_HoshiBoshi(
      float4 prm_pos         : POSITION,  //ポイントスプライトのポイント群
      float  prm_psize_rate  : PSIZE,     //PSIZEはポイントサイズでは無く、スケールの率(0.0～N (1.0=等倍)) が入ってくる
      float2 prm_ptn_no      : TEXCOORD0, //UVでは無くて、prm_ptn_no.xには、表示したいアニメーションパターン番号が埋め込んである
      float4 prm_col         : COLOR0     //オブジェクトのカラー

) {
	OUT_VS out_vs = (OUT_VS)0;

	out_vs.col = prm_col;
	out_vs.pos = mul(prm_pos    , g_matWorld);  //World

	//カメラの最大視野範囲(-_zf ～ _zf, -_zf ～ _zf, -_zf ～ _zf)
	//を超えている場合、ループする。
	if (out_vs.pos.x > g_zf) {
		out_vs.pos.x = out_vs.pos.x - (g_zf*2);
	}
	if (out_vs.pos.x < -g_zf) {
		out_vs.pos.x = out_vs.pos.x + (g_zf*2);
	}
	if (out_vs.pos.y > g_zf) {
		out_vs.pos.y = out_vs.pos.y - (g_zf*2);
	}
	if (out_vs.pos.y < -g_zf) {
		out_vs.pos.y = out_vs.pos.y + (g_zf*2);
	}
	if (out_vs.pos.z > g_zf) {
		out_vs.pos.z = out_vs.pos.z - (g_zf*2);
	}
	if (out_vs.pos.z < -g_zf) {
		out_vs.pos.z = out_vs.pos.z + (g_zf*2);
	}

// 自機の周りにある星々を滑らかに透明にしたい。
//
// 自機座標を(X,Y,Z)とした場合。
// f(x,y,z) = abs(X-x)+abs(Y-y)+abs(Z-z)　と置くと
// f(x,y,z) = D を満たす(x,y,z)は、距離がDのラミエルとなる。
// f(x,y,z) = g_default_DcamZ はつまり ① のような範囲である。（g_default_DcamZは自機からカメラの初期距離）
// ①を式変形して
// {abs(X-x)+abs(Y-y)+abs(Z-z)} / default_DcamZ = 1.0 … ① 
// これより、以下の範囲を考える
// {abs(X-x)/4 + abs(Y-y)/2 + abs(Z-z)/2} / g_default_DcamZ = 1.0 …② 
// {abs(X-x)/4 + abs(Y-y)/2 + abs(Z-z)/2} / g_default_DcamZ = 2.0 …③
//
// [真上からのイメージ（図の比率がオカシイが；）]
//
//      Z
//     ^
//     |
//     |
//     |
//     |
//     |                                            ＝＿                  
//     |                       (DcamZ,0)              ￣＝＿        ●                                  ●
//     |                     ／ ＼                        ￣＝＿          
//     |                   ／     ＼                        ②￣＝＿             ●   ￣＝＿      
//     |                 ／       ①＼                            ￣＝＿                ③￣＝＿  
//     |               ／             ＼                              ￣＝＿                  ￣＝＿
//     |             ／                 ＼                                ￣＝＿                  ￣＝＿
// ----+--------------------- 自機→ --------------------------------------------------------------------------------> X
//    0|   (-DcamZ,0)＼        ^        ／  (DcamZ,0)                     ＿＝￣ (4*DcamZ,0)      ＿＝￣(8*DcamZ,0)
//     |               ＼      |DcamZ ／                              ＿＝￣                  ＿＝￣
//     |                 ＼    |    ／         この領域では       ＿＝￣                  ＿＝￣
//     |                   ＼  |  ／           星は非表示     ＿＝￣        ●        ＿＝￣                    ●
//     |                     ＼v／                        ＿＝￣                  ＿＝￣
// ￣＝＿                     Cam (DcamZ,0)           ＿＝￣                  ＿＝￣         
//     ￣＝＿                  ^                  ＿＝￣    この領域で    ＿＝￣             
//     |   ￣＝＿              |              ＿＝￣     星が薄まる   ＿＝￣  ●(out_vs.pos.x, out_vs.pos.y, out_vs.pos.z)
//     |       ￣＝＿          |          ＿＝￣                  ＿＝￣      星
//     |           ￣＝＿      |      ＿＝￣                  ＿＝￣
//     |               ￣＝＿  v  ＿＝￣                  ＿＝￣
// ￣＝＿                  ￣＝ ＝￣                  ＿＝￣
//     ￣＝＿                  ^ (2*DcamZ,0)      ＿＝￣
//     |   ￣＝＿              |              ＿＝￣
//     |       ￣＝＿          |          ＿＝￣                           ●
//     |           ￣＝＿      |      ＿＝￣
//     |               ￣＝＿  v  ＿＝￣
//     |                   ￣＝ ＝￣
//                             (4*DcamZ,0)
//
// ここで (x,y,z) に星の座標を代入して、③→②へ移動中にアルファを減らそうとした。
//
//	float r2 = ( abs(out_vs.pos.x-g_MyShip_fX)/4 + 
//               abs(out_vs.pos.y-g_MyShip_fY)/2 + 
//               abs(out_vs.pos.z-g_MyShip_fZ)/2  ) / g_default_DcamZ;
//
//	if (r2 < 1.0) {
//		//②の内側、星非表示領域
//		//out_vs.col.a = 0;
//		out_vs.col.r = 1.0;
//		out_vs.col.g = 0.0;
//		out_vs.col.b = 0.0;
//	} else {
//		//②の外側
//        //out_vs.col.a = r2 - 1.0;
//		out_vs.col.rgb = r2;
//	}

	//<<検証用>>
	float r2 = ( abs(out_vs.pos.x-g_MyShip_fX)/5.0+ 
                 abs(out_vs.pos.y-g_MyShip_fY)/5.0+ 
                 abs(out_vs.pos.z-g_MyShip_fZ)/5.0 ) / g_default_DcamZ;

	if (r2 < 1.0) {
		//②の内側、星非表示領域
		//out_vs.col.a = 0;
		out_vs.col.r = 1.0;
		out_vs.col.g = 1.0;
		out_vs.col.b = 1.0;
		out_vs.col.a = 1.0;
	} else {
		//②の外側
        //out_vs.col.a = r2 - 1.0;
		out_vs.col.a = 0;
	}


//	//ZY座標について自機の周りは非表示
//	if (g_MyShip_fZ-g_default_DcamZ*2 <  out_vs.pos.z  && out_vs.pos.z <  g_MyShip_fZ+g_default_DcamZ*2) {
//		if (g_MyShip_fY-g_default_DcamZ*2 <  out_vs.pos.y  && out_vs.pos.y <  g_MyShip_fY+g_default_DcamZ*2) {
//			
//			out_vs.col.a = 0;
////			out_vs.col.r = 1.0 -  (abs(out_vs.pos.z - g_MyShip_fZ) + abs(out_vs.pos.y - g_MyShip_fY)) / g_default_DcamZ;
//		}
//	}


	out_vs.pos = mul(out_vs.pos , g_matView);  //View
	float dep = out_vs.pos.z + 1.0; //+1.0の意味は
                                    //VIEW変換は(0.0, 0.0, -1.0) から (0.0, 0.0, 0.0) を見ているため、
                                    //距離に加える。




	out_vs.pos = mul(out_vs.pos , g_matProj);  //射影変換


	//奥ほど小さく表示するために縮小率計算
	out_vs.psize = (g_TexSize / g_TextureSplitRowcol) * (g_default_DcamZ / dep) * prm_psize_rate*5.0;  //通常の奥行きの縮小率

    int ptnno = ((int)(prm_ptn_no.x + g_UvFlipPtnNo)) % (g_TextureSplitRowcol*g_TextureSplitRowcol);
	//スペキュラセマンテックス(COLOR1)を潰して表示したいUV座標左上の情報をPSに渡す
	out_vs.uv_ps.x = ((int)(ptnno % g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);
	out_vs.uv_ps.y = ((int)(ptnno / g_TextureSplitRowcol)) * (1.0 / g_TextureSplitRowcol);

	return out_vs;
}

//メッシュ標準ピクセルシェーダー（テクスチャ有り）
float4 PS_HoshiBoshi(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_col                : COLOR0,
	float4 prm_uv_ps              : COLOR1  //スペキュラでは無くて、表示したいUV座標左上の情報が入っている
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * prm_col; // * g_MaterialDiffuse;
	out_color.a = out_color.a * g_MasterAlpha; 
	return out_color;
}


float4 PS_Flush(
	float2 prm_uv_pointsprite	  : TEXCOORD0,     
	float4 prm_col                : COLOR0,
	float4 prm_uv_ps              : COLOR1
) : COLOR  {
	float2 uv = (float2)0;
	uv.x = prm_uv_pointsprite.x * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.x;
	uv.y = prm_uv_pointsprite.y * (1.0 / g_TextureSplitRowcol) + prm_uv_ps.y;
	float4 out_color = tex2D( MyTextureSampler, uv) * prm_col * float4(7.0, 7.0, 7.0, 1.0);// * g_MaterialDiffuse;
	out_color.a = out_color.a * g_MasterAlpha; 
	return out_color;
}

technique HoshiBoshiTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_HoshiBoshi();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //加算合成
		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_HoshiBoshi();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 VS_HoshiBoshi();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}

