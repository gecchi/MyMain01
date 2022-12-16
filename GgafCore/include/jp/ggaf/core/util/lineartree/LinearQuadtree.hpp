#ifndef GGAF_CORE_LINEARQUADTREE_H_
#define GGAF_CORE_LINEARQUADTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/util/lineartree/LinearTree.hpp"

#include "jp/ggaf/core/util/lineartree/LinearQuadtreeRounder.hpp"

namespace GgafCore {


#define MAX_QUADTREE_LEVEL 14

/**
 * 線形四分木クラス .
 * 線形四分木とは、四分木空間分割手法の各空間を、一列の配列(線形)に並べた状態を意味します。
 * 本クラスでの用語を次のように定める事とする。
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
 * <BR>
 * <B>＜空間レベル＞</B><BR>
 * 上記図の右に書いてある、各空間のレベルを指す。<BR>
 * <BR>
 * <B>＜モートン順序通し番号、空間番号＞</B><BR>
 * 上記図の各Level空間に振られている分割空間の番号のことを指す事とする。<BR>
 * 上記図の例ではLv1空間のモートン順序通し番号は 0～3、Lv2空間のモートン順序通し番号は0～15 というように使う。<BR>
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
 * サイト内コンテンツの 「その8 4分木空間分割を最適化する！」 http://marupeke296.com/COL_2D_No8_QuadTree.html<BR>
 * の記事を参考に（というか殆どそのまま）作成しています。<BR>
 * 目から鱗の非常に解りやすい解説に感謝いたします。<BR>
 * <BR>
 * @version 1.00
 * @since 2017/08/02
 * @author Masatoshi Tsuge
 */
template<class T>
class LinearQuadtree : public LinearTree<T, 2, 4> {

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
     * を
     * 0000000000000000 0a 0b 0c 0d 0e 0f 0g 0h  --> X方向情報
     * 0000000000000000 i0 j0 k0 l0 m0 n0 o0 p0  --> Y方向情報
     * こうして、ORした結果(下の結果)が戻り値になる。意味は、
     * 0000000000000000 ia jb kc ld me nf og ph
     *                                       ^^-->&B(ph)        = そのLevelの空間のモートン順序通し空間番号 0～3
     *                                    ^^ ^^-->&B(ogph)      = そのLevelの親空間のモートン順序通し空間番号 0～15
     *                                 ^^ ^^ ^^-->&B(nfogph)    = そのLevelの親の親空間のモートン順序通し空間番号 0～63
     *                              ^^ ^^ ^^ ^^
     *                               |  |  |  |
     *                               |  |  |  &B(ph) = そのLevelの空間のモートン順序の位置 0～3
     *                 ............  |  |  `---&B(og) = そのLevelの親空間のモートン順序の位置  0～3
     *                               |  `-------&B(nf) = そのLevelの親の親の空間のモートン順序の位置 0～3
     * </code></pre>
     * @param x_space_index 同一のレベル空間のx座標空間インデックス (ただし 0～255 とする)
     * @param y_space_index 同一のレベル空間のy座標空間インデックス (ただし 0～255 とする)
     * @return そのLevell空間の(x_index, y_index)で示される空間に対応する
     *         四分木モートン順序の通し空間番号(最大Level8で、0～87380)
     */
    static inline uint32_t getMortonOrderNumFromXYindex( uint32_t x_space_index, uint32_t y_space_index) {
        return LinearQuadtree::separateEveryTwoBit(x_space_index) |
               LinearQuadtree::separateEveryTwoBit(y_space_index)<<1;
    }

    /**
     * 2bitごとに間隔を開ける .
     * <pre><code>
     * 0000000000000000abcdefghijklmnop  を
     * 0a0b0c0d0e0f0g0h0i0j0k0l0m0n0o0p  にします
     * ＜アルゴリズム＞
     * n          = 0000 0000 0000 0000 abcd efgh ijkl mnop のとき
     * n<<8       = 0000 0000 abcd efgh ijkl mnop 0000 0000
     * n|n<<8     = 0000 0000 abcd efgh ???? ???? ijkl mnop
     * 0x00ff00ff = 0000 0000 1111 1111 0000 0000 1111 1111 であるので
     * (n|n<<8) & 0x00ff00ff =
     *              0000 0000 abcd efgh 0000 0000 ijkl mnop となる。
     * この結果をまた n に代入する(以下同様に)
     * n          = 0000 0000 abcd efgh 0000 0000 ijkl mnop
     * n<<4       = 0000 abcd efgh 0000 0000 ijkl mnop 0000
     * n|n<<4     = 0000 abcd ???? efgh 0000 ijkl ???? mnop
     * 0x0f0f0f0f = 0000 1111 0000 1111 0000 1111 0000 1111
     * n ← (n|n<<4) & 0x0f0f0f0f =
     *              0000 abcd 0000 efgh 0000 ijkl 0000 mnop
     * n<<2       = 00ab cd00 00ef gh00 00ij kl00 00mn op00
     * n|n(n<<2)  = 00ab ??cd 00ef ??gh 00ij ??kl 00mn ??op
     * 0x33333333 = 0011 0011 0011 0011 0011 0011 0011 0011
     * n ← (n|n<<2) & 0x33333333 =
     *              00ab 00cd 00ef 00gh 00ij 00kl 00mn 00op
     * n<<1       = 0ab0 0cd0 0ef0 0gh0 0ij0 0kl0 0mn0 0op0
     * n|n(n<<1)  = 0a?b 0c?d 0e?f 0g?h 0i?j 0k?l 0m?n 0o?p
     * 0x55555555 = 0101 0101 0101 0101 0101 0101 0101 0101
     * n ← (n|n<<2) & 0x55555555 =
     *              0a0b 0c0d 0e0f 0g0h 0i0j 0k0l 0m0n 0o0p
     * </code></pre>
     * @param n 0～255までの数値
     * @return 3bitごとに間隔が空けられた値
     */
    static inline uint32_t separateEveryTwoBit(uint32_t n) {
           n = (n | (n<<8) ) & 0x00ff00ff;
           n = (n | (n<<4) ) & 0x0f0f0f0f;
           n = (n | (n<<2) ) & 0x33333333;
           return (n | (n<<1) ) & 0x55555555;
    }

public:
    /** [r]root空間の対角の頂点となるx座標の小さい方 */
    const int _root_x1;
    /** [r]root空間の対角の頂点となるy座標の小さい方 */
    const int _root_y1;
    /** [r]root空間の対角の頂点となるz座標の小さい方 */
    const int _root_x2;
    /** [r]root空間の対角の頂点となるy座標大きい方 */
    const int _root_y2;
    /** [r]最小空間(=最高分割の空間)の1空間のX軸方向の距離 */
    const double _top_level_dx;
    /** [r]最小空間(=最高分割の空間)の1空間のY軸方向の距離 */
    const double _top_level_dy;

    const double _r_top_level_dx;
    const double _r_top_level_dy;

public:
    /**
     * 線形四分木空間を構築する.
     * @param prm_level 構築する空間レベル
     * @param x1 構築する外枠の空間座標
     * @param y1 〃
     * @param x2 〃
     * @param y2 〃
     */
    LinearQuadtree(uint32_t prm_level,
                   int x1, int y1,
                   int x2, int y2) : LinearTree<T,2,4>(prm_level),
    _root_x1(x1),
    _root_y1(y1),
    _root_x2(x2),
    _root_y2(y2),
    _top_level_dx( ((_root_x2-_root_x1) / ((float)(1<<LinearTree<T,2,4>::_top_space_level))) + 1),
    _top_level_dy( ((_root_y2-_root_y1) / ((float)(1<<LinearTree<T,2,4>::_top_space_level))) + 1),
    _r_top_level_dx(1.0 / _top_level_dx),
    _r_top_level_dy(1.0 / _top_level_dy)
    {
    #ifdef MY_DEBUG
        if (prm_level > MAX_QUADTREE_LEVEL) {
            throwCriticalException("LinearQuadtree::LinearQuadtree() 空間レベルオーバー！ prm_level="<<prm_level);
        }
    #endif
        _TRACE_("LinearQuadtree::LinearQuadtree("<<prm_level<<") 線形四分木空間配列要素数 _num_space="<<(LinearTree<T,2,4>::_num_space));
        _TRACE_(FUNC_NAME<<" 四分木ルートレベル(level=0)の空間位置=(" << _root_x1 << "," << _root_y1 << ")-(" << _root_x2 << "," << _root_y2 << ")");
        _TRACE_(FUNC_NAME<<" 四分木ルートレベル(level=0)の空間の広さ=" << _root_x2-_root_x1 << "x" << _root_y2-_root_y1 );
        _TRACE_(FUNC_NAME<<" 四分木末端レベル(level="<<(LinearTree<T,2,4>::_top_space_level)<<")の空間の広さ=" << (uint32_t)_top_level_dx << "x" << (uint32_t)_top_level_dy );
    }

    /**
     * 要素を四分木空間に登録する
     * 空間番号範囲外になった場合は無視される。
     * @param prm_pNodeElem 要素
     * @param tx1 要素対象オブジェクトの外枠の座標
     * @param ty1 〃
     * @param tx2 〃
     * @param ty2 〃
     */
    void registerElem(T* prm_pNodeElem,
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

        //Rect(要素)の左上のXY座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番かを取得
        const uint32_t minnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                              (uint32_t)((tx1 - _root_x1) * _r_top_level_dx),
                              (uint32_t)((ty1 - _root_y1) * _r_top_level_dy)
                          );

        //Rect(要素)の右下のXY座標点が所属する空間は、最大レベルの空間（分割されない最も深い空間）でモートン順序通し空間番号は何番かを取得
        const uint32_t maxnum_in_toplevel = LinearQuadtree::getMortonOrderNumFromXYindex(
                              (uint32_t)((tx2 - _root_x1) * _r_top_level_dx),
                              (uint32_t)((ty2 - _root_y1) * _r_top_level_dy)
                          );                 //↑_root_x2,_root_y2 と間違えていません。
        //空間に登録する（共通化）
        LinearTree<T,2,4>::registerElem((ITreeNodeElem*)prm_pNodeElem, minnum_in_toplevel, maxnum_in_toplevel);
//以下は共通化前のコード
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
//    //                                            o  o  x(以降x)      同一空間に内包されている判定（左からみる）
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
//    const uint32_t index = morton_order_space_num + (POW_N[_top_space_level-shift_num]-1)/3;
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
    }
    LinearQuadtreeRounder<T>* createRounder(void (T::*prm_pFuncHitCheck)(T*)) {
        LinearQuadtreeRounder<T>* pRounder = NEW LinearQuadtreeRounder<T>(LinearTree<T,2,4>::_paNodeSpaceArray, LinearTree<T,2,4>::_num_space, prm_pFuncHitCheck);
        return pRounder;
    }

    virtual ~LinearQuadtree() {
    }
};

}
#endif /*GGAF_CORE_LINEARQUADTREE_H_*/

