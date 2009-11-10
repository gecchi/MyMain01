#include "GgafCommonHeader.h"
#define DEBUG
#define MaxSplineSize 100


#define SPACE_MAXLEVEL     7
/**
 *
 *   用語定義(4分木での例)
 *
 *
 *
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
 *
 *  ＜モートン順序 ＞
 *  Zの順番で番号を振ることを指す(8分木ではZのZ)
 *  ＜モートン順序通し番号、空間番号＞
 *  上記の各レベル空間に振られている分割空間の番号のこと
 *  Lv2空間のモートン順序通し番号は0～15 というように使うこととする。
 *  ＜モートン順序位置＞
 *  4分割した場合(8分木では8分割)の左上、右上、左下、右下を それぞれ 0 1 2 3 (8分木では 0～7)と呼ぶ場合がある、
 *  【例１】
 *  Lv2 空間の モートン順序位置  2 というと
 *  +--+--+
 *  | 8| 9|
 *  +--+--+
 *  |10|11|
 *  +--+--+
 *  を指すこととする。
 *
 *  【例２】
 *  「Lv1の空間番号3の子空間のモートン順序位置3」と表現した場合は、
 *  Lv1の空間番号3の子空間＝Lv2空間の右下４つ
 *  +--+--+
 *  |12|13|
 *  +--+--+
 *  |14|15|
 *  +--+--+
 *  のことを指し、これのモートン順序位置3なので、Lv2空間モートン順序通し番号 14 を指してることとする。
 *
 *
 */
template<class T>
class GgafLinearOctree {

public:


    class Elem;

    class Space {
    public:
        /** 要素の先頭 */
        int _ary_index;
        int _belong_elem;
        Elem* _pElemFirst;
        Elem* _pElemLast;

        Space() {
            _pElemFirst = NULL;
            _pElemLast = NULL;
            _ary_index = 0;
            _belong_elem = 0;
        }

        bool push(Elem* prm_pElem) {
            if(prm_pElem) {
                return false;
            } else {
                processOnIncommingElem(prm_pElem);
                return true;
            }
        }

        /**
         * 要素が移動するときに呼び出されるコールバック。
         * @param prm_pElem 移動したがってる要素。
         */
        void processOnRemoveElem(Elem* prm_pElem) {
            prm_pElem->_pPrev->_pNext = prm_pElem->_pNext;
            prm_pElem->_pNext->_pPrev = prm_pElem->_pPrev;
            if (prm_pElem == _pElemFirst) {
                _pElemFirst = prm_pElem->_pNext;
            }
            if (prm_pElem == _pElemLast) {
                _pElemLast = prm_pElem->_pPrev;
            }
        }

        /**
         * 新しい要素の受け入れ。 .
         * 要素を末尾に追加
         * @param prm_pElem ニューカマー要素（ただし、前後要素はNULLが前提)
         */
        void processOnIncommingElem(Elem* prm_pElem) {
            if (_pElemFirst == NULL) {
                _pElemFirst = prm_pElem;
                _pElemLast = prm_pElem;
            } else {
                _pElemLast->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElemLast;
                prm_pElem->_pNext = NULL;
            }

        }

        void dump() {
            if (!_pElemFirst) {
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
    };

    class Elem {
    public:
        /** 所属空間 */
        Space* _pSpace_Current;

        /** 次要素 */
        Elem* _pNext;
        /** 前要素 */
        Elem* _pPrev;
        /** 対象オブジェクト */
        T* _pObject;

        Elem(T* prm_pObject) {
            _pSpace_Current = NULL;
            _pNext = NULL;
            _pPrev = NULL;
            _pObject = prm_pObject;
        }

        /**
         * 自身が他空間へ移動
         * @param prm_pSpace_target
         */
        Elem* moveToSpace(Space* prm_pSpace_target) {
            if (prm_pSpace_target == _pSpace_Current) {
                return NULL; //移動せんでいい
            }
            if (_pSpace_Current) { //既に所属してる場合(新規Elemじゃない場合)
                _pSpace_Current->processOnRemoveElem(this); //抜けますよ通知
            }
            _pNext = NULL;
            _pPrev = NULL;
            prm_pSpace_target->processOnIncommingElem(this); //入りますよ通知
            return this;
        }

        /**
         * 自身が離脱
         */
        Elem* extractFromCurrentSpace() {
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
        }

        void dump() {
            _TEXT_("o");
        }
    };

    /** 8分木の空間を意味する線形配列 */
    Space** _papSpace; //_papSpace[0] は ROOT空間へのポインタ


    int _root_X1; //root空間のx座標の小さい方
    int _root_Y1; //root空間のy座標の小さい方
    int _root_Z1; //root空間のz座標の小さい方
    int _root_X2; //root空間の対角の頂点となるx座標大きい方
    int _root_Y2; //root空間の対角の頂点となるy座標大きい方
    int _root_Z2; //root空間の対角の頂点となるz座標大きい方
    int _top_level_dX;  //最小空間のXの距離
    int _top_level_dY;  //最小空間のYの距離
    int _top_level_dZ;  //最小空間のZの距離


    DWORD* _paPow;
    DWORD _num_space;
    /** 最大空間レベル */
    DWORD _top_space_level; //ルート空間はLevel=0



    /**
     * コンストラクタ<BR>
     * @param   prm_pActor  適用Actor
     */
    GgafLinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
        _top_space_level = prm_level;
        //べき乗作成
        _paPow = NEW DWORD[SPACE_MAXLEVEL+1];
        _paPow[0] = 1;
        for(int i = 1; i < SPACE_MAXLEVEL + 1; i++) {
            _paPow[i] = _paPow[i-1] * 8;
            _TRACE_("_paPow["<<i<<"]="<< _paPow[i]);
        }

        //線形８分木配列作成
        _num_space = (_paPow[_top_space_level+1] -1) / 7; //空間数
        _TRACE_("_num_space="<<_num_space);
        if (_num_space > 100000) {
            return;
        }
        _papSpace = NEW Space*[_num_space];
        for (int i = 0; i < _num_space; i++) {
            _papSpace[i] = NEW Space();
            _papSpace[i]->_ary_index = i;
        }

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


    /**
     *
     * @return
     */

    /**
     * 要素を八分木空間に登録する
     * @param prm_pElem 要素
     * @param prm_X 要素対象オブジェクトのX座標
     * @param prm_Y 要素対象オブジェクトのY座標
     * @param prm_Z 要素対象オブジェクトのZ座標
     */
    void registElem(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
        //空間座標インデックス
        DWORD index = getSpaceIndex(tX1, tY1, tZ1, tX2, tY2, tZ2);


        _TRACE_("registElem:index="<<index);
        prm_pElem->moveToSpace(_papSpace[index]);

        // 引数の要素番号
        while(true) {
            //要素が追加されましたよカウント
            _papSpace[index]->_belong_elem ++;
            _TRACE_("_papSpace["<<index<<"]->_belong_elem ++  "<<(_papSpace[index]->_belong_elem));
            if (index == 0) {
                break;
            }
            // 親空間要素番号で繰り返す
            index = (index-1)>>3;

        }
    }



    // 座標から空間番号（線形八分木）を算出

    /**
     * 座標から空間配列要素番号（線形八分木配列の要素番号）を算出 .
     * まず、BOXの所属空間 Level と、その空間Levelのモートン順序通し空間番号を求め
     * 計算して配列Indexを返します
     * @param tX1
     * @param tY1
     * @param tZ1
     * @param tX2
     * @param tY2
     * @param tZ2
     * @return 空間番号
     */
    DWORD getSpaceIndex(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {

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
            if ((differ_bit_pos>>(i*3)) & 0x7 != 0 ) {
                shift_num = i+1;
            }
        }
        //xorしたdiffer_bit_pos を 右に3ビットシフトしつつ、マスク &B111(&H7) でANDを取り、&B000 でなくなっている位置をしらべる。
        //これは differ_bit_pos を ３ビットに区切り、その3ビットが食い違っている箇所をしらべている
        //食い違う3ビットの位置は、そのレベルのモトーン順序位置が食い違っていることを意味する。
        //最も遠い3ビットが食い違っている箇所(シフト回数＝shift_num)より所属空間レベルがわかる
        //最大空間分割Level = 5として、左上手前が6001番、右下奥を6041番に所属していたBOXを例にすると
        //
        //各レベル空間のモートン順序位置                             lv0 lv1 lv2 lv3 lv4 lv5
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
        //所属空間レベルは  _top_space_level - shift_num で求まり
        //「8の空間レベル乗」することで、そのレベル空間の0番の配列要素番号を算出(-1 は 配列は 0 から始まるため)
        //先の例でいうと shift_num = 3 で、最大空間分割Level(_top_space_level) = 5 であるので
        // 5 - 3 = 2 で所属空間レベルは 2
        // 8 ^ 2 = 64 つまり 空間レベル2 のモートン順序通し空間番号の0番は、配列の64番目。64番目の要素番号は-1して 63。
        //最後に、その所属空間レベルのモートン順序通し空間番号(morton_order_space_num)を足す。
        //11 + 63 = 74 よって配列要素番号は74となる
        _TRACE_("minnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
                "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
                "index="<<index);
#ifdef OREDEBUG
        if(index > _num_space) {
            _TRACE_("minnum_in_toplevel="<<minnum_in_toplevel<<"/maxnum_in_toplevel="<<maxnum_in_toplevel<<
                    "differ_bit_pos="<<differ_bit_pos<<"/shift_num="<<shift_num<<"/morton_order_space_num="<<morton_order_space_num<<
                    "index="<<index);
        }
#endif
        return index;
    }


    // 座標→線形8分木要素番号変換関数
    WORD getIndex(int tX, int tY, int tZ) {
        return getMortonOrderNumFromXYZindex(
                    (tX - _root_X1) / _top_level_dX,
                    (tY - _root_Y1) / _top_level_dY,
                    (tZ - _root_Z1) / _top_level_dZ
               );
    }

    // 3Dモートン空間番号算出関数


    /**
     * 同一Level空間の八分木モートン順序の通し空間番号取得.
     * 同一Levelとは任意のLevel空間のことですが、引数と結果は同一level空間ですよという意味です。
     * やっていることは
     * ・引数をそれぞれ3bitごとに間隔を開ける
     * ・引数2の結果を1ビット、引数2の結果を2ビット  ずらして OR を取る
     * つまり
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
     *
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = そのLevelの空間のモートン順序の位置 0～7
     *             ............  |   |   +---&B(wog) = そのLevelの親空間のモートン順序の位置  0～7
     *                           |   +-------&B(vnf) = そのLevelの親の親の空間のモートン順序の位置 0～7
     *
     *
     * @param x_index 同一のレベル空間のx座標空間インデックス (ただし 0～255 とする)
     * @param y_index 同一のレベル空間のy座標空間インデックス (ただし 0～255 とする)
     * @param z_index 同一のレベル空間のz座標空間インデックス (ただし 0～255 とする)
     * @return そのLevell空間の(x_index, y_index, z_index)で示される空間に対応する
     *         八分木モートン順序の通し空間番号(最大Level8で、0～23068671)
     */
    DWORD getMortonOrderNumFromXYZindex( DWORD x_space_index, DWORD y_space_index, DWORD z_space_index ) {
       return separateEveryThirdBit(x_space_index)    |
              separateEveryThirdBit(y_space_index)<<1 |
              separateEveryThirdBit(z_space_index)<<2;
    }

    //ビット分割関数

    /**
     * 3bitごとに間隔を開ける .
     * <code>
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
     * </code>
     * @param n 0～255までの数値
     * @return 3bitごとに間隔が空けられた値
     */
    inline DWORD separateEveryThirdBit(DWORD n) {
       n = ( n | n<<8 ) & 0x0000f00f;
       n = ( n | n<<4 ) & 0x000c30c3;
       n = ( n | n<<2 ) & 0x00249249;
       return n;
    }

    void dump() {
        int idx = 0;
        Space* _pSpace;
        for (int lv = 0; lv < _top_space_level; lv++) {
            for (int n = 0; n < _paPow[lv]; n++) {
                _pSpace = _papSpace[idx];
                _TEXT_("["<<idx<<"] ("<<lv<<"-"<<n<<")=");
                _pSpace.dump();
                _TEXT_("\n");
            }
        }
    }

    virtual ~GgafLinearOctree() {
    }
};

#define VULL ((void *)1)

int main() {
    GgafLinearOctree<int>* pLinearOctree =
            NEW GgafLinearOctree<int>
                (
                    5,
                    -8000 ,-8000 ,-8000 ,8000 ,8000 ,8000
                );
    int* xxx = NEW int(2);

    GgafLinearOctree<int>::Elem* pElem = NEW GgafLinearOctree<int>::Elem(xxx);
    pLinearOctree->registElem(pElem, 10 ,10 ,10, 41 ,51 ,61);
    pLinearOctree->registElem(pElem, 7000 ,7000 ,7000, 7999 ,7999 ,7999);
    pLinearOctree->registElem(pElem, 1 ,1 ,1, 1 ,1 ,1);
    _TRACE_("----------------------------------------------------------------八分木")
    int aPow[8];
    aPow[0] = 1;
    for(int i = 1; i < 8; i++) {
        aPow[i] = aPow[i-1] * 8;
    }
    int idx0 = 0;
    int LV0 = 0;

    for (int LV1 = 0; LV1 < 8; LV1++) {
        int mn1 = LV1;
        int idx1 = aPow[0] +
                    LV1;

        if (pLinearOctree->_papSpace[idx1]->_belong_elem == 0) {
            continue;
        } else {
            _TEXT_(" L1["<<LV1<<","<<mn1<<","<<idx1<<"]");
            pLinearOctree->_papSpace[idx1]->dump();
            _TEXT_("\n");
        }
        for (int LV2 = 0; LV2 < 8; LV2++) {
            int mn2 = LV1*aPow[1] +
                      LV2;
            int idx2 = aPow[0]+ aPow[1] +
                       LV1*aPow[1] +
                       LV2;


            if (pLinearOctree->_papSpace[idx2]->_belong_elem == 0) {
                continue;
            } else {
                _TEXT_("   L2["<<LV2<<","<<mn2<<","<<idx2<<"]");
                pLinearOctree->_papSpace[idx2]->dump();
                _TEXT_("\n");
            }
            for (int LV3 = 0; LV3 < 8; LV3++) {
                int mn3 = LV1*aPow[2] +
                          LV2*aPow[1] +
                          LV3;
                int idx3 = aPow[0]+ aPow[1] + aPow[2] +
                            LV1*aPow[2] +
                            LV2*aPow[1] +
                            LV3;

                if (pLinearOctree->_papSpace[idx3]->_belong_elem == 0) {
                    continue;
                } else {
                    _TEXT_("    L3["<<LV3<<","<<mn3<<","<<idx3<<"]");
                    pLinearOctree->_papSpace[idx3]->dump();
                    _TEXT_("\n");
                }
                for (int LV4 = 0; LV4 < 8; LV4++) {
                    int mn4 =LV1*aPow[3] +
                            LV2*aPow[2] +
                            LV3*aPow[1] +
                            LV4;
                    int idx4 = aPow[0]+ aPow[1] + aPow[2] + aPow[3] +
                                LV1*aPow[3] +
                                LV2*aPow[2] +
                                LV3*aPow[1] +
                                LV4;



                    if (pLinearOctree->_papSpace[idx4]->_belong_elem == 0) {
                        continue;
                    } else {
                        _TEXT_("     L4["<<LV4<<","<<mn4<<","<<idx4<<"]");
                        pLinearOctree->_papSpace[idx4]->dump();
                        _TEXT_("\n");
                    }
                    for (int LV5 = 0; LV5 < 8; LV5++) {
                        int mn5 =   LV1*aPow[4] +
                                    LV2*aPow[3] +
                                    LV3*aPow[2] +
                                    LV4*aPow[1] +
                                    LV5;
                        int idx5 =  aPow[0]+ aPow[1] + aPow[2] + aPow[3] + aPow[4] +
                                    LV1*aPow[4] +
                                    LV2*aPow[3] +
                                    LV3*aPow[2] +
                                    LV4*aPow[1] +
                                    LV5;

                        if (pLinearOctree->_papSpace[idx5]->_belong_elem == 0) {
                            continue;
                        } else {
                            _TEXT_("      L5["<<LV5<<","<<mn5<<","<<idx5<<"]");
                            pLinearOctree->_papSpace[idx5]->dump();
                            _TEXT_("\n");
                        }

                    }
                }
            }
        }
    }

}



