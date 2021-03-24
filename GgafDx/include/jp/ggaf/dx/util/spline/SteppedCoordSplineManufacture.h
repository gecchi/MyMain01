#ifndef GGAF_DX_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAF_DX_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/spline/SplineManufacture.h"

namespace GgafDx {

/**
 * �����ړ��ɂ��A�X�v���C���Ȑ��ړ��̂��߂̏��Z�b�g .
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineManufacture : public SplineManufacture {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_coord_data_file �X�v���C�����W���t�@�C��
     */
    SteppedCoordSplineManufacture(const char* prm_coord_data_file);

    /**
     * �R���X�g���N�^ .
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSpl);

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * SplineLeader �I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� SteppedCoordSplineVecDriverLeader �ł��B
     * @param GgafDx::GeoDriver �X�v���C���ړ����邽�߂̑��삷��I�u�W�F�N�g
     * @return SplineLeader �I�u�W�F�N�g
     */
    SplineLeader* createVecDriverLeader(GgafDx::VecDriver* prm_pVecDriver) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
