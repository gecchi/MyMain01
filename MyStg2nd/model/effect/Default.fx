////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����p�A�W���V�F�[�_�[
// 
// �T�v�FWorld�AView�A�ˉe�ϊ����āA�}�e���A���ƃe�N�X�`���������l�����ă����_�����O
//
// �p�����[�^:
// float4x4 g_matWorld		:	World�ϊ��s��
// float4x4 g_matView		:	View�ϊ��s��
// float4x4 g_matProj		:	�ˉe�ϊ��s��
// float4 g_MaterialAmbient	:	�}�e���A����Ambien���ːF
// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ːF
//
// Auther:Masatoshi Tsuge
// date:2009/02/04 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection = float3( -0.577, 0.577, -0.577 );      // ���C�g�̕���

float4 g_LightAmbient = float4( 0.2, 0.2, 0.2, 0.2 );   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse = float4( 1, 1, 1, 1 );           // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialAmbient;  //�}�e���A����Ambien���ːF
float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF


texture g_diffuseMap;
sampler MyTextureSampler = sampler_state {
	texture = <g_diffuseMap>;
};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float4 color  : COLOR0;
    float2 uv     : TEXCOORD0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS Default_VS(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float2 prm_uv     : TEXCOORD0,     // ���f���̒��_��UV
      float3 prm_normal : NORMAL         // ���f���̒��_�̖@��
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�

    //�@���v�Z
    float3 normal = normalize(mul(prm_normal, posWorldView)); //�@���� World �ϊ�

	//�J���[�v�Z(�����v�Z)���A�o�͂ɐݒ�
	out_vs.color = (g_LightDiffuse * g_MaterialDiffuse * max( dot(g_LightDirection, normal), 0)) +
                   (g_LightAmbient * g_MaterialAmbient);

	//���͕ʂł����Ă�����̂������̂ł͂Ȃ��̂�

	//UV�v�Z���o�͂ɐݒ�
	out_vs.uv = prm_uv;

	return out_vs;
}

// �s�N�Z���V�F�[�_
float4 Default_PS(
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color  : COLOR0 
) : COLOR  {
	//�e�N�X�`������
	return tex2D( MyTextureSampler, prm_uv );// * prm_color;
}

technique DefaultTec
{
	pass P0 {
		VertexShader = compile vs_2_0 Default_VS();
		PixelShader  = compile ps_2_0 Default_PS();
	}
}
