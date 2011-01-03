#ifndef COLLIAAPOS_PRISM_H_
#define COLLIAAPOS_PRISM_H_
namespace GgafDx9LibStg {


/**
 * AAPrism(�����s�v���Y���FAxis-Aligned Prism)�����蔻��v�f�N���X
 * �����s�v���Y���Ƃ́AAAB�̂���ʂ̑Ίp���ŃX���C�X���P��s�������̂̎��B
 * @version 1.00
 * @since 2010/12/28
 * @author Masatoshi Tsuge
 */
class ColliAAPrism : public ColliAAB {
public:

    int _pos_prism;
    /** �v���Y���Εӂ̋��E���X�� */
    double _a;
    /** �v���Y���Εӂ̋��E���̐ؕ� */
    double _b;
    /** �v���Y���ΕӖʂ̖@���x�N�g���̋t�x�N�g��X�v�f(�����蔻��v�Z�p) */
    float _vIH_x;
    /** �v���Y���ΕӖʂ̖@���x�N�g���̋t�x�N�g��Y�v�f(�����蔻��v�Z�p) */
    float _vIH_y;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);


    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
