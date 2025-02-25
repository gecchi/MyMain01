#ifndef GGAF_DX_FORMATION_H_
#define GGAF_DX_FORMATION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

#define FORMATION_END_DELAY (SEC_F(30))

namespace GgafDx {

/**
 * フォーメーション管理クラス .
 * 複数種類が存在するフォーメーション管理クラスのスーパークラスです。
 * 編隊の処理を簡便にするために設計。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class Formation : public GeometricActor {

public:
    /** [r]編隊要素として「管理されている」アクター数 . */
    int _num_formation_member;
    //実際に配下に登録されているアクター数と同じとは限らない。
    //appendChild()で増加、 setFormationMember() によりセット、summonMember() 上限で上書き再設定
    //やりたいことは、onDestroyMember() で編隊全滅判定を行いたい。
    //生成時に、配下に余裕を持って最大メンバーを 10 登録しておき、
    //実際に活動時に使用するメンバー数は 8 である、と後から確定したい。
    //この場合 8 消滅で編隊全滅とする。
    //この場合_num_formation_member は最初 10 であるが、summonMember(8) 時に 8 に上書きされる。

    /** [r]破壊による消滅したアクター数 (所属アクターの informDestroyedFollower() により増加)*/
    int _num_destory;
    /** [r]編隊要素の呼び出し数（summonMember() が成功し true を返したとき増加）*/
    int _num_summon;

    /** [r]フォーメーション要員が全滅した際に自身を解放する猶予フレーム。下位クラスで、sayonaraの引数になる。 */
    frame _offset_frames_end;
    /** [r]全滅時 true (Actor::notifyDestroyed() が設定) */
    bool _was_all_destroyed;

    bool _was_all_sayonara;
    /** [r]summonMember() できるかどうかフラフ。true:招集できる／false：招集できない（メンバー数分招集した） */
    bool _can_summon;
    /** 最後に破壊されたアクター */
    GeometricActor* _pLastDestroyedActor;
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    Formation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * 編隊構成要員が破壊された時の処理 .
     * pActor->notifyDestroyed() 時に自動的に実行される。
     * 通常フレームワーク実装者は本メソッドを使用することはない。
     * @param prm_pActor_destroyed やられたアクター
     */
    virtual void onDestroyMember(GeometricActor* prm_pActor_destroyed);

    /**
     * 編隊に所属したアクターが破壊(画面外ではない)により全滅した場合にコールバックされるメソッド（とする) .
     * 編隊全滅時の具体的な処理（編隊ボーナス加算や、特殊効果音等）を実装することを想定。 <BR>
     * また、本コールバックが機能するためには、編隊構成アクターが自身がやられた場合に、
     * pActor->notifyDestroyed() を呼び出す事が必要になります。
     * Actor::notifyDestroyed() の説明を参照して下さい。 <BR>
     * 編隊全滅時の処理が特にない場合は、pActor->notifyDestroyed()を通知する必要はありません。 <BR>
     * その場合は、本メソッドは空実装しておいて下さい 。 <BR>
     * @param prm_pActor_last_destroyed 最後にやられたアクター
     */
    virtual void onDestroyAll(GeometricActor* prm_pActor_last_destroyed) = 0;

    /**
     * 編隊に所属したアクターが全てさよなら(sayonara()が呼び出された)した場合コールバックされるメソッド（とする) .
     */
    virtual void onSayonaraAll() = 0;

    /**
     * メンバーが残っていれば解放する処理を実装済み .
     * 継承してオーバーライドする場合は、処理内で
     * Formation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    inline int getMemberNum() const {
        return _num_formation_member;
    }
    /**
     * summonMember() 可能な場合 true
     * @return true:未活動の編隊登録メンバーが未だ存在/false:もう存在しない。
     */
    inline bool canSummon() {
        return _can_summon;
    }
    /**
     * 登録した編隊のメンバーを順番にアクティブにして取得します.
     * @return 未活動の編隊登録メンバー。又は nullptr、未活動の編隊登録メンバーはもう無い。
     */
    virtual GeometricActor* summonMember(int prm_formation_child_num = INT_MAX) = 0;

    virtual ~Formation();
};

}
#endif /*GGAF_DX_FORMATION_H_*/
