#ifndef LINEAROCTREEFORACTOR_H_
#define LINEAROCTREEFORACTOR_H_
namespace GgafDx9LibStg {

/**
 * GgafActorを要素とし当たり判定機能を追加した線形八分木配列クラス .
 * 種別Aグループ 対 種別Bグループの2グループ間の当たり判定を行う
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class LinearOctreeForActor : public GgafCore::GgafLinearOctree {

public:

    /**
     * 当たり判定アクターを保持するスタック .
     * 速さの事しか考えてない危険なスタック
     */
    class CollisionStack {
    public:
        /** 一つの空間に 3000 もキャラが集まらないだろうという安易で浅はかな見積もり */
        GgafCore::GgafActor* _apActor[3000];
        /** カーソルポインタ  */
        DWORD _p;
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
        void push(GgafCore::GgafActor* prm_pActor) {
            _apActor[_p] = prm_pActor;
            _p++;

            if (_p > 3000) {
#ifdef MY_DEBUG
                _TRACE_("スタックを使い切りました、このままではメモリを破壊し異常終了するでしょう。_p-- やっときます。");
#endif
                _p--;
            }

        }
        /**
         * スタックから取り出す .
         * @return 取り出されたアクター
         */
        GgafCore::GgafActor* pop() {
            if (_p == 0) {
                return NULL;
            } else {
                _p--;
                return _apActor[_p];
            }
        }
        /**
         * 積んだスタックをなかった事にする。 .
         */
        void clear() {
            _p = 0;
        }
        ~CollisionStack() {
            clear();
        }
        void dump() {
            TEXT5("CollisionStack.dump=");
            for (DWORD i = 0; i < _p; i++) {
                TEXT5((_apActor[i]->getName())<<"->");
            }
            TEXT5("END");
        }
    };

    /** 全空間の当たり判定時、現在の空間に所属するアクター種別Aグループのスタック */
    CollisionStack _stackCurrentSpaceActor_GroupA;
    /** 全空間の当たり判定時、現在の空間に所属するアクター種別Bグループのスタック */
    CollisionStack _stackCurrentSpaceActor_GroupB;

    /** ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Aグループのスタック */
    CollisionStack _stackParentSpaceActor_GroupA;
    /** ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Bグループのスタック */
    CollisionStack _stackParentSpaceActor_GroupB;

    /** 今回当たり判定を行うアクター種別A */
    actorkind _kind_groupA;
    /** 今回当たり判定を行うアクター種別B */
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
    void executeHitChk(DWORD prm_index);

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

