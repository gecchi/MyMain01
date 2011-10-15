#ifndef GGAFFORMATIONACTOR_H_
#define GGAFFORMATIONACTOR_H_

namespace GgafCore {

/**
 * フォーメーションアクタークラス .
 * processJudgement()を実装済みのため、
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafFormation : public GgafActor {
private:



public:
    /** [r]編隊要素として管理されているアクター数(addSubLast() callUp() により増加) */
    int _num_sub;
    /** [r]破壊による消滅したアクター数 (所属アクターの informDestroyedFollower() により増加)*/
    int _num_destory;

    frame _offset_frames_end;

    /** 全滅時 true (GgafActor::notifyFormationAboutDestroyed() が設定) */
    bool _was_all_destroyed;
    bool _is_init;

    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafFormation(const char* prm_name, frame prm_offset_frames_end);

    void DestroyedFollower(GgafActor* prm_pActor_Destroyed);


    /**
     * 編隊に所属したアクターが破壊により全滅した場合に呼び出されるメソッド（とする) .
     * 編隊全滅時の具体的な処理（編隊ボーナス加算や、特殊効果音等）は下位で実装すること。 <BR>
     * また、本メソッドが機能するためには、アクター側で自身がやられた場合に、<BR>
     * wasDestroyedFollower() を呼び出す事が必須です。 <BR>
     * 編隊全滅時の処理がない場合は、override する必要はありません 。 <BR>
     * @param prm_pActor_LastDestroyed 最後にやられたアクター
     */
    virtual void onDestroyedAll(GgafActor* prm_pActor_LastDestroyed) = 0;


    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafFormation::onGarbaged() を呼び出して下さい。
     */
    virtual void onGarbaged() override;

    virtual ~GgafFormation();
};

}
#endif /*GGAFFORMATIONACTOR_H_*/
