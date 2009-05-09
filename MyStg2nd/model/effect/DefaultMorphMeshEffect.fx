////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MorphMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/05/07 
////////////////////////////////////////////////////////////////////////////////

float4x4 g_matWorld;  //World�ϊ��s��
float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��
int g_morph_target_num;  //���b�V���p�^�[����(���[�t�^�[�Q�b�g���j
float g_weight1; //�d��1
float g_weight2; //�d��2
float g_weight3; //�d��3
float g_weight4; //�d��4
float g_weight5; //�d��5
float g_weight6; //�d��6
float g_weight7; //�d��7
float g_weight8; //�d��8
float g_weight9; //�d��9

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

//���[�t�^�[�Q�b�g�Ȃ�
OUT_VS GgafDx9VS_DefaultMorphMesh0(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0       // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	//���_�v�Z
	float4 posWorld = mul( prm_pos0, g_matWorld );               // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���v�Z
    out_vs.normal = normalize(mul(prm_normal0, g_matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv0;
	return out_vs;
}

//���[�t�^�[�Q�b�g�P��
OUT_VS GgafDx9VS_DefaultMorphMesh1(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1         // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��

) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�u�����h���ϊ�
	float4 pos = lerp(prm_pos0, prm_pos1, g_weight1 );           // �u�����h
	float4 posWorld = mul( pos, g_matWorld );                   // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���u�����h���ϊ�
	float3 normal = lerp(prm_normal0, prm_normal1, g_weight1 );  //�u�����h
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv0;
	return out_vs;
}


//���[�t�^�[�Q�b�g�Q��
OUT_VS GgafDx9VS_DefaultMorphMesh2(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2         // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�u�����h���ϊ�
	float4 pos = lerp(prm_pos0, prm_pos1, g_weight1 );          // �u�����h
	pos = lerp(pos, prm_pos2, g_weight2 );
	float4 posWorld = mul( pos, g_matWorld );                   // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���u�����h���ϊ�
	float3 normal = lerp(prm_normal0, prm_normal1, g_weight1 );  //�u�����h
	normal = lerp(normal, prm_normal2, g_weight2 );
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv0;
	return out_vs;
}

//���[�t�^�[�Q�b�g�R��
OUT_VS GgafDx9VS_DefaultMorphMesh3(
      float4 prm_pos0    : POSITION0,      // ���f���̒��_
      float3 prm_normal0 : NORMAL0,        // ���f���̒��_�̖@��
      float2 prm_uv0     : TEXCOORD0,      // ���f���̒��_��UV
      float4 prm_pos1    : POSITION1,      // ���f���̃��[�t�^�[�Q�b�g1���_
      float3 prm_normal1 : NORMAL1,        // ���f���̃��[�t�^�[�Q�b�g1���_�̖@��
      float4 prm_pos2    : POSITION2,      // ���f���̃��[�t�^�[�Q�b�g2���_
      float3 prm_normal2 : NORMAL2,        // ���f���̃��[�t�^�[�Q�b�g2���_�̖@��
      float4 prm_pos3    : POSITION3,      // ���f���̃��[�t�^�[�Q�b�g3���_
      float3 prm_normal3 : NORMAL3         // ���f���̃��[�t�^�[�Q�b�g3���_�̖@��
) {
	OUT_VS out_vs = (OUT_VS)0;

	//���_�u�����h���ϊ�
	float4 pos = lerp(prm_pos0, prm_pos1, g_weight1 );
	pos = lerp(pos, prm_pos2, g_weight2);
	pos = lerp(pos, prm_pos3, g_weight3);
	float4 posWorld = mul( pos, g_matWorld );                   // World�ϊ�
	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = posWorldViewProj;                              // �o�͂ɐݒ�
    //�@���u�����h���ϊ�
	float3 normal = lerp(prm_normal0, prm_normal1, g_weight1 );
	normal = lerp(normal, prm_normal2, g_weight2);
	normal = lerp(normal, prm_normal3, g_weight3);
	out_vs.normal = normalize(mul(normal, g_matWorld)); 	    //�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv0;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultMorphMesh(
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

technique DefaultMorphMeshTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	//�y�l�������v�f�z
	//--- VS ---
	//�E���_�� World�AView�A�ˉe �ϊ�
	//�E�@���� World�ϊ�
	//--- PS ---
	//�EDiffuse���C�g�F(���F�͖���)
	//�EAmbient���C�g�F(���F�͖���)
	//�E���s�����C�g����
	//�E�������C�g
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
	//�E�I�u�W�F�N�g�̃e�N�X�`��
	//�E�I�u�W�F�N�g�̃}�e���A�����������iDiffuse���˃��ƃe�N�X�`�����̏�Z�j
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
	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh0();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	pass P1 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh1();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	pass P2 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh2();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

	pass P3 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMorphMesh3();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMorphMesh();
	}

}

