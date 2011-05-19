#include "GgafEffectConst.fx" 
////////////////////////////////////////////////////////////////////////////////
// Ggaf���C�u�����AGgafDx9MeshSetModel�p�V�F�[�_�[
// �y�T�v�z
// ���_�o�b�t�@�ɁA�������f���L�����̒��_��񂪁A�������J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 16�I�u�W�F�N�g�܂ŕ`��B��������_���B
// ��ʂ̓����G��e�ɂ́A���̃V�F�[�_�[�ŕ`�悷�邱�ƂƂ���B
// �A���A�P�I�u�W�F�N�g�ɂ��}�e���A���ݒ�͂P�����Ƃ�������������B
// author : Masatoshi Tsuge
// date:2009/03/06 
////////////////////////////////////////////////////////////////////////////////


float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightDirection;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
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
//float4x4 g_matWorld016;
//�I�u�W�F�N�g�̃}�e���A���F�iDiffuse���ːF�ƁAAmbien���ːF���ʁj
float4 g_colMaterialDiffuse001;
float4 g_colMaterialDiffuse002;
float4 g_colMaterialDiffuse003;
float4 g_colMaterialDiffuse004;
float4 g_colMaterialDiffuse005;
float4 g_colMaterialDiffuse006;
float4 g_colMaterialDiffuse007;
float4 g_colMaterialDiffuse008;
float4 g_colMaterialDiffuse009;
float4 g_colMaterialDiffuse010;
float4 g_colMaterialDiffuse011;
float4 g_colMaterialDiffuse012;
float4 g_colMaterialDiffuse013;
float4 g_colMaterialDiffuse014;
float4 g_colMaterialDiffuse015;
//float4 g_colMaterialDiffuse016;


/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam;


//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 col    : COLOR0;

    float3 normal   : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
    float3 cam  : TEXCOORD2;   //���_ -> ���_ �x�N�g��


};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDx9VS_DefaultMeshSet(
      float4 prm_pos    : POSITION,      // ���f���̒��_
      float  prm_index  : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float3 prm_normal : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
	OUT_VS out_vs = (OUT_VS)0;
	int index = (int)prm_index;

	//���_�v�Z
	float4x4 matWorld;
	float4 colorMaterialDiffuse;

	if (index == 0) {
		matWorld = g_matWorld001;
		colorMaterialDiffuse = g_colMaterialDiffuse001;
	} else if (index == 1) {
		matWorld = g_matWorld002;
		colorMaterialDiffuse = g_colMaterialDiffuse002;
	} else if (index == 2) {
		matWorld = g_matWorld003;
		colorMaterialDiffuse = g_colMaterialDiffuse003;
	} else if (index == 3) {
		matWorld = g_matWorld004;
		colorMaterialDiffuse = g_colMaterialDiffuse004;
	} else if (index == 4) {
		matWorld = g_matWorld005;
		colorMaterialDiffuse = g_colMaterialDiffuse005;
	} else if (index == 5) {
		matWorld = g_matWorld006;
		colorMaterialDiffuse = g_colMaterialDiffuse006;
	} else if (index == 6) {
		matWorld = g_matWorld007;
		colorMaterialDiffuse = g_colMaterialDiffuse007;
	} else if (index == 7) {
		matWorld = g_matWorld008;
		colorMaterialDiffuse = g_colMaterialDiffuse008;
	} else if (index == 8) {
		matWorld = g_matWorld009;
		colorMaterialDiffuse = g_colMaterialDiffuse009;
	} else if (index == 9) {
		matWorld = g_matWorld010;
		colorMaterialDiffuse = g_colMaterialDiffuse010;
	} else if (index == 10) {
		matWorld = g_matWorld011;
		colorMaterialDiffuse = g_colMaterialDiffuse011;
	} else if (index == 11) {
		matWorld = g_matWorld012;
		colorMaterialDiffuse = g_colMaterialDiffuse012;
	} else if (index == 12) {
		matWorld = g_matWorld013;
		colorMaterialDiffuse = g_colMaterialDiffuse013;
	} else if (index == 13) {
		matWorld = g_matWorld014;
		colorMaterialDiffuse = g_colMaterialDiffuse014;
	} else { //if (index == 14) {
		matWorld = g_matWorld015;
		colorMaterialDiffuse = g_colMaterialDiffuse015;
	}


    //���_�v�Z
    float4 posWorld = mul(prm_pos, matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�

    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.normal = normalize(mul(prm_normal, matWorld));     
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power)) * colorMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.col.a = colorMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.pos.z > (g_zf*0.9)*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
        out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
    } 
    //�}�X�^�[��
    out_vs.col.a *= g_alpha_master;

    return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDx9PS_DefaultMeshSet(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_col    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
    //�e�N�X�`���F��        
    float4 out_color = tex_color * prm_col;

    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
	return out_color + s;
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

technique DefaultMeshSetTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMeshSet();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile PS_VERSION GgafDx9PS_DefaultMeshSet();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_DefaultMeshSet();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
