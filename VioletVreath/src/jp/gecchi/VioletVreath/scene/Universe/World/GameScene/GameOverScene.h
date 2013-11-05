#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

#define ORDER_ID_NAMEENTRYSCENE 99
/**
 * ���@���S�Ł`�̃V�[��
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameOverScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT     ,
        PROG_DISP     ,
        PROG_NAMEENTRY,
        PROG_FINISH   ,
        PROG_BANPEI,
    };
    NameEntryScene* pNameEntryScene_;

    LabelGecchi16Font* pLabel01_;
    bool need_name_entry_;

public:
    GameOverScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
