#ifndef GGAFDXCOLLISIONPART_H_
#define GGAFDXCOLLISIONPART_H_
namespace GgafDxCore {

/**
 * �����蔻��v�f�N���X .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * �����蔻��v�f �E�E�E �P�� ���A������AAB�A�����̓v���Y���̓����蔻��B<BR>
 * �����蔻��̈� �E�E�E �����̓����蔻��v�f���W�܂��āA�O���[�v��������<BR>
 * �{�N���X�͓����蔻��u�v�f�v�����������N���X�ł��B<BR>
 * �`��� AAB �܂��� �v���Y�� �܂��� �� ���T�|�[�g�B�i���㑝���邩������Ȃ��j<BR>
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

    /** �����蔻��v�f��X�������� */
    coord _dx;
    /** �����蔻��v�f��Y�������� */
    coord _dy;
    /** �����蔻��v�f��Z�������� */
    coord _dz;
    /** �����蔻��v�f�̒��S�̃��[�J��X���W */
    coord _cx;
    /** �����蔻��v�f�̒��S�̃��[�J��Y���W */
    coord _cy;
    /** �����蔻��v�f�̒��S�̃��[�J��Z���W */
    coord _cz;
    /** �����蔻��v�f�̒��S�̃��[�J��X���W�i��]����O�̏����l�j */
    coord _base_cx;
    /** �����蔻��v�f�̒��S�̃��[�J��Y���W�i��]����O�̏����l�j */
    coord _base_cy;
    /** �����蔻��v�f�̒��S�̃��[�J��Z���W�i��]����O�̏����l�j */
    coord _base_cz;

    /** �����蔻��v�f��X���������̔��� */
    coord _hdx;
    /** �����蔻��v�f��Y���������̔��� */
    coord _hdy;
    /** �����蔻��v�f��Z���������̔��� */
    coord _hdz;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��X����]�̕��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
    bool _rotX;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��Y����]�̕��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
    bool _rotY;
    /** �{�̂̃��[�J�����W(0,0,0)�𒆐S��Z����]�̕��s�ړ��������邩�ǂ����i������]�O�Ղ̕��s�ړ��ł���A�v�f������]����̂ł͂Ȃ��j */
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
