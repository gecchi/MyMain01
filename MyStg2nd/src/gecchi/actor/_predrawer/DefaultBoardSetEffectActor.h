#ifndef DEFAULTBOARDSETEFFECTACTOR_H_
#define DEFAULTBOARDSETEFFECTACTOR_H_

namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetEffectActor : public GgafDx9LibStg::DefaultBoardSetActor {

public:
    DefaultBoardSetEffectActor(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    virtual ~DefaultBoardSetEffectActor();
};

}
#endif /*DEFAULTBOARDSETEFFECTACTOR_H_*/

