#ifndef CURSORNAMEENTRYMENU_H_
#define CURSORNAMEENTRYMENU_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



namespace VioletVreath {

/**
 * �l�[���G���g���[���J�[�\�� .
 * @version 1.00
 * @since 2012/10/04
 * @author Masatoshi Tsuge
 */
class CursorNameEntryMenu : public GgafLib::DefaultBoardActor {

public:
    CursorNameEntryMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorNameEntryMenu();
};

}
#endif /*CURSORNAMEENTRYMENU_H_*/

