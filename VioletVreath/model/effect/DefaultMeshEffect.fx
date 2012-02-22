#include "GgafEffectConst.fxh" 
/**
 * GgafDxMeshModel�p�V�F�[�_�[ .
 * �ÓI���f���P��`�悷��W���I�V�F�[�_�[�B
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

float g_far_rate;
/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
    


//float  g_specular = 5.0f;       //�X�y�L�����[�͈̔�
//float  g_specular_power = 1.0f;  //�X�y�L�����[�̋��x




/** ���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS {
    float4 pos : POSITION;
    float2 uv  : TEXCOORD0;
    float4 color : COLOR0;
    float3 normal   : TEXCOORD1;   //�I�u�W�F�N�g�̖@���x�N�g��
    float3 cam  : TEXCOORD2;   //���_ -> ���_ �x�N�g��

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
OUT_VS GgafDxVS_DefaultMesh(
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

    if (g_far_rate > 0.0) {
        if (out_vs.pos.z > g_zf*g_far_rate) {   
            out_vs.pos.z = g_zf*g_far_rate; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
        }
    } else {
        //���t�H�O
        if (out_vs.pos.z > 0.6*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
            out_vs.color.a *= (-3.0*(out_vs.pos.z/g_zf) + 3.0);
        }
    }
    //�}�X�^�[��
    out_vs.color.a *= g_alpha_master;
//    if (out_vs.pos.z > g_zf*0.98) {   
//        out_vs.pos.z = g_zf*0.98; //�{������O��Z�ł��A�`����������邽��0.9�ȓ��ɏ㏑���A
//    }
    return out_vs;
}

/**
 * �ʏ�s�N�Z���V�F�[�_�[
 */
float4 GgafDxPS_DefaultMesh(
    float2 prm_uv     : TEXCOORD0,
    float4 prm_color    : COLOR0,
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

float4 PS_Flush( 
    float2 prm_uv  : TEXCOORD0,
    float4 prm_color : COLOR0
) : COLOR  {                         
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    float4 tex_color = tex2D( MyTextureSampler, prm_uv);        
    float4 out_color = tex_color * prm_color * FLUSH_COLOR;
    out_color.a *= g_alpha_master;
    return out_color;
}


/**
 * �ʏ�e�N�j�b�N
 */
technique DefaultMeshTechnique
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION GgafDxPS_DefaultMesh();
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
        VertexShader = compile VS_VERSION GgafDxVS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

