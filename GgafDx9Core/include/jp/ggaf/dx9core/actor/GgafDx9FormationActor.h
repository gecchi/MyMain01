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
    virtual void processJudgement() override;

public:
    /** 所属アクター数 */
    int _num_sub;

    frame _frame_offset_end;
    /**
     *
     * @param prm_name
     * @param prm_frame_offset_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafDx9FormationActor(const char* prm_name, frame prm_frame_offset_end = 30*60);

    virtual void initialize() override {
    }

    virtual void processBehavior() override;

    virtual void processDraw() {
    }

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    /**
     * 編隊に所属したアクターが全滅した場合に呼び出すメソッドとする。 .
     * 具体的な処理（編隊ボーナス加算や、特殊効果音等）は下位で実装すること。
     * また、本メソッドが機能するためには、アクター側で自身がやられた場合に、
     * wasDestroyedFollower() を呼び出す事が必須です。
     * @param prm_pActorLast
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    }


    /**
     * 編隊に所属したアクターは、自身が消滅する際に呼び出すメソッド .
     * wasDestroyedFormation() が呼び出されるためには、本メソッドをアクター側で自身がやられた場合に
     * 都度呼びだして下さい。
     * 内部でカウンタを減らし、カウントが0になれば wasDestroyedFormation() を呼びださします。
     * @param prm_pActor
     */
    virtual void wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor);


    /**
     * メンバーの登録します.
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;

    virtual ~GgafDx9FormationActor();
};

}
#endif /*GGAFDX9FORMATIONACTOR_H_*/
