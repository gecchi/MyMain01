#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

#define FORMATION_END_DELAY (30*60)
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
     */
    virtual void processJudgement() override;

public:
    /** [r]所属アクター数(addSubLastにより増加、wasDestroyedFollowerで減少) */
    int _num_sub;
    int _num_destory;
    int _num_inactive;

    frame _offset_frames_end;
    bool _is_called_up;
    bool _is_init;

    /** 構成メンバーのストッカー */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    FormationActor(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    void setActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processDraw() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    GgafDx9GeometricActor* callUp();
    /**
     * 編隊のメンバーの登録します.
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;


    /**
     * 編隊に所属したアクターが全滅した場合に呼び出されるメソッド（とする) .
     * 編隊全滅時の具体的な処理（編隊ボーナス加算や、特殊効果音等）は下位で実装すること。 <BR>
     * また、本メソッドが機能するためには、アクター側で自身がやられた場合に、<BR>
     * wasDestroyedFollower() を呼び出す事が必須です。 <BR>
     * 編隊全滅時の処理がない場合は、override する必要はありません 。 <BR>
     * @param prm_pActorLast 最後にやられたアクター
     */
    virtual void wasDestroyedFormation(GgafDx9GeometricActor* prm_pActorLast) {
    }


    /**
     * 編隊に所属したアクターが消滅する際にコールしてもらうメソッド .
     * 編隊全滅判定を行いたい（wasDestroyedFormation(GgafDx9GeometricActor*) をコールバックさせたい）場合は、<BR>
     * 本メソッドをアクター側で自身がやられた時に、都度呼びだしを行う必要があります。<BR>
     * 具体的に、編隊要素の各アクターの「破壊による」消滅処理時に、次のような１行を加えてください。<BR>
     * （※「領域外による」消滅処理で呼び出してはいけません）<BR>
     * <code>
     *
     * ((FormationActor*)getParent())->wasDestroyedFollower(this);
     *
     * </code>
     * 実は、単に内部でカウンタを減らし、カウントが0になれば wasDestroyedFormation() をコールバックしているだけです。<BR>
     * @param prm_pActor やられたアクター
     */
    virtual void wasDestroyedFollower(GgafDx9GeometricActor* prm_pActor);

    virtual void wasInactiveFollower();

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
