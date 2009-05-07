////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MorphTwoMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/05/07 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
float�@g_weight; //�d��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

//so���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

//texture g_diffuseMap;
//sampler MyTextureSampler = sampler_state {
//	texture = <g_diffuseMap>;
//};

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultMorphTwoMesh(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv      : TEXCOORD0.      // ���f���̒��_��UV

      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g���_
      float4 prm_normal1 : NORMAL1         // ���f���̃��[�t�^�[�Q�b�g���_�̖@��
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�u�����h���ϊ�
	float4 pos = lerp(prm_pos0, prm_pos1, g_weight );           // �u�����h
	float4 posWorld = mul( pos, g_matWorld );                   // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���u�����h���ϊ�
	float3 normal = lerp(prm_normal0, prm_normal1, g_weight );  //�u�����h
    out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultMorphTwoMesh(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1
) : COLOR  {
	//���߂�F
	float4 out_color; 

    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B              
	out_color = g_LightDiffuse * g_MaterialDiffuse * tex_color * power; 
	//Ambient�F�����Z�B�}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B
	out_color =  (g_LightAmbient * g_MaterialDiffuse * tex_color) + out_color;  
	//���v�Z�A���͖@������у��C�g�����Ɉˑ����Ȃ��Ƃ���̂ŕʌv�Z�B�Œ�̓��C�g���F���l�����邪�A�{�V�F�[�_�[�̓��C�g���͖����B
	out_color.a = g_MaterialDiffuse.a * tex_color.a ; 

	return out_color;
}

technique DefaultMorphTwoMeshTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//�E�@���� World�ϊ�
	//--- PS ---
	//�EDiffuse���C�g�F
	//�EAmbient���C�g�F
	//�E���C�g����
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	//�E�I�u�W�F�N�g�̃e�N�X�`��
	//�E���������iDiffuse���˃��ƃe�N�X�`�����̏�Z�j
	//�y�g�p�����z
	//�E�e�N�X�`�������݂�s0���W�X�^�Ƀo�C���h����Ă��邱�ƁB
	//�y�ݒ�p�����[�^�z
	// float4x4 g_matWorld		:	World�ϊ��s��
	// float4x4 g_matView		:	View�ϊ��s��
	// float4x4 g_matProj		:	�ˉe�ϊ��s��   
	// float3 g_LightDirection	:	���C�g�̕���
	// float4 g_LightAmbient	:	Ambien���C�g�F�i���ːF�j
	// float4 g_LightDiffuse	:	Diffuse���C�g�F�i���ːF�j
	// float4 g_MaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	// s0���W�X�^				:	2D�e�N�X�`��
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphTwoMesh();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphTwoMesh();
	}
}

