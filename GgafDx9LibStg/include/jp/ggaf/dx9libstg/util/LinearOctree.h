#ifndef LINEAROCTREE_H_
#define LINEAROCTREE_H_
namespace GgafDx9LibStg {

class LinearOctree : public GgafCore::GgafObject {

public:
    int _X1; //root��Ԃ�x���W�̏�������
    int _Y1; //root��Ԃ�y���W�̏�������
    int _Z1; //root��Ԃ�z���W�̏�������
    int _X2; //root��Ԃ̑Ίp�̒��_�ƂȂ�x���W�傫����
    int _Y2; //root��Ԃ̑Ίp�̒��_�ƂȂ�y���W�傫����
    int _Z2; //root��Ԃ̑Ίp�̒��_�ƂȂ�z���W�傫����
    int _min_dX;  //�ŏ���Ԃ�X�̋���
    int _min_dY;  //�ŏ���Ԃ�Y�̋���
    int _min_dZ;  //�ŏ���Ԃ�Z�̋���


    int* _paPow[];
    int _num_space;
    int _level;
    GgafCore::GgafDx9GeometricActor* _papSpace[];   // ���`�W���؃^�z��


    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    LinearOctree(int prm_level, int X1 ,int Y1 ,int Z1 ,int X2 ,int Y2 ,int Z2);


    /**
     *
     * @return
     */
    void regist(GgafDx9Core::GgafDx9GeometricActor* prm_pActer);


    // ���W�����Ԕԍ����Z�o
    DWORD GetMortonNumber( D3DXVECTOR3 *Min, D3DXVECTOR3 *Max )
    {
        // �ŏ����x���ɂ�����e���ʒu���Z�o
        DWORD LT = GetPointElem(*Min);
        DWORD RB = GetPointElem(*Max);

        // ��Ԕԍ��������Z����
        // �ŏ�ʋ�؂肩�珊�����x�����Z�o
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


    // ���W�����`8���ؗv�f�ԍ��ϊ��֐�
    WORD getIndex(int tX, int tY, int tZ) {
        return Get3DMortonNumber(
            (tX - _X1) / _min_dX,
            (tY - _Y1) / _min_dY,
            (tZ - _Z1) / _min_dZ
            );
    }

    // 3D���[�g����Ԕԍ��Z�o�֐�
    WORD Get3DMortonNumber(WORD x, WORD y, WORD z)
    {
        return BitSeparateFor3D(x) | BitSeparateFor3D(y)<<1 | BitSeparateFor3D(z)<<2;
    }
    //�r�b�g�����֐�
    DWORD BitSeparateFor3D( WORD n )
    {
        DWORD s = n;
        s = ( s | s << 8 ) & 0x0000f00f;
        s = ( s | s << 4 ) & 0x000c30c3;
        s = ( s | s << 2 ) & 0x00249249;
        return s;
    }

          1111000000001111
      11000011000011000011
    1001001001001001001001





    00 000 000 000 000 000 000 000 000 000 000


    virtual ~LinearOctree();
};

}
#endif /*LINEAROCTREE_H_*/

