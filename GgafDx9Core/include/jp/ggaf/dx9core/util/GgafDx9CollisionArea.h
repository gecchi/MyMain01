#ifndef GGAFDX9COLLISIONAREA_H_
#define GGAFDX9COLLISIONAREA_H_
namespace GgafDx9Core {

/**
 * �����蔻��̈�C���^�[�t�F�C�X�N���X(�V)
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionArea : public GgafCore::GgafObject {

public:
    /** �e�����蔻��v�f�܂ޑS�̂̊O���̋��EBOX(8���ؓo�^�̂���) */
    int _AABB_X1, _AABB_Y1, _AABB_Z1, _AABB_X2, _AABB_Y2, _AABB_Z2;

    /** �e�����蔻��v�f�̔z�� */
    GgafDx9CollisionPart** _papColliPart;
    /** �S���蔻��v�f�� */
    int _nColliPart;


    GgafDx9CollisionArea(int prm_nColliPart);

    void updateAABB();


    virtual ~GgafDx9CollisionArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
