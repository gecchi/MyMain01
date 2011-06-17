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
    appcoord _x1;
    /** AAB��y���W�̏������� */
    appcoord _y1;
    /** AAB��z���W�̏������� */
    appcoord _z1;
    /** AAB�̑Ίp�̒��_�ƂȂ�x���W�傫���� */
    appcoord _x2;
    /** AAB�̑Ίp�̒��_�ƂȂ�y���W�傫���� */
    appcoord _y2;
    /** AAB�̑Ίp�̒��_�ƂȂ�z���W�傫���� */
    appcoord _z2;


    ColliAAB();

    void set(appcoord x1, appcoord y1, appcoord z1, appcoord x2, appcoord y2, appcoord z2, bool rotX, bool rotY, bool rotZ);

    void rotateRxRzRy(appangle rX, appangle rY, appangle rZ) override;

    virtual ~ColliAAB();
};

}
#endif /*COLIAAB_H_*/
