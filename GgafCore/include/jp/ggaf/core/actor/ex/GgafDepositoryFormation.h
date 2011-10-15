#ifndef GGAFDEOSITORYFORMATION_H_
#define GGAFDEOSITORYFORMATION_H_

namespace GgafCore {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDeositoryFormation : public GgafFormation {
private:

    void sayonaraFollwer();

    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
    }
public:
    /** [r]編隊要素として管理されているアクターのリスト */
    GgafCore::GgafLinkedListRing<GgafActor> _listFllower;
    bool _is_called_up;

    /** 全滅時 true (GgafActor::notifyFormationAboutDestroyed() が設定) */
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
    GgafDeositoryFormation(const char* prm_name, frame prm_offset_frames_end);

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

    /**
     * サブが無ければ死 .
     * processJudgement() を実装済みのため、オーバーライドしないで下さい。
     * どうしてもオーバーライドが必要な場合は、処理中での何処かで
     * <code>
     * GgafDeositoryFormation::processJudgement();
     * </code>
     * を呼び出してください、
     */
    virtual void processJudgement() override;

    /**
     * デポジトリからメンバー呼び出しする。 .
     * デポジトリモード時呼び出し可能。setFormationAbleActorDepository() の事前実行が必要。
     * 注意。初っ端に呼び出してもメンバーが確保できない場合、
     * 本フォーメーションオブジェクトは終了する。
     * @return
     */
    GgafActor* callUp();


    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafDeositoryFormation::onGarbaged() を呼び出して下さい。
     */
    virtual void onGarbaged() override;

    void sayonaraFollwer();

    virtual ~GgafDeositoryFormation();
};

}
#endif /*GGAFDEOSITORYFORMATION_H_*/
