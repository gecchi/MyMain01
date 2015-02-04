#ifndef GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#define GGAFLIB_STEPPEDCOORDSPLINEMANUFACTURE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

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
     * @param prm_source_file �X�v���C�����W���t�@�C��
     */
    SteppedCoordSplineManufacture(const char* prm_source_file);

    /**
     * �R���X�g���N�^ .
     * @param prm_pSplSrc �X�v���C�����W���I�u�W�F�N�g
     */
    SteppedCoordSplineManufacture(SplineSource* prm_pSplSrc);

    /**
     * �������i�v�Z�j���� .
     * �v���p�e�B��ύX�����ꍇ�A�����e�[�u�������X�V���邽�߂�
     * ��x���s����K�v������܂��B
     */
    void calculate() override;

    /**
     * SplineKurokoLeader�I�u�W�F�N�g�̐��� .
     * �C���X�^���X�� SteppedCoordSplineKurokoLeader �ł��B
     * @param prm_pKuroko �X�v���C���ړ�������ΏۃA�N�^�[
     * @return SplineKurokoLeader�I�u�W�F�N�g
     */
    SplineKurokoLeader* createKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko) override;

    virtual ~SteppedCoordSplineManufacture();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEMANUFACTURE_H_*/
