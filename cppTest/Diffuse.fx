float4x4 g_worldView;
float4x4 g_projMat;
float3 g_LD = float3( 1, 0, 0 );
float4 g_LC = float4( 1, 1, 1, 1 );

texture g_diffuseMap;
sampler diffuseSampler = sampler_state {
	texture = <g_diffuseMap>;
};

struct VS_OUT {
	float4 pos    : POSITION;
	float4 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;
};

VS_OUT Specular_VS( float4 inLocalPos : POSITION, float3 inLocalNormal : NORMAL, float4 inUV : TEXCOORD0 )
{
	VS_OUT Out = (VS_OUT)0;
	Out.pos = mul( inLocalPos, g_worldView );
	Out.pos = mul( Out.pos, g_projMat );

	// �@���x�N�g�������[���h��
	Out.normal = mul( inLocalNormal, g_worldView );
	
	Out.uv     = inUV;
	return Out;
}


float4 Specular_PS( float4 inUV : TEXCOORD0, float3 inWorldNormal : TEXCOORD1 ) : COLOR0
{
	// ���[���h�ɂ��郉�C�g�̕����Ɩ@���̌���������̋������Z�o
	float Power = clamp( dot( normalize(-g_LD), normalize( inWorldNormal ) ), 0.0f, 1.0f );
	
	float4 RC = tex2D( diffuseSampler, inUV );
	float4 SurfaceColor = RC * g_LC;
	return SurfaceColor * Power;
}

technique Diffuse
{
	pass P0
	{
		VertexShader = compile vs_2_0 Specular_VS();
		PixelShader = compile ps_2_0 Specular_PS();
	}	
}