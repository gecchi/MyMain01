#ifndef GGAFFORMATION_H_
#define GGAFFORMATION_H_

namespace GgafCore {

/**
 * フォーメーション管理クラス .
 * 複数種類が存在するフォーメーション管理クラスのスーパークラスです。
 * 編隊の処理を簡便にするために設計。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafFormation : public GgafMainActor {

public:
    /** [r]編隊要素として管理されているアクター数(addSubLast() callUpUntil() により増加) */
    int _num_formation_member;
    /** [r]破壊による消滅したアクター数 (所属アクターの informDestroyedFollower() により増加)*/
    int _num_destory;
    /** [r]フォーメーション要員が全滅した際に自身を解放する猶予フレーム。下位クラスで、sayonaraの引数になる。 */
    frame _offset_frames_end;
    /** [r]全滅時 true (GgafActor::notifyDestroyedToFormation() が設定) */
    bool _was_all_destroyed;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * 編隊構成要員が破壊された時の処理 .
     * pActor->notifyDestroyedToFormation() 時に自動的に実行される。
     * 通常フレームワーク実装者は本メソッドを使用することはない。
     * @param prm_pActor_destroyed
     */
    void destroyedFollower(GgafActor* prm_pActor_destroyed);

    /**
     * 編隊に所属したアクターが破壊(画面外ではない)により全滅した場合にコールバックされるメソッド（とする) .
     * 編隊全滅時の具体的な処理（編隊ボーナス加算や、特殊効果音等）を実装することを想定。 <BR>
     * また、本コールバックが機能するためには、編隊構成アクターが自身がやられた場合に、
     * pActor->notifyDestroyedToFormation() を呼び出す事が必要になります。
     * GgafActor::notifyDestroyedToFormation() の説明を参照して下さい。 <BR>
     * 編隊全滅時の処理が特にない場合は、pActor->notifyDestroyedToFormation()を通知する必要はありません。 <BR>
     * その場合は、本メソッドは空実装しておいて下さい 。 <BR>
     * @param prm_pActor_last_destroyed 最後にやられたアクター
     */
    virtual void onDestroyedAll(GgafActor* prm_pActor_last_destroyed) = 0;

    /**
     * メンバーが残っていれば解放する処理を実装済み .
     * 継承してオーバーライドする場合は、処理内で
     * GgafFormation::onEnded() を呼び出して下さい。
     */
    virtual void onEnded() override;

    virtual ~GgafFormation();
};

}
#endif /*GGAFFORMATION_H_*/
