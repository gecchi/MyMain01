#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

#define ORDER_ID_NAMEENTRYSCENE 99
/**
 * 自機が全滅～のシーン
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GameOverScene : public VvScene<GgafLib::DefaultScene> {

public:
    NameEntryScene* pNameEntryScene_;

    LabelGecchi16Font* pLabel01_;
    bool need_name_entry_;

public:
    GameOverScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
