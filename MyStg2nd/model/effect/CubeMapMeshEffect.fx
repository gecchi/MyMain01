#include "GgafEffectConst.fx" 
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */

//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam;
float g_specular;
float g_specular_power;


/** �J������World�ʒu */
float3 pos_camera; 

/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;
/** ���C�g�̕��� */
float3 g_vecLightDirection;
/** �����F�i���ːF�j*/
float4 g_colLightAmbient;
/** �g�U���F�i���ːF�j*/
float4 g_colLightDiffuse;
/** ���f���̃}�e���A���F�i�\�ʐF�j�B������g�U�����ːF�Ŋ������ːF�����˂� */
float4 g_colMaterialDiffuse;
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDx9TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;   
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDx9TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �A���t�@�J�[�e��(�t�F�[�h�C���E�A�E�g)�@�\(GgafDx9AlphaCurtain�Q��)�̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {                   
    float4 pos   : POSITION;      
    float3 normal: TEXCOORD0;    	// ���[���h��Ԃ̖@��
    float3 viewVecW: TEXCOORD1;  	// ���[���h��Ԃł̎����x�N�g��
    float4 col : COLOR0;
};  
/**
 * �W���I�Ȓ��_�V�F�[�_�[ .
 * ���_�o�b�t�@�ɂ́A
 * ���_�� World > View > �ˉe �ϊ����A���_�J���[�̐ݒ���s���Ă���B
 * ���f���̃}�e���A���F�t�A�܂�
 * �g�U���F�A�g�U�����ːF�A�����F�A�}�X�^�[�A���t�@�A�t�H�O�A��
 * ���x�d���̂��߃s�N�Z���V�F�[�_�[�ōs�킸�A���_�J���[�Ŏ������Ă���B
 * @param prm_pos    ���f�����_�̃��[�J�����W
 * @param prm_normal ���f�����_�̖@��
 * @param prm_normal ���f�����_��UV���W
 */
OUT_VS GgafDx9VS_CubeMapMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL   
) {
	OUT_VS out_vs = (OUT_VS)0;
	//���_�v�Z
	out_vs.pos = mul(prm_pos, g_matWorld);  //World
    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
	float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
	//�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
	out_vs.col = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse * float4(2.0, 2.0, 2.0, 1.0); //�S�̓I�ɖ��邭����;
    //���t�H�O
	out_vs.col.a = g_colMaterialDiffuse.a;
	if (out_vs.pos.z > (g_zf*0.9)*0.5) { // �ŉ��� 1/2 ��艜�̏ꍇ���X�ɓ�����
    	out_vs.col.a *= (-1.0/((g_zf*0.9)*0.5)*out_vs.pos.z + 2.0);
	} 
	//�}�X�^�[��
	out_vs.col.a *= g_alpha_master;

	return out_vs;
}

/**
 * �ʏ�s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
 */
float4 GgafDx9PS_CubeMapMesh(
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_col    : COLOR0
) : COLOR  {
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_col;
    //Blinker���l��
	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
		out_color.rgb *= g_tex_blink_power; //+ (tex_color * g_tex_blink_power);
	} 
    return out_color;
}

float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_col    : COLOR0
) : COLOR  {                         
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_col * float4(7.0, 7.0, 7.0, 1.0);;
	return out_color;
}


/**
 * �ʏ�e�N�j�b�N
 */
technique CubeMapMeshTechnique
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDx9PS_CubeMapMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDx9VS_CubeMapMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

