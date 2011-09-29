#ifndef DEFAULTBOARDEFFECTACTOR_H_
#define DEFAULTBOARDEFFECTACTOR_H_


namespace MyStg2nd {

/**
 * �v�������_�p�e�X�g�A�N�^�[ .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultBoardTestActor : public GgafLib::DefaultBoardActor {

public:
    DefaultBoardTestActor(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~DefaultBoardTestActor();
};

}
#endif /*DEFAULTBOARDEFFECTACTOR_H_*/

