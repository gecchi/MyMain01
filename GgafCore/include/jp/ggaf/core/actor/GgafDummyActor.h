#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * ダミーアクタークラス .
 * 子アクターが無くなれば自動的に自殺する悲しい一時的なアクターです。<BR>
 * 団体行動を採るときに、親アクターにすると何かと便利かもしれません。<BR>
 * @version 1.00
 * @since 2007/11/29
 * @author Masatoshi Tsuge
 */
class GgafDummyActor : public GgafMainActor {

public:
    GgafDummyActor(const char* prm_name);

    /**
     * 初期処理<BR>
     */
    virtual void initialize() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processBehavior() override {
    }

    /**
     * サブが無ければ死亡します。
     * ＜OverRide です＞<BR>
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            adios(1); //1フレーム後
        }
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processPreDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processAfterDraw() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processHappen(int prm_no) override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processFinal() override {
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual bool processBumpChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processOnHit(GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDummyActor();
};

}
#endif /*GGAFDUMMYACTOR_H_*/
