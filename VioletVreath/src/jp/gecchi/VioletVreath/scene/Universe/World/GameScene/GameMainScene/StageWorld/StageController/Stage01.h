#ifndef STAGE01_H_
#define STAGE01_H_
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"

namespace VioletVreath {

/**
 * ステージ01 .
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */
class Stage01 : public Stage {

public:
    WorldBoundSpace001* pWorldBoundSpace_;
    HoshiBoshi001* pHoshiBoshi_;

    Planet001* pPlanet_;
    Horizon001* pHorizon_;

    LabelGecchi16Font* pMessage_;

public:
    Stage01(const char* prm_name);
    /**
     * 初期処理
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~Stage01();
};

}
#endif /*STAGE01_H_*/
