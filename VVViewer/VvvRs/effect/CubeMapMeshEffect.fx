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
sampler BumpMapTextureSampler : register(s2);  

/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 pos    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color  : COLOR0;
    float3 normal : TEXCOORD1;   // ���[���h�ϊ������@��
    float3 cam    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};

struct OUT_VS_BM {
    float4 pos    : POSITION;    //���W
    float2 uv     : TEXCOORD0;   //�e�N�X�`��UV
    float4 color  : COLOR0;      //���_�J���[
    float3 normal : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
    float3 camTangentDirect    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
	float4 lightTangentDirect : TEXCOORD3;
	float4 harfTangentDirect : TEXCOORD4;

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
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
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

    out_color.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master; 
	return out_color;
}

float4x4 InvTangentMatrix(
	float3 prm_tangent,
	float3 prm_binormal,
	float3 prm_normal )
{
	float4x4 mat = { float4(prm_tangent , 0.0f), 
                     float4(prm_binormal, 0.0f), 
                     float4(prm_normal  , 0.0f)  , 
                     {  0.0f, 0.0f, 0.0f, 1.0f } };
	return transpose( mat );  // �]�u(�搳�K�����n�̍s��̋t�s��͓]�u�s��ŗǂ�����)
}


OUT_VS_BM GgafDxVS_BumpMapping(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0,
      float3 prm_tangent  : TEXCOORD1,
      float3 prm_binormal : TEXCOORD2  
) {
 	OUT_VS_BM out_vs = (OUT_VS_BM)0;

	//���_�v�Z
    float4 posWorld = mul(prm_pos, g_matWorld);
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe
    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�

	// �ڋ�ԍs��̋t�s����Z�o
	float4x4 invTangentMat = InvTangentMatrix(prm_tangent, prm_binormal, prm_normal );
	// ���C�g�x�N�g����ڋ�ԂɈڂ�
	out_vs.lightTangentDirect = mul( -g_vecLightDirection, invTangentMat );

        //�u���_���J�������_�v�����x�N�g���i�X�y�L�����Ŏg�p�j                                                        
    float3 cam = normalize(g_posCam.xyz - posWorld.xyz);
    out_vs.camTangentDirect  =  mul(cam, invTangentMat );

    if (g_specular_power != 0) {

        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(cam + (-g_vecLightDirection));
        //�n�[�t�x�N�g����ڋ�ԂɈڂ�
        out_vs.harfTangentDirect =  mul(vecHarf, invTangentMat );
    }






//    //���_�J���[�v�Z
//    //�@���� World �ϊ����Đ��K��
//    out_vs.normal = normalize(mul(prm_normal, g_matWorld));     
//    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U���̌����������߂�B
//    float power = max(dot(out_vs.normal, -g_vecLightDirection ), 0);      
//    //�g�U���F�Ɍ��������悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
//    out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * g_colMaterialDiffuse;
//    //�u���_���J�������_�v�����x�N�g��                                                        
//    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);

    out_vs.color = g_colMaterialDiffuse;
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;
    //���t�H�O
    if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
        out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
    }
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
	return out_vs;
}


float4 GgafDxPS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 inCamTangentDirect    : TEXCOORD2,   //�ڋ�ԍ��W�n�ɕϊ����ꂽ���_ -> ���_ �x�N�g��
    float3 inLightTangentDirect : TEXCOORD3,  //�ڋ�ԍ��W�n�ɕϊ����ꂽ�g�U�������x�N�g��
    float3 inHarfTangentDirect : TEXCOORD4     //�ڋ�ԍ��W�n�ɕϊ����ꂽ�n�[�t�x�N�g��
) : COLOR  {
    float a = prm_color.a; //���ێ�

	float3 normalVec = 2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz-1.0; //�@���}�b�v����̖@��
	normalVec = normalize( normalVec );//�@�����K��
    //�@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@���ɂȂ�j�ƁA
    //�g�U�������x�N�g��(���_�V�F�[�_�[�Őڋ�ԍ��W�n�ɗ\�ߕϊ��ς�) �̓��ς���
    //���C�g���ˊp�����߁A�ʂɑ΂���g�U���̌�����(power)�����߂�
    float power = max(dot(normalVec, normalize(inLightTangentDirect) ), 0); 

	float4 colTexCube = texCUBE(CubeMapTextureSampler, reflect(-inCamTangentDirect, normalVec));
    float4 colTex2D   = tex2D( MyTextureSampler, prm_uv);


    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g����
        //�ڋ�ԍ��W�n�ɗ\�ߕϊ��ς݁j�Ɩ@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@��)�̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(normalVec, inHarfTangentDirect)), g_specular ) * g_specular_power;
    }



//    float s = 0.0f; //�X�y�L��������
//    if (g_specular_power != 0) {
//        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
//        float3 vecHarf = normalize(prm_cam + (-g_vecLightDirection));
//        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
//        s = pow( max(0.0f, dot(prm_normal, vecHarf)), g_specular ) * g_specular_power;
//    }
    float4 out_color = colTex2D * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * prm_color ) + (colTexCube*g_reflectance) +s; //prm_color == g_colMaterialDiffuse

    //float4 out_color = (colTex2D * prm_color) + (colTexCube*g_reflectance) + s;
    //Blinker���l��
	if (colTex2D.r >= g_tex_blink_threshold || colTex2D.g >= g_tex_blink_threshold || colTex2D.b >= g_tex_blink_threshold) {
		out_color *= g_tex_blink_power; //+ (colTex2D * g_tex_blink_power);
	} 

    out_color.a = prm_color.a * colTex2D.a * colTexCube.a * g_alpha_master; 
	return out_color;
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
    out_color.a *= g_alpha_master;
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
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique BumpMapping
{
	//pass P0�u���b�V���W���V�F�[�_�[�v
	//���b�V����`�悷��
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_BumpMapping();
		PixelShader  = compile PS_VERSION GgafDxPS_BumpMapping();
	}
}


technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION GgafDxPS_CubeMapMesh();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_CubeMapMesh();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}

