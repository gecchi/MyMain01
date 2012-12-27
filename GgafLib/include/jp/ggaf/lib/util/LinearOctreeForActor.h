#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafLib {

/**
 * GgafActorを要素とし当たり判定機能を追加した線形八分木配列クラス .
 * 種別Aグループ 対 種別Bグループの2グループ間の当たり判定を行う
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

    UINT32 _num_space_minus_one;

public:
    /**
     * 当たり判定アクターを保持するスタック .
     * 速さの事しか考えてない危険なスタック
     */
    class CollisionStack {
    public:
        /** [r]一つの空間にスタックするアクターの配列 */
        GgafCore::GgafActor* _apActor[3000]; //１空間に 3000 もキャラが集まらないだろうという安易で浅はかな見積もり
        /** [r]カーソルポインタ  */
        UINT32 _p;

        /**
         * コンストラクタ
         * @return
         */
        CollisionStack() {
            _p = 0;
        }
        /**
         * スタックに積む .
         * @param prm_pActor 積むアクター
         */
        inline void push(GgafCore::GgafActor* prm_pActor) {
            if (_p > 3000-1) {
                _TRACE_("LinearOctreeForActor::push("<<prm_pActor->getName()<<") スタックを使い切りました。無視します。一箇所に当たり判定が塊過ぎです。");
                return;
            }
            _apActor[_p] = prm_pActor;
            _p++;
        }
        /**
         * スタックから取り出す .
         * @return 取り出されたアクター
         */
        inline GgafCore::GgafActor* pop() {
            if (_p == 0) {
                return nullptr;
            } else {
                _p--;
                return (_apActor[_p]);
            }
        }
        /**
         * 積んだスタックをなかった事にする。 .
         */
        inline void clear() {
            _p = 0;
        }
        ~CollisionStack() {
            clear();
        }
        void dump() {
            TEXT5("CollisionStack.dump=");
            for (UINT32 i = 0; i < _p; i++) {
                TEXT5((_apActor[i]->getName())<<"->");
            }
            TEXT5("END");
        }
    };

    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Aグループのスタック */
    CollisionStack _stackCurrentSpaceActor_GroupA;
    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Bグループのスタック */
    CollisionStack _stackCurrentSpaceActor_GroupB;

    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Aグループのスタック */
    CollisionStack _stackParentSpaceActor_GroupA;
    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Bグループのスタック */
    CollisionStack _stackParentSpaceActor_GroupB;

    /** [r]今回当たり判定を行うアクター種別A */
    actorkind _kind_groupA;
    /** [r]今回当たり判定を行うアクター種別B */
    actorkind _kind_groupB;


    /**
     * コンストラクタ
     * @param prm_level 作成する八分木空間レベル
     */
    LinearOctreeForActor(int prm_level);

    /**
     * 八分木所属の「アクター種別Aグループ 対 アクター種別Bグループ」を行う  .
     * アプリ側は本メソッドを呼ぶだけでよい。
     * @param prm_groupA アクター種別Aグループ
     * @param prm_groupB アクター種別Bグループ
     */
    void executeAllHitChk(actorkind prm_groupA, actorkind prm_groupB);

    /**
     * 引数の空間の当たり判定を行う  .
     * executeAllHitChk から使用される。
     * @param prm_index 線形八分木配列の配列要素番号
     */
    void executeHitChk(UINT32 prm_index);

    /**
     * アクター種別Aグループのスタックと、アクター種別Bグループのスタックの総当りの当たり判定を行う  .
     * executeHitChk から使用される。
     * @param prm_pStackA アクター種別Aグループのスタック
     * @param prm_pStackB アクター種別Bグループのスタック
     */
    void executeHitChk_RoundRobin(CollisionStack* prm_pStackA, CollisionStack* prm_pStackB);


    virtual ~LinearOctreeForActor();
};


}
#endif /*LINEAROCTREEFORACTOR_H_*/

