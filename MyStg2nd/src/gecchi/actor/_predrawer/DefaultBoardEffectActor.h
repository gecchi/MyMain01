#ifndef DEFAULTBOARDEFFECTACTOR_H_
#define DEFAULTBOARDEFFECTACTOR_H_


namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultBoardEffectActor : public GgafDx9LibStg::DefaultBoardActor {

public:
    DefaultBoardEffectActor(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~DefaultBoardEffectActor();
};

}
#endif /*DEFAULTBOARDEFFECTACTOR_H_*/

