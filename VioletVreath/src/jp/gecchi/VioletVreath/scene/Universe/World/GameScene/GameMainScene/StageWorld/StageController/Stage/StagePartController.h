#ifndef STAGEPARTCONTROLLER_H_
#define STAGEPARTCONTROLLER_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

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

    virtual ~StagePartController();
};

}
#endif /*STAGEPARTCONTROLLER_H_*/
