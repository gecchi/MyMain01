#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDepositoryFormation : public GgafFormation {
private:

    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
    }
public:
    /** [r]編隊要素として管理されているアクターのリスト */
    GgafCore::GgafLinkedListRing<GgafActor> _listFllower;
    bool _is_called_up;
    bool _is_all_called_up;
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
    GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * デポジトリモードにする。
     * 構成メンバーを、配下アクターにするか、デポジトリに置くかで、
     * 本クラスはモードが存在する。
     * 本メソッドを実行し、構成メンバーの入ったデポジトリを設定した場合、
     * 本フォーメーションオブジェクトはデポジトリモードになる。
     * デポジトリモードでは、addSubLast は不要。
     * メンバー呼び出しで、callUpUntil() が使用可能。
     * @param prm_pDepo
     */
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * サブが無ければ死 .
     * processJudgement() を実装済みのため、オーバーライドしないで下さい。
     * どうしてもオーバーライドが必要な場合は、処理中での何処かで
     * <code>
     * GgafDepositoryFormation::processJudgement();
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
    GgafActor* callUpUntil(int prm_formation_sub_num);


    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafDepositoryFormation::onEnded() を呼び出して下さい。
     */
    virtual void onEnded() override;

    virtual void sayonaraFollwer();

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
