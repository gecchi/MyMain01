#ifndef TREEFORMATION_H_
#define TREEFORMATION_H_

#define FORMATION_END_DELAY (30*60)
namespace GgafLib {



/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class TreeFormation : public GgafCore::GgafTreeFormation {
private:
    /**
     * 使用不可 .
     */
    virtual void processJudgement() override {
        GgafCore::GgafTreeFormation::processJudgement();
    }
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    TreeFormation(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);


    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }


    virtual void processDraw() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~TreeFormation();
};

}
#endif /*TREEFORMATION_H_*/
