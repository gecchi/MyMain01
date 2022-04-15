#ifndef GGAF_DX_FIXEDVELOCITYCURVEVECVEHICLELEADER_H_
#define GGAF_DX_FIXEDVELOCITYCURVEVECVEHICLELEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �����ړ��X�v���C���Ȑ��ړ��̐擱�ҁB .
 * �J�n�_�`�I���_�܂ŁA�����X�s�[�h�ňړ����܂��B<BR>
 * ���̕⊮�_�܂ł̋����𑪂�A���݂̈ړ����x����A���������������Z���u�c��ړ������v�����߂�B
 * �c��ړ�������0�ɂȂ�΁A���̕⊮�_�Ɍ�����ς��Ȃ���܂������𑪂�E�E�E���J��Ԃ��܂��B<BR>
 * �⊮�_�̖��x�������Ƃ���ł��Z���Ƃ���ł��ړ����x�ɉe���͂���܂���B<BR>
 * ���̂悤�ɓ��삷��悤�A�͎�(GgafDx::VecVehicle)�Ɏw�����o���Ĉړ����������܂��B<BR>
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class FixedVelocityCurveVecVehicleLeader : public VehicleLeader {

public:
    GgafDx::VecVehicle* _pVecVehicle_target;
    /** [r]�X�v���C�����Z�b�g(ldr�t�@�C���̏��ɑ���)  */
    FixedVelocityCurveManufacture* _pFixedVeloSplManuf;
    /** [r]���݌������Ă���Œ��̕⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** [r]����x�ňړ������ꍇ�̃J�[�u�ړ����̌o�߃t���[���� */
    float _leadning_float_frames;
    /** [r]���̕ς��ڂƂȂ��ԓ_(��_���܂�)�ɓ��B����_leadning_fFrames */
    float _float_frame_of_next;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pVecVehicle �Ώۂ̃A�N�^�[�̗͎�
     */
    FixedVelocityCurveVecVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::VecVehicle* prm_pVecVehicle_target);

    virtual void restart() override;

    /**
     * ���t���[���̐U�镑�����\�b�h .
     * start() ���s��������t���[���� behave() ���s�������Ƃ��������Ƃ͕s�v�B<BR>
     * start() ���s�����ŏ���behave()�́A�w���݂̍��W���|�C���g[0]�x�ւ̏����ƂȂ�܂��B<BR>
     */
    virtual void behave() override;


    virtual ~FixedVelocityCurveVecVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEVECVEHICLELEADER_H_*/
