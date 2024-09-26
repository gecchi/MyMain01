#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/lineartree/ITreeNodeElem.hpp"

#include <math.h>

namespace GgafCore {

#define MAX_TREE_LEVEL (20)

/**
 * 線形N分木共通 .
 * 線形4分木と線形8分木の共通処理をまとめたクラス
 * @tparam T 空間に登録させるオブジェクトの型
 * @tparam DIM 次元。2の場合4分木、3の場合8分木の機能となる。
 * @version 1.00
 * @since 2022/12/11
 * @author Masatoshi Tsuge
 */
template<class T, int DIM, int N>
class LinearTree : public Object {

public:

    /**
     * 線形N分木配列用空間クラス .
     * @version 1.00
     * @since 2009/11/23
     * @author Masatoshi Tsuge
     */
    class NodeSpace : public Object {
    public:
        /** [r]線形N分木配列の自身の要素番号 */
        uint32_t _self_index;
        /** [r]この空間＋子孫空間に所属してる要素の種別情報 */
        kind_t _kind_bit_field;
        /** [r]この空間に登録された要素連結リストの根本。_pNextNodeElem で連結されている。 */
        ITreeNodeElem* _pRootNodeElem;
        /** [r]登録を行った空間連結リスト用、次の空間(開放時に使用) */
        NodeSpace* _pRegNodeSpaceNext;

    public:
        /**
         * コンストラクタ
         * @return
         */
        NodeSpace() : Object() {
            _pRootNodeElem = nullptr;
            _kind_bit_field = 0;
            _self_index = 0xffffffff; //ありえない0xffffffffを入れておく
            _pRegNodeSpaceNext = nullptr;
        }

        /**
         * 要素登録 .
         * @param prm_pNodeElem 要素
         * @return true:そのインデックスに初回登録 ／ false:それ以外
         */
        void registerElem(ITreeNodeElem* prm_pNodeElem) {
            //引数の要素番号
            uint32_t index = _self_index;
            const kind_t this_kind = prm_pNodeElem->_kind;
            NodeSpace* p = this; //= & _paNodeSpaceArray[index]
            while (true) {
                if (p->_kind_bit_field & this_kind) {
                    //もう種別情報が設定済みならば、それ以上の親も設定済みの為、抜ける
                    break;
                } else {
                    //空間に種別情報が未設定ならば設定
                    p->_kind_bit_field |= this_kind;
                }
                if (index == 0) {
                    break;
                }
                //一つ上の親空間要素番号で繰り返す
                index = (index-1)>>DIM;
                p = p - (p->_self_index - index);
            }
            prm_pNodeElem->_pNextNodeElem = _pRootNodeElem; //初回は _pRootNodeElem == nullptr
            _pRootNodeElem = prm_pNodeElem;
        }

        void dump() {
            if (_pRootNodeElem == nullptr) {
                _TRACE_N_(""); //ノードなし
            } else {
                ITreeNodeElem* pElem = _pRootNodeElem;
                while (pElem) {
                    pElem->dump();
                    pElem = pElem ->_pNextNodeElem;
                }
            }
        }
        virtual ~NodeSpace() {
        }
    };

public:
    /** [r]N分木のN、2のDIM乗の値が入る（DIM:2→4, DIM:3→8,…)。	 */
//    const uint32_t _N;
    /** [r]N分木の空間を一直線に並べた線形配列 */
    NodeSpace* _paNodeSpaceArray; //_paNodeSpaceArray[0] は ROOT空間へのポインタ
    /** [r]登録を行った空間連結リストの根本。空間開放時に使用。_pRegNodeSpaceNext で連結されている。（clearAllElem() で使用する） */
    NodeSpace* _pRegNodeSpaceList;
    /** [r]最大空間レベル */
    const uint32_t _top_space_level; //ルート空間はLevel=0
    /** [r]全空間数 */
    uint32_t _num_space;
    char _aChar_strbit[33];
    /** [r]N（N分木のN）の2乗の配列、計算用。(20は十分最大レベル空間と思える適当な値) */
    uint32_t POW_N[MAX_TREE_LEVEL];

    /**
     * コンストラクタ .
     * @param prm_level 構築する空間レベル
     * @param prm_max_tree_level 想定できる最大空間レベル
     */
    LinearTree(uint32_t prm_level) : Object(),
    _top_space_level(prm_level) {
#ifdef MY_DEBUG
    if (prm_level > MAX_TREE_LEVEL) {
        throwCriticalException("LinearTree::LinearTree() 空間レベルオーバー！ prm_level="<<prm_level);
    }
#endif
        //計算用累乗の配列
        for (int lv = 0; lv < MAX_TREE_LEVEL; lv++) {
            POW_N[lv] = (uint32_t)(pow((double)N , lv));
        }
        //全空間数を求める
        _num_space = ((uint32_t)((POW_N[_top_space_level+1] -1) / (N-1)));
        //線形N分木配列作成
        _paNodeSpaceArray = NEW NodeSpace[_num_space];
        for (uint32_t i = 0; i < _num_space; i++) {
            _paNodeSpaceArray[i]._self_index = i;
        }
        _pRegNodeSpaceList = nullptr;
    }

    /**
     * 要素を空間に登録 .
     * @param prm_pNodeElem
     * @param minnum_in_toplevel BOXの左下手前のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でのモートン順序通し空間番号
     * @param maxnum_in_toplevel BOXの右上奥のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でのモートン順序通し空間番号
     */
    void registerElem(ITreeNodeElem* prm_pNodeElem, const uint32_t minnum_in_toplevel, const uint32_t maxnum_in_toplevel) {
        //どのレベルの空間に所属しているのか取得
        const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
        uint32_t shift_num = 0;
        for (uint32_t i = 0; i < _top_space_level; i++) {
            if (((differ_bit_pos>>(i*DIM)) & (N-1)) != 0 ) {
                shift_num = i+1;
            }
        }
        //【DIM=3, N=8 の線形八分木空間配列での処理説明】
        //xorしたdiffer_bit_pos を 右に3ビットシフトしつつ、マスク &B111(&H7) でANDを取り、&B000 で
        //なくなっている場合、shift_numに値を代入。
        //つまりこれは differ_bit_pos を まず ３ビットに区切り、その3ビットが食い違っている箇所のうち、
        //最も遠い位置をしらべている。
        //食い違う3ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
        //したがって最も遠い3ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
        //最大空間分割Level = 5として、左下手前が6001番、右上奥を6041番に所属していたBOXを例にすると
        //
        //                               lv0 lv1 lv2 lv3 lv4 lv5 ･･･各レベル空間のモートン順序位置
        //     6001 = 00 000 000 000 000 000 001 011 101 110 001
        // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
        // -----------------------------------------------------
        //      232 = 00 000 000 000 000 000 000 000 011 101 000
        //
        //                                                   111 ・・・ マスク
        //                                               111
        //                                           111
        //                                       111
        //  AND)                             111     <--- ここまで行って、最も遠い3ビットが食い違っている箇所が3回目だったことが解る
        // ------------------------------------------------------
        //                                   000 000 011 101 000     <--- 左からのマスク結果が  000 で、それが続く限り、6001番と6041番のモートン順序位置が同じである（=同一空間に所属）を意味する
        //                                    f   f   t   t   f      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) の判定
        //                                    5   4   3   2   1   0  shift_num(シフト回数)
        //                                    o   o   x(以降x)        同一空間に内包されている判定（左からみる）
        //
        //   上記より、6001番と6041番は空間レベル1、レベル2 までは同じ空間レベルに属していたが、
        //   空間レベル3からモートン順序位置が異なってしまうことが解る。したがって、
        //   「所属空間レベル」はLv2空間であると確定できる。これを調べるために
        //   XORが0以外になる最高のシフト回数  shift_num = 3 を求める。
        //   求めるためには、右に3ビットシフトして 0x7 で ANDを調べることを繰り返す必要があるということだ。
        //   Level = 5の場合、5回繰り返し、要は shift_num のシフト回数を調べれば、所属空間レベルが解る！

        //もしXOR結果が
        // 00 000 000 000 000 000 000 000 000 111 の場合ならば shift_num=1
        //これは
        //最大空間分割Level=5 の場合は所属空間レベルは4(=空間レベル5で食い違う)
        //最大空間分割Level=8 の場合は所属空間レベルは7(=空間レベル8で食い違う)

        // 00 000 000 000 000 111 110 000 101 111 などの場合は shift_num=5
        //これは
        //最大空間分割Level=5 の場合は所属空間レベルは0 つまりルート空間レベル所属
        //最大空間分割Level=8 の場合は所属空間レベルは4

        //まとめると
        //最大空間分割Level = 5 の場合
        //shift_num   = 0 1 2 3 4 5
        //所属空間Level = 5 4 3 2 1 0
        //最大空間分割Level=8 の場合
        //shift_num   = 0 1 2 3 4 5 6 7 8
        //所属空間Level = 8 7 6 5 4 3 2 1 0

        //所属空間のモートン順序の通し空間番号を求める
        const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*DIM);

        //不揃いの下位のビットを3ビット単位で除去し、所属のモートン順序番号を求める
        //
        // minnum_in_toplevel>>(shift_num*3); について、
        // minnum_in_toplevel=6001 でも 6041でもどちらでもよく
        //        lv0 lv1 lv2 lv3 lv4 lv5          lv0 lv1 lv2
        // 6001 = 000 001 011 101 110 001   -->    000 001 011 = 11
        // 6041 = 000 001 011 110 011 001   -->    000 001 011 = 11
        //                    ^^^ ^^^ ^^^
        //                  (shift_num*3 ビット除去)
        //
        // のように不揃いのビットを右へシフトしている
        // これで、左下手前が6001番、右上奥を6041番としたBOXは、所属空間Lv2の場合は、モートン順序通し空間番号11番(0番から数えて)であったことがわかる。
        // あとはこれを配列Indexに変換するのみ

        //所属空間(シフト回数)とその空間のモートン順序通し空間番号から線形八分木配列の要素番号を求める
        const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/(N-1);

        //(_POW8[_top_space_level-shift_num]-1)/7;
        //は、線形八分木空間配列の、所属空間レベルの最初の空間の要素番号をあらわす。
        //等比数列の和
        // Σr^k = r^0 + r^1 + r^2 + ... + r^n
        // Σr^k = (1 - r^(n+1)) / (1 - r)
        //
        //線形8分木の配列要素の空間レベルｎまでの合計空関数は r=8 で
        //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 となる
        //ここで、所属空間の最初の空間要素を求めるため、 n = 所属空間レベル-1 の計算値（親空間レベルまでの要素数）の、
        //その次の要素が所属空間レベルの先頭の要素になるはずだ！。という求め方をする。
        //したがって最後に値を +1 したものがほしい値であるが、配列は0番から始まるため、+1 -1 = 0 で、省略してしまおう。
        //先の例でいうと shift_num = 3 で、最大空間分割Level(_top_space_level) = 5 であるので
        // 5 - 3 = 2 で所属空間レベルは 2
        // n = 2 - 1 = 1 を代入して  (8^(1+1) - 1) / 7 = 9 で
        //所属空間のレベル2より一つ親の空間レベルである、空間レベル1までの配列要素数合計は9個とわかる。
        //所望の所属空間レベルは 2の最初の空間は配列は 9+1 の10番目から始まる。
        //配列の10番目とは、配列要素番号は-1して9になる。
        //+1 して -1 するので結局、所属空間レベルxの最初の配列要素番号は  (8^x - 1) / 7 となる

#ifdef MY_DEBUG
        if (index > _num_space-1) {
            throwCriticalException(
               "LinearOctree::registerElem() 空間オーバー !. \n"
               "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
               "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
               "index="<<index<<" _num_space="<<_num_space
            );
        }
#endif
        //要素を線形N分木空間に登録(所属させる)
        NodeSpace* pNodeSpace = &(_paNodeSpaceArray[index]);
        if (pNodeSpace->_pRootNodeElem) {
            pNodeSpace->registerElem(prm_pNodeElem);
        } else {
            pNodeSpace->registerElem(prm_pNodeElem);
            pNodeSpace->_pRegNodeSpaceNext = _pRegNodeSpaceList;
            _pRegNodeSpaceList = pNodeSpace;
        }
    }

    /**
     * 登録を行った空間のクリア処理
     */
    void clearAllElem() {
        //登録済み空間リストを使用してクリア
        NodeSpace* pNodeSpace = _pRegNodeSpaceList;
        while (pNodeSpace) {
            pNodeSpace->_pRootNodeElem = nullptr; //登録済み空間の根本を nullptr でクリア
            uint32_t index = pNodeSpace->_self_index;
            //_kind_bit_field の値は親空間に遡って 0 でリセットする。
            while (true) {
                if (_paNodeSpaceArray[index]._kind_bit_field == 0) {
                    break;
                }
                _paNodeSpaceArray[index]._kind_bit_field = 0;
                if (index == 0) {
                    break;
                }
                //親空間要素番号で繰り返す
                index = (index-1)>>DIM;
            }
            pNodeSpace = pNodeSpace->_pRegNodeSpaceNext;
        }
        //登録済みリストをクリア
        _pRegNodeSpaceList = nullptr;
    }


    /**
     * デバッグ用。登録状況出力 .
     */
    void putTree() {
        putTree(0);
    }

    void putTree(uint32_t prm_index, int prm_lv = 0, int prm_pos = 0) {
        int space_no = prm_index;
        if (_paNodeSpaceArray[prm_index]._kind_bit_field != 0) {
            for (int i = 0; i < prm_lv; i++) {
                space_no -= POW_N[i];
                _TRACE_N_("  ");
            }
            UTIL::dec2bin(_paNodeSpaceArray[prm_index]._kind_bit_field, _aChar_strbit);
            _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /Node->");
            _paNodeSpaceArray[prm_index].dump();
            _TRACE_N_("\n");
        }
        uint32_t lower_level_index = (prm_index<<DIM) + 1;
        if ( lower_level_index >= _num_space) {
            //要素数オーバー、つまりリーフ
            return; //親空間へ戻る
        } else {
            //もぐる
            for (int i = 0; i < (1<<DIM); i++) {
                putTree(lower_level_index+i, prm_lv+1, i);
            }
            return; //親空間へ戻る
        }
    }

    virtual ~LinearTree() {
        GGAF_DELETEARR(_paNodeSpaceArray);
    }
};

//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW8[(MAX_WORLD_HIT_CHECK_OCTREE_LEVEL+1)+1] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};
//
//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW4[(MAX_WORLD_HIT_CHECK_QUADTREE_LEVEL+1)+1] =
//    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
}
#endif /*GGAF_CORE_LINEARTREE_H_*/

