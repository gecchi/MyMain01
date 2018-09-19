#ifndef STAGEDEBUGPART03_H_
#define STAGEDEBUGPART03_H_
#include "VioletVreath.h"
#include "StageDebugPart.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�|�R .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPart03 : public StageDebugPart<GgafLib::DefaultScene> {


public:
    StageDebugPart03(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~StageDebugPart03();
};

}
#endif /*STAGEDEBUGPART03_H_*/
