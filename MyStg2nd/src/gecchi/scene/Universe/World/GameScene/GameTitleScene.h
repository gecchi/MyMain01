#ifndef GAMETITLESCENE_H_
#define GAMETITLESCENE_H_

#define GAMETITLE_SCENE_PROG_INIT          1
#define GAMETITLE_SCENE_PROG_PRE_TITLE     2
#define GAMETITLE_SCENE_PROG_TITLE         3

namespace MyStg2nd {


/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameTitleScene : public GgafDx9LibStg::DefaultScene {

public:

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;
    TitleBoard* _pTitleBoard;

    GameTitleScene(const char* prm_name);
    void reset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameTitleScene();
};

}
#endif /*GAMETITLESCENE_H_*/
