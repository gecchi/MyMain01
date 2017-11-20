#ifndef GGAFDXCORE_GGAFDXALPHACURTAIN_H_
#define GGAFDXCORE_GGAFDXALPHACURTAIN_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dxcore/scene/supporter/GgafDxSceneCurtain.h"

namespace GgafDxCore {

/**
 * ���J�[�e�� .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class GgafDxAlphaCurtain : public GgafDxSceneCurtain {
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pScene ���J�[�e�������t����V�[��
     * @param prm_min_alpha �J�[�e���������Ƃ��̃�
     * @param prm_max_alpha �J�[�e�����J�����Ƃ��̃�
     */
    GgafDxAlphaCurtain(GgafDxScene* prm_pScene);

    void behave() override;

    virtual ~GgafDxAlphaCurtain();
};

}
#endif /*GGAFDXCORE_GGAFDXALPHACURTAIN_H_*/

