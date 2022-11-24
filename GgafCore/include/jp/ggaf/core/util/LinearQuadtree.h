#ifndef GGAF_CORE_LINEARQUADTREE_H_
#define GGAF_CORE_LINEARQUADTREE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/util/TreeSpace.hpp"
#include "jp/ggaf/core/util/TreeElem.hpp"

#define MAX_QUADTREE_LEVEL 14

namespace GgafCore {

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
 * 具体的には _paQuadrant の要素番号。<BR>
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
class LinearQuadtree : public Object {

private:
    /**
     * 同一Level空間の四分木モートン順序の通し空間番号取得 .
     * 同一Levelとは <BR>
     * 「引数と結果は同一level空間ですよ」<BR>
     * という意味。本メソッドの引数は任意のLevel空間を受け入れる。<BR>
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
    /** [r]四分木の空間を一直線に並べた線形配列 */
    TreeSpace<2u>* _paQuadrant; //_paQuadrant[0] は ROOT空間へのポインタ
    /** [r]登録を行った空間の先頭要素 */
    TreeSpace<2u>* _pRegTreeSpaces;

    /** [r]最大空間レベル */
    const uint32_t _top_space_level; //ルート空間はLevel=0
    /** [r]root空間の対角の頂点となるx座標の小さい方 */
    const int _root_x1;
    /** [r]root空間の対角の頂点となるy座標の小さい方 */
    const int _root_y1;
    /** [r]root空間の対角の頂点となるz座標の小さい方 */
    const int _root_x2;
    /** [r]root空間の対角の頂点となるy座標大きい方 */
    const int _root_y2;
    /** [r]最小空間(=最高分割の空間)の1空間のX軸方向の距離 */
    const int _top_level_dx;
    /** [r]最小空間(=最高分割の空間)の1空間のY軸方向の距離 */
    const int _top_level_dy;

    const double _r_top_level_dx;
    const double _r_top_level_dy;
    /** [r]全空間数 */
    const uint32_t _num_space;
    /** [r]8の累乗の値を予め計算して保持している配列 */
    static const uint32_t _POW4[(MAX_QUADTREE_LEVEL+1)+1];

    char _aChar_strbit[33];
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
                       int x2, int y2);

    /**
     * 要素を四分木空間に登録する
     * 空間番号範囲外になった場合は無視される。
     * @param prm_pElem 要素
     * @param tx1 要素対象オブジェクトの外枠の座標
     * @param ty1 〃
     * @param tx2 〃
     * @param ty2 〃
     */
    void registerElem(TreeElem<2u>* const prm_pElem,
                      int tx1, int ty1,
                      int tx2, int ty2);

    /**
     * 四分木空間に登録されている全要素を消去する（未所属状態にする）.
     * 本メソッドクリアしたならば、<BR>
     * registerElem() <BR>
     * により四分木へ再度要素登録が可能となる。
     */
    void clearAllElem();

    /**
     * デバッグ用。四分木登録状況出力 .
     */
    void putTree();
    void putTree(uint32_t prm_index_begin, int prm_lv = 0, int prm_pos = 0);

    virtual ~LinearQuadtree();
};

}
#endif /*GGAF_CORE_LINEARQUADTREE_H_*/

