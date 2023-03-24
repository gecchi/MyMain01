#ifndef GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * ���W�ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveManufacture : public CurveManufacture {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_spl_file �X�v���C�����W���t�@�C��
     */
    SteppedCoordCurveManufacture(const char* prm_coord_spl_file);

    /**
     * �R���X�g���N�^ .
     * @param prm_pCurveSrc �X�v���C�����W���I�u�W�F�N�g
     */
    SteppedCoordCurveManufacture(CurveSource* prm_pCurve);

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * VehicleLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� SteppedCoordCurveVecVehicleLeader �ł��B
     * @param GgafDx::AxisVehicle �J�[�u�ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return VehicleLeader �I�u�W�F�N�g
     */
    VehicleLeader* createVecVehicleLeader(GgafDx::VecVehicle* prm_pVecVehicle) override;

    virtual ~SteppedCoordCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_*/
