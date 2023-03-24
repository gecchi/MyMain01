#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ゲームデモシーンクラス .
 * ゲームが行なわれている場面と言っても、ゲームデモが行なわれている場合もありました。
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameDemoScene : public VvScene<GgafLib::DefaultScene> {

public:
    struct ScoreInfo {
        int rank;
        std::string name;
        int score;
        std::string date;
    };

    LabelRankingFont** papLabel_ranking_;

    LabelGecchi16Font* pLabel01_;
    LabelGecchi16Font* pLabel02_;
    int demo_stage_;

public:
    GameDemoScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void onInactive() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
