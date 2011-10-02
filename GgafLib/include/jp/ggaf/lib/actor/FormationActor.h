#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

#define FORMATION_END_DELAY (30*60)
namespace GgafLib {



/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * 継承クラスはprocessJudgement()使用時注意すること。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDxCore::GgafDxGeometricActor {
private:
    /**
     * サブが無ければ死
     */
    virtual void processJudgement() override;

    virtual void onGarbaged();

    void sayonaraFollwer();


public:
    /** [r]所属アクター数(addSubLastにより増加、wasDestroyedFollowerで減少) */
    int _num_sub;
    int _num_destory;
//    int _num_inactive;

    GgafCore::GgafLinkedListRing<GgafCore::GgafMainActor> _listFllower;

    frame _offset_frames_end;
    bool _is_called_up;
    bool _was_all_destroyed;
    bool _is_init;

    /** 構成メンバーのストッカー（NULLの場合構成メンバーは配下アクターのはず） */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    FormationActor(const char* prm_name, frame prm_offset_frames_end = FORMATION_END_DELAY);

    /**
     * デポジトリモードにする。
     * 構成メンバーを、配下アクターにするか、デポジトリに置くかで、
     * 本クラスはモードが存在する。
     * 本メソッドを実行し、構成メンバーの入ったデポジトリを設定した場合、
     * 本フォーメーションオブジェクトはデポジトリモードになる。
     * デポジトリモードでは、addSubLast は不要。
     * メンバー呼び出しで、callUp() が使用可能。
     * @param prm_pDepo
     */
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

    /**
     * デポジトリからメンバー呼び出しする。 .
     * デポジトリモード時呼び出し可能。setActorDepository() の事前実行が必要。
     * 注意。初っ端に呼び出してもメンバーが確保できない場合、
     * 本フォーメーションオブジェクトは終了する。
     * @return
     */
    GgafDxGeometricActor* callUp();

    /**
     * 編隊のメンバーの登録します.
     * デポジトリモードではない場合、構成メンバーをこのメソッドにより初期登録しておく必要がある。
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;


    /**
     * 編隊に所属したアクターが破壊により全滅した場合に呼び出されるメソッド（とする) .
     * 編隊全滅時の具体的な処理（編隊ボーナス加算や、特殊効果音等）は下位で実装すること。 <BR>
     * また、本メソッドが機能するためには、アクター側で自身がやられた場合に、<BR>
     * wasDestroyedFollower() を呼び出す事が必須です。 <BR>
     * 編隊全滅時の処理がない場合は、override する必要はありません 。 <BR>
     * @param prm_pActorLast 最後にやられたアクター
     */
    virtual void onDestroyedFormation(GgafDxCore::GgafDxGeometricActor* prm_pActor_LastDestroyed) = 0;

//    /**
//     * 編隊に所属したアクターが全て非活動になった場合に呼び出されるメソッド（とする) .
//     * 下位で必要な実装すること。 <BR>
//     * また、本メソッドが機能するためには、アクター側で自身が非活動になった場合に、<BR>
//     * wasInactiveFollower() を呼び出す事が必須です。 <BR>
//     * 編隊非活動時の処理がない場合は、override する必要はありません 。 <BR>
//     * @param prm_pActorLast
//     */
//    virtual void wasAllInactivedFormation(GgafDxGeometricActor* prm_pActorLast) {
//    }

//    /**
//     * 編隊に所属したアクターが消滅する際にコールしてもらうメソッド .
//     * 編隊全滅判定を行いたい（onDestroyedFormation(GgafDxGeometricActor*) をコールバックさせたい）場合は、<BR>
//     * 本メソッドをアクター側で自身がやられた時に、都度呼びだしを行う必要があります。<BR>
//     * 具体的に、編隊要素の各アクターの「破壊による」消滅処理時に、次のような１行を加えてください。<BR>
//     * （※「領域外による」消滅処理で呼び出してはいけません）<BR>
//     * <code>
//     *
//     * ((FormationActor*)getParent())->wasDestroyedFollower(this);
//     *
//     * </code>
//     * 実は、単に内部でカウンタを減らし、カウントが0になれば onDestroyedFormation() をコールバックしているだけです。<BR>
//     * @param prm_pActor 破壊されたアクター
//     */
//    virtual void wasDestroyedFollower(GgafDxGeometricActor* prm_pActor);

    /**
     * 編隊に所属したアクターが非活動になった場合に呼び出してもらうメソッド。
     * onInactive() で本メソッドをコールして下さい。
     * @param prm_pActor 非活動になったアクター
     */
//    virtual void wasInactiveFollower(GgafDxGeometricActor* prm_pActor);

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
