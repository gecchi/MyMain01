#ifndef GGAFDXCOLLISIONPART_H_
#define GGAFDXCOLLISIONPART_H_
namespace GgafDxCore {

/**
 * �����蔻��̈�v�f .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * �����蔻��v�f �E�E�E �P�� ���A������AAB �̓����蔻��B<BR>
 * �����蔻��̈� �E�E�E �����̓����蔻��v�f���W�܂��āA�O���[�v��������<BR>
 * �{�N���X�͓����蔻��u�v�f�v�����������N���X�ł��B<BR>
 * �`��� AAB �܂��� �� ���T�|�[�g�B�i���㑝���邩������Ȃ��j<BR>
 * �����蔻��̃��[�J������]���s�ړ����T�|�[�g .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDxCollisionPart : public GgafCore::GgafObject {

public:
    /** �����蔻����(COLLI_AAB:�ӂ��e���ɕ��s�Ȓ����� / COLLI_AAPRISM:�ӂ��e���ɕ��s�ȃv���Y��/COLLI_SPHERE:��) */
    int _shape_kind;
    /** �L���t���O */
    bool _is_valid_flg;

    /** �����s������ */
    coord _aab_x1, _aab_y1, _aab_z1, _aab_x2, _aab_y2, _aab_z2;

    /** �����s�����̂�x�� */
    coord _dx;
    /** �����s�����̂�y�� */
    coord _dy;
    /** �����s�����̂�z�� */
    coord _dz;
    /** ���������s�����̒��S��X���W */
    coord _base_cx;
    /** ���������s�����̒��S��Y���W */
    coord _base_cy;
    /** ���������s�����̒��S��Z���W */
    coord _base_cz;
    /** �����s�����̒��S��X���W */
    coord _cx;
    /** �����s�����̒��S��Y���W  */
    coord _cy;
    /** �����s�����̒��S��Z���W  */
    coord _cz;

    /** x���̔��� */
    coord _hdx;
    /** y���̔��� */
    coord _hdy;
    /** z���̔��� */
    coord _hdz;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��X����]�̈ړ��������邩�ǂ����i�����̂�����]����̂ł͂Ȃ��j */
    bool _rotX;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Y����]�̈ړ��������邩�ǂ����i�����̂�����]����̂ł͂Ȃ��j */
    bool _rotY;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Z����]�̈ړ��������邩�ǂ����i�����̂�����]����̂ł͂Ȃ��j */
    bool _rotZ;


    GgafDxCollisionPart();

    /**
     * ����̈�̎��񕽍s�ړ����s���B
     * @param rX ���[�J��X����]�A���O���l(0~360000)
     * @param rY ���[�J��Y����]�A���O���l(0~360000)
     * @param rZ ���[�J��Z����]�A���O���l(0~360000)
     * @return
     */
    virtual void rotateRxRzRy(angle rX, angle rY, angle rZ) {
    }

    virtual ~GgafDxCollisionPart();
};

}
#endif /*GGAFDXCOLLISIONPART_H_*/
