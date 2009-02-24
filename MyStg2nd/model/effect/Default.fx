float4x4 g_matWorld;  //���[���h�ϊ��s��
float4x4 g_matView;   //VIEW�ϊ��s��
float4x4 g_matPro;    //�ˉe�ϊ��s��

// �o�[�e�b�N�X�V�F�[�_
struct OUT_VS
{
    float4 pos    : POSITION;
    float2 uv     : TEXCOORD0;
};



OUT_VS Default_VS(
      float4 prm_pos    : POSITION,          // ���f���̒��_
      float2 prm_uv     : TEXCOORD0          // ���f����UV
) {

	//���_�v�Z
	float4 pos;   // �o�͒��_���W
	pos = mul( prm_pos, g_matWorld );   // ���[���h�ϊ�
	pos = mul( pos, g_matView );    // �r���[�ϊ�
	pos = mul( pos, g_matPro );    // �ˉe�ϊ�

    //�@���v�Z


	//UV�v�Z


	//�o�֑͂��
	OUT_VS out_vs = (OUT_VS)0;
	out_vs.pos = pos;
	out_vs.uv = prm_uv;

	return out_vs;
}

// �s�N�Z���V�F�[�_�v���O����
float4 Default_PS(
	float2 prm_uv	 : TEXCOORD0,
    float4 prm_color : COLOR0 
) : COLOR  {
	//�e�N�X�`������
//	prm_color = tex2D( TextureSampler, prm_uv ) * prm_color;
    return prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
