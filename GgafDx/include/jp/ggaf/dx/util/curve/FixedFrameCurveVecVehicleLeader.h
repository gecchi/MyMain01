#ifndef GGAF_DX_FIXEDFRAMECURVEVECVEHICLELEADER_H_
#define GGAF_DX_FIXEDFRAMECURVEVECVEHICLELEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �Œ莞�ԁi�t���[���j�X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA���߂�ꂽ���Ԃňړ����܂��B<BR>
 * ���Ԃ̕⊮�_�`���̕⊮�_�܂ł��A�ϓ��Ɋ��������Ԃňړ����܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���͈ړ����x���B<BR>
 * �⊮�_�̖��x���Z���Ƃ���͈ړ����x���B<BR>
 * ���̂悤�ɓ��삷��悤�A�͎�(GgafDx::VecVehicle)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedFrameCurveVecVehicleLeader : public VehicleLeader {

public:
    GgafDx::VecVehicle* _pVecVehicle_target;
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
     * @param prm_pVecVehicle
     */
    FixedFrameCurveVecVehicleLeader(CurveManufacture* prm_pManufacture,
                                 GgafDx::VecVehicle* prm_pVecVehicle_target);

    virtual void restart() override;

    /**
     * �ړ����s���\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ��� behave() �́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedFrameCurveVecVehicleLeader();
};

}
#endif /*GGAF_LIB_FIXEDFRAMECURVEVECVEHICLELEADER_H_*/
