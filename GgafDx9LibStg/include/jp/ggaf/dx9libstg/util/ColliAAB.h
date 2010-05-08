#ifndef COLIAAB_H_
#define COLIAAB_H_
namespace GgafDx9LibStg {

/**
 * AAB(�����s�����́FAxis-Aligned Box)�����蔻��v�f�N���X
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAAB : public GgafDx9Core::GgafDx9CollisionPart {
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


    ColliAAB();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    bool rotateRxRzRy(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAAB_H_*/
