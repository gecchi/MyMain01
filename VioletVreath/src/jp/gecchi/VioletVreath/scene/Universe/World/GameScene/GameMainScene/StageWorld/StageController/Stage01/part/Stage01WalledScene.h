#ifndef STAGE01WALLEDSCENE_H_
#define STAGE01WALLEDSCENE_H_
#include "jp/ggaf/lib/scene/WalledScene.h"

namespace VioletVreath {

/**
 * ステージ01の壁 .
 * @version 1.00
 * @since 2010/08/23
 * @author Masatoshi Tsuge
 */
class Stage01WalledScene : public GgafLib::WalledScene {

public:
    Stage01WalledScene(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onFinishedAllSection() override;

    virtual ~Stage01WalledScene();
};

}
#endif /*STAGE01WALLEDSCENE_H_*/
