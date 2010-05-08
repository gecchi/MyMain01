float4x4 g_matWorld;  
float4x4 g_matView;   
float4x4 g_matProj;   

float3 g_LightDirection; 
float4 g_LightAmbient;   
float4 g_LightDiffuse;   

float4 g_MaterialDiffuse;

float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;
float g_zf;

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


OUT_VS GgafDx9VS_GroundMesh(
      float4 prm_pos    : POSITION,      // モデルの頂点
      float3 prm_normal : NORMAL,        // モデルの頂点の法線
      float2 prm_uv     : TEXCOORD0      // モデルの頂点のUV
) {
	OUT_VS out_vs = (OUT_VS)0;

	//頂点計算
	out_vs.pos = mul( mul( mul(prm_pos, g_matWorld), g_matView), g_matProj);  //World*View*射影変換
	//UVはそのまま
	out_vs.uv = prm_uv;

    //頂点カラー計算

	//法線を World 変換して正規化
    float3 normal = normalize(mul(prm_normal, g_matWorld)); 	
    //法線と、Diffuseライト方向の内積を計算し、面に対するライト方向の入射角による減衰具合を求める。
	float power = max(dot(normal, -g_LightDirection ), 0);      
	//Ambientライト色、Diffuseライト色、Diffuseライト方向、マテリアル色 を考慮したカラー作成。      
	out_vs.col = (g_LightAmbient + (g_LightDiffuse*power)) * g_MaterialDiffuse;
	//αフォグ
	out_vs.col.a = g_MaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // 最遠の 1/2 より奥の場合徐々に透明に
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //最遠の 3/4 より奥の場合徐々に透明に
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//マスターα
	out_vs.col.a *= g_MasterAlpha;

 //カメラの位置(0,0,-57.1259)
//実は世界は(-1.0f, -1.0f, 0 )という点から(1.0f, 1.0f, 1,0f)という点を対角線とする直方体の世界に収められてしまっています

//wは射影空間（視錐台空間）にある頂点座標をそれで割ることにより
//「頂点をスクリーンに投影するための立方体の領域（-1≦x≦1、-1≦y≦1そして0≦z≦1）に納める」
//という大切な役目をしています。wが「同次系」と呼ばれるのは、
//上の例のように視錐状にカメラの視線方向に広がっている頂点を同じXY座標に投影するためです。


	if ( out_vs.pos.z < 60) {
		out_vs.col.a = (out_vs.pos.z + 1.0)  / (57.1259*2);
//1 - (out_vs.pos.z / 57.1259);
	}
	return out_vs;
}

float4 GgafDx9PS_GroundMesh(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinkerを考慮
	if (tex_color.r >= g_BlinkThreshold || tex_color.g >= g_BlinkThreshold || tex_color.b >= g_BlinkThreshold) {
		out_color.rgb *= g_PowerBlink; //+ (tex_color * g_PowerBlink);
	} 
	return out_color;
}


technique GroundMeshTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh();
	}
}

