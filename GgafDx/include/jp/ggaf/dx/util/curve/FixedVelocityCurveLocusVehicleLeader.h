#ifndef GGAF_DX_FIXEDVELOCITYCURVELOCUSVEHICLELEADER_H_
#define GGAF_DX_FIXEDVELOCITYCURVELOCUSVEHICLELEADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �����ړ��X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA�����X�s�[�h�ňړ����܂��B<BR>
 * ���̕⊮�_�܂ł̋����𑪂�A���݂̈ړ����x����A���������������Z���u�c��ړ������v�����߂�B
 * �c��ړ�������0�ɂȂ�΁A���̕⊮�_�Ɍ�����ς��Ȃ���܂������𑪂�E�E�E���J��Ԃ��܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���ł��Z���Ƃ���ł��ړ����x�ɉe���͂���܂���B<BR>
 * ���̂悤�ɓ��삷��悤�A�ړ��ԗ�(GgafDx::LocusVehicle)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocityCurveLocusVehicleLeader : public VehicleLeader {

public:
    GgafDx::LocusVehicle* _pLocusVehicle_target;
    /** [r]�X�v���C�����Z�b�g(ldr�t�@�C���̏��ɑ���)  */
    FixedVelocityCurveManufacture* _pFixedVeloSplManuf;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** [r]����x�ňړ������ꍇ�̃J�[�u�ړ����̌o�߃t���[���� */
    double _leadning_double_frames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_leadning_fFrames */
    double _double_frame_of_next;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pLocusVehicle �Ώۂ̃A�N�^�[�̈ړ��ԗ�
     */
    FixedVelocityCurveLocusVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocusVehicle* prm_pLocusVehicle_target);

    virtual void restart() override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedVelocityCurveLocusVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVELOCUSVEHICLELEADER_H_*/
