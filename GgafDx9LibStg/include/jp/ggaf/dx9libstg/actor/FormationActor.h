#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * フォーメーションアクタークラス .
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDx9Core::GgafDx9GeometricActor {

public:

    DWORD _frame_offset_adios;

    FormationActor(const char* prm_name, DWORD prm_frame_offset_adios = 5*60);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    /**
     * サブが無ければ死
     * ＜OverRide です＞<BR>
     */
    virtual void processJudgement() {
        if (getSubFirst() == NULL) {
            _TRACE_("FormationActor["<<getName()<<" adios(5*60)!!!!!!!!!!!!");
            inactivate();
            adios(30*60);//１分後開放
        }
    }

    virtual void processDraw() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
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
