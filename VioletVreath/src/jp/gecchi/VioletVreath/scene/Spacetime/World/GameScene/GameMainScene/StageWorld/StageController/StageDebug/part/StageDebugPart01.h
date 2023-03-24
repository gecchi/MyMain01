#ifndef STAGEDEBUGPART01_H_
#define STAGEDEBUGPART01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "StageDebugPart.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージデバッグ－１ .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPart01 : public StageDebugPart<GgafLib::DefaultScene> {


public:
    StageDebugPart01(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~StageDebugPart01();
};

}
#endif /*STAGEDEBUGPART01_H_*/
