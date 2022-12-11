#ifndef GGAF_CORE_LINEARTREE_H_
#define GGAF_CORE_LINEARTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TreeNode.hpp"
#include "jp/ggaf/core/util/TreeElem.hpp"
#include "jp/ggaf/core/util/Util.h"
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
template<int DIM>
class LinearTree : public Object {

public:
    /** [r]N分木のN	 */
    const uint32_t _N;
    /** [r]N分木の空間を一直線に並べた線形配列 */
    TreeNode<DIM>* _paTreeNodeArray; //_paTreeNodeArray[0] は ROOT空間へのポインタ
    /** [r]登録を行った空間連結リストの根本。_pRegTreeNodeNext で連結されている。（clearAllElem() で使用する） */
    TreeNode<DIM>* _pRegTreeNodeList;
    /** [r]最大空間レベル */
    const uint32_t _top_space_level; //ルート空間はLevel=0
    /** [r]全空間数 */
    uint32_t _num_space;
    char _aChar_strbit[33];
    /** [r]N（N分木のN）の累乗の配列。計算用。(20は十分最大レベル空間と思える適当な値) */
    uint32_t POW_N[20];

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
        _paTreeNodeArray = NEW TreeNode<DIM>[_num_space];
        for (uint32_t i = 0; i < _num_space; i++) {
            _paTreeNodeArray[i]._self_index = i;
        }
        _pRegTreeNodeList = nullptr;
    }

    /**
     * 登録を行った空間のクリア処理
     */
    void clearAllElem() {
        //登録済み空間リストを使用してクリア
        TreeNode<DIM>* pTreeNode = _pRegTreeNodeList;
        while (pTreeNode) {
            pTreeNode->_pBelongElemList = nullptr; //登録済み空間の根本を nullptr でクリア
            uint32_t index = pTreeNode->_self_index;
            //_kind_bit_field の値は親空間に遡って 0 でリセットする。
            while (true) {
                if (_paTreeNodeArray[index]._kind_bit_field == 0) {
                    break;
                }
                _paTreeNodeArray[index]._kind_bit_field = 0;
                if (index == 0) {
                    break;
                }
                //親空間要素番号で繰り返す
                index = (index-1)>>DIM;
            }
            pTreeNode = pTreeNode->_pRegTreeNodeNext;
        }
        //登録済みリストをクリア
        _pRegTreeNodeList = nullptr;
    }

    /**
     *
     * @param prm_pElem
     * @param minnum_in_toplevel BOXの左下手前のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番か
     * @param maxnum_in_toplevel BOXの右上奥のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番か
     */
    void registerElem(TreeElem<DIM>* const prm_pElem, const uint32_t minnum_in_toplevel, const uint32_t maxnum_in_toplevel) {
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
        TreeNode<DIM>* pTreeNode = &(_paTreeNodeArray[index]);
        if (pTreeNode->_pBelongElemList) {
            pTreeNode->registerElem(prm_pElem);
        } else {
            pTreeNode->registerElem(prm_pElem);
            pTreeNode->_pRegTreeNodeNext = _pRegTreeNodeList;
            _pRegTreeNodeList = pTreeNode;
        }
    }
    /**
     * デバッグ用。登録状況出力 .
     */
    void putTree() {
        putTree(0);
    }

    void putTree(uint32_t prm_index, int prm_lv = 0, int prm_pos = 0) {
        int space_no = prm_index;
        if (_paTreeNodeArray[prm_index]._kind_bit_field != 0) {
            for (int i = 0; i < prm_lv; i++) {
                space_no -= POW_N[i];
                _TRACE_N_("  ");
            }
            UTIL::strbin(_paTreeNodeArray[prm_index]._kind_bit_field, _aChar_strbit);
            _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /TreeElem->");
            _paTreeNodeArray[prm_index].dump();
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
        GGAF_DELETEARR(_paTreeNodeArray);
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

