#ifndef GGAF_CORE_LINEARTREEROUNDER_H_
#define GGAF_CORE_LINEARTREEROUNDER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/LinearOctree.h"
#include "jp/ggaf/core/util/TreeSpace.hpp"

namespace GgafCore {

#define MAX_COLLISIONSTACK_ACTOR_NUM (2000)
/**
 * Tを要素とし当たり判定機能を追加した線形N分木または四分木の各要素に処理を行う .
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<class T, uint32_t DIMENSION>
class LinearTreeRounder : public Object {

    uint32_t _num_space;

public:
    /**
     * 当たり判定アクターを保持するスタック .
     * 速さの事しか考えてない危険なスタック
     */
    class TStack {
    public:
        /** [r]一つの空間にスタックするアクターの配列。使用するのは[0]〜[MAX_COLLISIONSTACK_ACTOR_NUM-1]。+1は、最後の要素を番兵にしている */
        T* _apT[MAX_COLLISIONSTACK_ACTOR_NUM+1]; //最後の要素(+1)は番兵
        /** [r]カーソルポインタ(次にPUSH出来る要素を指している)  */
        T** _papCur;
        /** [r]常にスタックの先頭要素を指している */
        T** _papFirst;
        /** [r]常にスタックの最後の要素の次を指している */
        T** _papBanpei;
    public:
        /**
         * コンストラクタ
         * @return
         */
        TStack() {
            _papFirst = &_apT[0];
            _papBanpei = &_apT[MAX_COLLISIONSTACK_ACTOR_NUM];
            _papCur = _papFirst;
        }
        /**
         * スタックに積む .
         * @param prm_pT 積むアクター
         */
        inline void push(T* prm_pObject) {
            if (_papCur == _papBanpei) {
                _TRACE_("＜警告＞ LinearTreeRounder::push("<<prm_pObject<<") スタックを使い切りました。無視します。一箇所に当たり判定が塊過ぎです。");
                return;
            }
            (*_papCur) = prm_pObject;
            ++_papCur;
        }

        /**
         * スタックから取り出す .
         * @return 取り出されたアクター
         */
        inline T* pop() {
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
         * @param prm_pTStack
         */
        inline void popush(TStack* prm_pTStack) {
            if (_papCur == _papBanpei) {
                _TRACE_("＜警告＞ LinearTreeRounder::popush("<<prm_pTStack<<") スタックを使い切ってます。無視します。一箇所に当たり判定が塊過ぎです。");
                prm_pTStack->clear();
                return;
            }
            while ((*_papCur) = prm_pTStack->pop()) { //代入。pop出来なければ nullptr。 I know "=" , not "=="
                 ++_papCur;
                 if (_papCur == _papBanpei) {
                    _TRACE_("＜警告＞ LinearTreeRounder::popush("<<prm_pTStack<<") スタックを使い切りました。無視します。一箇所に当たり判定が塊過ぎです。");
                    prm_pTStack->clear();
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
        ~TStack() {
            clear();
        }
    };

    TreeSpace<DIMENSION>* _paTargetSpace;
    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Aグループのスタック */
    TStack _stackGroupA_Current;
    /** [r]全空間の当たり判定時、現在の空間に所属するアクター種別Bグループのスタック */
    TStack _stackGroupB_Current;
    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Aグループのスタック */
    TStack _stackGroupA;
    /** [r]ある空間の当たり判定時、それよりも親空間に所属した全アクター種別Bグループのスタック */
    TStack _stackGroupB;

    /** [r]今回当たり判定を行うアクター種別A */
    kind_t _kind_groupA;
    /** [r]今回当たり判定を行うアクター種別B */
    kind_t _kind_groupB;
    /** [r]実行するTのメンバ関数 */
    void (T::*_pFunc)(T*);

public:
    /**
     * コンストラクタ
     * @param prm_level 作成するN分木空間レベル
     */
    LinearTreeRounder(TreeSpace<DIMENSION>* prm_paTargetSpace, int prm_num_space, void (T::*prm_pFunc)(T*)) {
        _paTargetSpace = prm_paTargetSpace;
        _num_space = prm_num_space;
        _pFunc = prm_pFunc;
        _kind_groupA = 0;
        _kind_groupB = 0;
    }

    /**
     * N分木所属の「アクター種別Aグループ 対 アクター種別Bグループ」を行う  .
     * アプリ側は本メソッドを呼ぶだけでよい。<BR>
     * ただし executeAllHitChk は processJudgement() で呼ぶ必要あり。<BR>
     * @param prm_kind_groupA アクター種別Aグループ
     * @param prm_kind_groupB アクター種別Bグループ
     */
    void executeAll(kind_t prm_kind_groupA, kind_t prm_kind_groupB) {
        _kind_groupA = prm_kind_groupA;
        _kind_groupB = prm_kind_groupB;
        kind_t k_bit = _paTargetSpace[0]._kind_bit_field;
        if ( (k_bit & prm_kind_groupA) && (k_bit & prm_kind_groupB) ) {
            //ではN分木を巡る旅へ行ってらっしゃい
            execute(0); //いってきます
            //はいお帰りなさい。
            _stackGroupA.clear();
            _stackGroupB.clear();
        }
    }

    /**
     * 引数の空間の当たり判定を行う  .
     * executeAllHitChk から使用される。
     * @param prm_index 線形N分木配列の配列要素番号
     */
    void execute(uint32_t prm_index) {
        TreeSpace<DIMENSION>* pOctant_this_level = &(_paTargetSpace[prm_index]);
        TreeElem<DIMENSION>* pElem = pOctant_this_level->_pElem_first;
        const kind_t kind_groupA = _kind_groupA;
        const kind_t kind_groupB = _kind_groupB;
        if (pElem) {
            TreeElem<DIMENSION>* pElem_last = pOctant_this_level->_pElem_last;
            while (true) {
                kind_t kind = pElem->_kind;
                T* pObject = (T*)(pElem->_pObject);
                if (kind & kind_groupA) {
                    _stackGroupA_Current.push(pObject);
                }
                if (kind & kind_groupB) {
                    _stackGroupB_Current.push(pObject);
                }
                if (pElem == pElem_last) {
                    break;
                }
                pElem = pElem->_pNext;
            }
            //現在の空間のグループAとグループB総当り
            executeRoundRobin(&_stackGroupA_Current, &_stackGroupB_Current);
            //現在の空間のグループAと親空間所属のグループB総当り
            executeRoundRobin(&_stackGroupA_Current, &_stackGroupB );
            //親空間所属のグループAと現在の空間のグループB総当り
            executeRoundRobin(&_stackGroupA , &_stackGroupB_Current);
        }
        const uint32_t lower_level_index = (prm_index<<DIMENSION) + 1; //_papOctant[prm_index] 空間の子空間のモートン順序位置0番の配列要素番号
        if ( lower_level_index >= _num_space) {
            //要素数オーバー、つまりリーフ
            _stackGroupA_Current.clear();
            _stackGroupB_Current.clear();
            return; //親空間へ戻る
        } else {

            //もぐる。が、その前に現空間アクターを親空間アクターのスタックへ追加。
            //もぐった空間から見た場合の親空間アクター累計を作っておいてやる。
            //(同時に現空間スタックも開放)
            T** temp_stackGroupA = _stackGroupA._papCur; //スタックポインタ保存(潜った後のリセットに使用)
            T** temp_stackGroupB = _stackGroupB._papCur; //スタックポインタ保存(潜った後のリセットに使用)
            _stackGroupA.popush(&_stackGroupA_Current); //Current を Parent に追加。同時にCurrentはクリアされる。
            _stackGroupB.popush(&_stackGroupB_Current); //Current を Parent に追加。同時にCurrentはクリアされる。
            bool isExistGroupA = _stackGroupA.isExist();
            bool isExistGroupB = _stackGroupB.isExist();

            //ヒットチェックを行いに、子空間(８個)へ潜りに行こう〜。
            //次のレベルの空間に種別AとBが登録されていれば潜る。
            //又は、次のレベルの空間に種別Aがあり、かつストックに種別Bがあれば潜る。
            //又は、次のレベルの空間に種別Bがあり、かつストックに種別Aがあれば潜る。
            //それ以外は潜らない
            TreeSpace<DIMENSION>* pOctant_lower_level = &(_paTargetSpace[lower_level_index]);
            kind_t kind_bit_field_lower_level = pOctant_lower_level->_kind_bit_field;
            if (kind_bit_field_lower_level & kind_groupA) {
                if (isExistGroupB || (kind_bit_field_lower_level & kind_groupB)) {
                    execute(lower_level_index);
                }
            } else if (kind_bit_field_lower_level & kind_groupB) {
                if (isExistGroupA) {
                    execute(lower_level_index);
                }
            }

            for (int i = 1; i < (1<<DIMENSION); i++) {
                kind_bit_field_lower_level = (++pOctant_lower_level)->_kind_bit_field;
                if (kind_bit_field_lower_level & kind_groupA) {
                    if (isExistGroupB || (kind_bit_field_lower_level & kind_groupB)) {
                        execute(lower_level_index+i);
                    }
                } else if (kind_bit_field_lower_level & kind_groupB) {
                    if (isExistGroupA) {
                        execute(lower_level_index+i);
                    }
                }
            }

            //お帰りなさい
            //スタックの解放（pushした分、元に戻す）
            _stackGroupA._papCur = temp_stackGroupA;
            _stackGroupB._papCur = temp_stackGroupB;
            return; //親空間へ戻る
        }
    }
    /**
     * アクター種別Aグループのスタックと、アクター種別Bグループのスタックの総当りの当たり判定を行う  .
     * executeHitChk から使用される。
     * @param prm_pStackA アクター種別Aグループのスタック
     * @param prm_pStackB アクター種別Bグループのスタック
     */
    void executeRoundRobin(TStack* prm_pStackA, TStack* prm_pStackB) {
        //LinearTreeRounderでは、要素の指す(Object*)インスタンスは Tが前提
        if (prm_pStackA->isExist() && prm_pStackB->isExist()) {
            void (T::*pFunc)(T*) = _pFunc;
            T** papStackT_A_Cur = prm_pStackA->_papCur;
            T** papStackT_B_Cur = prm_pStackB->_papCur;
            T** papStackT_A = prm_pStackA->_papFirst;
            while (papStackT_A != papStackT_A_Cur) {
                T** papStackT_B = prm_pStackB->_papFirst;
                while (papStackT_B != papStackT_B_Cur) {
                    ((*papStackT_A)->*pFunc)(*papStackT_B);
                    ++papStackT_B;
                }
                ++papStackT_A;
            }
        }
    }

    virtual ~LinearTreeRounder() {
    }
};

}
#endif /*GGAF_CORE_LINEARTREEROUNDER_H_*/

