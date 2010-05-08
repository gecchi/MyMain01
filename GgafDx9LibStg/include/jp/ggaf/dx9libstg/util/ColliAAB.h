#ifndef COLIAABB_H_
#define COLIAABB_H_
namespace GgafDx9LibStg {

/**
 * AABB�����蔻��v�f�N���X
 * @version 1.00
 * @since 2008/03/13
 * @author Masatoshi Tsuge
 */
class ColliAAB : public GgafDx9Core::GgafDx9CollisionPart {
public:
    /** AABB��x���W�̏������� */
    int _x1;
    /** AABB��y���W�̏������� */
    int _y1;
    /** AABB��z���W�̏������� */
    int _z1;
    /** AABB�̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    int _x2;
    /** AABB�̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    int _y2;
    /** AABB�̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    int _z2;


    ColliAAB();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, bool rotX, bool rotY, bool rotZ);

    bool rotate(angle rX, angle rY, angle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAABB_H_*/
