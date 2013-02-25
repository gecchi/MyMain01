#ifndef CURSORSOUNDCONFIGMENU_H_
#define CURSORSOUNDCONFIGMENU_H_


namespace VioletVreath {

/**
 * �T�E���h�R���t�B�O�̃J�[�\�� .
 * @version 1.00
 * @since 2013/02/25
 * @author Masatoshi Tsuge
 */
class CursorSoundConfigMenu : public GgafLib::DefaultBoardActor {

public:
    CursorSoundConfigMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorSoundConfigMenu();
};

}
#endif /*CURSORSOUNDCONFIGMENU_H_*/

