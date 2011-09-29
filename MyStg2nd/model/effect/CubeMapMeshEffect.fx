#include "GgafEffectConst.fxh" 
/**
 * @author Masatoshi Tsuge
 * @since 2010/12/21
 */
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam;
float g_reflectance;
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
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDxTextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;   
/** ���f���̃e�N�X�`���_�ŋ@�\(GgafDxTextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �A���t�@�J�[�e��(�t�F�[�h�C���E�A�E�g)�@�\(GgafDxAlphaCurtain�Q��)�̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
sampler CubeMapTextureSampler : register(s1);
/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color  : COLOR0;
    float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 cam    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
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
OUT_VS GgafDxVS_CubeMapMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
 	OUT_VS out_vs = (OUT_VS)0;

	//���_�v�Z
    float4 posWorld = mul(prm_pos, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�
    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.normal = normalize(mul(prm_normal, g_matWorld));     
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
    //�u���_���J�������_�v�����x�N�g��                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
    //�}�X�^�[��
    out_vs.color.a *= g_alpha_master;
	return out_vs;


//	OUT_VS out_vs = (OUT_VS)0;
//	//���_�v�Z
//	out_vs.pos = mul(prm_pos, g_matWorld);  //World
//    out_vs.viewVecW = out_vs.pos.xyz - pos_camera;
//	out_vs.pos = mul( mul(out_vs.pos , g_matView), g_matProj);  //View*�ˉe�ϊ�
//    out_vs.normal = normalize(mul(prm_normal, g_matWorld)); 
//    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
//	float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
//	//�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
//	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse * float4(2.0, 2.0, 2.0, 1.0); //�S�̓I�ɖ��邭����;
//    //���t�H�O
//	out_vs.color.a = g_colMaterialDiffuse.a;
//    if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
//        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
//    }
//	//�}�X�^�[��
//	out_vs.color.a *= g_alpha_master;
//
//	return out_vs;
}

/**
 * �ʏ�s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
 */
float4 GgafDxPS_CubeMapMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2   //���_ -> ���_ �x�N�g��
) : COLOR  {
	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-prm_cam, prm_normal));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
    }

    float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinker���l��
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a; 
	return out_color;




//	float3 vReflect = reflect( prm_viewVecW, prm_normal );
//    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
//	float4 out_color = tex_color * prm_color;
//    //Blinker���l��
//	if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
//		out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
//	} 
//    return out_color;
}

float4 PS_Flush( 
     float3 prm_normal: TEXCOORD0,
	 float3 prm_viewVecW: TEXCOORD1,
     float4 prm_color    : COLOR0
) : COLOR  {                         
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	float3 vReflect = reflect( prm_viewVecW, prm_normal );
    float4 tex_color = texCUBE(MyTextureSampler, vReflect);
	float4 out_color = tex_color * prm_color * FLUSH_COLOR;
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
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

