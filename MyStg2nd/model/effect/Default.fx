// ���[���h�r���[�ˉe�ϊ��s��錾
float4x4 g_worldMat;
float4x4 g_viewMat;
float4x4 g_projMat;
float4 pos : POSITION;

// ���_�V�F�[�_
float4 BasicTransform( float4 inLocalPos : POSITION ) : POSITION
{

	pos = mul( inLocalPos, g_worldMat );
	pos = mul( pos, g_viewMat );
	pos = mul( pos, g_projMat );
	return pos;
}

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
      VertexShader = compile vs_2_0 BasicTransform();
      PixelShader = compile ps_2_0 NoWorkingPixelShader();
   }
}