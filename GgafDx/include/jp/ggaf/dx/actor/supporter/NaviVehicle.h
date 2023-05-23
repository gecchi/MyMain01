#ifndef GGAF_DX_NAVIVEHICLE_H_
#define GGAF_DX_NAVIVEHICLE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �A�N�^�[�̈ړ��x��(�z�[�~���O) .
 * ���g���僌�[�U�[�̃z�[�~���O�v�Z���A�ėp�I�ɐ؂�o���B<BR>
 * setAcceByVc() ����肽��������<BR>
 * @version 1.00
 * @since 2022/05/09
 * @author Masatoshi Tsuge
 */
class NaviVehicle : public ActorVehicle {

public:
    /** [r]�ړ����x */
    velo _velo;
    /** [r]�ړ����x��� */
    velo _top_velo;
    /** [r]�ړ����x���� */
    velo _bottom_velo;
    /** [r]�ړ����xX������(�P�ʃx�N�g���ł͂���܂���) */
    velo _velo_vc_x;
    /** [r]�ړ����xY������(�P�ʃx�N�g���ł͂���܂���) */
    velo _velo_vc_y;
    /** [r]�ړ����xZ������(�P�ʃx�N�g���ł͂���܂���) */
    velo _velo_vc_z;

    /** [r]�ړ������x */
    acce _acce;
    /** [r]�ړ������x���*/
    acce _top_acce;
    /** [r]�ړ������x����*/
    acce _bottom_acce;
    /** [r]�ړ������xX������(�P�ʃx�N�g���ł͂���܂���) */
    acce _acce_vc_x;
    /** [r]�ړ������xY������(�P�ʃx�N�g���ł͂���܂���) */
    acce _acce_vc_y;
    /** [r]�ړ������xZ������(�P�ʃx�N�g���ł͂���܂���) */
    acce _acce_vc_z;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  ���Ăɏ��Actor
     */
    explicit NaviVehicle(GeometricActor* prm_pActor);

    /**
     * �ړ����x�̏�������������������� .
     * @param prm_velo01 ���x�P
     * @param prm_velo02 ���x�Q
     */
    void forceVeloRange(velo prm_velo01, velo prm_velo02);

    /**
     * �ړ������x�̏���������������� .
     * @param prm_acce01 �����x�P
     * @param prm_acce02 �����x�Q
     */
    void forceAcceRange(acce prm_acce01, acce prm_acce02);

    /**
     * �ړ����������W�A�ړ����x��l�Őݒ肷�� .
     * �ړ����x�����` �ړ����x��� �͈̔͊O��ݒ肵���ꍇ�A
     * �����͂��̂܂܂ŁA���߂͈͓̔��ɔ[�߂��Đݒ肳���B
     * @param prm_tx �ړ�����X���W
     * @param prm_ty �ړ�����Y���W
     * @param prm_tz �ړ�����Z���W
     * @param prm_velo �ړ����x
     */
    void setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    /**
     * �ړ�����������](Rz, Ry)�A�ړ����x��l�Őݒ肷�� .
     * �ړ����x�����` �ړ����x��� �͈̔͊O��ݒ肵���ꍇ�A
     * �����͂��̂܂܂ŁA���߂͈͓̔��ɔ[�߂��Đݒ肳���B
     * @param prm_rz �ړ�����z����]�l
     * @param prm_ry �ړ�����y����]�l
     * @param prm_velo �ړ����x
     */
    void setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    /**
     * XYZ���x�N�g�������ŁA�ړ����x��ݒ肷�� .
     * �ړ����x�����` �ړ����x��� �͈̔͊O��ݒ肵���ꍇ�A
     * �����͂��̂܂܂ŁA���߂͈͓̔��ɔ[�߂��Đݒ肳���B
     * @param prm_velo_vc_x
     * @param prm_velo_vc_y
     * @param prm_velo_vc_z
     */
    void setVeloByVc(velo prm_velo_vc_x, velo prm_velo_vc_y, velo prm_velo_vc_z);

    /**
     * �ړ����x�� 0 �ɐݒ肷�� .
     * �A���A�ړ����x���� �� 0 ���傫���ꍇ�A
     * �������ړ����x�����̑��x��X�������ɐݒ肳���B
     */
    void setVeloZero();

    /**
     * �ړ����������W�A�ړ������x��l�Őݒ肷�� .
     * �ړ������x�����` �ړ������x��� �͈̔͊O��ݒ肵���ꍇ�A
     * �����͂��̂܂܂ŁA���߂͈͓̔��ɔ[�߂��Đݒ肳���B
     * @param prm_tx �ړ�����X���W(�܂��́A�^�[�Q�b�g�̕����x�N�g��X���W)
     * @param prm_ty �ړ�����Y���W(�܂��́A�^�[�Q�b�g�̕����x�N�g��Y���W)
     * @param prm_tz �ړ�����Z���W(�܂��́A�^�[�Q�b�g�̕����x�N�g��Z���W)
     * @param prm_acce �ړ������x
     */
    void setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce);

    /**
     * XYZ���x�N�g�������ŁA�ړ������x��ݒ肷�� .
     * �ړ������x�����` �ړ������x��� �͈̔͊O��ݒ肵���ꍇ�A
     * �����͂��̂܂܂ŁA���߂͈͓̔��ɔ[�߂��Đݒ肳���B
     * ���������āA���g����ڕW���ւ̕����x�N�g����n���ƁA���܂���Ƀz�[�~���O�O���ɂȂ�܂��B
     * @param prm_acce_vc_x �ړ������xX������(�܂��́A�^�[�Q�b�g�̕����x�N�g��X����)
     * @param prm_acce_vc_y �ړ������xY������(�܂��́A�^�[�Q�b�g�̕����x�N�g��Y����)
     * @param prm_acce_vc_z �ړ������xZ������(�܂��́A�^�[�Q�b�g�̕����x�N�g��Z����)
     */
    void setAcceByVc(acce prm_acce_vc_x, acce prm_acce_vc_y, acce prm_acce_vc_z);

    /**
     * �ړ������x�� 0 �ɐݒ肷�� .
     * �A���A�ړ������x���� �� 0 ���傫���ꍇ�A
     * �������ړ������x�����̑��x��X�������ɐݒ肳���B
     */
    void setAcceZero();

    /**
     * ����(���s�ړ��x��)���U�镑�� .
     * ����(���s�ړ��x��)�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɉ���(���s�ړ��x��)��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~NaviVehicle();
};

}
#endif /*GGAF_DX_NAVIVEHICLE_H_*/

