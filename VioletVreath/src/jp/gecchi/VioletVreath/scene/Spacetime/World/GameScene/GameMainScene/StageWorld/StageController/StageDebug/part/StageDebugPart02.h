#ifndef STAGEDEBUGPART02_H_
#define STAGEDEBUGPART02_H_
#include "VioletVreath.h"
#include "StageDebugPart.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �X�e�[�W�f�o�b�O�|�Q .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPart02 : public StageDebugPart<GgafLib::DefaultScene> {


public:
    StageDebugPart02(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~StageDebugPart02();
};

}
#endif /*STAGEDEBUGPART02_H_*/
