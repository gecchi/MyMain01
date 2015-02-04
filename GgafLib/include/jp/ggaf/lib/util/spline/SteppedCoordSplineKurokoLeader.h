#ifndef GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#define GGAFLIB_STEPPEDCOORDSPLINEKUROKOLEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineKurokoLeader : public SplineKurokoLeader {

public:
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture calculate()�ς݂�SplineManufacture��ݒ肷�邱��
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     */
    SteppedCoordSplineKurokoLeader(SplineManufacture* prm_pManufacture,  GgafDxCore::GgafDxKuroko* const prm_pKuroko);

    /**
     * �R���X�g���N�^ .
     * �����ړ��̂��߂̕K�v�ȏ������O�v�Z���A�I�u�W�F�N�g�ɗ��ߍ��݂܂��B
     * @param prm_pKuroko �Ώۂ̃A�N�^�[�̍���
     * @param prm_sp �v�Z�ς݃X�v���C���I�u�W�F�N�g
     * @return
     */
    SteppedCoordSplineKurokoLeader(GgafDxCore::GgafDxKuroko* const prm_pKuroko,
                                    SplineLine* prm_sp);


    virtual void restart() override;
    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave() override;

    virtual ~SteppedCoordSplineKurokoLeader();
};

}
#endif /*GGAFLIB_FIXEDVELOCITYSPLINEKUROKOLEADER_H_*/
