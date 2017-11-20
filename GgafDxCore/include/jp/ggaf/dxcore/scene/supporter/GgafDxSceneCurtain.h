#ifndef GGAFDXCORE_GGAFDXSCENECURTAIN_H_
#define GGAFDXCORE_GGAFDXSCENECURTAIN_H_
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/core/util/GgafCurtain.hpp"

namespace GgafDxCore {

/**
 * �V�[���̃J�[�e�� .
 * @version 1.00
 * @since 2017/11/17
 * @author Masatoshi Tsuge
 */
class GgafDxSceneCurtain : public GgafCore::GgafCurtain<float> {

private:
    /** [r]�J�[�e�������t����V�[�� */
    GgafDxScene* _pDxScene;

public:

    /**
     * �R���X�g���N�^ .
     * @param prm_pScene �J�[�e�������t����V�[��
     */
    GgafDxSceneCurtain(GgafDxScene* prm_pScene,
                       float prm_curtain_rail_length,
                       float prm_min_position,
                       float prm_max_position);

    GgafDxScene* getScene() {
        return _pDxScene;
    }
    /**
     * �V�[���̍ŏ�ʂ��猩�āA�J�[�e���̈ʒu�i�܂��Ă������j���擾 .
     * @return �J�[�e���̈ʒu
     */
    virtual float getCurtainPositionFromTopScene();

    virtual void behave() override;

    virtual ~GgafDxSceneCurtain();
};

}
#endif /*GGAFDXCORE_GGAFDXSCENECURTAIN_H_*/

