#ifndef GGAF_LIB_STEPPEDCOORDSPLINERIKISHALEADER_H_
#define GGAF_LIB_STEPPEDCOORDSPLINERIKISHALEADER_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/util/spline/SplineLeader.h"

namespace GgafLib {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordSplineRikishaLeader : public SplineLeader {

public:
    GgafDx::Rikisha* _pRikisha_target;
    SteppedCoordSplineManufacture* _pSteppedSplManuf;

    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pRikisha �Ώۂ̃A�N�^�[�̗͎�
     */
    SteppedCoordSplineRikishaLeader(SplineManufacture* prm_pManufacture, GgafDx::Rikisha* prm_pRikisha);

    virtual void restart() override;
    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave() override;

    virtual ~SteppedCoordSplineRikishaLeader();
};

}
#endif /*GGAF_LIB_FIXEDVELOCITYSPLINERIKISHALEADER_H_*/
