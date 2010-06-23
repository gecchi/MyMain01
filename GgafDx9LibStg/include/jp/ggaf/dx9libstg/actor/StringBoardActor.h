#ifndef STRINGBOARDACTOR_H_
#define STRINGBOARDACTOR_H_
namespace GgafDx9LibStg {

/**
 * 座標変換済み板ポリ文字表示
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class StringBoardActor : public GgafDx9Core::GgafDx9StringBoardActor {

public:
    StringBoardActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~StringBoardActor();

};

}
#endif /*STRINGBOARDACTOR_H_*/
