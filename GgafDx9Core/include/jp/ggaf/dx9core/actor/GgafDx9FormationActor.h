#ifndef GGAFDX9FORMATIONACTOR_H_
#define GGAFDX9FORMATIONACTOR_H_
namespace GgafDx9Core {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * 継承クラスはprocessJudgement()使用時注意すること。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDx9FormationActor : public GgafDx9GeometricActor {
private:
    /**
     * サブが無ければ死
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            _TRACE_("GgafDx9FormationActor["<<getName()<<" end("<<_frame_offset_end<<")!!!!!!!!!!!!");
            inactivate();
            sayonara(_frame_offset_end);
        }
    }

public:

    DWORD _frame_offset_end;
    /**
     *
     * @param prm_name
     * @param prm_frame_offset_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafDx9FormationActor(const char* prm_name, DWORD prm_frame_offset_end = 20*60);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processDraw() {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * メンバーの登録します.
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub);

    virtual ~GgafDx9FormationActor();
};

}
#endif /*GGAFDX9FORMATIONACTOR_H_*/
