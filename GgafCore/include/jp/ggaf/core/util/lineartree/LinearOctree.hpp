#ifndef GGAF_CORE_LINEAROCTREE_H_
#define GGAF_CORE_LINEAROCTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTree.hpp"

#include "jp/ggaf/core/util/lineartree/LinearOctreeRounder.hpp"
namespace GgafCore {

#define MAX_OCTREE_LEVEL 8

/**
 * 線形八分木クラス .
 * 線形八分木とは、八分木空間分割手法の各空間を、一列の配列(線形)に並べた状態を意味します。
 * 本クラスでの用語を次のように定める事とする。
 * 立体図がコメントAAで表現できないため、4分木の図を例に言葉の説明するが。本クラスの機能は立体の八分木です。
 * <pre><code>
 *  +-----------+
 *  |           |
 *  |           |
 *  |     0     |
 *  |           |   Lv0 空間
 *  |           |
 *  |           |
 *  +-----------+
 *
 *  +-----+-----+
 *  |     |     |
 *  |  0  |  1  |
 *  |     |     |
 *  +-----+-----+   Lv1 空間
 *  |     |     |
 *  |  2  |  3  |
 *  |     |     |
 *  +-----+-----+
 *
 *  +--+--+--+--+
 *  | 0| 1| 4| 5|
 *  +--+--+--+--+
 *  | 2| 3| 6| 7|
 *  +--+--+--+--+   Lv2 空間
 *  | 8| 9|12|13|
 *  +--+--+--+--+
 *  |10|11|14|15|
 *  +--+--+--+--+
 * </code></pre>
 * <BR>
 * <B>用語定義</B>
 * <BR>
 * <B>＜モートン順序＞</B><BR>
 * Z字のような順番で番号を振る手法事態を指す言葉。
 * 4分木では平面を4分割し左上、右上、左下、右下の順序で振る「手法」の事。<BR>
 * 8分木では立体空間（直方体）を8分割、Z字*2回で番号を振る「手法」の事を指す。<BR>
 * <BR>
 * <B>＜空間レベル＞</B><BR>
 * 上記図の右に書いてある、各空間のレベルを指す。<BR>
 * <BR>
 * <B>＜モートン順序通し番号、空間番号＞</B><BR>
 * 上記図の各Level空間に振られている分割空間の番号のことを指す事とする。<BR>
 * 上記図の例ではLv1空間のモートン順序通し番号は 0～3、Lv2空間のモートン順序通し番号は0～15 というように使う。<BR>
 * 実際は八分木で立体なので。Lv1空間モートン順序通し番号は0～7、Lv2空間モートン順序通し番号は0～63 になる。<BR>
 * <BR>
 * <B>＜子空間、親空間。（子レベル、親レベル）＞</B><BR>
 * ある空間レベルの +1 を子空間、ある空間レベルの -1 を親空間と呼ぶことにする。<BR>
 * <BR>
 * <B>＜子孫空間＞</B><BR>
 * ある空間レベルの +1～末端レベルの空間すべてを子孫空間と呼ぶことにする。<BR>
 * <BR>
 * <B>＜モートン順序位置＞</B><BR>
 * ある空間を4分割し、左上、右上、左下、右下を
 * それぞれ 0 1 2 3 (8分木では 0～7)と表現したい場合がある、
 * この 0 1 2 3 の事をモートン順序位置と呼ぶこととする。<BR>
 * <BR>
 * <B>＜空間(配列)要素番号＞</B><BR>
 * 空間番号に対応する線形配列のインデックスを指す。<BR>
 * 具体的には _paNodeSpaceArray の要素番号。<BR>
 * <BR>
 *
 *  <B>【例１】</B><BR>
 *  Lv2 空間の モートン順序位置 2 の空間というと
 *  <pre><code>
 *  +--+--+
 *  | 8| 9|
 *  +--+--+
 *  |10|11|
 *  +--+--+
 *  </code></pre>
 *  を指すこととする。<BR>
 *
 *  <B>【例２】</B><BR>
 *  「Lv1空間の空間番号3の子空間のモートン順序位置2」と表現した場合は、
 *  Lv1の空間番号3の子空間＝Lv2空間を４分割したの右下
 *  <pre><code>
 *  +--+--+
 *  |12|13|
 *  +--+--+
 *  |14|15|
 *  +--+--+
 *  </code></pre>
 *  のことを指し、これのモートン順序位置2なので、Lv2空間モートン順序通し番号<B>14</B>を指してることとする。<BR>
 *  【その他使用例】<BR>
 *  ・Lv1 空間のモートン順序位置 1 は Lv2 空間の空間番号 4 5 6 7 に当たる。<BR>
 *  ・Lv2 空間番号 13 は、親空間のモートン順序位置 3 に存在する。<BR>
 *  というように表現したりする（と定義する）。<BR>
 * <BR>
 * 【謝辞】<BR>
 * 本プログラムは、<BR>
 * 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html<BR>
 * サイト内コンテンツの 「その15 8分木空間分割を最適化する！」 http://marupeke296.com/COL_3D_No15_Octree.html<BR>
 * の記事を参考に（というか殆どそのまま）作成しています。<BR>
 * 目から鱗の非常に解りやすい解説に感謝いたします。<BR>
 * <BR>
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearOctree : public LinearTree<T, 3, 8> {

private:
    /**
     * 引数の座標インデックスに対応する、最大レベルの空間（分割されない最も深い空間）でのモートン順序の通し空間番号取得 .
     * やっていることは<BR>
     * ・引数をそれぞれ3bitごとに間隔を開ける<BR>
     * ・引数2の結果を1ビット、引数2の結果を2ビット  ずらして OR を取る<BR>
     * 以上。<BR>
     * <BR>
     * 図解すると、つまり
     * <pre><code>
     * 000000000000000000000000abcdefgh ,
     * 000000000000000000000000ijklmnop ,
     * 000000000000000000000000qrstuvwx
     * を
     * 00000000 00a 00b 00c 00d 00e 00f 00g 00h  --> X方向情報
     * 00000000 0i0 0j0 0k0 0l0 0m0 0n0 0o0 0p0  --> Y方向情報
     * 00000000 q00 r00 s00 t00 u00 v00 w00 x00  --> Z方向情報
     * こうして、ORした結果(下の結果)が戻り値になる。意味は、
     * 00000000 qia rjb skc tld ume vnf wog xph
     *                                      ^^^-->&B(xph)       = そのLevelの空間のモートン順序通し空間番号 0～7
     *                                  ^^^^^^^-->&B(wogxph)    = そのLevelの親空間のモートン順序通し空間番号 0～63
     *                              ^^^^^^^^^^^-->&B(vnfwogxph) = そのLevelの親の親空間のモートン順序通し空間番号 0～511
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = そのLevelの空間のモートン順序の位置 0～7
     *             ............  |   |   `---&B(wog) = そのLevelの親空間のモートン順序の位置  0～7
     *                           |   `-------&B(vnf) = そのLevelの親の親の空間のモートン順序の位置 0～7
     * </code></pre>
     * @param x_space_index 同一のレベル空間のx座標空間インデックス (ただし 0～255 とする)
     * @param y_space_index 同一のレベル空間のy座標空間インデックス (ただし 0～255 とする)
     * @param z_space_index 同一のレベル空間のz座標空間インデックス (ただし 0～255 とする)
     * @return そのLevell空間の(x_index, y_index, z_index)で示される空間に対応する
     *         八分木モートン順序の通し空間番号(最大Level8で、0～23068671)
     */
    static inline uint32_t getMortonOrderNumFromXYZindex( uint32_t x_space_index, uint32_t y_space_index, uint32_t z_space_index ) {
        return LinearOctree::separateEveryThreeBit(x_space_index)    |
               LinearOctree::separateEveryThreeBit(y_space_index)<<1 |
               LinearOctree::separateEveryThreeBit(z_space_index)<<2;
    }


    /**
     * 3bitごとに間隔を開ける .
     * <pre><code>
     * 000000000000000000000000abcdefgh  を
     * 0000000000a00b00c00d00e00f00g00h  にします
     * ＜アルゴリズム＞
     * n          = 0000 0000 0000 0000 0000 0000 abcd efgh のとき
     * n<<8       = 0000 0000 0000 0000 abcd efgh 0000 0000
     * n|n<<8     = 0000 0000 0000 0000 abcd efgh abcd efgh
     * 0x0000f00f = 0000 0000 0000 0000 1111 0000 0000 1111 であるので
     * (n|n<<8) & 0x0000f00f =
     *              0000 0000 0000 0000 abcd 0000 0000 efgh となる。
     * この結果をまた n に代入する
     * n          = 0000 0000 0000 0000 abcd 0000 0000 efgh
     * 以下同様に
     * n<<4       = 0000 0000 0000 abcd 0000 0000 efgh 0000
     * n|n<<4     = 0000 0000 0000 abcd abcd 0000 efgh efgh
     * 0x000c30c3 = 0000 0000 0000 1100 0011 0000 1100 0011
     * n ← (n|n<<4) & 0x000c30c3 =
     *              0000 0000 0000 ab00 00cd 0000 ef00 00gh
     * n<<2       = 0000 0000 00ab 0000 cd00 00ef 0000 gh00
     * n|n(n<<2)  = 0000 0000 00ab ab00 cdcd 00ef ef00 ghgh
     * 0x00249249 = 0000 0000 0010 0100 1001 0010 0100 1001
     * n ← (n|n<<2) & 0x00249249 =
     *              0000 0000 00a0 0b00 c00d 00e0 0f00 g00h
     * </code></pre>
     * @param n 0～255までの数値
     * @return 3bitごとに間隔が空けられた値
     */
    static inline uint32_t separateEveryThreeBit(uint32_t n) {
        n = ( n | n<<8 ) & 0x0000f00f;
        n = ( n | n<<4 ) & 0x000c30c3;
        n = ( n | n<<2 ) & 0x00249249;
        return n;
    }

public:
    /** [r]root空間の対角の頂点となるx座標の小さい方 */
    const int _root_x1;
    /** [r]root空間の対角の頂点となるy座標の小さい方 */
    const int _root_y1;
    /** [r]root空間の対角の頂点となるz座標の小さい方 */
    const int _root_z1;
    /** [r]root空間の対角の頂点となるx座標大きい方 */
    const int _root_x2;
    /** [r]root空間の対角の頂点となるy座標大きい方 */
    const int _root_y2;
    /** [r]root空間の対角の頂点となるz座標大きい方 */
    const int _root_z2;
    /** [r]最小空間(=最高分割の空間)の1空間のX軸方向の距離 */
    const double _top_level_dx;
    /** [r]最小空間(=最高分割の空間)の1空間のY軸方向の距離 */
    const double _top_level_dy;
    /** [r]最小空間(=最高分割の空間)の1空間のZ軸方向の距離 */
    const double _top_level_dz;

    const double _r_top_level_dx;
    const double _r_top_level_dy;
    const double _r_top_level_dz;

public:
    /**
     * 線形八分木空間を構築する.
     * @param prm_level 構築する空間レベル
     * @param x1 構築する外枠の空間座標
     * @param y1 〃
     * @param z1 〃
     * @param x2 〃
     * @param y2 〃
     * @param z2 〃
     */
    LinearOctree(uint32_t prm_level,
                 int x1, int y1, int z1,
                 int x2, int y2, int z2) : LinearTree<T, 3, 8>(prm_level),
    _root_x1(x1),
    _root_y1(y1),
    _root_z1(z1),
    _root_x2(x2),
    _root_y2(y2),
    _root_z2(z2),
    _top_level_dx( (_root_x2-_root_x1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _top_level_dy( (_root_y2-_root_y1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _top_level_dz( (_root_z2-_root_z1) / ((double)(1<<LinearTree<T,3,8>::_top_space_level)) ),
    _r_top_level_dx(1.0 / _top_level_dx),
    _r_top_level_dy(1.0 / _top_level_dy),
    _r_top_level_dz(1.0 / _top_level_dz)
    {
    #ifdef MY_DEBUG
        if (prm_level > MAX_OCTREE_LEVEL) {
            throwCriticalException("LinearOctree::LinearOctree() 空間レベルオーバー！ prm_level="<<prm_level);
        }
    #endif
        _TRACE_("LinearOctree::LinearOctree("<<prm_level<<") 線形八分木空間配列要素数 _num_space="<<(LinearTree<T,3,8>::_num_space));
        _TRACE_(FUNC_NAME<<" 八分木ルートレベル(level=0)の空間位置=(" << _root_x1 << "," << _root_y1 << "," << _root_z1 << ")-(" << _root_x2 << "," << _root_y2 << "," << _root_z2 << ")");
        _TRACE_(FUNC_NAME<<" 八分木ルートレベル(level=0)の空間の広さ=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 << "x" << _root_z2-_root_z1);
        _TRACE_(FUNC_NAME<<" 八分木末端レベル(level="<<(LinearTree<T,3,8>::_top_space_level)<<")の空間の広さ=" << (uint32_t)_top_level_dx << "x" << (uint32_t)_top_level_dy << "x" << (uint32_t)_top_level_dz);
    }

    /**
     * 要素を八分木空間に登録する
     * 空間番号範囲外になった場合は無視される。
     * @param prm_pNodeElem 要素
     * @param tx1 要素対象オブジェクトの外枠の座標
     * @param ty1 〃
     * @param tz1 〃
     * @param tx2 〃
     * @param ty2 〃
     * @param tz2 〃
     */
    void registerElem(T* const prm_pNodeElem,
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

        //BOXの左下手前のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番かを取得
        const uint32_t minnum_in_toplevel = LinearOctree::getMortonOrderNumFromXYZindex(
                            (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                            (uint32_t)((ty1 - _root_y1) * _r_top_level_dy),
                            (uint32_t)((tz1 - _root_z1) * _r_top_level_dz)
                        );

        //BOXの右上奥のXYZ座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番かを取得
        const uint32_t maxnum_in_toplevel = LinearOctree::getMortonOrderNumFromXYZindex(
                            (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                            (uint32_t)((ty2 - _root_y1) * _r_top_level_dy),
                            (uint32_t)((tz2 - _root_z1) * _r_top_level_dz)
                        );                 //↑_root_x2,_root_y2,_root_z2 と間違えていません。
        //空間に登録する（共通化）
       LinearTree<T,3,8>::registerElem((ITreeNodeElem*)prm_pNodeElem, minnum_in_toplevel,maxnum_in_toplevel);

//以下は共通化前のコード
//    //引数のBOXは、どのレベルの空間に所属しているのか取得
//    const uint32_t differ_bit_pos = maxnum_in_toplevel ^ minnum_in_toplevel;
//    uint32_t shift_num = 0;
//    for (uint32_t i = 0; i < _top_space_level; i++) {
//        if (((differ_bit_pos>>(i*3)) & 0x7) != 0 ) {
//            shift_num = i+1;
//        }
//    }
//    //xorしたdiffer_bit_pos を 右に3ビットシフトしつつ、マスク &B111(&H7) でANDを取り、&B000 で
//    //なくなっている場合、shift_numに値を代入。
//    //つまりこれは differ_bit_pos を まず ３ビットに区切り、その3ビットが食い違っている箇所のうち、
//    //最も遠い位置をしらべている。
//    //食い違う3ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
//    //したがって最も遠い3ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
//    //最大空間分割Level = 5として、左下手前が6001番、右上奥を6041番に所属していたBOXを例にすると
//    //
//    //                               lv0 lv1 lv2 lv3 lv4 lv5 ･･･各レベル空間のモートン順序位置
//    //     6001 = 00 000 000 000 000 000 001 011 101 110 001
//    // XOR)6041 = 00 000 000 000 000 000 001 011 110 011 001
//    // -----------------------------------------------------
//    //      232 = 00 000 000 000 000 000 000 000 011 101 000
//    //
//    //                                                   111 ・・・ マスク
//    //                                               111
//    //                                           111
//    //                                       111
//    //  AND)                             111     <--- ここまで行って、最も遠い3ビットが食い違っている箇所が3回目だったことが解る
//    // ------------------------------------------------------
//    //                                   000 000 011 101 000     <--- 左からのマスク結果が  000 で、それが続く限り、6001番と6041番のモートン順序位置が同じである（=同一空間に所属）を意味する
//    //                                    f   f   t   t   f      if (differ_bit_pos>>(i*3)) & 0x7 != 0 ) の判定
//    //                                    5   4   3   2   1   0  shift_num(シフト回数)
//    //                                    o   o   x(以降x)        同一空間に内包されている判定（左からみる）
//    //
//    //   上記より、6001番と6041番は空間レベル1、レベル2 までは同じ空間レベルに属していたが、
//    //   空間レベル3からモートン順序位置が異なってしまうことが解る。したがって、
//    //   「所属空間レベル」はLv2空間であると確定できる。これを調べるために
//    //   XORが0以外になる最高のシフト回数  shift_num = 3 を求める。
//    //   求めるためには、右に3ビットシフトして 0x7 で ANDを調べることを繰り返す必要があるということだ。
//    //   Level = 5の場合、5回繰り返し、要は shift_num のシフト回数を調べれば、所属空間レベルが解る！
//
//    //もしXOR結果が
//    // 00 000 000 000 000 000 000 000 000 111 の場合ならば shift_num=1
//    //これは
//    //最大空間分割Level=5 の場合は所属空間レベルは4(=空間レベル5で食い違う)
//    //最大空間分割Level=8 の場合は所属空間レベルは7(=空間レベル8で食い違う)
//
//    // 00 000 000 000 000 111 110 000 101 111 などの場合は shift_num=5
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
//    const uint32_t morton_order_space_num = minnum_in_toplevel>>(shift_num*3);
//    //不揃いの下位のビットを3ビット単位で除去し、所属のモートン順序番号を求める
//    //
//    // minnum_in_toplevel>>(shift_num*3); について、
//    // minnum_in_toplevel=6001 でも 6041でもどちらでもよく
//    //        lv0 lv1 lv2 lv3 lv4 lv5          lv0 lv1 lv2
//    // 6001 = 000 001 011 101 110 001   -->    000 001 011 = 11
//    // 6041 = 000 001 011 110 011 001   -->    000 001 011 = 11
//    //                    ^^^ ^^^ ^^^
//    //                  (shift_num*3 ビット除去)
//    //
//    // のように不揃いのビットを右へシフトしている
//    // これで、左下手前が6001番、右上奥を6041番としたBOXは、所属空間Lv2の場合は、モートン順序通し空間番号11番(0番から数えて)であったことがわかる。
//    // あとはこれを配列Indexに変換するのみ
//
//    //所属空間(シフト回数)とその空間のモートン順序通し空間番号から線形八分木配列の要素番号を求める
//    const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/7;
//    //(_POW8[_top_space_level-shift_num]-1)/7;
//    //は、線形八分木空間配列の、所属空間レベルの最初の空間の要素番号をあらわす。
//    //等比数列の和
//    // Σr^k = r^0 + r^1 + r^2 + ... + r^n
//    // Σr^k = (1 - r^(n+1)) / (1 - r)
//    //
//    //線形8分木の配列要素の空間レベルｎまでの合計空関数は r=8 で
//    //(1 - 8^(n+1)) / (1-8)  =  (1-8^(n+1)) / -7  =  (8^(n+1) - 1) / 7 となる
//    //ここで、所属空間の最初の空間要素を求めるため、 n = 所属空間レベル-1 の計算値（親空間レベルまでの要素数）の、
//    //その次の要素が所属空間レベルの先頭の要素になるはずだ！。という求め方をする。
//    //したがって最後に値を +1 したものがほしい値であるが、配列は0番から始まるため、+1 -1 = 0 で、省略してしまおう。
//    //先の例でいうと shift_num = 3 で、最大空間分割Level(_top_space_level) = 5 であるので
//    // 5 - 3 = 2 で所属空間レベルは 2
//    // n = 2 - 1 = 1 を代入して  (8^(1+1) - 1) / 7 = 9 で
//    //所属空間のレベル2より一つ親の空間レベルである、空間レベル1までの配列要素数合計は9個とわかる。
//    //所望の所属空間レベルは 2の最初の空間は配列は 9+1 の10番目から始まる。
//    //配列の10番目とは、配列要素番号は-1して9になる。
//    //+1 して -1 するので結局、所属空間レベルxの最初の配列要素番号は  (8^x - 1) / 7 となる
    }

    LinearOctreeRounder<T>* createRounder(void (T::*prm_pFuncHitCheck)(T*)) {
        LinearOctreeRounder<T>* pRounder = NEW LinearOctreeRounder<T>( LinearTree<T,3,8>::_paNodeSpaceArray,  LinearTree<T,3,8>::_num_space, prm_pFuncHitCheck);
        return pRounder;
    }

    virtual ~LinearOctree() {
    }
};

}
#endif /*GGAF_CORE_LINEAROCTREE_H_*/

