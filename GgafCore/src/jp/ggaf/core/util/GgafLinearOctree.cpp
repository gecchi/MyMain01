#include "jp/ggaf/core/util/GgafLinearOctree.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/util/GgafUtil.h"


using namespace GgafCore;


GgafLinearOctree::GgafLinearOctree(uint32_t prm_level,
                                   int x1, int y1, int z1,
                                   int x2, int y2, int z2) : GgafObject(),
_top_space_level(prm_level),
_root_x1(x1),
_root_y1(y1),
_root_z1(z1),
_root_x2(x2),
_root_y2(y2),
_root_z2(z2),
_top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<_top_space_level))) + 1 ),
_top_level_dz( ((_root_z2-_root_z1) / ((float)(1<<_top_space_level))) + 1 ), //+1は空間数をオーバーしないように余裕をもたせるため
_r_top_level_dx(1.0 / _top_level_dx),
_r_top_level_dy(1.0 / _top_level_dy),
_r_top_level_dz(1.0 / _top_level_dz)
{
    //べき乗作成
    _pa_8pow = NEW uint32_t[(prm_level+1)+1];
    _pa_8pow[0] = 1;
    for (uint32_t i = 1; i < (prm_level+1)+1; i++) {
        _pa_8pow[i] = _pa_8pow[i-1] * 8;
        //_TRACE_("_pa_8pow["<<i<<"]="<<_pa_8pow[i]);
    }
    //線形八分木配列作成
    _num_space = (uint32_t)((_pa_8pow[_top_space_level+1] -1) / 7); //空間数
    _TRACE_("GgafLinearOctree::GgafLinearOctree("<<prm_level<<") 線形八分木空間配列要素数 _num_space="<<_num_space);
    _paOctant = NEW GgafTreeSpace<3u>[_num_space];
    for (uint32_t i = 0; i < _num_space; i++) {
        _paOctant[i]._my_index = i;
    }
    _pRegElemFirst = nullptr;

    _TRACE_(FUNC_NAME<<" 八分木ルートレベル(level=0)の空間の広さ=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 << "x" << _root_z2-_root_z1);
    _TRACE_(FUNC_NAME<<" 八分木末端レベル(level="<<_top_space_level<<")の空間の広さ=" << _top_level_dx << "x" << _top_level_dy << "x" << _top_level_dz);

}

void GgafLinearOctree::registerElem(GgafTreeElem<3u>* const prm_pElem,
                                    int tx1, int ty1, int tz1,
                                    int tx2, int ty2, int tz2) {

    //はみ出る場合は補正
    if (tx1 <= _root_x1)  { tx1 = _root_x1; }
    if (tx2 >= _root_x2)  { tx2 = _root_x2; }
    if (ty1 <= _root_y1)  { ty1 = _root_y1; }
    if (ty2 >= _root_y2)  { ty2 = _root_y2; }
    if (tz1 <= _root_z1)  { tz1 = _root_z1; }
    if (tz2 >= _root_z2)  { tz2 = _root_z2; }
    //軸座標の大小が裏返った場合、つまりLevel0より外か、Level0全体より大きい場合は無視する
    if (tx1 >= tx2 || ty1 >= ty2 || tz1 >= tz2) {
        return; //空間外は登録しない
    }

    //＜tx1,ty1,tz1,tx2,ty2,tz2 から、空間番号 を求める＞
    //BOX領域座標から空間配列要素番号（線形八分木配列の要素番号）を算出 .
    //まず、BOXの所属空間 Level と、その空間Levelのモートン順序通し空間番号を求め
    //モートン順序通し空間番号から計算して配列の index を求める。


    //BOXの左下手前のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    const uint32_t minnum_in_toplevel = GgafLinearOctree::getMortonOrderNumFromXYZindex(
                                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy),
                                            (uint32_t)((tz1 - _root_z1) * _r_top_level_dz)
                                        );

    //BOXの右上奥のXYZ座標点が所属する空間は、最大レベル空間でモートン順序通し空間番号は何番かを取得
    const uint32_t maxnum_in_toplevel = GgafLinearOctree::getMortonOrderNumFromXYZindex(
                                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy),
                                            (uint32_t)((tz2 - _root_z1) * _r_top_level_dz)
                                        );                 //↑_root_x2,_root_y2,_root_z2 と間違えていません。


    //引数のBOXは、どのレベルの空間に所属しているのか取得
    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
    uint32_t shift_num = 0;
    for (uint32_t i = 0; i < _top_space_level; i++) {
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
    //                                    o   o   x(以降x)        同一空間に無いほうされている判定（左からみる）
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
    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
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
    const uint32_t index = morton_order_space_num + (_pa_8pow[_top_space_level-shift_num]-1)/7;
    //(_pa_8pow[_top_space_level-shift_num]-1)/7;
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
           "GgafLinearOctree::registerElem() 空間オーバー !. \n"
           "Root=("<<_root_x1<<","<<_root_y1<<","<<_root_z1<<")-("<<_root_x2<<","<<_root_y2<<","<<_root_z2<<")\n"
           "Elem=("<<tx1<<","<<ty1<<","<<tz1<<")-("<<tx2<<","<<ty2<<","<<tz2<<")\n"
           "_top_level_dx="<<_top_level_dx<<" _top_level_dy="<<_top_level_dy<<" _top_level_dz="<<_top_level_dz<<"\n"
           "minnum_in_toplevel="<<minnum_in_toplevel<<" maxnum_in_toplevel="<<maxnum_in_toplevel<<"\n"
           "differ_bit_pos="<<differ_bit_pos<<" shift_num="<<shift_num<<" morton_order_space_num="<<morton_order_space_num<<"\n"
           "index="<<index<<" _num_space="<<_num_space
        );
        _TRACE_("Min_x_index="<<((uint32_t)((tx1 - _root_x1) / _top_level_dx)));
        _TRACE_("Min_y_index="<<((uint32_t)((ty1 - _root_y1) / _top_level_dy)));
        _TRACE_("Min_z_index="<<((uint32_t)((tz1 - _root_z1) / _top_level_dz)));
        _TRACE_("Man_x_index="<<((uint32_t)((tx2 - _root_x1) / _top_level_dx)));
        _TRACE_("Man_y_index="<<((uint32_t)((ty2 - _root_y1) / _top_level_dy)));
        _TRACE_("Man_z_index="<<((uint32_t)((tz2 - _root_z1) / _top_level_dz)));
    }
#endif

    //登録したElemをリストに追加して保持しておく。
    //理由は、後で clearAllElem() 一斉にクリアしたいが為。ここの仕組みは最適化の余地がある。
    //例えば登録済みの空間Indexのみを配列で保持して後でclearAllElem() する。連結リストより速いのでは。
    //TODO:最後に全要素を八分木からクリアするより良い方法があるまでは、この方法で一旦保持する・・・なんかない
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
        throwGgafCriticalException("登録しようとした引数要素は、他の空間に所属状態です。"
                                   "クリアがなされていないか、２重登録しています。現所属空間インデックス="<<(prm_pElem->_pSpace_current->_my_index)<<"  要素対象オブジェクト="<<(prm_pElem->_pObject));
#endif
    }
    //要素を線形八分木空間に登録(所属させる)
    _paOctant[index].registerElem(prm_pElem);
}

void GgafLinearOctree::clearAllElem() {
    //登録済みの要素リストを使用して、八分木をクリア
    GgafTreeElem<3u>* pElem = _pRegElemFirst;
    while (pElem) {

        //pElem->clear();

        if(pElem->_pSpace_current == nullptr) {
            //スルー
        } else {
            uint32_t index = pElem->_pSpace_current->_my_index;
            while (true) {
                if (_paOctant[index]._kind_bit_field == 0 ) {
                    break;
                } else {
                    _paOctant[index]._kind_bit_field = 0;
                    _paOctant[index]._pElem_first = nullptr;
                    _paOctant[index]._pElem_last = nullptr;
                }
                if (index == 0) {
                    break;
                }
                // 親空間要素番号で繰り返す
                index = (index-1)>>3;
            }
            pElem->_pNext = nullptr;
            pElem->_pPrev = nullptr;
            pElem->_pSpace_current = nullptr;
        }
        pElem = pElem->_pRegLinkNext;
    }
    _pRegElemFirst = nullptr;
}



GgafLinearOctree::~GgafLinearOctree() {
    GGAF_DELETEARR(_paOctant);
    GGAF_DELETEARR(_pa_8pow);
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

    if (_paOctant[0]._kind_bit_field == 0) {
        _TRACE_("8分木に何も無し！");
    } else {
        UTIL::strbin(_paOctant[LV0]._kind_bit_field, aChar_strbit);
        _TRACE_N_("LV0."<<lv0_order_num<<"(POS:"<<lv0_order_pos<<")["<<LV0<<"]="<<aChar_strbit<<" /GgafTreeElem->");
        _paOctant[LV0].dump();
        _TRACE_N_("\n");
    }

    uint32_t index_lv1_begin = LV0*8 + 1;
    if (index_lv1_begin > _num_space-1) { return; }

    for (uint32_t LV1 = index_lv1_begin, lv1_order_pos = 0; LV1 < index_lv1_begin+8; LV1++, lv1_order_num++, lv1_order_pos++) {
        if (_paOctant[LV1]._kind_bit_field == 0) { continue; }
        UTIL::strbin(_paOctant[LV1]._kind_bit_field, aChar_strbit);
        _TRACE_N_("  LV1-"<<lv1_order_num<<"(POS:"<<lv1_order_pos<<")["<<LV1<<"]="<<aChar_strbit<<" /GgafTreeElem->");
        _paOctant[LV1].dump();
        _TRACE_N_("\n");
        ////
        uint32_t index_lv2_begin = LV1*8 + 1;
        if (index_lv2_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック

        for (uint32_t LV2 = index_lv2_begin, lv2_order_pos = 0; LV2 < index_lv2_begin+8; LV2++, lv2_order_num++, lv2_order_pos++) {
            if (_paOctant[LV2]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
            UTIL::strbin(_paOctant[LV2]._kind_bit_field, aChar_strbit);
            _TRACE_N_("    LV2-"<<lv2_order_num<<"(POS:"<<lv2_order_pos<<")["<<LV2<<"]="<<aChar_strbit<<" /GgafTreeElem->");
            _paOctant[LV2].dump();
            _TRACE_N_("\n");
            ///
            uint32_t index_lv3_begin = LV2*8 + 1;
            if (index_lv3_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
            for (uint32_t LV3 = index_lv3_begin, lv3_order_pos = 0; LV3 < index_lv3_begin+8; LV3++, lv3_order_num++, lv3_order_pos++) {
                if (_paOctant[LV3]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                UTIL::strbin(_paOctant[LV3]._kind_bit_field, aChar_strbit);
                _TRACE_N_("      LV3-"<<lv3_order_num<<"(POS:"<<lv3_order_pos<<")["<<LV3<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                _paOctant[LV3].dump();
                _TRACE_N_("\n");
                ///
                uint32_t index_lv4_begin = LV3*8 + 1;
                if (index_lv4_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                for (uint32_t LV4 = index_lv4_begin, lv4_order_pos = 0; LV4 < index_lv4_begin+8; LV4++, lv4_order_num++, lv4_order_pos++) {
                    if (_paOctant[LV4]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                    UTIL::strbin(_paOctant[LV4]._kind_bit_field, aChar_strbit);
                    _TRACE_N_("        LV4-"<<lv4_order_num<<"(POS:"<<lv4_order_pos<<")["<<LV4<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                    _paOctant[LV4].dump();
                    _TRACE_N_("\n");
                    ///
                    uint32_t index_lv5_begin = LV4*8 + 1;
                    if (index_lv5_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                    for (uint32_t LV5 = index_lv5_begin, lv5_order_pos = 0; LV5 < index_lv5_begin+8; LV5++, lv5_order_num++, lv5_order_pos++) {
                        if (_paOctant[LV5]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                        UTIL::strbin(_paOctant[LV5]._kind_bit_field, aChar_strbit);
                        _TRACE_N_("          LV5-"<<lv5_order_num<<"(POS:"<<lv5_order_pos<<")["<<LV5<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                        _paOctant[LV5].dump();
                        _TRACE_N_("\n");
                        ///
                        uint32_t index_lv6_begin = LV5*8 + 1;
                        if (index_lv6_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                        for (uint32_t LV6 = index_lv6_begin, lv6_order_pos = 0; LV6 < index_lv6_begin+8; LV6++, lv6_order_num++, lv6_order_pos++) {
                            if (_paOctant[LV6]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                            UTIL::strbin(_paOctant[LV6]._kind_bit_field, aChar_strbit);
                            _TRACE_N_("            LV6-"<<lv6_order_num<<"(POS:"<<lv6_order_pos<<")["<<LV6<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                            _paOctant[LV6].dump();
                            _TRACE_N_("\n");
                            ///
                            uint32_t index_lv7_begin = LV6*8 + 1;
                            if (index_lv7_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                            for (uint32_t LV7 = index_lv7_begin, lv7_order_pos = 0; LV7 < index_lv7_begin+8; LV7++, lv7_order_num++, lv7_order_pos++) {
                                if (_paOctant[LV7]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                                UTIL::strbin(_paOctant[LV7]._kind_bit_field, aChar_strbit);
                                _TRACE_N_("              LV7-"<<lv7_order_num<<"(POS:"<<lv7_order_pos<<")["<<LV7<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                                _paOctant[LV7].dump();
                                _TRACE_N_("\n");
                                ///
                                uint32_t index_lv8_begin = LV7*8 + 1;
                                if (index_lv8_begin > _num_space-1) { continue; } //次の階層にもぐれるかLvチェック
                                for (uint32_t LV8 = index_lv8_begin, lv8_order_pos = 0; LV8 < index_lv8_begin+8; LV8++, lv8_order_num++, lv8_order_pos++) {
                                    if (_paOctant[LV8]._kind_bit_field == 0) { continue; }  //何も無いので下位表示を飛ばし
                                    UTIL::strbin(_paOctant[LV8]._kind_bit_field, aChar_strbit);
                                    _TRACE_N_("                LV8-"<<lv8_order_num<<"(POS:"<<lv8_order_pos<<")["<<LV8<<"]="<<aChar_strbit<<" /GgafTreeElem->");
                                    _paOctant[LV8].dump();
                                    _TRACE_N_("\n");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


