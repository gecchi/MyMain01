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

    void sayonaraFollwer();


public:
    /** 全滅時 true (GgafActor::notifyDestroyedToFormation() が設定) */
    bool _was_all_destroyed;

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
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * 構成メンバーを活動させるには、通常通り activate() を使用。
     * 構成メンバーを活動終了時は、sayonara() を使用。
     * @param prm_pSub 編隊のメンバーのアクター
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override;

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafTreeFormation::onEnded() を呼び出して下さい。
     */
    virtual void onEnded() override;

    virtual ~GgafTreeFormation();
};

}
#endif /*GGAFTREEFORMATION_H_*/
