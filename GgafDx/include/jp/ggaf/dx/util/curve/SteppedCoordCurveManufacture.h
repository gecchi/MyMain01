#ifndef GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDCURVEMANUFACTURE_H_
#include "GgafDxCommonHeader.h"
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
     * @param prm_coord_data_file �X�v���C�����W���t�@�C��
     */
    SteppedCoordCurveManufacture(const char* prm_coord_data_file);

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
     * DriverLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� SteppedCoordCurveVecDriverLeader �ł��B
     * @param GgafDx::GeoDriver �X�v���C���ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return DriverLeader �I�u�W�F�N�g
     */
    DriverLeader* createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) override;

    virtual ~SteppedCoordCurveManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEMANUFACTURE_H_*/
