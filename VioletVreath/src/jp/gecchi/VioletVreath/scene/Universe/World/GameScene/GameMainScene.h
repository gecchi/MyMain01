#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ゲームのメインシーンクラス .
 * 主な仕事はランクアップステージの切り替えです。
 * @version 1.00
 * @since 2008/10/08
 * @author Masatoshi Tsuge
 */
class GameMainScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT    ,
        PROG_BEGIN   ,
        PROG_PLAY    ,
        PROG_FINISH  ,
        _BANPEI_,
    };

    char buf_[60];
    LabelScoreFont* pLabelG_SCORE;
    LabelGecchi16Font* pLabelG_RANK;
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
    void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
