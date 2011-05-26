#ifndef GGAFLINEAROCTREE_H_
#define GGAFLINEAROCTREE_H_
namespace GgafCore {

// 本プログラムは、
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html
// サイト内コンテンツの 「その15 8分木空間分割を最適化する！」 http://marupeke296.com/COL_3D_No15_Octree.html
// の記事を参考に作成しています。
//                                            2009/01/13 Masatoshi Tsuge


/**
 * 線形八分木クラス .
 * 線形八分木とは、八分木空間分割手法の各空間を、一列の配列(線形)に並べた状態を意味します。
 * 本クラスでの用語を次のように定める事とする。
 * 立体図がコメントAAで表現できないため、4分木の図を例に言葉の説明するが。本クラスの機能は立体の８分木です。
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
 * <B>＜モートン順序通し番号＞</B><BR>
 * 上記図の各Level空間に振られている分割空間の番号のことを指す事とする。<BR>
 * 上記図の例ではLv2空間のモートン順序通し番号は0～15 というように使う。<BR>
 * 実際は８分木なので。立体でLv2空間モートン順序通し番号は0~15*15 になる。<BR>
 * <BR>
 * <B>＜空間番号＞</B><BR>
 * 上記図の右に書いてあるように、各空間Lv毎にモートン順序で振られた番号を指す。<BR>
 * <BR>
 * <B>＜空間(配列)要素番号＞</B><BR>
 * 空間番号に対応する線形配列のインデックスを指す。<BR>
 * 具体的には _paSpace の要素番号。<BR>
 * <BR>
 * <B>＜モートン順序位置＞</B><BR>
 * ある空間を4分割し、左上、右上、左下、右下を
 * それぞれ 0 1 2 3 (8分木では 0～7)と表現したい場合がある、
 * この 0 1 2 3 の事をモートン順序位置と呼ぶこととする。<BR>
 * <BR>
 *
 *  <B>【例１】</B><BR>
 *  Lv2 空間の モートン順序位置  2 というと
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
 *  その他使用例<BR>
 *  ・Lv1 空間のモートン順序位置 1 は Lv2 空間の空間番号 4 5 6 7 に当たる。<BR>
 *  ・Lv2 空間番号 13 は、親空間の空間番号 3 の内のモートン順序位置 1 の空間である。<BR>
 *  というように表現したりする（と定義する）。<BR>
 *
 * @version 1.00
 * @since 2009/11/23
 * @author Masatoshi Tsuge
 */
class GgafLinearOctree {

public:

    /** 8分木の空間を意味する線形配列 */
    GgafLinearOctreeSpace* _paSpace; //_paSpace[0] は ROOT空間へのポインタ
    /**s     */
    GgafLinearOctreeElem* _pRegElemFirst;
    /** root空間の対角の頂点となるx座標の小さい方 */
    int _root_X1;
    /** root空間の対角の頂点となるy座標の小さい方 */
    int _root_Y1;
    /** root空間の対角の頂点となるz座標の小さい方 */
    int _root_Z1;
    /** root空間の対角の頂点となるx座標大きい方 */
    int _root_X2;
    /** root空間の対角の頂点となるy座標大きい方 */
    int _root_Y2;
    /** root空間の対角の頂点となるz座標大きい方 */
    int _root_Z2;
    /** 最小空間(=最高空間レベル)のXの距離 */
    int _top_level_dX;
    /** 最小空間(=最高空間レベル)のYの距離 */
    int _top_level_dY;
    /** 最小空間(=最高空間レベル)のZの距離 */
    int _top_level_dZ;

    /** 8の累乗の値を予め計算して保持している配列 */
    UINT32* _paPow;
    /** 全空間数 */
    UINT32 _num_space;
    /** 最大空間レベル */
    int _top_space_level; //ルート空間はLevel=0

    /**
     * 線形八分木空間を構築する.
     * @param prm_level 構築する空間レベル
     */
    GgafLinearOctree(int prm_level);

    /**
     * 空間レベル0の実範囲を更新.
     * 随時変更可能。
     * @param X1 構築する外枠の空間座標
     * @param Y1 〃
     * @param Z1 〃
     * @param X2 〃
     * @param Y2 〃
     * @param Z2 〃
     */
    virtual void setRootSpace(int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2);

    /**
     * 要素を八分木空間に登録する
     * 空間番号範囲外になった場合は無視される。
     * @param prm_pElem 要素
     * @param tX1 要素対象オブジェクトの外枠の座標
     * @param tY1 〃
     * @param tZ1 〃
     * @param tX2 〃
     * @param tY2 〃
     * @param tZ2 〃
     */
    virtual void registElem(GgafLinearOctreeElem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2);


    virtual void clearElem();

    /**
     * 同一Level空間の八分木モートン順序の通し空間番号取得 .
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
    inline UINT32 getMortonOrderNumFromXYZindex( UINT32 x_space_index, UINT32 y_space_index, UINT32 z_space_index ) {
       return separateEveryThirdBit(x_space_index) | separateEveryThirdBit(y_space_index)<<1 | separateEveryThirdBit(z_space_index)<<2;
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
    inline UINT32 separateEveryThirdBit(UINT32 n) {
       n = ( n | n<<8 ) & 0x0000f00f;
       n = ( n | n<<4 ) & 0x000c30c3;
       n = ( n | n<<2 ) & 0x00249249;
       return n;
    }


    virtual ~GgafLinearOctree();
    /**
     * デバッグ用ツリー状況出力 .
     */
    void putTree();
};

}
#endif /*GGAFLINEAROCTREE_H_*/

