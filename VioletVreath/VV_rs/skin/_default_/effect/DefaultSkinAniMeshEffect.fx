#include "GgafEffectConst.fxh"
////////////////////////////////////////////////////////////////////////////////
// ggaf ���C�u�����AGgafDx::SkinAniMeshModel�p�V�F�[�_�[
//
// author : Masatoshi Tsuge
// date:2009/03/06
////////////////////////////////////////////////////////////////////////////////
#define _draw_combined_matrix_set_num (20)
/** ���f����World�ϊ��s��i�t���[�����j */
float4x4 g_matBone001;
float4x4 g_matBone002;
float4x4 g_matBone003;
float4x4 g_matBone004;
float4x4 g_matBone005;
float4x4 g_matBone006;
float4x4 g_matBone007;
float4x4 g_matBone008;
float4x4 g_matBone009;
float4x4 g_matBone010;
//float4x4 g_matBone011;
//float4x4 g_matBone012;
//float4x4 g_matBone013;
//float4x4 g_matBone014;
//float4x4 g_matBone015;
//float4x4 g_matBone016;
//float4x4 g_matBone017;
//float4x4 g_matBone018;
//float4x4 g_matBone019;
//float4x4 g_matBone020;
//float4x4 g_matBone021;
//float4x4 g_matBone022;
//float4x4 g_matBone023;
//float4x4 g_matBone024;
//float4x4 g_matBone025;
//float4x4 g_matBone026;
//float4x4 g_matBone027;
//float4x4 g_matBone028;
//float4x4 g_matBone029;
//float4x4 g_matBone030;
//float4x4 g_matBone031;
//float4x4 g_matBone032;
//float4x4 g_matBone033;
//float4x4 g_matBone034;
//float4x4 g_matBone035;
//float4x4 g_matBone036;
//float4x4 g_matBone037;
//float4x4 g_matBone038;
//float4x4 g_matBone039;
//float4x4 g_matBone040;
//float4x4 g_matBone041;
//float4x4 g_matBone042;
//float4x4 g_matBone043;
//float4x4 g_matBone044;
//float4x4 g_matBone045;
//float4x4 g_matBone046;
//float4x4 g_matBone047;
//float4x4 g_matBone048;
//float4x4 g_matBone049;
//float4x4 g_matBone050;

//float4x4 g_matBoneOffset001;
//float4x4 g_matBoneOffset002;
//float4x4 g_matBoneOffset003;
//float4x4 g_matBoneOffset004;
//float4x4 g_matBoneOffset005;
//float4x4 g_matBoneOffset006;
//float4x4 g_matBoneOffset007;
//float4x4 g_matBoneOffset008;
//float4x4 g_matBoneOffset009;
//float4x4 g_matBoneOffset010;
//float4x4 g_matBoneOffset011;
//float4x4 g_matBoneOffset012;
//float4x4 g_matBoneOffset013;
//float4x4 g_matBoneOffset014;
//float4x4 g_matBoneOffset015;
//float4x4 g_matBoneOffset016;
//float4x4 g_matBoneOffset017;
//float4x4 g_matBoneOffset018;
//float4x4 g_matBoneOffset019;
//float4x4 g_matBoneOffset020;
//float4x4 g_matBoneOffset021;
//float4x4 g_matBoneOffset022;
//float4x4 g_matBoneOffset023;
//float4x4 g_matBoneOffset024;
//float4x4 g_matBoneOffset025;
//float4x4 g_matBoneOffset026;
//float4x4 g_matBoneOffset027;
//float4x4 g_matBoneOffset028;
//float4x4 g_matBoneOffset029;
//float4x4 g_matBoneOffset030;
//float4x4 g_matBoneOffset031;
//float4x4 g_matBoneOffset032;
//float4x4 g_matBoneOffset033;
//float4x4 g_matBoneOffset034;
//float4x4 g_matBoneOffset035;
//float4x4 g_matBoneOffset036;
//float4x4 g_matBoneOffset037;
//float4x4 g_matBoneOffset038;
//float4x4 g_matBoneOffset039;
//float4x4 g_matBoneOffset040;
//float4x4 g_matBoneOffset041;
//float4x4 g_matBoneOffset042;
//float4x4 g_matBoneOffset043;
//float4x4 g_matBoneOffset044;
//float4x4 g_matBoneOffset045;
//float4x4 g_matBoneOffset046;
//float4x4 g_matBoneOffset047;
//float4x4 g_matBoneOffset048;
//float4x4 g_matBoneOffset049;
//float4x4 g_matBoneOffset050;


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



float4x4 getBoneWorldMatrix(int prm_infl_bone_id_order) {

    if (prm_infl_bone_id_order == 0) {
        return g_matBone001;
    }
    if (prm_infl_bone_id_order == 1) {
        return g_matBone002;
    }
    if (prm_infl_bone_id_order == 2) {
        return g_matBone003;
    }
    if (prm_infl_bone_id_order == 3) {
        return g_matBone004;
    }
    if (prm_infl_bone_id_order == 4) {
        return g_matBone005;
    }
    if (prm_infl_bone_id_order == 5) {
        return g_matBone006;
    }
    if (prm_infl_bone_id_order == 6) {
        return g_matBone007;
    }
    if (prm_infl_bone_id_order == 7) {
        return g_matBone008;
    }
    if (prm_infl_bone_id_order == 8) {
        return g_matBone009;
    }
//    if (prm_infl_bone_id_order == 9) {
        return g_matBone010;
//    }
//    if (prm_infl_bone_id_order == 10) {
//        return g_matBone011;
//    }
//    if (prm_infl_bone_id_order == 11) {
//        return g_matBone012;
//    }
//    if (prm_infl_bone_id_order == 12) {
//        return g_matBone013;
//    }
//    if (prm_infl_bone_id_order == 13) {
//        return g_matBone014;
//    }
//    if (prm_infl_bone_id_order == 14) {
//        return g_matBone015;
//    }
//    if (prm_infl_bone_id_order == 15) {
//        return g_matBone016;
//    }
//    if (prm_infl_bone_id_order == 16) {
//        return g_matBone017;
//    }
//    if (prm_infl_bone_id_order == 17) {
//        return g_matBone018;
//    }
//    if (prm_infl_bone_id_order == 18) {
//        return g_matBone019;
//    }
//    if (prm_infl_bone_id_order == 19) {
//        return g_matBone020;
//    }
//    if (prm_infl_bone_id_order == 20) {
//        return g_matBone021;
//    }
//    if (prm_infl_bone_id_order == 21) {
//        return g_matBone022;
//    }
//    if (prm_infl_bone_id_order == 22) {
//        return g_matBone023;
//    }
//    if (prm_infl_bone_id_order == 23) {
//        return g_matBone024;
//    }
//    if (prm_infl_bone_id_order == 24) {
//        return g_matBone025;
//    }
//    if (prm_infl_bone_id_order == 25) {
//        return g_matBone026;
//    }
//    if (prm_infl_bone_id_order == 26) {
//        return g_matBone027;
//    }
//    if (prm_infl_bone_id_order == 27) {
//        return g_matBone028;
//    }
//    if (prm_infl_bone_id_order == 28) {
//        return g_matBone029;
//    }
//    return g_matBone030;

}


//���b�V���W�����_�V�F�[�_�[
OUT_VS VS_DefaultSkinAniMesh(
      float4 prm_posModel_Local  : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local : NORMAL,        // ���f���̒��_�̖@��
      float  prm_bone_combi_index         : PSIZE ,        // ���f���̃C���f�b�N�X�i���ڂ̃I�u�W�F�N�g���H�j
      float2 prm_uv              : TEXCOORD0 ,     // ���f���̒��_��UV
      float4 infl_weight         : BLENDWEIGHT,
      int4   infl_bone_id       : BLENDINDICES0,
      int4   infl_bone_id_order       : BLENDINDICES1
) {
    OUT_VS out_vs = (OUT_VS)0;
//    const int bone_combi_index = ((int)prm_bone_combi_index) % _draw_combined_matrix_set_num;
//    const int bone_combi_index = (int)(infl_bone_idx[0]);
    //���_�v�Z
//
//    float w[4] = (float[4])infl_weight;
//    int b[4] = (int[4])infl_bone_idx;
//    float4x4 matBoneWorld = getBoneWorldMatrix(b[0]) * w[0];
//    if (w[1] > 0.0f) {
//        matBoneWorld = getBoneWorldMatrix(b[1]) * w[1];
//    }
//    else if (w[2] == 0.0f) {
//        matBoneWorld = getBoneWorldMatrix((int)(infl_bone_idx[0])) * w[0] +
//                       getBoneWorldMatrix((int)(infl_bone_idx[1])) * w[1];
//    }

//        matBoneWorld = getBoneWorldMatrix((int)(infl_bone_idx[0])) * infl_weight[0];
//        mtBoneWorld += getBoneWorldMatrix((int)(infl_bone_idx[1])) * infl_weight[1];a
//        if (infl_weight[2] > 0) {
//            matBoneWorld += getBoneWorldMatrix((int)(infl_bone_idx[2])) * infl_weight[2];
//            if (infl_weight[3] > 0) {
//                matBoneWorld += getBoneWorldMatrix((int)(infl_bone_idx[3])) * infl_weight[3];
//            }
//        }
//    }
    float4x4 matBoneWorld = getBoneWorldMatrix((int)(infl_bone_id_order[0])) * infl_weight[0];
    if (infl_weight[1] > 0.00f) {
        matBoneWorld = matBoneWorld + getBoneWorldMatrix((int)(infl_bone_id_order[1])) * infl_weight[1];
        if (infl_weight[2] > 0.00f) {
            matBoneWorld = matBoneWorld + getBoneWorldMatrix((int)(infl_bone_id_order[2])) * infl_weight[2];
            if (infl_weight[3] > 0.00f) {
                matBoneWorld = matBoneWorld + getBoneWorldMatrix((int)(infl_bone_id_order[3])) * infl_weight[3];
            }
        }
    }


    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, matBoneWorld);
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe
    //UV�͂��̂܂�
    out_vs.uv = prm_uv;

    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    const float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matBoneWorld));
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
    // float4x4 g_matBone		:	World�ϊ��s��
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


