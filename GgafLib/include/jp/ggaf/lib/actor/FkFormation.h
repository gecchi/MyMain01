#ifndef GGAFLIB_FKFORMATION_H_
#define GGAFLIB_FKFORMATION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/actor/ex/GgafDxFkFormation.h"

namespace GgafLib {

/**
 * �t�H���[�h�L�l�}�e�b�N�̂悤�ȃt�H�[���[�V�����A�N�^�[�N���X .
 * @version 1.00
 * @since 2013/06/21
 * @author Masatoshi Tsuge
 */
class FkFormation : public GgafDxCore::GgafDxFkFormation {

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_offset_frames_end �q�������Ȃ����Ƃ��ɉ������P�\�t���[��
     * @return
     */
    FkFormation(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual ~FkFormation();
};

}
#endif /*GGAFLIB_FKFORMATION_H_*/
