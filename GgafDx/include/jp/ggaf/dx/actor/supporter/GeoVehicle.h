#ifndef GGAF_DX_GEOVEHICLE_H_
#define GGAF_DX_GEOVEHICLE_H_
#include "GgafDxCommonHeader.h"
#include "ActorVehicle.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * �쐬�� .
 * GeometricActor �̃����o��<BR>
 * _x, _y, _z  �E�E�E �A�N�^�[�̍��W<BR>
 * ���A�e�������ɊȒP�ɑ��삷�邽�߂ɍ쐬�B<BR>
 * @version 1.00
 * @since 2022/05/09
 * @author Masatoshi Tsuge
 */
class GeoVehicle : public ActorVehicle {

public:

    velo _velo;
    acce _acce;

    /** [r/w]X�������ړ����x */
    velo _velo_x;
    /** [r/w]Y�������ړ����x */
    velo _velo_y;
    /** [r/w]Z�������ړ����x */
    velo _velo_z;
    /** [r/w]�ړ����x��� */
    velo _top_velo;
    /** [r/w]�ړ����x���� */
    velo _bottom_velo;

    /** [r/w]X�������ړ������x */
    acce _acce_x;
    /** [r/w]Y�������ړ������x */
    acce _acce_y;
    /** [r/w]Z�������ړ������x */
    acce _acce_z;
    /** [r/w]�ړ������x���*/
    acce _top_acce;
    /** [r/w]�ړ������x����*/
    acce _bottom_acce;


public:
    /**
     * �R���X�g���N�^<BR>
     * @param   prm_pActor  ���Ăɏ��Actor
     */
    explicit GeoVehicle(GeometricActor* prm_pActor);

    /**
     * �ړ����x�̏������������ .
     * @param prm_velo01 ���x�P
     * @param prm_velo02 ���x�Q
     */
    void forceVeloRange(velo prm_velo01, velo prm_velo02);

    /**
     * �ړ������x�̏������������ .
     * @param prm_acce01 �����x�P
     * @param prm_acce02 �����x�Q
     */
    void forceAcceRange(acce prm_acce01, acce prm_acce02);

    /**
     * X��Y��Z�������̈ړ����x��ڕW���W�ƈړ����x�Őݒ肷��B
     * @param prm_tx �ڕWX���W
     * @param prm_ty �ڕWY���W
     * @param prm_tz �ڕWZ���W
     * @param prm_velo �ړ����x
     */
    void setVeloTwd(coord prm_tx, coord prm_ty, coord prm_tz, velo prm_velo);

    void setVeloTwd(angle prm_rz, angle prm_ry, velo prm_velo);

    void setVelo(velo prm_velo_x, velo prm_velo_y, velo prm_velo_z);

    void setVeloZero();

    void setAcceTwd(coord prm_tx, coord prm_ty, coord prm_tz, acce prm_acce);

    void setAcce(acce prm_acce_x, acce prm_acce_y, acce prm_acce_z);

    void setAcceZero();

    /**
     * ���x�A�����x�����Z�b�g�A�e��������������ݒ�B
     */
    void reset();

    /**
     * ����(���s�ړ��x��)���U�镑�� .
     * ����(���s�ړ��x��)�@�\�𗘗p����ꍇ�́A���̃��\�b�h�𖈃t���[���Ăяo�����s���Ă��������B<BR>
     * �t�ɉ���(���s�ړ��x��)��K�v�Ƃ��Ȃ��ꍇ�́A���̃��\�b�h���Ăяo���Ȃ����ƂŁA�p�t�H�[�}���X�ɉe����^���܂���B<BR>
     */
    virtual void behave();

    virtual ~GeoVehicle();
};

}
#endif /*GGAF_DX_GEOVEHICLE_H_*/

