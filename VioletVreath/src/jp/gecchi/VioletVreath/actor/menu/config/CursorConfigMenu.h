#ifndef CURSORCONFIGMENU_H_
#define CURSORCONFIGMENU_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"



namespace VioletVreath {

/**
 * �R���t�B�O���j���[�J�[�\�� .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class CursorConfigMenu : public GgafLib::DefaultBoardActor {

public:
    CursorConfigMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorConfigMenu();
};

}
#endif /*CURSORCONFIGMENU_H_*/

