#ifndef COLLIAAPRISM_H_
#define COLLIAAPRISM_H_
namespace GgafDx9LibStg {


#define XY_XpYn   1
#define XY_XnYp   2
#define XY_XpYp   3
#define XY_XnYn   4

#define YZ_YpZn   5
#define YZ_YnZp   6
#define YZ_YpZp   7
#define YZ_YnZn   8

#define ZX_ZpXn   9
#define ZX_ZnXp   10
#define ZX_ZpXp   11
#define ZX_ZnXn   12

/**
 * AAPrism(�����s�v���Y���FAxis-Aligned Prism)�����蔻��v�f�N���X
 * �����s�v���Y���Ƃ́AAAB�̂���ʂ̑Ίp���ŃX���C�X���P��s�������̂̎��B
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** AAB��x���W�̏������� */
    int _x1;
    /** AAB��y���W�̏������� */
    int _y1;
    /** AAB��z���W�̏������� */
    int _z1;
    /** AAB�̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    int _x2;
    /** AAB�̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    int _y2;
    /** AAB�̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    int _z2;

    int _pos_prism;
    int _slant_x1;
    int _slant_y1;
    int _slant_x2;
    int _slant_y2;
    int _slant_cal;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);

    bool rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
