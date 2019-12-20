#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::SkinAniMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////

/** ���f����World�ϊ��s��i�t���[�����j */
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
float4x4 g_matWorld017;
float4x4 g_matWorld018;
float4x4 g_matWorld019;
float4x4 g_matWorld020;
float4x4 g_matWorld021;
float4x4 g_matWorld022;
float4x4 g_matWorld023;
float4x4 g_matWorld024;
float4x4 g_matWorld025;
float4x4 g_matWorld026;
float4x4 g_matWorld027;
float4x4 g_matWorld028;
float4x4 g_matWorld029;
float4x4 g_matWorld030;

/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** ���f���̎ˉe�ϊ��s�� */
float4x4 g_matProj;
/** ���C�g�̕����x�N�g���i���K���ς݁j */
float3 g_vecLightFrom_World;
/** �J�����i���_�j�̈ʒu�x�N�g�� */
float3 g_posCam_World;
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
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̓_�ŋ��x */
float g_tex_blink_power;
/** ���f���̃e�N�X�`���F�_�ŋ@�\(GgafDx::TextureBlinker�Q��)�̑ΏۂƂȂ�RGB�̂������l(0.0�`1.0) */
float g_tex_blink_threshold;
/** �t�F�[�h�C���E�A�E�g�@�\(GgafDx::AlphaCurtain�Q��)�̂��߂̃}�X�^�[�A���t�@�l(0.0�`1.0) */
float g_alpha_master;
/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** -1.0 or 0.999 �B�����ł��\���������������ꍇ��0.999 ����������B*/
float g_far_rate;

//s0���W�X�^�̃T���v�����g��(�Œ�p�C�v���C���ɃZ�b�g���ꂽ�e�N�X�`�����V�F�[�_�[�Ŏg��)
sampler MyTextureSampler : register(s0);

/** ���_�V�F�[�_�[�o�͍\���� */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ���)
    float2 uv              : TEXCOORD0;   //���_�e�N�X�`��UV
    float4 color           : COLOR0;      //���_�J���[
    float3 vecNormal_World : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World    : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
};
///////////////////////////////////////////////////////////////////////////

//���b�V���W�����_�V�F�[�_�[
OUT_VS VS_DefaultSkinAniMesh(
      float4 prm_posModel_Local    : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@��
      float  prm_index           : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float2 prm_uv     : TEXCOORD0      // ���f���̒��_��UV

) {
    OUT_VS out_vs = (OUT_VS)0;
    const int index = (int)prm_index;

    //���_�v�Z
    float4x4 matWorld;

    if (index == 0) {
        matWorld = g_matWorld001;
    } else if (index == 1) {
        matWorld = g_matWorld002;
    } else if (index == 2) {
        matWorld = g_matWorld003;
    } else if (index == 3) {
        matWorld = g_matWorld004;
    } else if (index == 4) {
        matWorld = g_matWorld005;
    } else if (index == 5) {
        matWorld = g_matWorld006;
    } else if (index == 6) {
        matWorld = g_matWorld007;
    } else if (index == 7) {
        matWorld = g_matWorld008;
    } else if (index == 8) {
        matWorld = g_matWorld009;
    } else if (index == 9) {
        matWorld = g_matWorld010;
    } else if (index == 10) {
        matWorld = g_matWorld011;
    } else if (index == 11) {
        matWorld = g_matWorld012;
    } else if (index == 12) {
        matWorld = g_matWorld013;
    } else if (index == 13) {
        matWorld = g_matWorld014;
    } else if (index == 14) {
        matWorld = g_matWorld015;
    } else if (index == 15) {
        matWorld = g_matWorld016;
    } else if (index == 16) {
        matWorld = g_matWorld017;
    } else if (index == 17) {
        matWorld = g_matWorld018;
    } else if (index == 18) {
        matWorld = g_matWorld019;
    } else if (index == 19) {
        matWorld = g_matWorld020;
    } else if (index == 20) {
        matWorld = g_matWorld021;
    } else if (index == 21) {
        matWorld = g_matWorld022;
    } else if (index == 22) {
        matWorld = g_matWorld023;
    } else if (index == 23) {
        matWorld = g_matWorld024;
    } else if (index == 24) {
        matWorld = g_matWorld025;
    } else if (index == 25) {
        matWorld = g_matWorld026;
    } else if (index == 26) {
        matWorld = g_matWorld027;
    } else if (index == 27) {
        matWorld = g_matWorld028;
    } else if (index == 28) {
        matWorld = g_matWorld029;
    } else { //if (index == 29) {
        matWorld = g_matWorld030;
    }
    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, matWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�͂��̂܂�
    out_vs.uv = prm_uv;

    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld));
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
    float refl_power = dot(vecNormal_World, -g_vecLightFrom_World);
    //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
    refl_power = refl_power * 0.5f + 0.5f;
    refl_power *= refl_power;
    //�g�U���F�ɔ��˗����悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color.rgb = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse.rgb;
    //���̓��C�g�Ɋ֌W�Ȃ��}�e���A������D��Ƃ���
    out_vs.color.a = g_colMaterialDiffuse.a;

    //�u���_���J�������_�v�����x�N�g���B�s�N�Z���V�F�[�_�[�̃X�y�L�����[�v�Z�Ŏg�p�B
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

    //�������̕\�����@�B
    if (g_far_rate > 0.0) {
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*g_far_rate; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        if (out_vs.posModel_Proj.z > 0.666f*g_zf) {   // �ŉ��̖� 2/3 ��肳��ɉ��̏ꍇ���X�ɓ�����
            //  z : 0.666*g_zf �` 1.0*g_zf  �� �� : 1.0 �` 0.0  �ƂȂ�悤�ɂ���ɂ�
            //  �� = ( (0.0-1.0)*z - (0.666*g_zf*0.0) + (1.0*1.0*g_zf) ) / (1.0*g_zf-0.666*g_zf)
            //  �� = (3.0*(g_zf-z))/g_zf = (3.0*g_zf - 3.0*z)/g_zf = 3.0 - 3.0*z/g_zf
            out_vs.color.a *= (-3.0*(out_vs.posModel_Proj.z/g_zf) + 3.0);
        }
    }
    return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 PS_DefaultSkinAniMesh(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0,
    float3 prm_vecNormal_World : TEXCOORD1,
    float3 prm_vecEye_World    : TEXCOORD2
) : COLOR  {
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    //�o�͐F�Ƀe�N�X�`���F�Ƀ}�e���A���J���[���l��
    float4 colOut = colTex * prm_color;
    //�X�y�L���������v�Z
    float s = 0.0f;
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        const float3 vecHarf = normalize(prm_vecEye_World + (-g_vecLightFrom_World));
        //�n�[�t�x�N�g���Ɩ@���̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(prm_vecNormal_World, vecHarf)), g_specular ) * g_specular_power;
    }
    //�o�͐F�ɃX�y�L�����[���l��
    colOut.rgb += s;
    //Blinker���l��
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    }
    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}

float4 PS_DefaultSkinAniMesh2(
    float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
    //�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color;

    //Blinker���l��
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //+ (colTex * g_tex_blink_power);
    }
    //�}�X�^�[��
    colOut.a *= g_alpha_master;
    return colOut;
}


technique DefaultSkinAniMeshTechnique
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
    // float3 g_vecLightFrom_World	:	���C�g�̕���
    // float4 g_colLightAmbient	:	Ambien���C�g�F�i���ːF�j
    // float4 g_colLightDiffuse	:	Diffuse���C�g�F�i���ːF�j
    // float4 g_colMaterialDiffuse	:	�}�e���A����Diffuse���ˁiAmbient���˂Ƌ��ʁj
    // s0���W�X�^				:	2D�e�N�X�`��
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSkinAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultSkinAniMesh();
    }
}

technique DefaultSkinAniMeshTechnique2
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultSkinAniMesh();
        PixelShader  = compile PS_VERSION PS_DefaultSkinAniMesh2();
    }
}


