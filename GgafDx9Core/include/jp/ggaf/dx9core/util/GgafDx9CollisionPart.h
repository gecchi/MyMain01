#ifndef GGAFDX9COLLISIONPART_H_
#define GGAFDX9COLLISIONPART_H_
namespace GgafDx9Core {

/**
 * �����蔻�蕔�i
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionPart : public GgafCore::GgafObject {

public:
    /** ��� */
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
     * ����̈�̎���]�ړ����s���B
     * @param rX
     * @param rY
     * @param rZ
     * @return
     */
    virtual bool rotate(GgafDx9Core::angle rX, GgafDx9Core::angle rY, GgafDx9Core::angle rZ) {
        return false;
    }

    virtual ~GgafDx9CollisionPart();
};

}
#endif /*GGAFDX9COLLISIONPART_H_*/
