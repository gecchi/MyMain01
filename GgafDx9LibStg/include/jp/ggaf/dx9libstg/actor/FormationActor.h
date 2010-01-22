#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * 継承クラスはprocessJudgement()使用時注意すること。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDx9Core::GgafDx9GeometricActor {
private:
    /**
     * サブが無ければ死
     * ＜OverRide です＞<BR>
     */
    virtual void processJudgement() override {
        if (getSubFirst() == NULL) {
            _TRACE_("FormationActor["<<getName()<<" adios(5*60)!!!!!!!!!!!!");
            inactivate();
            adios(20*60);//20秒後開放
        }
    }

public:

    DWORD _frame_offset_adios;

    FormationActor(const char* prm_name, DWORD prm_frame_offset_adios = 5*60);

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

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
