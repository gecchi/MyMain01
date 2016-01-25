#ifndef GGAFDXCORE_GGAFDXCOLLISIONPART_H_
#define GGAFDXCORE_GGAFDXCOLLISIONPART_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �����蔻��v�f�N���X .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * a)�����蔻��v�f �E�E�E �P�� �� or AAB or �v���Y�� �̓����蔻��̗��̐}�`�B<BR>
 * b)�����蔻��̈� �E�E�E ��L�̕����̓����蔻��v�f���W�܂��āA�O���[�v���������B<BR>
 * �{�N���X�� a) �����蔻��u�v�f�v�����������N���X�ł��B<BR>
 * �`��� AAB �܂��� �v���Y�� �܂��� �� ���T�|�[�g�B�i���㑝���邩������Ȃ��j<BR>
 * �����蔻��̃��[�J������]���s�ړ����T�|�[�g .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDxCollisionPart : public GgafCore::GgafObject {

public:
    /** �����蔻����(COLLI_AABOX / COLLI_AAPRISM / COLLI_AAPYRAMID / COLLI_SPHERE) */
    int _shape_kind;
    /** �L���t���O */
    bool _is_valid_flg;
    /** �����蔻�苫�E�����̂̃��[�J�����W */
    coord _x1, _y1, _z1, _x2, _y2, _z2;
    /** �����蔻�苫�E�����̂�X�������� */
    coord _dx;
    /** �����蔻�苫�E�����̂�Y�������� */
    coord _dy;
    /** �����蔻�苫�E�����̂�Z�������� */
    coord _dz;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��X���W */
    coord _cx;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��Y���W */
    coord _cy;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��Z���W */
    coord _cz;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��X���W�i��]����O�̏����l�j */
    coord _base_cx;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��Y���W�i��]����O�̏����l�j */
    coord _base_cy;
    /** �����蔻�苫�E�����̂̒��S�̃��[�J��Z���W�i��]����O�̏����l�j */
    coord _base_cz;

    /** _dx �̔����i�v�Z�p�j*/
    coord _hdx;
    /** _dy �̔����i�v�Z�p�j*/
    coord _hdy;
    /** _dz �̔����i�v�Z�p�j*/
    coord _hdz;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��X����]�̋O�Ղɕ��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
    bool _rot_x;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��Y����]�̋O�Ղɕ��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
    bool _rot_y;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��Z����]�̋O�Ղɕ��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
    bool _rot_z;
    /** ����]�̋O�Ղɕ��s�ړ�����̂��ǂ��� */
    bool _rot;

public:
    GgafDxCollisionPart();

    /**
     * ����̈�̎��񕽍s�ړ����s���B
     * @param rx ���[�J��X����]�A���O���l(0~360000)
     * @param ry ���[�J��Y����]�A���O���l(0~360000)
     * @param rz ���[�J��Z����]�A���O���l(0~360000)
     * @return
     */
    virtual void rotateRxRzRy(angle rx, angle ry, angle rz) = 0;

    virtual ~GgafDxCollisionPart();
};

}
#endif /*GGAFDXCORE_GGAFDXCOLLISIONPART_H_*/
