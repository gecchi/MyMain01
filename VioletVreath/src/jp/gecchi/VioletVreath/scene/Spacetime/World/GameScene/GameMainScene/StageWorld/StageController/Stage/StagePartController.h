#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"


namespace VioletVreath {

/**
 * �X�e�[�W�R���g���[���[��� .
 * @version 1.00
 * @since 2011/10/21
 * @author Masatoshi Tsuge
 */
class StagePartController : public VvScene<GgafLib::DefaultScene> {

public:
    StagePartController(const char* prm_name);
//    /** �q�V�[���̑S��BGM���t�F�[�h�A�E�g����B */
//    void fadeout_stop_AllPartSceneBgm();
    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
