#ifndef GGAFTREEFORMATION_H_
#define GGAFTREEFORMATION_H_

namespace GgafCore {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:

    void sayonaraFollwer();


public:

    /** 全滅時 true (GgafActor::notifyFormationAboutDestroyed() が設定) */
    bool _was_all_destroyed;
    bool _is_init;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);


    /**
     * サブが無ければ死 .
     * processJudgement() を実装済みのため、オーバーライドしないで下さい。
     * どうしてもオーバーライドが必要な場合は、処理中での何処かで
     * <code>
     * GgafTreeFormation::processJudgement();
     * </code>
     * を呼び出してください、
     */
    virtual void processJudgement() override;


    /**
     * 編隊のメンバーの登録します.
     * デポジトリモードではない場合、構成メンバーをこのメソッドにより初期登録しておく必要がある。
     * 具体的には、addSubLast() を呼び出し、種別を引き継ぎます。
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddSubLastしてください。
     * @param prm_pSub 登録アクター
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
