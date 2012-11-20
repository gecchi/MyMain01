#include "stdafx.h"
using namespace GgafCore;


GgafLinearOctree::GgafLinearOctree(int prm_level) {
    _top_space_level = prm_level;
    _top_level_dX = 0;
    _top_level_dY = 0;
    _top_level_dZ = 0;
    _root_X1 = 0;
    _root_Y1 = 0;
    _root_Z1 = 0;
    _root_X2 = 0;
    _root_Y2 = 0;
    _root_Z2 = 0;
    //べき乗作成
    _paUint32_pow = NEW UINT32[(prm_level+1)+1];
    _paUint32_pow[0] = 1;
    for(int i = 1; i < (prm_level+1)+1; i++) {
        _paUint32_pow[i] = _paUint32_pow[i-1] * 8;
        //_TRACE_("_paUint32_pow["<<i<<"]="<<_paUint32_pow[i]);
    }
    //線形８分木配列作成
    _num_space = (int)((_paUint32_pow[_top_space_level+1] -1) / 7); //空間数
    _TRACE_("線形八分木空間配列要素数 _num_space="<<_num_space);
    _paSpace = NEW GgafLinearOctreeSpace[_num_space];
    for (UINT32 i = 0; i < _num_space; i++) {
        _paSpace[i]._my_index = i;
    }
    _pRegElemFirst = nullptr;
}

void GgafLinearOctree::setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
    _root_X1 = X1;
    _root_Y1 = Y1;
    _root_Z1 = Z1;
    _root_X2 = X2;
    _root_Y2 = Y2;
    _root_Z2 = Z2;
    _top_level_dX = ((_root_X2-_root_X1) / ((float)(1<<_top_space_level))) + 1;
    _top_level_dY = ((_root_Y2-_root_Y1) / ((float)(1<<_top_space_level))) + 1;
    _top_level_dZ = ((_root_Z2-_root_Z1) / ((float)(1<<_top_space_level))) + 1; //+1は空間数をオーバーしないように余裕をもたせるため
    _TRACE_("八分木レベル0空間=" << _root_X2-_root_X1 << "x" << _root_Y2-_root_Y1 << "x" << _root_Z2-_root_Z1);
    _TRACE_("八分木レベル"<<_top_space_level<<"空間=" << _top_level_dX << "x" << _top_level_dY << "x" << _top_level_dZ);
}

void GgafLinearOctree::registElem(GgafLinearOctreeElem* prm_pElem,
                                  int tX1 ,int tY1 ,int tZ1,
                                  int tX2 ,int tY2 ,int tZ2) {

    //はみ出る場合は補正
    if (tX1 <= _root_X1)  { tX1 = _root_X1+1; }
    if (tX2 >= _root_X2)  { tX2 = _root_X2-1; }
    if (tY1 <= _root_Y1)  { tY1 = _root_Y1+1; }
    if (tY2 >= _root_Y2)  { tY2 = _root_Y2-1; }
    if (tZ1 <= _root_Z1)  { tZ1 = _root_Z1+1; }
    if (tZ2 >= _root_Z2)  { tZ2 = _root_Z2-1; }

    //軸座標の大小が裏返った場合、つまりLevel0より外か、Level0全体より大きい場合は無視する
    if (tX1 >= tX2 || tY1 >= tY2 || tZ1 >= tZ2) {
        return; //空間外は登録しない
    }

    //BOX領域座標から空間配列要素番号（線形八分木配列の要素番号）を算出 .
    //まず、BOXの所属空間 Level と、その空間Levelのモートン順序通し空間番号を求め
    //モートン順序通し空間番号から計算して配列のIndexを求める。
    UINT32 index = 0xffffffff; //tX1,tY1,tZ1,tX2,tY2,tZ2 から、これ(index)を求める

    //BOXの左下手前のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    UINT32 minnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (UINT32)((tX1 - _root_X1) / _top_level_dX),
                                  (UINT32)((tY1 - _root_Y1) / _top_level_dY),
                                  (UINT32)((tZ1 - _root_Z1) / _top_level_dZ)
                                );

    //BOXの右上奥のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    UINT32 maxnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (UINT32)((tX2 - _root_X1) / _top_level_dX),
                                  (UINT32)((tY2 - _root_Y1) / _top_level_dY),
                                  (UINT32)((tZ2 - _root_Z1) / _top_level_dZ)
                                );                 //↑_root_X2,_root_Y2,_root_Z2 と間違えていません。


    //引数のBOXは、どのレベルの空間に所属しているのか取得
    UINT32 differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    UINT32 shift_num = 0;
    UINT32 lv = (UINT32)_top_space_level;
    for(UINT32 i = 0; i < lv; i++) {
        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
            shift_num = i+1;
        }
    }
    //xorしたdiffer_bit_pos を 右に3ビットシフトしつつ、マスク &B111(&H7) でANDを取り、&B000 で
    //なくなっている場合、shift_numに値を代入。
    //つまりこれは differ_bit_pos を まず ３ビットに区切り、その3ビットが食い違っている箇所のうち、
    //最も遠い位置をしらべている。
    //食い違う3ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
    //したがって最も遠い3ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
    //最大空間分割Level = 5として、左下手前が6001番、右上奥を6041番に所属していたBOXを例にすると
    //
    //各レベル空間のモートン順序位置 lv0 lv1 lv2 lv3 lv4 lv5
    //     6001 = 00 000 000 000 000 000 001 011 101 110 001
    // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
    // -----------------------------------------------------
    //      232 = 00 000 000 000 000 000 000 000 011 101 000
    //
    //                                                   111
    //                                               111
    //                                           111
    //                                       111
    //  AND)                             111     <--- ここまで行って、最も遠い3ビットが食い違っている箇所が3回目だったことが解る
    // ------------------------------------------------------
    //                                   000 000 011 101 000
    //                                    o   o   x   x   o      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) の判定
    //                                    5   4   3   2   1   0   shift_num(シフト回数)
    //
    //   上記より、6001番と6041番は空間レベル1、レベル2 までは同じ空間レベルに属していたが、
    //   空間レベル3からモートン順序位置が異なってしまうことが解る。したがって、
    //   「所属空間レベル」はLv2空間であると確定できる。これを調べるために
    //   XORが0以外になる最高のシフト回数  shift_num = 3 を求める。
    //   求めるためには、右に3ビットシフトして 0x7 で ANDを調べることを繰り返す必要があるということだ。
    //   要は shift_num のシフト回数を調べれば、所属空間レベルが解る！

    //もしXOR結果が
    // 000 000 000 000 000 000 000 111 の場合ならば shift_num=1
    //これは
    //最大空間分割Level=5 の場合は所属空間レベルは4(=空間レベル5で食い違う)
    //最大空間分割Level=8 の場合は所属空間レベルは7(=空間レベル8で食い違う)

    // 000 000 000 111 110 000 101 111 などの場合は shift_num=5
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
    UINT32 morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
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
    // これで、左下手前が6001番、右上奥を6041番としたBOXは、所属空間Lv2の場合は、モートン順序通し空間番号11番であったことがわかる。
    // あとはこれを配列Indexに変換するのみ

    //所属空間(シフト回数)とその空間のモートン順序通し空間番号から線形八分木配列の要素番号を求める
    index = morton_order_space_num + (_paUint32_pow[_top_space_level-shift_num]-1)/7;
    //(_paUint32_pow[_top_space_level-shift_num]-1)/7;
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

        _TRACE_(
           "GgafLinearOctree::registElem() 空間オーバー !. \n"<<
           "Root=("<<_root_X1<<","<<_root_Y1<<","<<_root_Z1<<")-("<<_root_X2<<","<<_root_Y2<<","<<_root_Z2<<")\n"<<
           "Elem=("<<tX1<<","<<tY1<<","<<tZ1<<")-("<<tX2<<","<<tY2<<","<<tZ2<<")\n"<<
           "_top_level_dX="<<_top_level_dX<<" _top_level_dY="<<_top_level_dY<<" _top_level_dZ="<<_top_level_dZ<<"\n"<<
           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"<<
           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"<<
           "index="<<index<<" _num_space="<<_num_space
        );
        _TRACE_("Min_X_index="<<((UINT32)((tX1 - _root_X1) / _top_level_dX)));
        _TRACE_("Min_Y_index="<<((UINT32)((tY1 - _root_Y1) / _top_level_dY)));
        _TRACE_("Min_Z_index="<<((UINT32)((tZ1 - _root_Z1) / _top_level_dZ)));
        _TRACE_("Man_X_index="<<((UINT32)((tX2 - _root_X1) / _top_level_dX)));
        _TRACE_("Man_Y_index="<<((UINT32)((tY2 - _root_Y1) / _top_level_dY)));
        _TRACE_("Man_Z_index="<<((UINT32)((tZ2 - _root_Z1) / _top_level_dZ)));
    }
#endif

    //登録Elemリストに追加（後でクリアしたいが為）
    if (prm_pElem->_pSpace_current == nullptr) {
        if (_pRegElemFirst == nullptr) {
            prm_pElem->_pRegLinkNext = nullptr;
            _pRegElemFirst = prm_pElem;
        } else {
            prm_pElem->_pRegLinkNext = _pRegElemFirst;
            _pRegElemFirst = prm_pElem;
        }
    } else {
#ifdef MY_DEBUG
        throwGgafCriticalException("GgafLinearOctree::registElem() 登録しようとした引数要素は、他の空間に所属状態です。"<<
                                   "クリアがなされていないか、２重登録しています。現所属空間インデックス="<<(prm_pElem->_pSpace_current->_my_index)<<"  要素対象オブジェクト="<<(prm_pElem->_pObject));
#endif
    }

    prm_pElem->_pLinearOctree = this;
    //要素を線形８分木空間に登録(所属させる)
    prm_pElem->belongTo(&(_paSpace[index]));
}

void GgafLinearOctree::clearElem() {
    if (_pRegElemFirst == nullptr) {
        return;
    }
    GgafLinearOctreeElem* pElem = _pRegElemFirst;
    while(true) {
        pElem->clear();
        pElem = pElem -> _pRegLinkNext;
        if (pElem == nullptr) {
            break;
        }
    }
    _pRegElemFirst = nullptr;
}

GgafLinearOctree::~GgafLinearOctree() {
    DELETEARR_IMPOSSIBLE_NULL(_paSpace);
    DELETEARR_IMPOSSIBLE_NULL(_paUint32_pow);
}


void GgafLinearOctree::putTree() {
    char aChar_strbit[33];
    int lv0_order_num = 0;
    int lv1_order_num = 0;
    int lv2_order_num = 0;
    int lv3_order_num = 0;
    int lv4_order_num = 0;
    int lv5_order_num = 0;
    int lv6_order_num = 0;
    int lv7_order_num = 0;
    int lv8_order_num = 0;

    int lv0_order_pos = 0;

    int LV0 = 0;


    if (_paSpace[0]._kindinfobit == 0) {
        _TRACE_("8分木に何も無し！");
    } else {
        UTIL::strbin(_paSpace[LV0]._kindinfobit, aChar_strbit);
        _TEXT_("LV0."<<lv0_order_num<<"(POS:"<<lv0_order_pos<<")["<<LV0<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV0].dump();
        _TEXT_("\n");
    }

    UINT32 index_lv1_begin = LV0*8 + 1;
    if (index_lv1_begin > _num_space-1) { return; }

    for (UINT32 LV1 = index_lv1_begin, lv1_order_pos = 0; LV1 < index_lv1_begin+8; LV1++, lv1_order_num++, lv1_order_pos++) {
        if (_paSpace[LV1]._kindinfobit == 0) { continue; }
        UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
        _TEXT_("  LV1-"<<lv1_order_num<<"(POS:"<<lv1_order_pos<<")["<<LV1<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
        _paSpace[LV1].dump();
        _TEXT_("\n");
        ////
        UINT32 index_lv2_begin = LV1*8 + 1;
        if (index_lv2_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック

        for (UINT32 LV2 = index_lv2_begin, lv2_order_pos = 0; LV2 < index_lv2_begin+8; LV2++, lv2_order_num++, lv2_order_pos++) {
            if (_paSpace[LV2]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
            UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
            _TEXT_("    LV2-"<<lv2_order_num<<"(POS:"<<lv2_order_pos<<")["<<LV2<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
            _paSpace[LV2].dump();
            _TEXT_("\n");
            ///
            UINT32 index_lv3_begin = LV2*8 + 1;
            if (index_lv3_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
            for (UINT32 LV3 = index_lv3_begin, lv3_order_pos = 0; LV3 < index_lv3_begin+8; LV3++, lv3_order_num++, lv3_order_pos++) {
                if (_paSpace[LV3]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                _TEXT_("      LV3-"<<lv3_order_num<<"(POS:"<<lv3_order_pos<<")["<<LV3<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                _paSpace[LV3].dump();
                _TEXT_("\n");
                ///
                UINT32 index_lv4_begin = LV3*8 + 1;
                if (index_lv4_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                for (UINT32 LV4 = index_lv4_begin, lv4_order_pos = 0; LV4 < index_lv4_begin+8; LV4++, lv4_order_num++, lv4_order_pos++) {
                    if (_paSpace[LV4]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                    UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                    _TEXT_("        LV4-"<<lv4_order_num<<"(POS:"<<lv4_order_pos<<")["<<LV4<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                    _paSpace[LV4].dump();
                    _TEXT_("\n");
                    ///
                    UINT32 index_lv5_begin = LV4*8 + 1;
                    if (index_lv5_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                    for (UINT32 LV5 = index_lv5_begin, lv5_order_pos = 0; LV5 < index_lv5_begin+8; LV5++, lv5_order_num++, lv5_order_pos++) {
                        if (_paSpace[LV5]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                        UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                        _TEXT_("          LV5-"<<lv5_order_num<<"(POS:"<<lv5_order_pos<<")["<<LV5<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                        _paSpace[LV5].dump();
                        _TEXT_("\n");
                        ///
                        UINT32 index_lv6_begin = LV5*8 + 1;
                        if (index_lv6_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                        for (UINT32 LV6 = index_lv6_begin, lv6_order_pos = 0; LV6 < index_lv6_begin+8; LV6++, lv6_order_num++, lv6_order_pos++) {
                            if (_paSpace[LV6]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                            UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                            _TEXT_("            LV6-"<<lv6_order_num<<"(POS:"<<lv6_order_pos<<")["<<LV6<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                            _paSpace[LV6].dump();
                            _TEXT_("\n");
                            ///
                            UINT32 index_lv7_begin = LV6*8 + 1;
                            if (index_lv7_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                            for (UINT32 LV7 = index_lv7_begin, lv7_order_pos = 0; LV7 < index_lv7_begin+8; LV7++, lv7_order_num++, lv7_order_pos++) {
                                if (_paSpace[LV7]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                                UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                                _TEXT_("              LV7-"<<lv7_order_num<<"(POS:"<<lv7_order_pos<<")["<<LV7<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                                _paSpace[LV7].dump();
                                _TEXT_("\n");
                                ///
                                UINT32 index_lv8_begin = LV7*8 + 1;
                                if (index_lv8_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                                for (UINT32 LV8 = index_lv8_begin, lv8_order_pos = 0; LV8 < index_lv8_begin+8; LV8++, lv8_order_num++, lv8_order_pos++) {
                                    if (_paSpace[LV8]._kindinfobit == 0) { continue; }  //何も無いので下位表示を飛ばし
                                    UTIL::strbin(_paSpace[LV1]._kindinfobit, aChar_strbit);
                                    _TEXT_("                LV8-"<<lv8_order_num<<"(POS:"<<lv8_order_pos<<")["<<LV8<<"]="<<aChar_strbit<<" /GgafLinearOctreeElem->");
                                    _paSpace[LV8].dump();
                                    _TEXT_("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


