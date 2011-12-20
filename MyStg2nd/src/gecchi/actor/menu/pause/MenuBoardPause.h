#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_
namespace MyStg2nd {

/**
 * �|�[�Y�����j���[ .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
class MenuBoardPause :
    public GgafLib::MenuActor<GgafLib::DefaultBoardActor> {

public:

    /**
     *
     * @param prm_name
     * @param prm_pAmount config�ς݂� AmountGraph�I�u�W�F�N�g�̎Q��
     */
    MenuBoardPause(const char* prm_name);

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void addVal(double prm_val);


    virtual ~MenuBoardPause();
};

}
#endif /*ENAGYBAR_H_*/

