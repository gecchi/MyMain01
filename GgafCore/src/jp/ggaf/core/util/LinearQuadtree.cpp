#include "jp/ggaf/core/util/LinearQuadtree.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/util/TreeSpace.hpp"
#include "jp/ggaf/core/util/Util.h"

using namespace GgafCore;

//const uint32_t LinearQuadtree::_POW4[(MAX_QUADTREE_LEVEL+1)+1] =
//    {1, 4, 16, 64, 256, 1024, 4096, 16384, 65536, 262144, 1048576, 4194304, 16777216, 67108864, 268435456, 1073741824};

LinearQuadtree::LinearQuadtree(uint32_t prm_level,
                                       int x1, int y1,
                                       int x2, int y2) : LinearTree(prm_level),
//_top_space_level(prm_level),
_root_x1(x1),
_root_y1(y1),
_root_x2(x2),
_root_y2(y2),
_top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<_top_space_level))) + 1 ), //+1は空間数をオーバーしないように余裕をもたせるため
_r_top_level_dx(1.0 / _top_level_dx),
_r_top_level_dy(1.0 / _top_level_dy)
{
//    _num_space = (uint32_t)((_POW4[_top_space_level+1] -1) / 3);
    //線形四分木配列作成
    _TRACE_("LinearQuadtree::LinearQuadtree("<<prm_level<<") 線形四分木空間配列要素数 _num_space="<<_num_space);
//    _paTreeSpaceArray = NEW TreeSpace<2u>[_num_space];
//    for (uint32_t i = 0; i < _num_space; i++) {
//        _paTreeSpaceArray[i]._my_index = i;
//    }
//    _pRegTreeSpaces = nullptr;
    _TRACE_(FUNC_NAME<<" 四分木ルートレベル(level=0)の空間位置=(" << _root_x1 << "," << _root_y1 << ")-(" << _root_x2 << "," << _root_y2 << ")");
    _TRACE_(FUNC_NAME<<" 四分木ルートレベル(level=0)の空間の広さ=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 );
    _TRACE_(FUNC_NAME<<" 四分木末端レベル(level="<<_top_space_level<<")の空間の広さ=" << _top_level_dx << "x" << _top_level_dy );
}


void LinearQuadtree::registerElem(TreeElem<2u>* const prm_pElem,
                                      int tx1, int ty1,
                                      int tx2, int ty2 ) {

    //はみ出る場合は補正
    if (tx1 <= _root_x1)  { tx1 = _root_x1; }
    if (tx2 >= _root_x2)  { tx2 = _root_x2; }
    if (ty1 <= _root_y1)  { ty1 = _root_y1; }
    if (ty2 >= _root_y2)  { ty2 = _root_y2; }
    //軸座標の大小が裏返った場合、つまりLevel0より外か、Level0全体より大きい場合は無視する
    if (tx1 >= tx2 || ty1 >= ty2) {
        return; //空間外は登録しない
    }

    //＜tx1,ty1,tx2,ty2 から、空間番号 を求める＞
    //Rect(要素)領域座標から空間配列要素番号（線形四分木配列の要素番号）を算出 .
    //まず、Rect(要素)の所属空間 Level と、その空間Levelのモートン順序通し空間番号を求め
    //モートン順序通し空間番号から計算して配列の index を求める。


    //Rect(要素)の左上のXY座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    const uint32_t minnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy)
                                        );

    //Rect(要素)の右下のXY座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    const uint32_t maxnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy)
                                        );                 //↑_root_x2,_root_y2 と間違えていません。

    LinearTree::registerElem(prm_pElem, minnum_in_toplevel, maxnum_in_toplevel);
//    //引数のRect(要素)は、どのレベルの空間に所属（内包されている）しているのか、最大のレベル空間を取得
//    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
//    uint32_t shift_num = 0;
//    for (uint32_t i = 0; i < _top_space_level; i++) {
//        if (((differ_bit_pos>>(i*2)) & 0x3) != 0 ) {
//            shift_num = i+1;
//        }
//    }
//    //xorしたdiffer_bit_pos を 右に2ビットシフトしつつ、マスク &B11(&H3) でANDを取り、&B000 で
//    //なくなっている場合、shift_numに値を代入。
//    //つまりこれは differ_bit_pos を まず2ビットに区切り、その2ビットが食い違っている箇所のうち、
//    //最も遠い位置をしらべている。
//    //食い違う2ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
//    //したがって最も遠い2ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
//    //最大空間分割 Level = 5 として、左上が804番、右下を877番に所属していたRect(要素)を例にすると
//    //
//    //                                         L0 L1 L2 L3 L4 L5 ・・・各レベル空間のモートン順序位置
//    //     804 = 00 00 00 00 00 00 00 00 00 00 00 11 01 00 10 00
//    // XOR)877 = 00 00 00 00 00 00 00 00 00 00 00 11 01 10 11 01
//    // ------------------------------------------------------------
//    //      37 = 00 00 00 00 00 00 00 00 00 00 00 00 00 10 01 01
//    //
//    //                                                        11 ・・・ マスク
//    //                                                     11
//    //                                                  11
//    //                                               11
//    //  AND)                                      11     <--- ここまで行って、最も遠い3ビットが食い違っている箇所が3回目だったことが解る
//    // -------------------------------------------------------------
//    //                                            00 00 10 01 01     <--- 左からのマスク結果が  00 で、それが続く限り、、804番と877番のモートン順序位置が同じである（=同一空間に所属）を意味する
//    //                                            f  f  t  t  t      if (differ_bit_pos>>(i*2)) & 0x3 != 0 ) の判定
//    //                                            5  4  3  2  1  0   shift_num(シフト回数)
//    //                                            o  o  x(以降x)      同一空間に無いほうされている判定（左からみる）
//    //
//    //   上記より、804番と877番は空間レベル1、レベル2 までは同じ空間レベルに属していたが、
//    //   空間レベル3からモートン順序位置が異なってしまうことが解る。したがって、
//    //   「所属空間（MAX）レベル」はLv2空間であると確定できる。これを調べるために
//    //   XORが0以外になる最高のシフト回数  shift_num = 3 を求める。
//    //   求めるためには、右に3ビットシフトして 0x3 で ANDを調べることを繰り返す必要があるということだ。
//    //   Level = 5の場合、5回繰り返し、要は shift_num のシフト回数を調べれば、所属空間レベルが解る！
//
//    //もしXOR結果が
//    // 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 11 の場合ならば shift_num=1
//    //これは
//    //最大空間分割Level=5 の場合は所属空間レベルは4(=空間レベル5で食い違う)
//    //最大空間分割Level=8 の場合は所属空間レベルは7(=空間レベル8で食い違う)
//
//    // 00 00 00 00 00 00 00 00 00 00 00 11 10 00 10 00 の場合は shift_num=5
//    //これは
//    //最大空間分割Level=5 の場合は所属空間レベルは0 つまりルート空間レベル所属
//    //最大空間分割Level=8 の場合は所属空間レベルは4
//
//    //まとめると
//    //最大空間分割Level = 5 の場合
//    //shift_num   = 0 1 2 3 4 5
//    //所属空間Level = 5 4 3 2 1 0
//    //最大空間分割Level=8 の場合
//    //shift_num   = 0 1 2 3 4 5 6 7 8
//    //所属空間Level = 8 7 6 5 4 3 2 1 0
//
//    //所属空間のモートン順序の通し空間番号を求める
//    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*2);
//    //不揃いの下位のビットを2ビット単位で除去し、所属のモートン順序番号を求める
//    //
//    // minnum_in_toplevel>>(shift_num*2); について、
//    // minnum_in_toplevel=804 でも 877でもどちらでもよく
//    //       L0 L1 L2 L3 L4 L5          L0 L1 L2
//    // 804 = 00 11 01 00 10 00   -->    00 11 01 = 13
//    // 877 = 00 11 01 10 11 01   -->    00 11 01 = 13
//    //                ^^ ^^ ^^
//    //                  (shift_num*2 ビット除去)
//    //
//    // のように不揃いのビットを右へシフトしている
//    // これで、左上が804番、右下を877番としたRect(要素)は、所属空間Lv2の場合は、モートン順序通し空間番号13番(0番から数えて)であったことがわかる。
//    // あとはこれを配列Indexに変換するのみ
//
//    //所属空間(シフト回数)とその空間のモートン順序通し空間番号から線形四分木配列の要素番号を求める
//    const uint32_t index = morton_order_space_num + (POW2D[_top_space_level-shift_num]-1)/3;
//    //(_POW4[_top_space_level-shift_num]-1)/7;
//    //は、線形四分木空間配列の、所属空間レベルの最初の空間の要素番号をあらわす。
//    //等比数列の和
//    // Σr^k = r^0 + r^1 + r^2 + ... + r^n
//    // Σr^k = (1 - r^(n+1)) / (1 - r)
//    //
//    //線形4分木の配列要素の空間レベルｎまでの合計空関数は r=4 で
//    //(1 - 4^(n+1)) / (1-4)  =  (1-4^(n+1)) / -3  =  (4^(n+1) - 1) / 3 となる
//    //ここで、所属空間の最初の空間要素を求めるため、 n = 所属空間レベル-1 の計算値（親空間レベルまでの要素数）の、
//    //その次の要素が所属空間レベルの先頭の要素になるはずだ！。という求め方をする。
//    //したがって最後に値を +1 したものがほしい値であるが、配列は0番から始まるため、+1 -1 = 0 で、省略してしまおう。
//    //先の例でいうと shift_num = 3 で、最大空間分割Level(_top_space_level) = 5 であるので
//    // 5 - 3 = 2 で所属空間レベルは 2
//    // n = 2 - 1 = 1 を代入して  (4^(1+1) - 1) / 3 = 5 で
//    //所属空間のレベル2より一つ親の空間レベルである、空間レベル1までの配列要素数合計は5個とわかる。
//    //所望の所属空間レベルは 2の最初の空間は配列は 5+1 の6番目から始まる。
//    //配列の6番目とは、配列要素番号は-1して5になる。
//    //+1 して -1 するので結局、所属空間レベルxの最初の配列要素番号は  (4^x - 1) / 3 となる
//
//
//#ifdef MY_DEBUG
//    if (index > _num_space-1) {
//
//        _TRACE_(
//           "LinearQuadtree::registerElem() 空間オーバー !. \n"
//           "Root=("<<_root_x1<<","<<_root_y1<<")-("<<_root_x2<<","<<_root_y2<<")\n"
//           "Elem=("<<tx1<<","<<ty1<<")-("<<tx2<<","<<ty2<<")\n"
//           "_top_level_dx="<<_top_level_dx<<" _top_level_dy="<<_top_level_dy<<"\n"
//           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
//           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
//           "index="<<index<<" _num_space="<<_num_space
//        );
//        _TRACE_("Min_x_index="<<((uint32_t)((tx1 - _root_x1) / _top_level_dx)));
//        _TRACE_("Min_y_index="<<((uint32_t)((ty1 - _root_y1) / _top_level_dy)));
//        _TRACE_("Man_x_index="<<((uint32_t)((tx2 - _root_x1) / _top_level_dx)));
//        _TRACE_("Man_y_index="<<((uint32_t)((ty2 - _root_y1) / _top_level_dy)));
//    }
//#endif
//
//    //要素を線形四分木空間に登録(所属させる)
//    TreeSpace<2u>* pTreeSpace = &(_paTreeSpaceArray[index]);
//    if (pTreeSpace->_pBelongElems) {
//        pTreeSpace->registerElem(prm_pElem);
//    } else {
//        pTreeSpace->registerElem(prm_pElem);
//        pTreeSpace->_pRegTreeSpaceNext = _pRegTreeSpaces;
//        _pRegTreeSpaces = pTreeSpace;
//    }
}

//void LinearQuadtree::clearAllElem() {
//    //登録済み空間リストを使用して、四分木をクリア
//    TreeSpace<2u>* pTreeSpace = _pRegTreeSpaces;
//    while (pTreeSpace) {
//        pTreeSpace->_pBelongElems = nullptr;
//        uint32_t index = pTreeSpace->_my_index;
//        while (true) {
//            if (_paTreeSpaceArray[index]._kind_bit_field == 0) {
//                break;
//            }
//            _paTreeSpaceArray[index]._kind_bit_field = 0;
//            if (index == 0) {
//                break;
//            }
//            //親空間要素番号で繰り返す
//            index = (index-1)>>2;
//        }
//
//        pTreeSpace = pTreeSpace->_pRegTreeSpaceNext;
//    }
//    _pRegTreeSpaces = nullptr;
//}

LinearQuadtree::~LinearQuadtree() {
//    GGAF_DELETEARR(_paTreeSpaceArray);
}

//void LinearQuadtree::putTree(uint32_t prm_index, int prm_lv, int prm_pos) {
//    int space_no = prm_index;
//    if (_paTreeSpaceArray[prm_index]._kind_bit_field != 0) {
//        for (int i = 0; i < prm_lv; i++) {
//            space_no -= _POW4[i];
//            _TRACE_N_("  ");
//        }
//        UTIL::strbin(_paTreeSpaceArray[prm_index]._kind_bit_field, _aChar_strbit);
//        _TRACE_N_("LV"<<prm_lv<<"-"<<space_no<<"(POS:"<<prm_pos<<")["<<prm_index<<"]="<<_aChar_strbit<<" /TreeElem->");
//        _paTreeSpaceArray[prm_index].dump();
//        _TRACE_N_("\n");
//    }
//    uint32_t lower_level_index = (prm_index<<2) + 1;
//    if ( lower_level_index >= _num_space) {
//        //要素数オーバー、つまりリーフ
//        return; //親空間へ戻る
//    } else {
//        //もぐる
//        for (int i = 0; i < (1<<2); i++) {
//            putTree(lower_level_index+i, prm_lv+1, i);
//        }
//        return; //親空間へ戻る
//    }
//}
//
//void LinearQuadtree::putTree() {
//    putTree(0);
//}


