#ifndef GAMEMAINSCENE_H_
#define GAMEMAINSCENE_H_
namespace MyStg2nd {

/**
 * ゲームメインシーンクラス .
 */
class GameMainScene : public GgafLib::DefaultScene {

public:
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
    void processFinal() override;
    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;
    virtual ~GameMainScene();

};

}
#endif /*GAMEMAINSCENE_H_*/
