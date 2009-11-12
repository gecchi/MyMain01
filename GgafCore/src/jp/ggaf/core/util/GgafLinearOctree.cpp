#include "stdafx.h"
using namespace std;
using namespace GgafCore;



////// GgafLinearOctree::Space //////

GgafLinearOctree::Space::Space() {
    _pElemFirst = NULL;
    _pElemLast = NULL;
    _my_index = 0;
    _kindinfobit = 0;
}

void GgafLinearOctree::Space::dump() {
    if (_pElemFirst == NULL) {
        _TEXT_("x");
    } else {
        Elem* pElem = _pElemFirst;
        while (true) {
            pElem->dump();

            if (pElem == _pElemLast) {
                break;
            }
            pElem = pElem -> _pNext;
        }
    }
}
GgafLinearOctree::Space::~Space() {
}


////// GgafLinearOctree::Elem //////

GgafLinearOctree::Elem::Elem(GgafObject* prm_pObject, DWORD prm_kindbit) {
    _pSpace_Current = NULL;
    _pNext = NULL;
    _pPrev = NULL;
    _pObject = prm_pObject;
    _kindbit = prm_kindbit;
    _pLinearOctree = NULL;
    _pRegLinkNext = NULL;
}

void GgafLinearOctree::Elem::extract() {
    if(_pSpace_Current == NULL) {
        //_TRACE_("GgafLinearOctree::Elem::extract() できません。意図してますか？");
        return;
    }
    //情報リセット
    int index = _pSpace_Current->_my_index;
    while(true) {
        //一つでもextract()すると情報は崩れることを注意、アプリケーションロジックからextract() は使用しないこと。
        //基本ツリーは、登録と、クリア飲み行うという設計
        _pLinearOctree->_paSpace[index]._kindinfobit =
                        _pLinearOctree->_paSpace[index]._kindinfobit ^ _kindbit;

        if (index == 0) {
            break;
        }
        // 親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
    if (this == _pSpace_Current->_pElemFirst && this == _pSpace_Current->_pElemLast) {
        //先頭かつ末尾の場合
        _pSpace_Current->_pElemFirst = NULL;
        _pSpace_Current->_pElemLast = NULL;
        _pSpace_Current = NULL;
    } else if (this == _pSpace_Current->_pElemFirst) {
        //先頭だった場合
        _pSpace_Current->_pElemFirst = _pNext;
        _pSpace_Current->_pElemFirst->_pPrev = NULL;
        _pNext = NULL;
        _pSpace_Current = NULL;
    } else if (this == _pSpace_Current->_pElemLast) {
        //末尾だった場合
        _pSpace_Current->_pElemLast = _pPrev;
        _pSpace_Current->_pElemLast->_pNext = NULL;
        _pPrev = NULL;
        _pSpace_Current = NULL;
    } else {
        //中間だった場合
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        _pNext = NULL;
        _pPrev = NULL;
        _pSpace_Current = NULL;
    }
}

void GgafLinearOctree::Elem::addElem(Space* prm_pSpace_target) {
    if (_pSpace_Current == prm_pSpace_target) {
        //_TRACE_("addElemせんでいい");
        return;
    } else {
        if (prm_pSpace_target->_pElemFirst == NULL) {
            //１番目に追加の場合
            prm_pSpace_target->_pElemFirst = this;
            prm_pSpace_target->_pElemLast = this;
            _pNext = NULL;
            _pPrev = NULL;
            _pSpace_Current = prm_pSpace_target;
        } else {
            //末尾に追加の場合
            prm_pSpace_target->_pElemLast->_pNext = this;
            _pPrev = prm_pSpace_target->_pElemLast;
            _pNext = NULL;
            prm_pSpace_target->_pElemLast = this;
            _pSpace_Current = prm_pSpace_target;
        }
    }
    //引数の要素番号
    int index = prm_pSpace_target->_my_index;
    //親空間すべてに要素種別情報を流す
    while(true) {
        _pLinearOctree->_paSpace[index]._kindinfobit =
                _pLinearOctree->_paSpace[index]._kindinfobit | this->_kindbit;
        if (index == 0) {
            break;
        }
        //一つ上の親空間要素番号で繰り返す
        index = (index-1)>>3;
    }
}

//void GgafLinearOctree::Elem::moveToSpace(Space* prm_pSpace_target) {
//    if (prm_pSpace_target == _pSpace_Current) {
//        return; //移動せんでいい
//    } else {
//        if(_pSpace_Current) {
//            extract(); //抜けますよ
//        }
//        addElem(prm_pSpace_target); //入りますよ
//        return;
//    }
//}

void GgafLinearOctree::Elem::dump() {
    _TEXT_("o");
}

GgafLinearOctree::Elem::~Elem() {
}

////// GgafLinearOctree //////

GgafLinearOctree::GgafLinearOctree(int prm_level) {
    _top_space_level = prm_level;
    //べき乗作成
    _paPow = NEW DWORD[SPACE_MAXLEVEL+1];
    _paPow[0] = 1;
    for(int i = 1; i < SPACE_MAXLEVEL + 1; i++) {
        _paPow[i] = _paPow[i-1] * 8;
    }
    //線形８分木配列作成
    _num_space = (_paPow[_top_space_level+1] -1) / 7; //空間数
    _TRACE_("_num_space="<<_num_space);
    _paSpace = NEW Space[_num_space];
    for (DWORD i = 0; i < _num_space; i++) {
        _paSpace[i]._my_index = i;
    }xx
    _pRegElemFirst = NULL;

}

void GgafLinearOctree::setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
    _root_X1 = X1;
    _root_Y1 = Y1;
    _root_Z1 = Z1;
    _root_X2 = X2;
    _root_Y2 = Y2;
    _root_Z2 = Z2;
    _top_level_dX = (_root_X2-_root_X1) / ((float)(1<<_top_space_level));
    _top_level_dY = (_root_Y2-_root_Y1) / ((float)(1<<_top_space_level));
    _top_level_dZ = (_root_Z2-_root_Z1) / ((float)(1<<_top_space_level));
}

void GgafLinearOctree::registElem(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
    if (prm_pElem->_pSpace_Current == NULL) {
        //登録Elemリストに追加
        if (_pRegElemFirst == NULL) {
            prm_pElem->_pRegLinkNext = NULL;
            _pRegElemFirst = prm_pElem;
        } else {
            prm_pElem->_pRegLinkNext = _pRegElemFirst;
            _pRegElemFirst = prm_pElem;
        }
    }

    //空間座標インデックス
    prm_pElem->_pLinearOctree = this;
    DWORD index = getSpaceIndex(tX1, tY1, tZ1, tX2, tY2, tZ2);
    if (index < _num_space) { //Root空間を更新した際に起こりうるため、この判定は必要。

        prm_pElem->addElem(&(_paSpace[index]));
    }


//    if (index > _num_space) {
//        //_TRACE_("over space!!");
//        prm_pElem->extract();
//    } else {
//        prm_pElem->moveToSpace(_paSpace[index]);
//    }
}
void GgafLinearOctree::clearElem() {
    if (_pRegElemFirst == NULL) {
        return;
    }
    Elem* pElem = _pRegElemFirst;
    while(true) {

        pElem->extract();
        pElem = pElem -> _pRegLinkNext;
		if (pElem == NULL) {
            break;
        }

    }
    _pRegElemFirst = NULL;
}

DWORD GgafLinearOctree::getSpaceIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
    //まず、BOXの所属空間 Level と、その空間Levelのモートン順序通し空間番号を求める

    //BOXの左上手前のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    DWORD minnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (DWORD)((tX1 - _root_X1) / _top_level_dX),
                                  (DWORD)((tY1 - _root_Y1) / _top_level_dY),
                                  (DWORD)((tZ1 - _root_Z1) / _top_level_dZ)
                                );

    //BOXの右下奥のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    DWORD maxnum_in_toplevel = getMortonOrderNumFromXYZindex(
                                  (DWORD)((tX2 - _root_X1) / _top_level_dX),
                                  (DWORD)((tY2 - _root_Y1) / _top_level_dY),
                                  (DWORD)((tZ2 - _root_Z1) / _top_level_dZ)
                                );


    //引数のBOXは、どのレベルの空間に所属しているのか取得
    DWORD differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    DWORD shift_num = 0;
    for(DWORD i = 0; i < _top_space_level; i++) {
        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
            shift_num = i+1;
        }
    }
    //xorしたdiffer_bit_pos を 右に3ビットシフトしつつ、マスク &B111(&H7) でANDを取り、&B000 でなくなっている位置をしらべる。
    //これは differ_bit_pos を ３ビットに区切り、その3ビットが食い違っている箇所をしらべている
    //食い違う3ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
    //最も遠い3ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
    //最大空間分割Level = 5として、左上手前が6001番、右下奥を6041番に所属していたBOXを例にすると
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
    //   上記より、6001番と6041番は空間レベル1、レベル2 までは同じ空間レベルに属していたが
    //   空間レベル3からモートン順序位置が異なってしまうことが解る。したがって、
    //   「所属空間レベル」はLv2空間であるとわかる。これを調べるために
    //   XORが0以外になる最高のシフト回数  shift_num = 3回 を求める。
    //   求めるためには、右に3ビットシフトして 0x7 で ANDを調べることを繰り返す必要があるということだ。
    //   shift_num のシフト回数を調べれば、所属空間レベルが解る！

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
    DWORD morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
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
    // これで、左上手前が6001番、右下奥を6041番としたBOXは、所属空間Lv2の場合は、モートン順序通し空間番号11番であったことがわかる。
    // あとはこれを配列Indexに変換するのみ

    //所属空間(シフト回数)とその空間のモートン順序通し空間番号から線形八分木配列の要素番号を求める
    DWORD index = morton_order_space_num + (_paPow[_top_space_level-shift_num]-1)/7;
    //(_paPow[_top_space_level-shift_num]-1)/7;
    //は、線形八分木空間配列の、所属空間レベルの最初の空間の要素番号をあらわす。
    //等比数列の和
    //     Σr^k = r^0 + r^1 + r^2 + ... + r^n
    //(1-r)Σr^k = (1-r)(r^0 + r^1 + r^2 + ... + r^n)
    //          = (r^0 + r^1 + r^2 + ... + r^n) - (r^1 + r^2 + ... + r^n + r^(n+1))
    //          = 1 - r^(n+1)
    //であるので
    //Σr^k = (1 - r^(n+1)) / (1 - r)
    //
    //線形8分木の配列要素の空間レベルｎまでの合計空関数は r=8 で
    //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 となる
    //ここで、所属空間の最初の空間要素を求めるため、 n = 所属空間レベル-1 の計算値（親空間レベルまでの要素数）の、
    //その次の要素が所属空間レベルの先頭の要素になるはずだ！。という求め方をする。
    //したがって最後に値を +1 したものがほしい値であるが、配列は0番から始まるため +1 を省略してしまおう。
    //先の例でいうと shift_num = 3 で、最大空間分割Level(_top_space_level) = 5 であるので
    // 5 - 3 = 2 で所属空間レベルは 2
    // n = 2 - 1 = 1 を代入して  (8^(1+1) - 1) / 7 = 9 で
    //所属空間のレベル2より一つ親の空間レベルである、空間レベル1までの配列要素数合計は9個とわかる。
    //所望の所属空間レベルは 2の最初の空間は配列は 9+1 の10番目から始まる。
    //配列の10番目とは、配列要素番号は-1して9になる。
    //+1 して -1 するので結局、所属空間レベルxの最初の配列要素番号は  (8^x - 1) / 7 となる

#ifdef OREDEBUG
    if(index > _num_space) {
//        _TRACE_("index > _num_space でおかしいです。minnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
//                "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
//                "index="<<index);
    }
#endif
    return index;
}


GgafLinearOctree::~GgafLinearOctree() {
    DELETEARR_IMPOSSIBLE_NULL(_paSpace);
    DELETEARR_IMPOSSIBLE_NULL(_paPow);
}


void GgafLinearOctree::putTree() {
    int _paPow[8];
    _paPow[0] = 1;
    for(int i = 1; i < 8; i++) {
        _paPow[i] = _paPow[i-1] * 8;
    }
    int mn0 = 0;
    int idx0 = 0;
    int LV0 = 0;

    if (_paSpace[0]._kindinfobit == 0) {
        _TRACE_("ツリーに何も無し！");
    } else {
        _TEXT_("L0["<<LV0<<","<<mn0<<","<<idx0<<"]_kind="<<_paSpace[0]._kindinfobit<<" ");
        _paSpace[idx0].dump();
        _TEXT_("\n");
    }
    for (int LV1 = 0; LV1 < 8; LV1++) {
        int mn1 = LV1;
        int idx1 = _paPow[0] +
                    LV1;

        if (_paSpace[idx1]._kindinfobit == 0) {
            continue;
        } else {
            _TEXT_(" L1["<<LV1<<","<<mn1<<","<<idx1<<"]_kind="<<_paSpace[idx1]._kindinfobit<<" ");
            _paSpace[idx1].dump();
            _TEXT_("\n");
        }
        for (int LV2 = 0; LV2 < 8; LV2++) {
            int mn2 = LV1*_paPow[1] +
                      LV2;
            int idx2 = _paPow[0]+ _paPow[1] +
                       LV1*_paPow[1] +
                       LV2;


            if (_paSpace[idx2]._kindinfobit == 0) {
                continue;
            } else {
                _TEXT_("   L2["<<LV2<<","<<mn2<<","<<idx2<<"]_kind="<<_paSpace[idx2]._kindinfobit<<" ");
                _paSpace[idx2].dump();
                _TEXT_("\n");
            }
            for (int LV3 = 0; LV3 < 8; LV3++) {
                int mn3 = LV1*_paPow[2] +
                          LV2*_paPow[1] +
                          LV3;
                int idx3 = _paPow[0]+ _paPow[1] + _paPow[2] +
                            LV1*_paPow[2] +
                            LV2*_paPow[1] +
                            LV3;

                if (_paSpace[idx3]._kindinfobit == 0) {
                    continue;
                } else {
                    _TEXT_("    L3["<<LV3<<","<<mn3<<","<<idx3<<"]_kind="<<_paSpace[idx3]._kindinfobit<<" ");
                    _paSpace[idx3].dump();
                    _TEXT_("\n");
                }
                for (int LV4 = 0; LV4 < 8; LV4++) {
                    int mn4 =LV1*_paPow[3] +
                            LV2*_paPow[2] +
                            LV3*_paPow[1] +
                            LV4;
                    int idx4 = _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] +
                                LV1*_paPow[3] +
                                LV2*_paPow[2] +
                                LV3*_paPow[1] +
                                LV4;



                    if (_paSpace[idx4]._kindinfobit == 0) {
                        continue;
                    } else {
                        _TEXT_("     L4["<<LV4<<","<<mn4<<","<<idx4<<"]_kind="<<_paSpace[idx4]._kindinfobit<<" ");
                        _paSpace[idx4].dump();
                        _TEXT_("\n");
                    }
                    for (int LV5 = 0; LV5 < 8; LV5++) {
                        int mn5 =   LV1*_paPow[4] +
                                    LV2*_paPow[3] +
                                    LV3*_paPow[2] +
                                    LV4*_paPow[1] +
                                    LV5;
                        int idx5 =  _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] + _paPow[4] +
                                    LV1*_paPow[4] +
                                    LV2*_paPow[3] +
                                    LV3*_paPow[2] +
                                    LV4*_paPow[1] +
                                    LV5;

                        if (_paSpace[idx5]._kindinfobit == 0) {
                            continue;
                        } else {
                            _TEXT_("      L5["<<LV5<<","<<mn5<<","<<idx5<<"]_kind="<<_paSpace[idx5]._kindinfobit<<" ");
                            _paSpace[idx5].dump();
                            _TEXT_("\n");
                        }
                        for (int LV6 = 0; LV6 < 8; LV6++) {
                            int mn6 =   LV1*_paPow[5] +
                                        LV2*_paPow[4] +
                                        LV3*_paPow[3] +
                                        LV4*_paPow[2] +
                                        LV5*_paPow[1] +
                                        LV6;
                            int idx6 =  _paPow[0]+ _paPow[1] + _paPow[2] + _paPow[3] + _paPow[4] + _paPow[5] +
                                        LV1*_paPow[5] +
                                        LV2*_paPow[4] +
                                        LV3*_paPow[3] +
                                        LV4*_paPow[2] +
                                        LV5*_paPow[1] +
                                        LV6;

                            if (_paSpace[idx6]._kindinfobit == 0) {
                                continue;
                            } else {
                                _TEXT_("       L6["<<LV6<<","<<mn6<<","<<idx6<<"]_kind="<<_paSpace[idx6]._kindinfobit<<" ");
                                _paSpace[idx6].dump();
                                _TEXT_("\n");
                            }

                        }

                    }
                }
            }
        }
    }
}


