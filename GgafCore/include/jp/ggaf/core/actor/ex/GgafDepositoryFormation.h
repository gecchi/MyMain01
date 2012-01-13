#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * デポジトリ管理のフォーメーションアクタークラス .
 * 編隊メンバーは使い回すフォーメーション。
 * processJudgement()を実装済み
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
    /** これ以上 callUpUntil() 不可の場合 true */
    bool _is_all_called_up;
    /** 全滅時 true (GgafActor::notifyFormationAboutDestroyed() が設定) */
    bool _was_all_destroyed;

    /** 構成メンバーのストッカー（NULLの場合構成メンバーは配下アクターのはず） */
    GgafCore::GgafActorDepository* _pDepo;
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end フォーメーション終了時の猶予フレーム
     * @return
     */
    GgafDepositoryFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * デポジトリモードにする。
     * GgafFormation は２つのフォーメーション管理モードが存在する。
     * 構成メンバーを、配下アクターにするか、デポジトリに置くかで管理モードが決定する。
     * 本メソッドを実行し、構成メンバーの入ったデポジトリを設定した場合、
     * 本フォーメーションオブジェクトはデポジトリモードになる。
     * デポジトリモードでは、addSubLast は不要。
     * メンバーを活動させるには、専用メソッド callUpUntil() を使用する必要がある。
     * メンバーを活動終了時は、sayonara() を使用。
     * @param prm_pDepo
     */
    void setFormationAbleActorDepository(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * サブが無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() し、デポジトリに戻った場合、
     * 本フォーメーションオブジェクトが自動解放されるようにするための
     * 実装です。
     * 下位で processJudgement() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * GgafTreeFormation::processJudgement();
     * </code>
     * を呼び出してください、
     */
    virtual void processJudgement() override;

    /**
     * デポジトリからメンバー呼び出しする。 .
     * デポジトリモード時呼び出し可能。setFormationAbleActorDepository() の事前実行が必要。
     * 本メソッドを呼び出すと、デポジトリに管理されたメンバーが一つ dispatch() されます。(同時に activate() もされる)
     * デポジトリのメンバーが枯渇した場合 NULL が返ります。
     * また、引数の prm_formation_sub_num は最大編隊構成要員数で、この数以上の呼び出しでも NULL が返ります。
     * 一度でも NULL が返されると、内部フラグ isAllCalledUp() が true になり、以降本フォーメーションオブジェクトは
     * メンバー呼び出しできないようになります。と同時に、 processJudgement() で自動的に sayonara() がコールされ
     * フォーメーションオブジェクトは解放されます。
     * 注意。初っ端に呼び出してもメンバーが確保できない場合も、
     * 本フォーメーションオブジェクトは終了してしまいます。
     * 構成メンバーを登録後に呼び出すようにして下さい。
     * @param prm_formation_sub_num 本フォーメーションの最大編隊構成要員数
     * @return 編隊構成要員のアクター。
     *         最大編隊構成要員数をオーバーして呼び出した場合、或いは
     *         デポジトリに構成要員がもういない場合は NULL
     */
    GgafActor* callUpUntil(int prm_formation_sub_num = INT_MAX);

    bool isAllCalledUp();

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafDepositoryFormation::onEnded() を呼び出して下さい。
     */
    virtual void onEnded() override;

    /**
     * デポジトリモード管理の編隊全てに sayonara() を実行する。
     */
    virtual void sayonaraFollwer();

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
