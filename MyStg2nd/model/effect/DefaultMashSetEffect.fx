////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshSetModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


int g_nVertexs;

float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;

float4x4 g_matView;   //View�ϊ��s��
float4x4 g_matProj;   //�ˉe�ϊ��s��

float3 g_LightDirection; // ���C�g�̕���
float4 g_LightAmbient;   // Ambien���C�g�F�i���ːF�j
float4 g_LightDiffuse;   // Diffuse���C�g�F�i���ːF�j

float4 g_MaterialDiffuse001;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse002;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse003;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse004;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse005;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse006;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse007;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF
float4 g_MaterialDiffuse008;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

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
	float4 col    : COLOR0;
	float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
};


///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultMeshSet(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,    // ���f���̒��_�ԍ�
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0     // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float4 colorMaterialDiffuse;  //�}�e���A����Diffuse���ːF�ƁAAmbien���ːF

	if (index == 0) {
		matWorld = g_matWorld001;
		colorMaterialDiffuse = g_MaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colorMaterialDiffuse = g_MaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colorMaterialDiffuse = g_MaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colorMaterialDiffuse = g_MaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colorMaterialDiffuse = g_MaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colorMaterialDiffuse = g_MaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colorMaterialDiffuse = g_MaterialDiffuse007;
	} else {
		matWorld = g_matWorld008;
		colorMaterialDiffuse = g_MaterialDiffuse008;
	} 

//	float4 posWorld = mul( prm_pos, matWorld );               // World�ϊ�
//	float4 posWorldView = mul(posWorld, g_matView );            // View�ϊ�
//	float4 posWorldViewProj = mul( posWorldView, g_matProj);    // �ˉe�ϊ�
	out_vs.pos = mul( mul(mul( prm_pos, matWorld ), g_matView ), g_matProj); //World*View*�ˉe�ϊ�
    //�@���v�Z
    out_vs.normal = normalize(mul(prm_normal, matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	out_vs.col = colorMaterialDiffuse;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultMeshSet(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_col    : COLOR0
) : COLOR  {
	//���߂�F
	float4 out_color; 
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(prm_normal, -g_LightDirection ), 0);          
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B              
	out_color =  g_LightDiffuse * prm_col * tex_color * power; 
	//Ambient�F�����Z�B�{�V�F�[�_�[�ł̓}�e���A����Ambien���ːF�́A�}�e���A����Diffuse���ːF�Ɠ����F�Ƃ���B
	out_color =  (g_LightAmbient * prm_col * tex_color) + out_color;  
	//���v�Z�A���͖@������у��C�g�����Ɉˑ����Ȃ��Ƃ���̂ŕʌv�Z�B�Œ�̓��C�g���F���l�����邪�A�{�V�F�[�_�[�̓��C�g���͖����B
	out_color.a = prm_col.a * tex_color.a ;    // tex_color.a �̓}�e���A�������e�N�X�`����

	return out_color;
}

float4 GgafDx9PS_DefaultMeshSet2(
	float2 prm_uv	  : TEXCOORD0,
	float3 prm_normal : TEXCOORD1,
	float4 prm_col    : COLOR0
) : COLOR  {
	//���߂�F
	float4 out_color; 
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);                
	//���C�g�����A���C�g�F�A�}�e���A���F�A�e�N�X�`���F���l�������F�쐬�B              
	out_color =  g_LightDiffuse * prm_col * tex_color; 
	//���v�Z�A���͖@������у��C�g�����Ɉˑ����Ȃ��Ƃ���̂ŕʌv�Z�B�Œ�̓��C�g���F���l�����邪�A�{�V�F�[�_�[�̓��C�g���͖����B
	out_color.a = prm_col.a * tex_color.a ;    // tex_color.a �̓}�e���A�������e�N�X�`����

	return out_color;
}

technique DefaultMeshSetTechnique
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
	//�E�I�u�W�F�N�g�̃}�e���A����Diffuse���ˁi�F��Ambient���˂Ƌ��ʁj
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

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMeshSet();
	}
}


technique DefaultMeshSetTechnique2
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;

		VertexShader = compile vs_2_0 GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_DefaultMeshSet2();
	}
}

