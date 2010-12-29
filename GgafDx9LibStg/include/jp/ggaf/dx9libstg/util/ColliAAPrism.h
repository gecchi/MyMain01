#ifndef COLLIAAPRISM_H_
#define COLLIAAPRISM_H_
namespace GgafDx9LibStg {

                              //   XYZnp
#define PRISM_XY_nn   (0x18)  //0b 11000
#define PRISM_XY_np   (0x19)  //0b 11001
#define PRISM_XY_pn   (0x1a)  //0b 11010
#define PRISM_XY_pp   (0x1b)  //0b 11011
#define PRISM_YZ_nn   (0xc)   //0b 01100
#define PRISM_YZ_np   (0xd)   //0b 01101
#define PRISM_YZ_pn   (0xe)   //0b 01110
#define PRISM_YZ_pp   (0xf)   //0b 01111
#define PRISM_ZX_nn   (0x14)  //0b 10100
#define PRISM_ZX_np   (0x15)  //0b 10101
#define PRISM_ZX_pn   (0x16)  //0b 10110
#define PRISM_ZX_pp   (0x17)  //0b 10111


#define PRISM_nn      (0x0)    //0b 00000
#define PRISM_np      (0x1)    //0b 00001
#define PRISM_pn      (0x2)    //0b 00010
#define PRISM_pp      (0x3)    //0b 00011
#define PRISM_XY      (0x18)   //0b 11000
#define PRISM_YZ      (0xc)    //0b 01100
#define PRISM_ZX      (0x14)   //0b 10100

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
    double _a;
    double _b;

    ColliAAPrism();

    void set(int x1, int y1, int z1, int x2, int y2, int z2, int pos_prism, bool rotX, bool rotY, bool rotZ);


    virtual ~ColliAAPrism();
};

}
#endif /*COLIAAB_H_*/
