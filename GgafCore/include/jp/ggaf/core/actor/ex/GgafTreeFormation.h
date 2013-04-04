#ifndef GGAFTREEFORMATION_H_
#define GGAFTREEFORMATION_H_

namespace GgafCore {

/**
 * 配下ツリー管理のフォーメーション管理クラス .
 * 編隊メンバーは使い捨てのフォーメーション。
 * 使用する場合は、本クラスを継承し、addSubLast(GgafActor*) により
 * 編隊メンバーを追加していってください。
 * processJudgement()を実装済み。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:
    /**
     * 使用不可 .
     * @param prm_pSub
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
    }

    /** [r]callUpMember()用のカーソル */
    GgafCore::GgafActor* _pIte;
    bool _can_call_up;
    void sayonaraFollwer();

public:
    /** [r]全滅時 true (GgafActor::notifyDestroyedToFormation() が設定) */
    bool _was_all_destroyed;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * サブが無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() した場合、本フォーメーションオブジェクトが自動解放される
     * ようにするために実装済みです。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * 編隊のメンバーを登録します.
     * GgafFormation は２つのフォーメーション管理モードが存在する。
     * 構成メンバーを、配下アクターにするか、デポジトリに置くかで管理モードが決定する。
     * 本メソッドを実行し、編隊構成メンバーを配下アクターに設定した場合、
     * 本フォーメーションオブジェクトは配下管理モードになる。このモードの編隊メンバーは使い捨てである。
     * 配下管理モードは、構成メンバーをこのメソッドにより初期登録しておく必要がある。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddFormationMember してください。
     * 自動で inactivateImmed() がじっこうされるので、
     * 構成メンバーを活動させるには、通常通り activate() を使用。
     * 構成メンバーを活動終了時は、sayonara() を使用。解放対象になります。
     * @param prm_pSub 編隊のメンバーのアクター
     */
    virtual void addFormationMember(GgafCore::GgafActor* prm_pSub);

    /**
     * 登録した編隊のメンバーを順番に取得します.
     * addSubLast(GgafCore::GgafActor*) により、登録した編隊メンバーを順番に取り出します。
     * nullptr が帰ってきた場合は、１順終了です。
     * @return
     */
    GgafActor* callUpMember();

    /**
     * callUpMember() 可能な場合 true
     * @return
     */
    inline bool canCallUp() {
        return _can_call_up;
    }

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafTreeFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    virtual ~GgafTreeFormation();
};

}
#endif /*GGAFTREEFORMATION_H_*/
