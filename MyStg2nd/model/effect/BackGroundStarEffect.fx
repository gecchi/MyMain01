////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����ABackGroundStar001�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_vecLightDirection; // ���C�g�̕���
float4 g_colLightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_colLightDiffuse;   // Diffuse���C�g�F�i���ːF�j
float g_alpha_master;   



float4 g_colMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

float g_tex_blink_power;   
float g_tex_blink_threshold;

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS BackGroundStarVS_DefaultMesh(
      float4 prm_pos    : POSITION      // ���f���̒��_

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
	float4 posWorld = mul( prm_pos, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 BackGroundStarPS_DefaultMesh(
) : COLOR  {
	//���߂�F
	return float4( 1, 1, 1, 0.9 );
}


technique BackGroundStarTechnique
{
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 BackGroundStarVS_DefaultMesh();
		PixelShader  = compile ps_2_0 BackGroundStarPS_DefaultMesh();
	}
}

