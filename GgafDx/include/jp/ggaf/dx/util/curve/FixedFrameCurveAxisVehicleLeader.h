#ifndef GGAF_DX_FIXEDFRAMECURVEAXISVEHICLELEADER_H_
#define GGAF_DX_FIXEDFRAMECURVEAXISVEHICLELEADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�AGgafDx::AxisVehicle �Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2018/07/25
 * @author Masatoshi Tsuge
 */
class FixedFrameCurveAxisVehicleLeader : public VehicleLeader {

public:
    GgafDx::AxisVehicle* _pAxisVehicle_target;
    /** [r]�X�v���C�����Z�b�g(ldr�t�@�C���̏��ɑ���) */
    FixedFrameCurveManufacture* _pFixedFrameSplManuf;
    /** _leading_frames�ɉ��Z�����␳�t���[�� */
    frame _hosei_frames;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** �O���_point_index */
    int _prev_point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     *
     * @param prm_pManufacture
     * @param prm_pAxisVehicle
     */
    FixedFrameCurveAxisVehicleLeader(CurveManufacture* prm_pManufacture,
                                    GgafDx::AxisVehicle* prm_pAxisVehicle_target);

    virtual void restart() override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;

    virtual ~FixedFrameCurveAxisVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDFRAMECURVEVECVEHICLELEADER_H_*/
