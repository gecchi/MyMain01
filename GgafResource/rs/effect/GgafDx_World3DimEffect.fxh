#include "GgafDx_Effect.fxh"


/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** �ˉe�ϊ��s�� */
float4x4 g_matProj;

/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;
/** �J�����̏����ʒu��Z���W( < 0) */
float g_cameraZ_org;
/** �t�H�O�J�n��zf���������B-1.0 or 0.0�`1.0�B�����ł��\���������������ꍇ�� ���̒l ����������B*/
float g_fog_starts_far_rate;



float getFogRate(float posModel_proj_z) {
    // �ŉ��� g_fog_starts_far_rate ��肳��ɉ��̏ꍇ���X�ɓ�����
    //  z : g_fog_starts_far_rate*g_zf �` 1.0*g_zf  �� �� : 1.0 �` 0.0  �ƂȂ�悤�ɂ���ɂ�
    if (posModel_proj_z < g_fog_starts_far_rate) {
        return 1.0;
    } else {
        return (posModel_proj_z-g_zf)/((g_fog_starts_far_rate-1)*g_zf);
    }

}
//( (min_b-max_b)*a - (max_a*min_b) + (max_b*min_a) ) / (min_a-max_a);
//min_a=g_zf*g_fog_starts_far_rate
//max_a=g_zf*1.0
//a=posModel_proj_z
//min_b=0
//max_b=1.0;
//=( (0-1.0)*posModel_proj_z - ((g_zf*1.0)*0) + (1.0*(g_zf*g_fog_starts_far_rate)) ) / ((g_zf*g_fog_starts_far_rate)-(g_zf*1.0))
//=-(posModel_proj_z-g_fog_starts_far_rate*g_zf)/((g_fog_starts_far_rate-1)*g_zf)
//�����
//�� 1.0-(-(posModel_proj_z-g_fog_starts_far_rate*g_zf)/((g_fog_starts_far_rate-1)*g_zf))
//�� (posModel_proj_z-g_zf)/((g_fog_starts_far_rate-1)*g_zf)
