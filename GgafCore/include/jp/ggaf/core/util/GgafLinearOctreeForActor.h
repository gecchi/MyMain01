#ifndef GGAFCORE_GGAFLINEAROCTREEFORACTOR_H_
#define GGAFCORE_GGAFLINEAROCTREEFORACTOR_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafCore {

#define MAX_COLLISIONSTACK_ACTOR_NUM (2000)
/**
 * GgafActorを要素とし当たり判定機能を追加した線形八分木配列クラス .
 * 種別Aグループ 対 種別Bグループの2グループ間の当たり判定を行う
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctreeForActor : public GgafObject {

    uint32_t _num_space_minus_one;

public:
    /**
     * 当たり判定アクターを保持するスタック .
     * 速さの事しか考えてない危険なスタック
     */
    class ActorStack {
    public:
        /** [r]一つの空間にスタックするアクターの配列。使用するのは[0]～[MAX_COLLISIONSTACK_ACTOR_NUM-1]。+1は、最後の要素を番兵にしている */
        GgafCore::GgafActor* _apActor[MAX_COLLISIONSTACK_ACTOR_NUM+1]; //最後の要素(+1)は番兵
        /** [r]カーソルポインタ(次にPUSH出来る要素を指している)  */
        GgafCore::GgafActor** _papCur;
        /** [r]常にスタックの先頭要素を指している */
        GgafCore::GgafActor** _papFirst;
        /** [r]常にスタックの最後の要素の次を指している */
        GgafCore::GgafActor** _papBanpei;
    public:
        /**
         * コンストラクタ
         * @return
         */
        ActorStack() {
            _papFirst = &_apActor[0];
            _papBanpei = &_apActor[MAX_COLLISIONSTACK_ACTOR_NUM];
            _papCur = _papFirst;
        }
        /**
         * スタックに積む .
         * @param prm_pActor 積むアクター
         */
        inline void push(GgafCore::GgafActor* prm_pObject) {
            if (_papCur == _papBanpei) {
                _TRACE_("＜警告＞ GgafLinearOctreeForActor::push("<<prm_pObject<<") スタックを使い切りました。無視します。一箇所に当たり判定が塊過ぎです。");
                return;
            }
            (*_papCur) = prm_pObject;
            ++_papCur;
        }

        /**
         * スタックから取り出す .
         * @return 取り出されたアクター
         */
        inline GgafCore::GgafActor* pop() {
            if (_papCur == _papFirst) {
                return nullptr;
            } else {
                --_papCur;
                return (*_papCur);
            }
        }

        inline bool isExist() {
            return _papCur == _papFirst ? false : true;
        }

        /**
         * 引数のスタックから全て取り出し(pop)、出来る限り自身のスタックに積む(push) .
         * 引数のスタックは、必ず空になる。
         * @param prm_pActorStack
         */
        inline void popush(ActorStack* prm_pActorStack) {
            if (_papCur == _papBanpei) {
                _TRACE_("＜警告＞ GgafLinearOctreeForActor::popush("<<prm_pActorStack<<") スタックを使い切ってます。無視します。一箇所に当たり判定が塊過ぎです。");
                prm_pActorStack->clear();
                return;
            }
            while ((*_papCur) = prm_pActorStack->pop()) { //代入。pop出来なければ nullptr。 I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("＜警告＞ GgafLinearOctreeForActor::popush("<<prm_pActorStack<<") スタックを使い切りました。無視します。一箇所に当たり判定が塊過ぎです。");
                    prm_pActorStack->clear();
                    break;
                }
            }
        }
        /**
         * 積んだスタックをなかった事にする。 .
         */
        inline void clear() {
            _papCur = _papFirst;
        }
        ~ActorStack() {
            clear();
        }
    };

    GgafLinearOctree* _pTargetLinearOctree;
    GgafLinearOctreeOctant* _paTargetLinearOctant;
    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Aグループのスタック */
    ActorStack _stackGroupA_Current;
    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Bグループのスタック */
    ActorStack _stackGroupB_Current;
    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Aグループのスタック */
    ActorStack _stackGroupA;
    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Bグループのスタック */
    ActorStack _stackGroupB;

    /** [r]今回当たり判定を行うアクター種別A */
    actorkind _kind_groupA;
    /** [r]今回当たり判定を行うアクター種別B */
    actorkind _kind_groupB;
    /** [r]実行するGgafActorのメンバ関数 */
    void (GgafActor::*_pFunc)(GgafActor*);
public:
    /**
     * コンストラクタ
     * @param prm_level 作成する八分木空間レベル
     */
    GgafLinearOctreeForActor(GgafLinearOctree* prm_paTargetLinearOctree, void (GgafActor::*prm_pFunc)(GgafActor*));

    /**
     * 八分木所属の「アクター種別Aグループ 対 アクター種別Bグループ」を行う  .
     * アプリ側は本メソッドを呼ぶだけでよい。<BR>
     * ただし executeAllHitChk は processJudgement() で呼ぶ必要あり。<BR>
     * @param prm_groupA アクター種別Aグループ
     * @param prm_groupB アクター種別Bグループ
     */
    void executeAll(actorkind prm_groupA, actorkind prm_groupB);

    /**
     * 引数の空間の当たり判定を行う  .
     * executeAllHitChk から使用される。
     * @param prm_index 線形八分木配列の配列要素番号
     */
    void execute(uint32_t prm_index);

    /**
     * アクター種別Aグループのスタックと、アクター種別Bグループのスタックの総当りの当たり判定を行う  .
     * executeHitChk から使用される。
     * @param prm_pStackA アクター種別Aグループのスタック
     * @param prm_pStackB アクター種別Bグループのスタック
     */
    void executeRoundRobin(ActorStack* prm_pStackA, ActorStack* prm_pStackB);

    virtual ~GgafLinearOctreeForActor();
};


}
#endif /*GGAFCORE_GGAFLINEAROCTREEFORACTOR_H_*/

