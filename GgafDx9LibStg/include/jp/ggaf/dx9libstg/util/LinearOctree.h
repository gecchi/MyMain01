#ifndef LINEAROCTREE_H_
#define LINEAROCTREE_H_
namespace GgafDx9LibStg {

template<class T>
class LinearOctree {

public:


    class Elem;

    class Space {
    public:
        /** 要素の先頭 */
        Elem* _pElemFirst;
        Elem* _pElemLast;
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
            } else {
                _pElemLast->_pNext = prm_pElem;
                prm_pElem->_pPrev = _pElemLast;
                prm_pElem->_pNext = NULL;
            }

        }
    }

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

        /**
         * 自身が他空間へ移動
         * @param prm_pSpace_target
         */
        Elem* moveTo(Space* prm_pSpace_target) {
            if (prm_pSpace_target == _pSpace_Current) {
                return; //移動せんでいい
            }
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
            prm_pSpace_target->processOnIncommingElem(this);
            return this;
        }

        /**
         * 自身が離脱
         */
        Elem* extract() {
            _pSpace_Current->processOnRemoveElem(this);
            _pNext = NULL;
            _pPrev = NULL;
        }
    }

    /** 8分木の空間を意味する線形配列 */
    Space** _papSpace[]; //_papSpace[0] は ROOT空間へのポインタ


    int _root_X1; //root空間のx座標の小さい方
    int _root_Y1; //root空間のy座標の小さい方
    int _root_Z1; //root空間のz座標の小さい方
    int _root_X2; //root空間の対角の頂点となるx座標大きい方
    int _root_Y2; //root空間の対角の頂点となるy座標大きい方
    int _root_Z2; //root空間の対角の頂点となるz座標大きい方
    int _max_level_dX;  //最小空間のXの距離
    int _max_level_dY;  //最小空間のYの距離
    int _max_level_dZ;  //最小空間のZの距離


    int* _paPow[];
    int _num_space;
    /** 最大空間レベル */
    DWORD _level; //ルート空間はLevel=0



    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    LinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2) {
        _level = prm_level;
        //べき乗作成
        _paPow = NEW int[_level+1];
        _paPow[0] = 1;
        for(int i = 1; i < _level + 1; i++) {
            _paPow[i] = _paPow[i-1]*8;
        }

        //線形８分木配列作成
        _num_space = (_paPow[_level+1] -1) / 7; //空間数
        _papSpace = NEW Space*[_num_space];
        for (int i = 0; i < _num_space; i++) {
            _papSpace[i] = NEW Space();
        }

        _X1 = X1;
        _Y1 = Y1;
        _Z1 = Z1;
        _X2 = X2;
        _Y2 = Y2;
        _Z2 = Z2;
        _min_dX = (_X2-_X1) / ((float)(1<<Level));
        _min_dY = (_Y2-_Y1) / ((float)(1<<Level));
        _min_dZ = (_Z2-_Z1) / ((float)(1<<Level));
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
    void regist(Elem* prm_pElem, int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {
        //空間座標インデックス


    }


    // 座標から空間番号を算出
    DWORD GetMortonNumber(int tX1 ,int tY1 ,int tZ1 ,int tX2 ,int tY2 ,int tZ2) {

        //BOXの左上手前のXYZ座標点が所属する空間は、最大レベル空間でモートン順序番号何番かを取得
        DWORD min_num_in_maxlevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX1 - _root_X1) / _max_level_dX),
                                      (DWORD)((tY1 - _root_Y1) / _max_level_dY),
                                      (DWORD)((tZ1 - _root_Z1) / _max_level_dZ)
                                    );

        //BOXの右下奥のXYZ座標点が所属する空間は、最大レベル空間でモートン順序番号何番かを取得
        DWORD max_num_in_maxlevel = getMortonOrderNumFromXYZindex(
                                      (DWORD)((tX2 - _root_X2) / _max_level_dX),
                                      (DWORD)((tY2 - _root_Y2) / _max_level_dY),
                                      (DWORD)((tZ2 - _root_Z2) / _max_level_dZ)
                                     );
        //引数のBOXは、どのレベルの空間にすっぽり収まっているか取得

        DWORD differ_bit_pos = max_num_in_maxlevel ^ min_num_in_maxlevel;
        //differ_bit_pos を 右に3ビットずらしながらマスク 111 でANDを取り、 000 でなくなっている位置をしらべる。
        //これは differ_bit_pos を ３ビットに区切り、その3ビットが食い違っている箇所をしらべている
        //最も遠い3ビットが食い違っている箇所(シフト回数＝shift_pos)より所属レベルがわかる

        //XOR結果が
        // 000 000 000 000 000 000 000 111 の場合shift_pos=1
        //これは
        //最大空間分割Level=5 の場合は所属空間レベルは4
        //最大空間分割Level=8 の場合は所属空間レベルは8

        // 000 000 000 000 000 000 101 000 の場合は shift_pos=2
        //これは
        //最大空間分割Level=5 の場合は所属空間レベルは3
        //最大空間分割Level=8 の場合は所属空間レベルは7

        // 000 000 000 111 110 111 101 111 などの場合は shift_pos=5
        //これは
        //最大空間分割Level=5 の場合は所属空間レベルは0 つまりルート空間所属
        //最大空間分割Level=8 の場合は所属空間レベルは4

        DWORD shift_pos = 0;
        //＜例＞
        //最大空間分割Level = 5 の場合
        //shift_pos =  0 1 2 3 4 5
        //所属Level   =  5 4 3 2 1 0
        //最大空間分割Level=8 の場合
        //shift_pos =  1 2 3 4 5 6 7 8
        //所属Level   =  7 6 5 4 3 2 1 0
        for(DWORD bit3_index = 0; bit3_index < _level; lv++) {
            if (differ_bit_pos>>(bit3_index*3)) & 0x7 != 0 ) {
                shift_pos = bit3_index+1;
            }
        }

   255        11 11 11 11
   768     11 00 00 00 00

 bit3_index   4  3  2  1  0
             11 11 11 11 11


        DWORD SpaceNum = RB>>(HiLevel*3);
        DWORD AddNum = (m_iPow[m_uiLevel-HiLevel]-1)/7;
        SpaceNum += AddNum;

        if(SpaceNum > m_dwCellNum)
            return 0xffffffff;

        return SpaceNum;
    }


    // 座標→線形8分木要素番号変換関数
    WORD getIndex(int tX, int tY, int tZ) {
        return Get3DMortonNumber(
            (tX - _X1) / _min_dX,
            (tY - _Y1) / _min_dY,
            (tZ - _Z1) / _min_dZ
            );
    }

    // 3Dモートン空間番号算出関数


    /**
     * 同一Level空間の八分木モートン順序取得.
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
     * こうして、ORします。意味は、
     * 00000000 qia rjb skc tld ume vnf wog xph
     *                                      ^^^-->&B(xph) = そのLevelの空間の通しモートン順序番号 0～7
     *                                  ^^^^^^^-->&B(wogxph) = そのLevelの親空間の通しモートン順序番号 0～63
     *                              ^^^^^^^^^^^-->&B(vnfwogxph) = そのLevelの親の親空間の通しモートン順序番号 0～511
     *
     *                          ^^^ ^^^ ^^^ ^^^
     *                           |   |   |   |
     *                           |   |   |   &B(xph) = そのLevelの空間のモートン順序位置 0～7
     *             ............  |   |   +---&B(wog) = そのLevelの親空間のモートン順序位置  0～7
     *                           |   +-------&B(vnf) = そのLevelの親の親の空間のモートン順序位置 0～7
     *
     *
     * @param x_index 特定のレベル空間のx座標空間インデックス (ただし 0～255 とする)
     * @param y_index 特定のレベル空間のy座標空間インデックス (ただし 0～255 とする)
     * @param z_index 特定のレベル空間のz座標空間インデックス (ただし 0～255 とする)
     * @return そのLevell空間の(x_index, y_index, z_index)で示される空間に対応する
     *         八分木モートン通しモートン順序番号(最大Level8で、0～23068671)
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
     * n|n(n<<8) & 0x0000f00f =
     *              0000 0000 0000 0000 abcd 0000 0000 efgh となる。
     * この結果をまた n に代入する
     * n          = 0000 0000 0000 0000 abcd 0000 0000 efgh
     * 以下同様に
     * n<<4       = 0000 0000 0000 abcd 0000 0000 efgh 0000
     * n|n<<4     = 0000 0000 0000 abcd abcd 0000 efgh efgh
     * 0x000c30c3 = 0000 0000 0000 1100 0011 0000 1100 0011
     * n ← n|n(n<<4) & 0x000c30c3 =
     *              0000 0000 0000 ab00 00cd 0000 ef00 00gh
     * n<<2       = 0000 0000 00ab 0000 cd00 00ef 0000 gh00
     * n|n(n<<2)  = 0000 0000 00ab ab00 cdcd 00ef ef00 ghgh
     * 0x00249249 = 0000 0000 0010 0100 1001 0010 0100 1001
     * n ← n|n(n<<2) & 0x00249249 =
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


    virtual ~LinearOctree();
};

}
#endif /*LINEAROCTREE_H_*/

