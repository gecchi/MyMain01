#ifndef GGAF_DX_SCENECURTAIN_H_
#define GGAF_DX_SCENECURTAIN_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/Curtain.hpp"

namespace GgafDx {

/**
 * �V�[���̃J�[�e�� .
 * @version 1.00
 * @since 2017/11/17
 * @author Masatoshi Tsuge
 */
class SceneCurtain : public GgafCore::Curtain<float> {

private:
    /** [r]�J�[�e�������t����V�[�� */
    Scene* _pDxScene;

public:

    /**
     * �R���X�g���N�^ .
     * @param prm_pScene �J�[�e�������t����V�[��
     */
    SceneCurtain(Scene* prm_pScene,
                       float prm_curtain_rail_length,
                       float prm_min_position,
                       float prm_max_position);

    Scene* getScene() {
        return _pDxScene;
    }
    /**
     * �V�[���̍ŏ�ʂ��猩�āA�J�[�e���̈ʒu�i�܂��Ă������j���擾 .
     * @return �J�[�e���̈ʒu
     */
    virtual float getCurtainPositionFromTopScene();

    virtual void behave() override;

    virtual ~SceneCurtain();
};

}
#endif /*GGAF_DX_SCENECURTAIN_H_*/

