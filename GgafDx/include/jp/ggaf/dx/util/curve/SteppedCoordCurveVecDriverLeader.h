#ifndef GGAF_DX_STEPPEDCOORDCURVEVECDRIVERLEADER_H_
#define GGAF_DX_STEPPEDCOORDCURVEVECDRIVERLEADER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dx/util/curve/DriverLeader.h"

namespace GgafDx {

/**
 * �X�v���C���Ȑ��ړ� .
 * �P���ɁA�t���[�����ɏ��Ԃɕ⊮�_���W�ֈړ��B
 * @version 1.00
 * @since 2009/10/28
 * @author Masatoshi Tsuge
 */
class SteppedCoordCurveVecDriverLeader : public DriverLeader {

public:
    GgafDx::VecDriver* _pVecDriver_target;
    SteppedCoordCurveManufacture* _pSteppedSplManuf;

    /** [r]�⊮�_(��_���܂�)�̐� */
    int _point_index;
    /** start()����̌o�߃t���[���� */
    frame _leading_frames;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pManufacture
     * @param prm_pVecDriver �Ώۂ̃A�N�^�[�̗͎�
     */
    SteppedCoordCurveVecDriverLeader(CurveManufacture* prm_pManufacture, GgafDx::VecDriver* prm_pVecDriver);

    virtual void restart() override;
    /**
     * ���t���[���̐U�镑�����\�b�h .
     * ���p�҂͖��t���[�����̃��\�b�h���Ăяo���K�v������܂��B
     */
    virtual void behave() override;

    virtual ~SteppedCoordCurveVecDriverLeader();
};

}
#endif /*GGAF_DX_FIXEDVELOCITYCURVEVECDRIVERLEADER_H_*/
