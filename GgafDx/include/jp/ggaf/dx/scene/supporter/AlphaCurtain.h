#ifndef GGAF_DX_ALPHACURTAIN_H_
#define GGAF_DX_ALPHACURTAIN_H_
#include "jp/ggaf/GgafDxCommonHeader.h"

#include "jp/ggaf/dx/scene/supporter/SceneCurtain.h"

namespace GgafDx {

/**
 * ���J�[�e�� .
 * @version 1.00
 * @since 2010/04/21
 * @author Masatoshi Tsuge
 */
class AlphaCurtain : public SceneCurtain {
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_pScene ���J�[�e�������t����V�[��
     * @param prm_min_alpha �J�[�e���������Ƃ��̃�
     * @param prm_max_alpha �J�[�e�����J�����Ƃ��̃�
     */
    AlphaCurtain(Scene* prm_pScene);

    void behave() override;

    virtual ~AlphaCurtain();
};

}
#endif /*GGAF_DX_ALPHACURTAIN_H_*/

