#include "GgafDx_Effect.fxh"

/** -1.0 or 0.0�`1.0�B�����ł��\���������������ꍇ�� ���̒l ����������B*/
//float g_far_rate_alpha_fog;

/** ���݂̎ˉe�ϊ��s��v�f��zf�B�J�������牓���̃N���b�v�ʂ܂ł̋���(�ǂ��܂ł̋������\���Ώۂ��j> zn */
float g_zf;

/** ���f����View�ϊ��s�� */
float4x4 g_matView;
/** �ˉe�ϊ��s�� */
float4x4 g_matProj;

/*
float adjustDotByDot(floatz posModel_proj_z) {
    //�������̕\�����@�B
    if (g_far_rate_alpha_fog < 0.0) {
        //���̏ꍇ�A�ǂ�ȉ����ł��\������
        if (posModel_proj_z > g_zf*0.999) {
            //�{������O��Z�ł��A�`����������邽�߁A�ˉe���Z���W���㏑���A
            out_vs.posModel_Proj.z = g_zf*0.999; //�{������O��Z�ł��A�`����������邽�� g_zf*0.999 �ɏ㏑���A
        }
    } else {
        //���t�H�O
        if (out_vs.posModel_Proj.z > g_zf*g_far_rate) {   // �ŉ��� g_far_rate ��肳��ɉ��̏ꍇ���X�ɓ�����
            //  z : g_far_rate*g_zf �` 1.0*g_zf  �� �� : 1.0 �` 0.0  �ƂȂ�悤�ɂ���ɂ�
            //  �� = ( (0-1)*z - (g_zf*0) + (1* (far_rate*g_zf)) ) / ((far_rate*g_zf)-g_zf)
            //  �� = (far_rate*g_zf - z) / (far_rate*g_zf - g_zf)
            out_vs.color.a *= (  (g_far_rate*g_zf - out_vs.posModel_Proj.z) / ((g_far_rate-1.0)*g_zf) );
        }
    }
}
*/