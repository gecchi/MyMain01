// ���[���h�r���[�ˉe�ϊ��s��錾
float4x4 matWorldViewProj;


// ���_�V�F�[�_
float4 BasicTransform( float4 LocalPos : POSITION ) : POSITION
{
   // ���[�J�����W�ɂ��钸�_�����[���h�r���[�ˉe�ϊ���
   // ��C�ɃX�N���[�����W�ɂ��Ă��܂�
   return mul( LocalPos, matWorldViewProj );
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