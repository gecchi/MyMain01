float4x4 g_matWorld;  
float4x4 g_matView;   
float4x4 g_matProj;   

float3 g_LightDirection; 
float4 g_LightAmbient;   
float4 g_LightDiffuse;   

float4 g_MaterialDiffuse;

float g_Blinker;   

sampler MyTextureSampler : register(s0);


struct OUT_VS
{
    float4 pos    : POSITION;
	float3 normal : TEXCOORD1;   
    float4 color  : COLOR0;
	float2 uv     : TEXCOORD0;

};


OUT_VS GgafDx9VS_GroundMesh(
      float4 prm_pos    : POSITION,     
      float3 prm_normal : NORMAL,       
	  float4 prm_color  : COLOR0,
      float2 prm_uv     : TEXCOORD0     

) {
	OUT_VS out_vs = (OUT_VS)0;

	out_vs.pos = mul( mul(prm_pos, g_matWorld), g_matView);
	out_vs.color = prm_color;
//カメラの位置(0,0,-57.1259)
//実は世界は(-1.0f, -1.0f, 0 )という点から(1.0f, 1.0f, 1,0f)という点を対角線とする直方体の世界に収められてしまっています

//wは射影空間（視錐台空間）にある頂点座標をそれで割ることにより
//「頂点をスクリーンに投影するための立方体の領域（-1≦x≦1、-1≦y≦1そして0≦z≦1）に納める」
//という大切な役目をしています。wが「同次系」と呼ばれるのは、
//上の例のように視錐状にカメラの視線方向に広がっている頂点を同じXY座標に投影するためです。


	if ( out_vs.pos.z < 60) {
		out_vs.color.a = (out_vs.pos.z + 1.0)  / (57.1259*2);
//1 - (out_vs.pos.z / 57.1259);
	}

	out_vs.pos = mul(out_vs.pos, g_matProj);  
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
	out_vs.uv = prm_uv;
	return out_vs;
}

float4 GgafDx9PS_GroundMesh(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_color  : COLOR0
) : COLOR  {
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	float4 out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; 
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  
	out_color.a = g_MaterialDiffuse.a * tex_color.a * prm_color.a; 

	return out_color;
}

float4 GgafDx9PS_GroundMesh2(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_color  : COLOR0 
) : COLOR  {
	//テクスチャをサンプリングして色取得（原色を取得）
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//ライト色、マテリアル色、テクスチャ色を考慮した色作成。              
	float4 out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color; 
	//α計算、
	out_color.a = g_MaterialDiffuse.a * tex_color.a * prm_color.a; 

	return out_color;
}


technique GroundMeshTechnique
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
		ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh();
	}
}

technique GroundMeshTechnique2
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        ColorVertex  = True;

		VertexShader = compile vs_2_0 GgafDx9VS_GroundMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_GroundMesh2();
	}
}


