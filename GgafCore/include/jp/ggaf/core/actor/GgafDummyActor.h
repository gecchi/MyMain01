#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * ダミーアクタークラス .
 * 子アクターが無くなれば自動的に自殺する悲しい一時的なアクターです。<BR>
 * 団体行動を採るときに、親アクターにすると何かと便利かもしれない。<BR>
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

    virtual void processBehavior() override {
    }

    /**
     * 毎フレームのGgafDummyActor判定処理
     * サブが無ければ自動的に死亡する処理になっている。
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            end(1); //1フレーム後
        }
    }

    virtual void processPreDraw() override {
    }

    virtual void processDraw() override {
    }

    virtual void processAfterDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    /**
     * 当たり判定不要のため常にfalseを返す .
     * @param prm_pOtherActor
     * @return false
     */
    virtual bool processHitChkLogic(GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafActor* prm_pOtherActor) override {
    }

    virtual ~GgafDummyActor();
};

}
#endif /*GGAFDUMMYACTOR_H_*/
