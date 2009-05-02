////////////////////////////////////////////////////////////////////////////////
// ���[�U�[�`�b�v�p�V�F�[�_�[
//
// Auther:Masatoshi Tsuge
// date:2009/04/23
////////////////////////////////////////////////////////////////////////////////

int g_kind; //�`�b�v��� 1:���� 2:���� 3:�擪 �i�������擪�͖������D��j

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
};


///////////////////////////////////////////////////////////////////////////

//���[�U�[�`�b�v���_�V�F�[�_�[
OUT_VS GgafDx9VS_LaserChip(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
//
	if (g_X - g_matWorld._41 < 0) {
		prm_pos.z = -prm_pos.z;
	}
//
//	if (g_Y - g_matWorld._42 < 0) {
//		prm_pos.y = -prm_pos.y;
//	}
//
	if (abs(g_Z - g_matWorld._43) < 1.5) {
		if (abs(g_Y - g_matWorld._42) < 1.0) {
			prm_pos.z = 0;
		}
	}

	float4 posWorld;
	if (prm_pos.x > 0) {        
		float4x4 matWorld = g_matWorld_front;
		matWorld._41 = g_X;  // ��O���̃`�b�v���W��
		matWorld._42 = g_Y;  
		matWorld._43 = g_Z;  
		posWorld = mul( prm_pos, matWorld );  // World�ϊ�
	} else {
		//���_�v�Z
		posWorld = mul( prm_pos, g_matWorld );        // World�ϊ�
	}
	float4 posWorldView = mul(posWorld    , g_matView);  // View�ϊ�
	out_vs.pos          = mul(posWorldView, g_matProj);  // �ˉe�ϊ�

	//UV
	if (g_kind == 1) {
		out_vs.uv.x = prm_uv.x - 0.5;
		out_vs.uv.y = prm_uv.y;
	} else if (g_kind == 3) {
		out_vs.uv.x = prm_uv.x;
		out_vs.uv.y = prm_uv.y - 0.5;
	} else {
		out_vs.uv = prm_uv;
	}
	return out_vs;
}

float4 GgafDx9PS_LaserChip(
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



