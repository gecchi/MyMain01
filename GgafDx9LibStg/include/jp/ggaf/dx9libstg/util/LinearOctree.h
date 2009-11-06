#ifndef LINEAROCTREE_H_
#define LINEAROCTREE_H_
namespace GgafDx9LibStg {

class LinearOctree : public GgafCore::GgafObject {

public:
    int _X1; //root空間のx座標の小さい方
    int _Y1; //root空間のy座標の小さい方
    int _Z1; //root空間のz座標の小さい方
    int _X2; //root空間の対角の頂点となるx座標大きい方
    int _Y2; //root空間の対角の頂点となるy座標大きい方
    int _Z2; //root空間の対角の頂点となるz座標大きい方
    int _min_dX;  //最小空間のXの距離
    int _min_dY;  //最小空間のYの距離
    int _min_dZ;  //最小空間のZの距離


    int* _paPow[];
    int _num_space;
    int _level;
    GgafCore::GgafDx9GeometricActor* _papSpace[];   // 線形８分木タ配列


    /**
     * コンストラクタ<BR>
     * @param	prm_pActor	適用Actor
     */
    LinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2);


    /**
     *
     * @return
     */
    void regist(GgafDx9Core::GgafDx9GeometricActor* prm_pActer);


    // 座標から空間番号を算出
    DWORD GetMortonNumber( D3DXVECTOR3 *Min, D3DXVECTOR3 *Max )
    {
        // 最小レベルにおける各軸位置を算出
        DWORD LT = GetPointElem(*Min);
        DWORD RB = GetPointElem(*Max);

        // 空間番号を引き算して
        // 最上位区切りから所属レベルを算出
        DWORD Def = RB ^ LT;
        unsigned int HiLevel = 1;
        unsigned int i;
        for(i=0; i<m_uiLevel; i++)
        {
            DWORD Check = (Def>>(i*3)) & 0x7;
            if( Check != 0 )
                HiLevel = i+1;
        }
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
     * 8分木モートン順序計算 .
     * @param x x軸空間の何個目空間か
     * @param y y軸空間の何個目空間か
     * @param z z軸空間の何個目空間か
     * @return (x,y,z)で示される
     */
    DWORD Get3DMortonOrder( BYTE x, BYTE y, BYTE z ) {
       return BitSeparateFor3D(x) | BitSeparateFor3D(y)<<1 | BitSeparateFor3D(z)<<2;
    }

    //ビット分割関数

    /**
     * 3バイトごとに間隔を開ける関数 .
     * <code>
     * n
     * abcd efgh
     *
     * DWORD s = n
     * 0000 0000 0000 0000 0000 0000 abcd efgh
     *
     * (s<<8)
     * 0000 0000 0000 0000 abcd efgh 0000 0000
     *
     * s|s(s<<8)
     * 0000 0000 0000 0000 abcd efgh abcd efgh
     *
     * 0x0000f00f
     * 0000 0000 0000 0000 1111 0000 0000 1111
     *
     * s = s|s(s<<8) & 0x0000f00f
     * 0000 0000 0000 0000 abcd 0000 0000 efgh
     *
     * s<<4
     * 0000 0000 0000 abcd 0000 0000 efgh 0000
     *
     * s|s(s<<4)
     * 0000 0000 0000 abcd abcd 0000 efgh efgh
     *
     * 0x000c30c3
     * 0000 0000 0000 1100 0011 0000 1100 0011
     *
     * s = s|s(s<<4) & 0x000c30c3
     * 0000 0000 0000 ab00 00cd 0000 ef00 00gh
     *
     * s<<2
     * 0000 0000 00ab 0000 cd00 00ef 0000 gh00
     *
     * s|s(s<<2)
     * 0000 0000 00ab ab00 cdcd 00ef ef00 ghgh
     *
     * 0x00249249
     * 0000 0000 0010 0100 1001 0010 0100 1001
     *
     * s|s(s<<2) & 0x00249249
     * 0000 0000 00a0 0b00 c00d 00e0 0f00 g00h
     *
     * 00 000 000 00a 00b 00c 00d 00e 00f 00g 00h
     *
     */
    DWORD separateEveryThirdBit(BYTE n) {
       DWORD s = n;
       s = ( s | s<<8 ) & 0x0000f00f;
       s = ( s | s<<4 ) & 0x000c30c3;
       s = ( s | s<<2 ) & 0x00249249;
       return s;
    }


    virtual ~LinearOctree();
};

}
#endif /*LINEAROCTREE_H_*/

