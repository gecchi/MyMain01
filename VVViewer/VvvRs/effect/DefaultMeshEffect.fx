#include "GgafEffectConst.fxh" 
/**
 * GgafLib::DefaultMeshActor �p�V�F�[�_�[ .
 * �ÓI���f���P��`�悷��W���I�ȃV�F�[�_�[�B
 * ���_�o�b�t�@�t�H�[�}�b�g��
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
 * ���A�O��Ƃ���B
 * @author Masatoshi Tsuge
 * @since 2009/03/06 
 */

/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;
/** ���C�g�̕����x�N�g���i���K���ς݁j */
float3 g_vecLightDirection;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam;
/** �����̐F */
float4 g_colLightAmbient;
/** ���C�g�̐F(���C�g�̊g�U���ˎ��̃��C�g���g�̐F) */
float4 g_colLightDiffuse;
/** ���f���̃}�e���A���F(���C�g�ɂ��g�U���ˎ��̃��f���̐F) */
float4 g_colMaterialDiffuse;
/** �X�y�L�����[�͈̔́i�n�[�t�x�N�g���E�@�����ς�g_specular��j */
float g_specular;
/** �X�y�L�����[�̋��x */
float g_specular_power;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDxTextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;   
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDxTextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �t�F�[�h�C���E�A�E�g�@�\(GgafDxAlphaCurtain�Q��)�̂��߂̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** -1.0 or 0.999 �B�����ł��\���������������ꍇ��0.999 ����������B*/ 
float g_far_rate;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
sampler BumpMapTextureSampler : register(s2);  
/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 pos    : POSITION;    //���W
    float2 uv     : TEXCOORD0;   //�e�N�X�`��UV
    float4 color  : COLOR0;      //���_�J���[
    float3 normal : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
    float3 cam    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
};    
/** ���_�V�F�[�_�[�A�o�͍\����(�o���v�}�b�s���O�p) */
struct OUT_VS_BM {
    float4 pos    : POSITION;    //���W
    float2 uv     : TEXCOORD0;   //�e�N�X�`��UV
    float4 color  : COLOR0;      //���_�J���[
    float3 normal : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
    float3 cam    : TEXCOORD2;   //���_ -> ���_ �x�N�g��
	float4 lightTangentDirect : TEXCOORD3;
	float4 harfTangentDirect : TEXCOORD4;

};

/**
 * ���[�J�����ڋ�ԕϊ� �s���Ԃ� .
 * �ڋ�ԂƂ̓��b�V���T�[�t�F�C�X��̂���_�ɂ����āA
 * �e�N�X�`��u�����x�N�g��, �e�N�X�`��v�����x�N�g��, �@���x�N�g�� ��
 * �R���ŕ\���������W�n�̎��B�R���͒������Ă���B
 * @param prm_tangent  �ڃx�N�g��(u�����P�ʃx�N�g��)
 * @param prm_binormal �]�@���x�N�g��(v�����P�ʃx�N�g��)
 * @param prm_normal   �@���x�N�g��
 **/
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


/**
 * GgafLib::DefaultMeshActor �p�̕W�����_�V�F�[�_�[ .
 * ���_�� World > View > �ˉe �ϊ�������A
 * ���f���̃}�e���A���F�t�𒸓_�J���[�̐ݒ�ōs���B
 * �}�e���A���F�t�Ƃ͋�̈ʓI��
 * �g�U���F�A�g�U�����ːF�A�����F�A�}�X�^�[�A���t�@�A�t�H�O�A�̎��B
 * @param prm_pos    ���_�̃��[�J�����W
 * @param prm_normal ���_�̖@��
 * @param prm_uv     ���_��UV���W
 */
OUT_VS GgafDxVS_DefaultMesh(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0 
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    float4 posWorld = mul(prm_pos, g_matWorld); //World�ϊ�
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
    //�u���_���J�������_�v�����x�N�g���i�X�y�L�����Ŏg�p�j                                                        
    out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;

    //�������̕\�����@�B
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //�}�X�^�[��
    out_vs.color.a *= g_alpha_master;

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor �p�̕W���s�N�Z���V�F�[�_�[ .
 * @param prm_uv     �s�N�Z���ł�UV���W
 * @param prm_color  �s�N�Z���ł̐F�i���_�J���[�ɂ��j
 * @param prm_normal �s�N�Z���ł̖@��
 * @param prm_cam    �s�N�Z���ł̍��W -> ���_ �x�N�g��
 */
float4 GgafDxPS_DefaultMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
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
    float4 out_color = tex_color * prm_color + s;
    //Blinker���l��
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    } 
    //�}�X�^�[��
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * GgafLib::DefaultMeshActor �p�̕W�����_�V�F�[�_�[ .
 * ���_�� World > View > �ˉe �ϊ�������A
 * ���f���̃}�e���A���F�t�𒸓_�J���[�̐ݒ�ōs���B
 * �}�e���A���F�t�Ƃ͋�̈ʓI��
 * �g�U���F�A�g�U�����ːF�A�����F�A�}�X�^�[�A���t�@�A�t�H�O�A�̎��B
 * @param prm_pos    ���_�̃��[�J�����W
 * @param prm_normal ���_�̖@��
 * @param prm_uv     ���_��UV���W
 * @param prm_tangent  �ڃx�N�g��(u�����P�ʃx�N�g��)
 * @param prm_binormal �]�@���x�N�g��(v�����P�ʃx�N�g��)
 */
OUT_VS_BM GgafDxVS_BumpMapping(
      float4 prm_pos    : POSITION, 
      float3 prm_normal : NORMAL,   
      float2 prm_uv     : TEXCOORD0,
      float3 prm_tangent  : TEXCOORD1,
      float3 prm_binormal : TEXCOORD2  
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //���_�v�Z
    float4 posWorld = mul(prm_pos, g_matWorld); //World�ϊ�
    out_vs.pos = mul( mul( posWorld, g_matView), g_matProj);  //World*View*�ˉe

    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�

	// �ڋ�ԍs��̋t�s����Z�o
	float4x4 invTangentMat = InvTangentMatrix(prm_tangent, prm_binormal, prm_normal );
	// ���C�g�x�N�g����ڋ�ԂɈڂ�
	out_vs.lightTangentDirect = mul( -g_vecLightDirection, invTangentMat );


    if (g_specular_power != 0) {
        //�u���_���J�������_�v�����x�N�g���i�X�y�L�����Ŏg�p�j                                                        
        out_vs.cam = normalize(g_posCam.xyz - posWorld.xyz);
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf = normalize(out_vs.cam + (-g_vecLightDirection));
        //�n�[�t�x�N�g����ڋ�ԂɈڂ�
        out_vs.harfTangentDirect =  mul(vecHarf, invTangentMat );
    }

    //���_�J���[�v�Z(�g�U���F,�}�e���A���F)
    out_vs.color = g_colMaterialDiffuse;


    //���̓}�e���A�������ŗD��Ƃ���i�㏑������j
    out_vs.color.a = g_colMaterialDiffuse.a;

    //�������̕\�����@�B
    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //�}�X�^�[��
    out_vs.color.a *= g_alpha_master;

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor �p�̕W���s�N�Z���V�F�[�_�[ .
 * @param prm_uv     �s�N�Z���ł�UV���W
 * @param prm_color  �s�N�Z���ł̐F�i���_�J���[�ɂ��j
 * @param prm_normal �s�N�Z���ł̖@��
 * @param prm_cam    �s�N�Z���ł̍��W -> ���_ �x�N�g��
 */
float4 GgafDxPS_BumpMapping(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color  : COLOR0,
    float3 prm_normal : TEXCOORD1,
    float3 prm_cam    : TEXCOORD2,   //���_ -> ���_ �x�N�g��
    float3 inLightTangentDirect : TEXCOORD3,  //�ڋ�ԍ��W�n�ɕϊ����ꂽ�g�U�������x�N�g��
    float3 inHarfTangentDirect : TEXCOORD4
) : COLOR  {
    float a = prm_color.a; //���ێ�

	float3 normalVec = 2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz-1.0; //�@���}�b�v����̖@��
	normalVec = normalize( normalVec );//�@�����K��
    //�@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@���ɂȂ�j�ƁA
    //�g�U�������x�N�g��(���_�V�F�[�_�[�Őڋ�ԍ��W�n�ɗ\�ߕϊ��ς�) �̓��ς���
    //���C�g���ˊp�����߁A�ʂɑ΂���g�U���̌�����(power)�����߂�
    float power = max(dot(normalVec, normalize(inLightTangentDirect) ), 0); 


    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g����
        //�ڋ�ԍ��W�n�ɗ\�ߕϊ��ς݁j�Ɩ@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@��)�̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(normalVec, inHarfTangentDirect)), g_specular ) * g_specular_power;
    }



    //�����F�A�e�N�X�`���F�A���_�J���[�A�������A�X�y�L���� ���l�������F�쐬  
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);
//tex_color * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * g_colMaterialDiffuse ) + s;
//tex�Emate�E(amb + (light�Ep))  + s

    float4 out_color = tex_color * ((g_colLightAmbient + ( g_colLightDiffuse * power)) * prm_color ) + s; //prm_color == g_colMaterialDiffuse
    //Blinker���l��
    if (tex_color.r >= g_tex_blink_threshold || tex_color.g >= g_tex_blink_threshold || tex_color.b >= g_tex_blink_threshold) {
        out_color *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    } 
    //�}�X�^�[��
    out_color.a = a * g_alpha_master;
    return out_color;
}

/**
 * GgafLib::DefaultMeshActor �p�̑M���s�N�Z���V�F�[�_�[ .
 * �e�N�X�`�����F�� FLUSH_COLOR �{���Đݒ�B
 * @param prm_uv     �s�N�Z���ł�UV���W
 * @param prm_color  �s�N�Z���ł̐F�i���_�J���[�ɂ��j
 */
float4 PS_Flush( 
    float2 prm_uv  : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {                         
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
    float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
    return out_color;
}

/**
 * �ʏ�e�N�j�b�N .
 */
technique DefaultMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default  
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

technique BumpMapping
{
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

/**
 * ���Z�����e�N�j�b�N .
 */
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
    }
}

/**
 * �M���e�N�j�b�N .
 */
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

