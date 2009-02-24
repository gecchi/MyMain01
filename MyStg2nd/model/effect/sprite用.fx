
float4x4 g_matWorld;  //���[���h�ϊ��s��
float4x4 g_matView;   //VIEW�ϊ��s��
float4x4 g_matPro;    //�ˉe�ϊ��s��

float3 g_LD = float3( 1, 0, 0 );      // ���C�g�̕���
float4 g_LC = float4( 1, 1, 1, 1 );   // ���C�g�J���[�i���ːF�j

texture g_diffuseMap;
sampler MyTextureSampler = sampler_state {
	texture = <g_diffuseMap>;
};

//texture	Tex1;		//�e�N�X�`��
//sampler TextureSampler = sampler_state
//{
//    Texture = <Tex1>;
//	//�t�B���^�ݒ�
//    MinFilter = LINEAR;
//    MagFilter = LINEAR;
//    MipFilter = LINEAR;    
//    //�e�N�X�`�����b�s���O
//    AddressU = Wrap;
//    AddressV = Wrap;
//};
// 
//���_�V�F�[�_�[�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
    float2 uv     : TEXCOORD0;
    float3 normal : TEXCOORD1; // �s�N�Z���V�F�[�_�[�ɖ@������n�����߂� TEXCOORD1 �Ƃ���
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,       // ���f���̒��_
      float2 prm_uv     : TEXCOORD0,      // ���f���̒��_��UV
      float3 prm_normal : NORMAL         // ���f���̒��_�̖@��
) {

	//���_�v�Z
	float4 pos;   // �o�͒��_���W
	pos = mul( prm_pos, g_matWorld );   // ���[���h�ϊ�
	pos = mul( pos, g_matView );    // �r���[�ϊ�
	pos = mul( pos, g_matPro );    // �ˉe�ϊ�

    //�@���v�Z
	float3 normal;
	normal = mul( prm_normal, g_matWorld );  //�@�������[���h�ϊ�

	//UV�v�Z


	//�o�֑͂��
	OUT_VS out_vs = (OUT_VS)0;
	out_vs.pos    = pos;
	out_vs.uv     = prm_uv; //�s�N�Z���V�F�[�_�[��
	out_vs.normal = normal; //�s�N�Z���V�F�[�_�[��
	return out_vs;
}

// �s�N�Z���V�F�[�_
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,  //���_�V�F�[�_�[�Ń��[���h�ϊ��ς݂̖@��
    float4 prm_color : COLOR0 
) : COLOR  {
	//�e�N�X�`������
	prm_color = tex2D( MyTextureSampler, prm_uv ) * prm_color;
    return prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
