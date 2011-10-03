#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_

#define FORMATION_END_DELAY (30*60)
namespace GgafLib {



/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDxCore::GgafDxGeometricActor {
private:

    virtual void onGarbaged();

    void sayonaraFollwer();


public:
    /** [r]編隊要素として管理されているアクター数(addSubLast() callUp() により増加) */
    int _num_sub;
    /** [r]破壊による消滅したアクター数 (IFormationAble::informDestroyedFollower() により増加)*/
    int _num_destory;
    /** [r]編隊要素として管理されているアクターのリスト */
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
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    /**
     * サブが無ければ死 .
     * processJudgement() を実装済みのため、オーバーライドしないで下さい。
     * どうしてもオーバーライドが必要な場合は、処理中での何処かで
     * <code>
     * FormationActor::processJudgement();
     * </code>
     * を呼び出してください、
     */
    virtual void processJudgement() override;

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
     * デポジトリモード時呼び出し可能。setFormationAbleActorDepository() の事前実行が必要。
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

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
