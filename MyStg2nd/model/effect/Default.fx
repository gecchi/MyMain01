// ���[���h�r���[�ˉe�ϊ��s��錾
float4x4 g_worldMat;
float4x4 g_viewMat;
float4x4 g_projMat;
//float4 pos : POSITION;


struct VS_OUT {
	float4 pos    : POSITION;
	float4 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;
};

VS_OUT Specular_VS( float4 inLocalPos : POSITION, float3 inLocalNormal : NORMAL, float4 inUV : TEXCOORD0 )
{
	VS_OUT Out = (VS_OUT)0;
	Out.pos = mul( inLocalPos, g_worldMat );
	Out.pos = mul( Out.pos, g_viewMat );
	Out.pos = mul( Out.pos, g_projMat );

	// �@���x�N�g�������[���h�ցH
	Out.normal = inLocalNormal;
//mul( inLocalNormal, g_worldView );
	
	Out.uv     = inUV;
	return Out;
}

//
//// ���_�V�F�[�_
//float4 BasicTransform( float4 inLocalPos : POSITION ) : POSITION
//{
//
//	pos = mul( inLocalPos, g_worldMat );
//	pos = mul( pos, g_viewMat );
//	pos = mul( pos, g_projMat );
//	return pos;
//}
//
// �s�N�Z���V�F�[�_
float4 NoWorkingPixelShader( float4 ScreenColor : COLOR ) : COLOR
{
   // ���͂��ꂽ�X�N���[���s�N�Z���̐F�����̂܂܃X���[
   return ScreenColor;
}


technique BasicTec
{
   pass P0
   {
      VertexShader = compile vs_2_0 Specular_VS();
      PixelShader = compile ps_2_0 NoWorkingPixelShader();
   }
}