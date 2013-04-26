#ifndef GGAFDEPOSITORYFORMATION_H_
#define GGAFDEPOSITORYFORMATION_H_

namespace GgafCore {

/**
 * デポジトリ管理のフォーメーション管理ークラス .
 * 編隊メンバーは使い回すフォーメーション。
 * 使用する場合は、本クラスを継承し、
 * setFormationMemberDepo(GgafActorDepository*) により
 * 編隊メンバー所属のデポジトリオブジェクトを登録してください。
 * processJudgement()を実装済み
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDepositoryFormation : public GgafFormation {
private:
//    /**
//     * 使用不可 .
//     * @param prm_pSub
//     */
//    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
//        throwGgafCriticalException("GgafDepositoryFormation::addSubLast() は使用不可です。");
//    }

public:
    /** [r]編隊要素として管理されているアクターのリスト */
    GgafCore::GgafLinkedListRing<GgafActor> _listFollower;
    /** [r]これ以上 callUpMember() 不可の場合 true */
    bool _can_call_up;
    /** [r]全滅時 true (GgafActor::notifyDestroyedToFormation() が設定) */
    bool _was_all_destroyed;
    /** [r]構成メンバーのストッカー（nullptrの場合構成メンバーは配下アクターのはず） */
    GgafCore::GgafActorDepository* _pDepo;

public:
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
     * メンバーを活動させるには、専用メソッド callUpMember() を使用する必要がある。
     * メンバーを活動終了時は、sayonara() を使用。
     * @param prm_pDepo
     */
    void setFormationMemberDepo(GgafCore::GgafActorDepository* prm_pDepo);

    /**
     * サブが無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() し、デポジトリに戻った場合、
     * 本フォーメーションオブジェクトが自動解放されるようにするための
     * 実装です。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * デポジトリからアクターを本フォーメーションメンバーとして設定し取得する（招集する） .
     * etFormationMemberDepository() の事前実行が必要。<BR>
     * 本メソッドを呼び出すと、デポジトリに管理されたメンバーが一つ dispatch() されます。(同時に activate() もされる)
     * デポジトリのメンバーがすべて活動中で、枯渇している場合 nullptr が返ります。
     * また、引数の prm_formation_sub_num は最大編隊構成要員数で、この数以上の呼び出しでも nullptr が返ります。
     * 一度でも nullptr が返されると、内部フラグ canCallUp() が false になり、以降本フォーメーションオブジェクトは
     * メンバー呼び出しできないようになります。と同時に、processFinal() で自動的に sayonara(_offset_frames_end) が実行され、
     * フォーメーションオブジェクトは自動終了体制に入ります。_offset_frames_end のデフォルト値は FORMATION_END_DELAY フレームです。
     * 注意。初っ端に呼び出してもメンバーが確保できない場合も、
     * 本フォーメーションオブジェクトは sayonara(_offset_frames_end) が実行され終了してしまいます。
     * 構成メンバーを登録後に呼び出すようにして下さい。
     * @param prm_formation_sub_num 本フォーメーションの最大編隊構成要員数
     * @return 編隊構成要員のアクター。
     *         最大編隊構成要員数をオーバーして呼び出した場合、或いは
     *         デポジトリに構成要員がもういない場合は nullptr
     */
    GgafActor* callUpMember(int prm_formation_sub_num = INT_MAX);

    /**
     * callUpMember() 可能な場合 true
     * @return
     */
    bool canCallUp();

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafDepositoryFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    /**
     * デポジトリモード管理の編隊全てに sayonara() を実行する。
     */
    virtual void sayonaraFollwer();

    virtual void processOnSayonara() override {
    }

    virtual ~GgafDepositoryFormation();
};

}
#endif /*GGAFDEPOSITORYFORMATION_H_*/
