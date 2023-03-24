#ifndef STAGE02_01_H_
#define STAGE02_01_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ステージ2－１ .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02_01 : public VvScene<GgafLib::DefaultScene> {

public:
    Stage02_01(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage02_01();
};

}
#endif /*STAGE02_01_H_*/
