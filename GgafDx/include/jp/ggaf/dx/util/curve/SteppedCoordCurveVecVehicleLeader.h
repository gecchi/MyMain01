#ifndef GGAF_DX_STEPPEDCOORDCURVEVECVEHICLELEADER_H_
#define GGAF_DX_STEPPEDCOORDCURVEVECVEHICLELEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/VehicleLeader.h"

namespace GgafDx {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveVecVehicleLeader : public VehicleLeader {

public:
    GgafDx::VecVehicle* _pVecVehicle_target;
    SteppedCoordCurveManufacture* _pSteppedSplManuf;

    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pVecVehicle �Ώۂ̃A�N�^�[�̗͎�
     */
    SteppedCoordCurveVecVehicleLeader(CurveManufacture* prm_pManufacture, GgafDx::VecVehicle* prm_pVecVehicle);

    virtual void restart() override;
    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave() override;

    virtual ~SteppedCoordCurveVecVehicleLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEVECVEHICLELEADER_H_*/
