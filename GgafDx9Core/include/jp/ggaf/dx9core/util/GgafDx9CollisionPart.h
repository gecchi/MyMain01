#ifndef GGAFDX9COLLISIONPART_H_
#define GGAFDX9COLLISIONPART_H_
namespace GgafDx9Core {

/**
 * �����蔻��̈�v�f .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * �����蔻��v�f �E�E�E �P�� ���A������AABB �̓����蔻��B<BR>
 * �����蔻��̈� �E�E�E �����̓����蔻��v�f���W�܂��āA�O���[�v��������<BR>
 * �{�N���X�͓����蔻��u�v�f�v�����������N���X�ł��B<BR>
 * �`��� AABB �܂��� �� ���T�|�[�g�B�i���㑝���邩������Ȃ��j<BR>
 * �����蔻��̃��[�J������]���s�ړ����T�|�[�g .
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionPart : public GgafCore::GgafObject {

public:
    /** �����蔻����(COLLI_AABB:�ӂ��e���ɕ��s�Ȓ����� / COLLI_SPHERE:��) */
    int _shape_kind;
    /** �L���t���O */
    bool _is_valid_flg;

    /** ���EBOX(8���ؓo�^�̂���) */
    int _aabb_x1, _aabb_y1, _aabb_z1, _aabb_x2, _aabb_y2, _aabb_z2;

    /** ���EBOX��x�� */
    int _dx;
    /** ���EBOX��y�� */
    int _dy;
    /** ���EBOX��z�� */
    int _dz;
    /** �������EBOX���S��X���W */
    int _base_cx;
    /** �������EBOX���S��Y���W */
    int _base_cy;
    /** �������EBOX���S��Z���W */
    int _base_cz;
    /** ���EBOX���S��X���W */
    int _cx;
    /** ���EBOX���S��Y���W  */
    int _cy;
    /** ���EBOX���S��Z���W  */
    int _cz;

    /** x���̔��� */
    int _hdx;
    /** y���̔��� */
    int _hdy;
    /** z���̔��� */
    int _hdz;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��X����]�̈ړ��������邩�ǂ����i��������]����̂ł͂Ȃ��j */
    bool _rotX;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Y����]�̈ړ��������邩�ǂ����i��������]����̂ł͂Ȃ��j */
    bool _rotY;
    /** ���S�_���A�I�u�W�F�N�g��(0,0)�𒆐S��Z����]�̈ړ��������邩�ǂ����i��������]����̂ł͂Ȃ��j */
    bool _rotZ;


    GgafDx9CollisionPart();

    /**
     * ����̈�̎��񕽍s�ړ����s���B
     * @param rX ���[�J��X����]�A���O���l(0~360000)
     * @param rY ���[�J��Y����]�A���O���l(0~360000)
     * @param rZ ���[�J��Z����]�A���O���l(0~360000)
     * @return
     */
    virtual bool rotate(angle rX, angle rY, angle rZ) {
        return false;
    }

    virtual ~GgafDx9CollisionPart();
};

}
#endif /*GGAFDX9COLLISIONPART_H_*/
