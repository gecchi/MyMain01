#include "GgafDx_World3DimEffect.fxh"
/**
 * GgafLib::DefaultMeshActor �p�V�F�[�_�[ .
 * �ÓI���f���P��`�悷��W���I�ȃV�F�[�_�[�B
 * ���_�o�b�t�@�t�H�[�}�b�g�́A�ȉ��̂悤�� GgafLib::MeshModel �ɒ�`����Ă�����̂�O��Ƃ��Ă��܂��B
 *
 * FVF = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX3 |
 *                                                        D3DFVF_TEXCOORDSIZE2(0) |     // �e�N�X�`�����W
 *                                                        D3DFVF_TEXCOORDSIZE3(1) |     // �ڃx�N�g��
 *                                                        D3DFVF_TEXCOORDSIZE3(2)   )   // �]�@���x�N�g��
 * {
 *     float x, y, z;             // ���W(���[�J�����W�n)
 *     float nx, ny, nz;          // �@���x�N�g��(���[�J�����W�n)
 *     DWORD color;               // ���_�J���[
 *     float tu, tv;              // �e�N�X�`�����W
 *     float tan_x, tan_y, tan_z; // �ڃx�N�g��(u�����P�ʃx�N�g���A�o���v�}�b�s���O���Ɏg�p) (���[�J�����W�n)
 *     float bin_x, bin_y, bin_z; // �]�@���x�N�g��(v�����P�ʃx�N�g���A�o���v�}�b�s���O���Ɏg�p) (���[�J�����W�n)
 * };
 *
 * @author Masatoshi Tsuge
 * @since 2009/03/06
 */

/** ���f����World�ϊ��s�� */
float4x4 g_matWorld;
/** ���f����World�ϊ��s��̋t�s�� */
float4x4 g_matInvWorld;
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

float g_lambert_flg;


/** �e�N�X�`���̃T���v���[(s0 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler MyTextureSampler : register(s0);
/** �@���}�b�v�e�N�X�`���̃T���v���[(s2 ���W�X�^�ɃZ�b�g���ꂽ�e�N�X�`�����g��) */
sampler BumpMapTextureSampler : register(s2);

/** ���_�V�F�[�_�[�o�͍\���� */
struct OUT_VS {
    float4 posModel_Proj   : POSITION;    //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ���)
    float2 uv              : TEXCOORD0;   //���_�e�N�X�`��UV
    float4 color           : COLOR0;      //���_�J���[
    float3 vecNormal_World : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World    : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
};

/**
 * GgafLib::DefaultMeshActor �p�̕W�����_�V�F�[�_�[ .
 * ���_�� World > View > �ˉe �ϊ�������A
 * ���f���Ɉȉ��̐F���u�����h���A���_�J���[�Ƃ��Ă̐ݒ肷��
 * �E���C�g�̐F�i�g�U���F�j
 * �E���f���̃}�e���A���F�i�g�U�����ːF�j
 * �E�����F�����Z
 *  �i���ȏ�̐F�ƃ��f���\�ʂ̖@���ƃ��C�g���ˊp�Ƃ̍����v�Z���A���C�g�̐F���������l���j
 * �E�����`�掞�̃��t�H�O
 * @param prm_posModel_Local  ���_�̃��[�J�����W
 * @param prm_vecNormal_Local ���[�J�����_�ł̖@���x�N�g��
 * @param prm_uv              ���_��UV���W
 * @return OUT_VS ���_�V�F�[�_�[�o�͍\���́B��L�̐������Q��
 */
OUT_VS VS_DefaultMesh(
      float4 prm_posModel_Local  : POSITION,
      float3 prm_vecNormal_Local : NORMAL,
      float2 prm_uv              : TEXCOORD0
) {
    OUT_VS out_vs = (OUT_VS)0;

    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld);        //World�ϊ�
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe

    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�

    //���_�J���[�v�Z
    //�@���� World �ϊ����Đ��K��
    out_vs.vecNormal_World = normalize(mul(prm_vecNormal_Local, g_matWorld));
    //�@���ƁA�g�U�������̓��ς��烉�C�g���ˊp�����߁A�ʂɑ΂���g�U�����˗������߂�B
    float refl_power = dot(out_vs.vecNormal_World, -g_vecLightFrom_World);
    if (g_lambert_flg > 0) {
        //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
        refl_power = refl_power * 0.5f + 0.5f;
        refl_power *= refl_power;
    } else {
        //�ʏ�̃����o�[�g���ˁA���ς̕��̒l���J�b�g
        refl_power = max(refl_power, 0);
    }
    //�g�U���F�ɔ��˗����悶�A�����F�����Z���A�S�̂��}�e���A���F���|����B
    out_vs.color.rgb = (g_colLightAmbient + (g_colLightDiffuse*refl_power)) * g_colMaterialDiffuse.rgb;
    //���̓��C�g�Ɋ֌W�Ȃ��}�e���A������D��Ƃ���
    out_vs.color.a = g_colMaterialDiffuse.a;
    //�u���_���J�������_�v�����x�N�g���B�s�N�Z���V�F�[�_�[�̃X�y�L�����[�v�Z�Ŏg�p�B
    out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);

    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor �p�̕W���s�N�Z���V�F�[�_�[ .
 * �e�s�N�Z���ɁA���_�J���[�Őݒ肳�ꂽ�F�ɂƉ��L�̐F���u�����h����B
 * �E�e�N�X�`���̐F
 * �E�X�y�L�����[�̋��������Z
 * �EBlinker�i�����臒l���傫���F�ɂ��ē_�Ō��ʁj���l��
 * �E�}�X�^�[��
 * @param prm_uv              UV���W
 * @param prm_color           �F�i�}�e���A���A���C�g�A���t�H�O�l���ς݁j
 * @param prm_vecNormal_World �@���x�N�g��(���[���h���W�n)
 * @param prm_vecEye_World    ����(���_ -> ���_)�x�N�g��(���[���h���W�n)
 */
float4 PS_DefaultMesh(
    float2 prm_uv              : TEXCOORD0,
    float4 prm_color           : COLOR0,
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


/**
 * ���[�J�����ڋ�ԕϊ� �s���Ԃ� .
 * �ڋ�ԂƂ̓��b�V���T�[�t�F�C�X��̂���_�ɂ����āA
 * �e�N�X�`��u�����x�N�g��, �e�N�X�`��v�����x�N�g��, �@���x�N�g�� ��
 * �R���ŕ\���������W�n�̎��B�R���͒������Ă���B<BR>
 * �w�}���y�P����[�ǂ��ƃR���x�̋L�� <BR>
 * http://marupeke296.com/DXPS_S_No5_NormalMap.html<BR>
 * ������p�����Ē����܂����B<BR>
 * @param prm_vecTangent  �ڃx�N�g��(u�����P�ʃx�N�g��)
 * @param prm_vecBinormal �]�@���x�N�g��(v�����P�ʃx�N�g��)
 * @param prm_vecNormal   �@���x�N�g��
 **/
float4x4 getInvTangentMatrix(
    float3 prm_vecTangent,
    float3 prm_vecBinormal,
    float3 prm_vecNormal )
{
    float4x4 mat = { float4(prm_vecTangent , 0.0f),
                     float4(prm_vecBinormal, 0.0f),
                     float4(prm_vecNormal  , 0.0f)  ,
                     {  0.0f, 0.0f, 0.0f, 1.0f } };
    return transpose( mat );  // �]�u(�搳�K�����n�̍s��̋t�s��͓]�u�s��ŗǂ�����)
}


/** �o���v�}�b�s���O�p���_�V�F�[�_�[�A�o�͍\���� */
struct OUT_VS_BM {
    float4 posModel_Proj    : POSITION;    //�ŏI�I�Ȓ��_���W(���[���h�E�r���[�E�ˉe�ϊ���)
    float2 uv               : TEXCOORD0;   //���_�e�N�X�`��UV
    float4 color            : COLOR0;      //���_�J���[
    float3 vecNormal_World  : TEXCOORD1;   //���_�̖@���x�N�g��(���[���h���W�n)
    float3 vecEye_World     : TEXCOORD2;   //���_�̎���(���_->���_)�x�N�g��(���[���h���W�n)
    float4 vecLight_Tangent : TEXCOORD3;   //���_�̃��C�g�x�N�g��(���[�J���̐ڋ�ԍ��W�n)
    float4 vecHarf_Tangent  : TEXCOORD4;   //���_�̃n�[�t�x�N�g��(���[�J���̐ڋ�ԍ��W�n)
};

/**
 * GgafLib::DefaultMeshActor �o���v�}�b�s���O�p�̒��_�V�F�[�_�[ .
 * ���_�� World > View > �ˉe �ϊ�������A
 * ���f���Ɉȉ��̐F���u�����h���A���_�J���[�Ƃ��Ă̐ݒ肷��
 * �E���f���̃}�e���A���F�i�g�U�����ːF�j
 * �E�����`�掞�̃��t�H�O�B
 * @param prm_posModel_Local    ���f�����_(���[�J�����W�n)
 * @param prm_vecNormal_Local   ���_�̖@��(���[�J�����W�n)
 * @param prm_uv                ���_��UV���W
 * @param prm_vecTangent_Local  ���_�̐ڃx�N�g��(u�����P�ʃx�N�g��)(���[�J�����W�n)
 * @param prm_vecBinormal_Local ���_�̏]�@���x�N�g��(v�����P�ʃx�N�g��)(���[�J�����W�n)
 */
OUT_VS_BM VS_BumpMapping(
      float4 prm_posModel_Local    : POSITION,
      float3 prm_vecNormal_Local   : NORMAL,
      float2 prm_uv                : TEXCOORD0,
      float3 prm_vecTangent_Local  : TEXCOORD1,
      float3 prm_vecBinormal_Local : TEXCOORD2
) {
    OUT_VS_BM out_vs = (OUT_VS_BM)0;

    //���_�v�Z
    const float4 posModel_World = mul(prm_posModel_Local, g_matWorld); //World�ϊ�
    out_vs.posModel_Proj = mul( mul( posModel_World, g_matView), g_matProj);  //World*View*�ˉe

    //UV�v�Z
    out_vs.uv = prm_uv;  //���̂܂�

    // �ڋ�ԍs��̋t�s����Z�o
    const float4x4 matTangent = getInvTangentMatrix(prm_vecTangent_Local, prm_vecBinormal_Local, prm_vecNormal_Local );
    // World���C�g�x�N�g����ڋ�ԂɈڂ�
    const float3 vecLight_Local = mul(-g_vecLightFrom_World, g_matInvWorld); //���[�J���ɖ߂��āiTODO:�����͗\�ߌv�Z�ł���c�j
    out_vs.vecLight_Tangent = mul(vecLight_Local, matTangent);         //�ڋ�ԍ��W�n��

    if (g_specular_power != 0) {
        //�u���_���J�������_�v�����x�N�g���i�X�y�L�����Ŏg�p�j
        out_vs.vecEye_World = normalize(g_posCam_World.xyz - posModel_World.xyz);
        //World�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g���j
        float3 vecHarf_World = normalize(out_vs.vecEye_World + (-g_vecLightFrom_World));
        //World�n�[�t�x�N�g����ڋ�ԂɈڂ�
        float3 vecHarf_Local = mul(vecHarf_World, g_matInvWorld); //���[�J���ɖ߂���
        out_vs.vecHarf_Tangent = mul(vecHarf_Local, matTangent ); //�ڋ�ԍ��W�n��
    }

    //���_�J���[�Ƀ}�e���A���F��ݒ肵�Ă����A
    //���C�g�̊g�U���F�v�Z�́A�o���v�}�b�s���O�̌v�Z�̃s�N�Z���V�F�[�_�[�ōs��
    out_vs.color = g_colMaterialDiffuse;

    //�������̕\�����@�B
    if (g_fog_starts_far_rate < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (out_vs.posModel_Proj.z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        out_vs.color.a *= getFogRate(out_vs.posModel_Proj.z);
    }

    return out_vs;
}

/**
 * GgafLib::DefaultMeshActor �o���v�}�b�s���O�p�̃s�N�Z���V�F�[�_�[ .
 * �@���}�b�v���瓾���@�����l�����g�U���̌��������v�Z���A
 * �^���I�ɕ\�ʂɉ��ʂ�����悤�ɂ݂���B
 * �e�s�N�Z���ɁA���_�J���[�Őݒ肳�ꂽ�F�ɂƉ��L�̐F���u�����h����B
 * �E���C�g�̐F�i�g�U���F�j
 * �E���f���̃}�e���A���F�i�g�U�����ːF�j
 * �E�����F�����Z
 * �E�����F���u�����h
 * �E�X�y�L�����[�̋��������Z
 *  �i���ȏ�̐F�ɂ��āA���f���\�ʂ̖@���ƃ��C�g���ˊp�Ƃ̍����v�Z���A���C�g�̐F���������l������
 *      ���̍ہA���f���\�ʂ̖@���ɂ��ẮA�@���}�b�v���瓾���@�����l������j
 * �EBlinker�i�����臒l���傫���F�ɂ��ē_�Ō��ʁj���l��
 * �E�}�X�^�[�����u�����h
 * @param prm_uv               UV���W
 * @param prm_color            �F�i���_�J���[�ɂ��}�e���A���F���ݒ�ρj
 * @param prm_vecNormal_World  �@���x�N�g��(World���W�n)
 * @param prm_vecEye_World     ����(���_->���_)�x�N�g��(World���W�n)
 * @param prm_vecLight_Tangent �g�U�������x�N�g��(�ڋ�ԍ��W�n)
 * @param prm_vecHarf_Tangent  �n�[�t�x�N�g��(�ڋ�ԍ��W�n)
 */
float4 PS_BumpMapping(
    float2 prm_uv               : TEXCOORD0,
    float4 prm_color            : COLOR0,
    float3 prm_vecNormal_World  : TEXCOORD1,
    float3 prm_vecEye_World     : TEXCOORD2,
    float3 prm_vecLight_Tangent : TEXCOORD3,
    float3 prm_vecHarf_Tangent  : TEXCOORD4
) : COLOR  {
    const float a = prm_color.a; //���ێ�

    //�@���}�b�v����̖@��
    const float3 vecNormal_Tangent = normalize(2.0f * tex2D( BumpMapTextureSampler, prm_uv ).xyz - 1.0);

    //�@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@���ɂȂ�j�ƁA
    //�g�U�������x�N�g��(���_�V�F�[�_�[�Őڋ�ԍ��W�n�ɗ\�ߕϊ��ς�) �̓��ς���
    //���C�g���ˊp�����߁A�ʂɑ΂���g�U���̌�����(power)�����߂�
    float refl_power = dot(vecNormal_Tangent, normalize(prm_vecLight_Tangent));
    if (g_lambert_flg > 0) {
        //���ς̕��̒l���g�p���āA�n�[�t�E�����o�[�g �Ŋg�U���̉�͂��s��
        refl_power = refl_power * 0.5f + 0.5f;
        refl_power *= refl_power;
    } else {
        //�ʏ�̃����o�[�g���ˁA���ς̕��̒l���J�b�g
        refl_power = max(refl_power, 0);
    }

    float s = 0.0f; //�X�y�L��������
    if (g_specular_power != 0) {
        //�n�[�t�x�N�g���i�u���_���J�������_�v�����x�N�g�� �ƁA�u���_�����C�g�v�����x�N�g���̐^�񒆂̕����x�N�g����
        //�ڋ�ԍ��W�n�ɗ\�ߕϊ��ς݁j�Ɩ@��(�@���}�b�v�̖@���A�܂�ڋ�ԍ��W�n�̖@��)�̓��ς��X�y�L��������v�Z
        s = pow( max(0.0f, dot(vecNormal_Tangent, prm_vecHarf_Tangent)), g_specular ) * g_specular_power; //�@���}�b�v�̓ʉ����l���B
    }

    const float4 colTex = tex2D( MyTextureSampler, prm_uv); //�P����UV����F�擾�A�܂�@���}�b�v�̓ʉ��͖��l���B
    //�����F�A�e�N�X�`���F�A���_�J���[�A�������A�X�y�L���� ���l�������F�쐬
    //tex�Emate�E(amb + (light�Epow)) + spow
    float4 colOut = colTex * ((g_colLightAmbient + ( g_colLightDiffuse * refl_power)) * prm_color ) + s; //prm_color = g_colMaterialDiffuse
    //Blinker���l��
    if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
        colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
    }
    colOut.a = a * g_alpha_master;
    return colOut;
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
    const float4 colTex = tex2D( MyTextureSampler, prm_uv);
    float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
    return colOut;
}

/**
 * �ʏ�G�t�F�N�g��Technique .
 */
technique DefaultMeshTechnique
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;

        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;

        //SrcBlendAlpha = One;    //default
        //DestBlendAlpha = Zero;  //default
        //BlendOpAlpha = Add;     //default

        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

/**
 * �o���v�}�b�s���O�G�t�F�N�g�̃e�N�j�b�N .
 */
technique BumpMapping
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_BumpMapping();
        PixelShader  = compile PS_VERSION PS_BumpMapping();
    }
}

/**
 * ���Z�����G�t�F�N�g�̃e�N�j�b�N .
 */
technique DestBlendOne
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

technique DestBlendOneMax
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = One;
        BlendOp = Max;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_DefaultMesh();
    }
}

/**
 * �M���G�t�F�N�g�̃e�N�j�b�N .
 */
technique Flush
{
    pass P0 {
        AlphaBlendEnable = true;
        SeparateAlphaBlendEnable = false;
        SrcBlend  = SrcAlpha;
        DestBlend = InvSrcAlpha;
        BlendOp = Add;
        VertexShader = compile VS_VERSION VS_DefaultMesh();
        PixelShader  = compile PS_VERSION PS_Flush();
    }
}

