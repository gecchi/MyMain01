////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// Auther:Masatoshi Tsuge
// date:2009/04/15 
////////////////////////////////////////////////////////////////////////////////

float g_X; //��O���s���`�b�vX
float g_Y; //��O���s���`�b�vY
float g_Z; //��O���s���`�b�vZ



float4x4 g_matWorld;  //���g��World�ϊ��s��
float4x4 g_matWorld_front;  //��O���s���`�b�v��World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	float4 posWorld;
	if (prm_pos.x > 0) {        
		g_matWorld_front._41 = g_X;  // ��O���̃`�b�v���W��
		g_matWorld_front._42 = g_Y;  
		g_matWorld_front._43 = g_Z;  
		posWorld = mul( prm_pos, g_matWorld_front );  // World�ϊ�
	} else {
		//���_�v�Z
		posWorld = mul( prm_pos, g_matWorld );   // World�ϊ�
	}
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	//�@���v�Z
	out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
	float4 prm_color_dist  : COLOR0,
	float2 prm_uv	  : TEXCOORD0
) : COLOR  {
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);
	return tex_color;
}


technique LaserChipTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = One;


		VertexShader = compile vs_2_0 GgafDx9VS_LaserChip();
		PixelShader  = compile ps_2_0 GgafDx9PS_LaserChip();
	}


}



