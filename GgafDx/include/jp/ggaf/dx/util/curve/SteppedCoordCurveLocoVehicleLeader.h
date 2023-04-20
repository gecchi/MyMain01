#ifndef GGAF_DX_STEPPEDCOORDCURVELOCOVEHICLELEADER_H_
#define GGAF_DX_STEPPEDCOORDCURVELOCOVEHICLELEADER_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveLocoVehicleLeader : public VehicleLeader {

public:
    GgafDx::LocoVehicle* _pLocoVehicle_target;
    SteppedCoordCurveManufacture* _pSteppedSplManuf;

    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pLocoVehicle �Ώۂ̃A�N�^�[�̈ړ��ԗ�
     */
    SteppedCoordCurveLocoVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::LocoVehicle* prm_pLocoVehicle);

    virtual void restart() override;
    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave() override;

    virtual ~SteppedCoordCurveLocoVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVELOCOVEHICLELEADER_H_*/
