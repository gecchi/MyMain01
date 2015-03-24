#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/scene/DefaultScene.h"

#include "jp/ggaf/core/GgafFactory.h"

namespace VioletVreath {

/**
 * �X�e�[�W�R���g���[���[��� .
 * @version 1.00
 * @since 2011/10/21
 * @author Masatoshi Tsuge
 */
class StagePartController : public GgafLib::DefaultScene {

public:
    StagePartController(const char* prm_name);
    /** �T�u�V�[���̑S��BGM���t�F�[�h�A�E�g����B */
    void fadeout_stop_AllPartSceneBgm();
    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
