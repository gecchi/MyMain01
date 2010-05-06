////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshSetModel�p�V�F�[�_�[
// �y�T�v�z
// ���_�o�b�t�@�ɁA�������f���L�����̒��_��񂪁A�������J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� DrawIndexedPrimitive�ŁA�ő�
// �P�Q�I�u�W�F�N�g�܂ŕ`��B��������_���B
// ��ʂ̓����G��e�ɂ́A���̃V�F�[�_�[�ŕ`�悷�邱�ƂƂ���B
// �A���A�P�I�u�W�F�N�g�ɂ��}�e���A���ݒ�͂P�����Ƃ�������������B
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


int g_nVertexs;
float g_zf;
float g_PowerBlink;   
float g_BlinkThreshold;
float g_MasterAlpha;

// ���C�g�̕���
float3 g_LightDirection;
// Ambien���C�g�F�i���ːF�j
float4 g_LightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_LightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  
//���[���h�ϊ��s��
float4x4 g_matWorld001;
float4x4 g_matWorld002;
float4x4 g_matWorld003;
float4x4 g_matWorld004;
float4x4 g_matWorld005;
float4x4 g_matWorld006;
float4x4 g_matWorld007;
float4x4 g_matWorld008;
float4x4 g_matWorld009;
float4x4 g_matWorld010;
float4x4 g_matWorld011;
float4x4 g_matWorld012;
float4x4 g_matWorld013;
float4x4 g_matWorld014;
float4x4 g_matWorld015;
float4x4 g_matWorld016;
//�I�u�W�F�N�g�̃}�e���A���F�iDiffuse���ːF�ƁAAmbien���ːF���ʁj
float4 g_MaterialDiffuse001;
float4 g_MaterialDiffuse002;
float4 g_MaterialDiffuse003;
float4 g_MaterialDiffuse004;
float4 g_MaterialDiffuse005;
float4 g_MaterialDiffuse006;
float4 g_MaterialDiffuse007;
float4 g_MaterialDiffuse008;
float4 g_MaterialDiffuse009;
float4 g_MaterialDiffuse010;
float4 g_MaterialDiffuse011;
float4 g_MaterialDiffuse012;
float4 g_MaterialDiffuse013;
float4 g_MaterialDiffuse014;
float4 g_MaterialDiffuse015;
float4 g_MaterialDiffuse016;

float g_offsetU001;
float g_offsetU002;
float g_offsetU003;
float g_offsetU004;
float g_offsetU005;
float g_offsetU006;
float g_offsetU007;
float g_offsetU008;
float g_offsetU009;
float g_offsetU010;
float g_offsetU011;
float g_offsetU012;
float g_offsetU013;
float g_offsetU014;
float g_offsetU015;
float g_offsetU016;

float g_offsetV001;
float g_offsetV002;
float g_offsetV003;
float g_offsetV004;
float g_offsetV005;
float g_offsetV006;
float g_offsetV007;
float g_offsetV008;
float g_offsetV009;
float g_offsetV010;
float g_offsetV011;
float g_offsetV012;
float g_offsetV013;
float g_offsetV014;
float g_offsetV015;
float g_offsetV016;

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDx9VS_SpriteMeshSet(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float offsetU;
	float offsetV;
	float4 colorMaterialDiffuse;

	if (index == 0) {
		matWorld = g_matWorld001;
		colorMaterialDiffuse = g_MaterialDiffuse001;
		offsetU  = g_offsetU001;
		offsetV  = g_offsetV001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colorMaterialDiffuse = g_MaterialDiffuse002;
		offsetU  = g_offsetU002;
		offsetV  = g_offsetV002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colorMaterialDiffuse = g_MaterialDiffuse003;
		offsetU  = g_offsetU003;
		offsetV  = g_offsetV003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colorMaterialDiffuse = g_MaterialDiffuse004;
		offsetU  = g_offsetU004;
		offsetV  = g_offsetV004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colorMaterialDiffuse = g_MaterialDiffuse005;
		offsetU  = g_offsetU005;
		offsetV  = g_offsetV005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colorMaterialDiffuse = g_MaterialDiffuse006;
		offsetU  = g_offsetU006;
		offsetV  = g_offsetV006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colorMaterialDiffuse = g_MaterialDiffuse007;
		offsetU  = g_offsetU007;
		offsetV  = g_offsetV007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		colorMaterialDiffuse = g_MaterialDiffuse008;
		offsetU  = g_offsetU008;
		offsetV  = g_offsetV008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		colorMaterialDiffuse = g_MaterialDiffuse009;
		offsetU  = g_offsetU009;
		offsetV  = g_offsetV009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		colorMaterialDiffuse = g_MaterialDiffuse010;
		offsetU  = g_offsetU010;
		offsetV  = g_offsetV010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		colorMaterialDiffuse = g_MaterialDiffuse011;
		offsetU  = g_offsetU011;
		offsetV  = g_offsetV011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		colorMaterialDiffuse = g_MaterialDiffuse012;
		offsetU  = g_offsetU012;
		offsetV  = g_offsetV012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		colorMaterialDiffuse = g_MaterialDiffuse013;
		offsetU  = g_offsetU013;
		offsetV  = g_offsetV013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		colorMaterialDiffuse = g_MaterialDiffuse014;
		offsetU  = g_offsetU014;
		offsetV  = g_offsetV014;
	} else if (index == 14) {
		matWorld = g_matWorld015;
		colorMaterialDiffuse = g_MaterialDiffuse015;
		offsetU  = g_offsetU015;
		offsetV  = g_offsetV015;
	} else {
		matWorld = g_matWorld016;
		colorMaterialDiffuse = g_MaterialDiffuse016;
		offsetU  = g_offsetU016;
		offsetV  = g_offsetV016;
	}
	//World*View*�ˉe�ϊ�
	out_vs.pos = mul(mul(mul( prm_pos, matWorld ), g_matView ), g_matProj);
    //�@���v�Z
    out_vs.normal = normalize(mul(prm_normal, matWorld)); 	//�@���� World �ϊ����Đ��K��
	//UV�͂��̂܂�
	out_vs.uv.x = prm_uv.x + offsetU;
	out_vs.uv.y = prm_uv.y + offsetV;
    //���_�J���[�v�Z

	//�@���� World �ϊ����Đ��K��
    float3 normal = normalize(mul(prm_normal, matWorld)); 	
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(normal, -g_LightDirection ), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g�����A�}�e���A���F ���l�������J���[�쐬�B      
	out_vs.col = (g_LightAmbient + (g_LightDiffuse*power)) * colorMaterialDiffuse;
	//���t�H�O
	out_vs.col.a = colorMaterialDiffuse.a;
	if (out_vs.pos.z > g_zf*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/(g_zf*0.5)*out_vs.pos.z + 2.0);
	} 
//	if (out_vs.pos.z > g_zf*0.75) { //�ŉ��� 3/4 ��艜�̏ꍇ���X�ɓ�����
//    	out_vs.col.a *= (-1.0/(g_zf*0.25)*out_vs.pos.z + 4.0);
//	}
	//�}�X�^�[��
	out_vs.col.a *= g_MasterAlpha;
	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_SpriteMeshSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col;

    //Blinker���l��
	if (tex_color.r >= g_BlinkThreshold || tex_color.g >= g_BlinkThreshold || tex_color.b >= g_BlinkThreshold) {
		out_color *= g_PowerBlink; //+ (tex_color * g_PowerBlink);
	} 
	return out_color;
}

float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_col    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);
	return out_color;
}

technique SpriteMeshSetTechnique
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
		VertexShader = compile vs_2_0 GgafDx9VS_SpriteMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_SpriteMeshSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile vs_2_0 GgafDx9VS_SpriteMeshSet();
		PixelShader  = compile ps_2_0 GgafDx9PS_SpriteMeshSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile vs_2_0 GgafDx9VS_SpriteMeshSet();
		PixelShader  = compile ps_2_0 PS_Flush();
	}
}
