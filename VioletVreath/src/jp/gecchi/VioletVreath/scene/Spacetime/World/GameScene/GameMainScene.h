#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ゲームのメインシーンクラス .
 * 主な仕事はランクアップステージの切り替えです。
 * @version 1.00
 * @since 2008/10/08
 * @author Masatoshi Tsuge
 */
class GameMainScene : public VvScene<GgafLib::DefaultScene> {

public:
    char buf_[60];
    LabelScoreFont* pLabel_SCORE_;
    LabelGecchi16Font* pLabel_RANK_;
    LabelGecchi16Font* pLabel_STAMINA_;
    LabelGecchi8Font* pLabel_JIKI_x_;
    LabelGecchi8Font* pLabel_JIKI_y_;
    LabelGecchi8Font* pLabel_JIKI_z_;
    LabelRankFont* pRankFont_;

public:
    GameMainScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void processBehavior() override;
    void onInactive() override;
    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
