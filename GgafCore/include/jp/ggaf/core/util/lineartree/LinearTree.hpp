#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/util/lineartree/LinearTreeRounder.hpp"
#include <math.h>

namespace GgafCore {

/**
 * 線形N分木共通 .
 * 線形4分木と線形8分木の共通処理をまとめたクラス
 * @tparam DIM 次元。2の場合4分木、3の場合8分木の機能となる。
 * @version 1.00
 * @since 2022/12/11
 * @author Masatoshi Tsuge
 */
template<class T, int DIM>
class LinearTree : public Object {

public:

    /**
     * 線形N分木配列用空間にぶら下がる要素クラス .
     * @version 1.00
     * @since 2009/11/23
     * @author Masatoshi Tsuge
     */
    class NodeElem : public Object {
    public:
        /** [r]要素オブジェクト（これが本体） */
        T* const _pObject;
        /** [r]要素オブジェクトの種別 */
        kind_t _kind;
        /** [r]空間に登録された要素（NodeSpace._pNodeValueList）にぶら下がる次要素 */
        NodeElem* _pNextValue;
        /**
         * コンストラクタ .
         * @param prm_pObject 対象オブジェクト(キャラクタなどN分木で管理したい実際の値)
         */
        NodeElem(T* prm_pObject) : Object() ,
            _pObject(prm_pObject)
        {
            _kind = 0;
            _pNextValue = nullptr;
        }
        void dump() {
            _TRACE_N_("o");
        }
        virtual ~NodeElem() {
        }
    };


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
        /** [r]この空間に登録された要素連結リストの根本。_pNextValue で連結されている。 */
        NodeElem* _pNodeValueList;
        /** [r]登録を行った空間連結リスト用、次の空間(開放時に使用) */
        NodeSpace* _pRegNodeSpaceNext;
    public:
        /**
         * コンストラクタ
         * @return
         */
        NodeSpace() : Object() {
            _pNodeValueList = nullptr;
            _kind_bit_field = 0;
            _self_index = 0xffffffff; //ありえない0xffffffffを入れておく
            _pRegNodeSpaceNext = nullptr;
        }
        /**
         * 要素登録 .
         * @param prm_pElem 要素
         * @return true:そのインデックスに初回登録 ／ false:それ以外
         */
        void registerElem(NodeElem* const prm_pElem) {
            //引数の要素番号
            uint32_t index = _self_index;
            const kind_t this_kind = prm_pElem->_kind;
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
            prm_pElem->_pNextValue = _pNodeValueList; //初回は _pNodeValueList == nullptr
            _pNodeValueList = prm_pElem;
        }
        void dump() {
            if (_pNodeValueList == nullptr) {
                _TRACE_N_("x");
            } else {
                NodeElem* pElem = _pNodeValueList;
                while (pElem) {
                    pElem->dump();
                    pElem = pElem ->_pNextValue;
                }
            }
        }
        virtual ~NodeSpace() {
        }
    };

public:
    /** [r]N分木のN、2のDIM乗の値が入る（DIM:2→4, DIM:3→8,…)。	 */
    const uint32_t _N;
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
    uint32_t POW_N[20];

    LinearTreeRounder<T,DIM>* _pLinearTreeRounder;
    /**
     * コンストラクタ .
     * @param prm_level 構築する空間レベル
     * @param prm_max_tree_level 想定できる最大空間レベル
     */
    LinearTree(uint32_t prm_level) : Object(),
    _N((uint32_t)pow(2.0, DIM)),
    _top_space_level(prm_level) {
        //計算用累乗の配列
        for (int lv = 0; lv < 20; lv++) {
            POW_N[lv] = (uint32_t)(pow((double)_N , lv));
        }
        //全空間数を求める
        _num_space = ((uint32_t)((POW_N[_top_space_level+1] -1) / (_N-1)));
        //線形N分木配列作成
        _paNodeSpaceArray = NEW NodeSpace[_num_space];
        for (uint32_t i = 0; i < _num_space; i++) {
            _paNodeSpaceArray[i]._self_index = i;
        }
        _pRegNodeSpaceList = nullptr;
        _pLinearTreeRounder = nullptr;
    }

    LinearTreeRounder<T,DIM>* getLinearTreeRounder(void (T::*prm_pFunc)(T*)) {
        if (!_pLinearTreeRounder) {
            _pLinearTreeRounder = NEW LinearTreeRounder<T,DIM>(_paNodeSpaceArray,
                                                               _num_space,
                                                                prm_pFunc);
        }
        return _pLinearTreeRounder;
    }

    /**
     * 要素を空間に登録 .
     * @param prm_pElem
     * @param minnum_in_toplevel BOXの左下手前のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でのモートン順序通し空間番号
     * @param maxnum_in_toplevel BOXの右上奥のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でのモートン順序通し空間番号
     */
    void registerElem(NodeElem* const prm_pElem, const uint32_t minnum_in_toplevel, const uint32_t maxnum_in_toplevel) {
        //どのレベルの空間に所属しているのか取得
        const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
        uint32_t shift_num = 0;
        for (uint32_t i = 0; i < _top_space_level; i++) {
            if (((differ_bit_pos>>(i*DIM)) & (_N-1)) != 0 ) {
                shift_num = i+1;
            }
        }
        //次の２行の意味は、LinearOctree.cpp、LinearQuadtree.cpp のコメント「以下は共通化前のコード」以降を参照
        const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*DIM);
        const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/(_N-1);

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
        if (pNodeSpace->_pNodeValueList) {
            pNodeSpace->registerElem(prm_pElem);
        } else {
            pNodeSpace->registerElem(prm_pElem);
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
            pNodeSpace->_pNodeValueList = nullptr; //登録済み空間の根本を nullptr でクリア
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
            UTIL::strbin(_paNodeSpaceArray[prm_index]._kind_bit_field, _aChar_strbit);
            _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /NodeElem->");
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
        GGAF_DELETE_NULLABLE(_pLinearTreeRounder);
    }
};

//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW8[(MAX_OCTREE_LEVEL+1)+1] = {1, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};
//
//template<int DIM>
//const uint32_t LinearTree<DIM>::_POW4[(MAX_QUADTREE_LEVEL+1)+1] =
//    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};
}
#endif /*GGAF_CORE_LINEARTREE_H_*/

