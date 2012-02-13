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

    char _buf[60];
    LabelGecchi16Font* _pFont16_SCORE;
    LabelGecchi16Font* _pFont16_RANK;
    LabelGecchi16Font* _pFont16_STAMINA;
    LabelGecchi8Font* _pFont8_JIKI_X;
    LabelGecchi8Font* _pFont8_JIKI_Y;
    LabelGecchi8Font* _pFont8_JIKI_Z;
    LabelRankFont* _pRankFont;

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
