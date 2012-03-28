#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_
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
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAY    ,
        PROG_FINISH  ,
    };

    char buf_[60];
    LabelGecchi16Font* pLabel_SCORE_;
    LabelGecchi16Font* pLabel_RANK_;
    LabelGecchi16Font* pLabel_STAMINA_;
    LabelGecchi8Font* pLabel_JIKI_X_;
    LabelGecchi8Font* pLabel_JIKI_Y_;
    LabelGecchi8Font* pLabel_JIKI_Z_;
    LabelRankFont* pRankFont_;

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
