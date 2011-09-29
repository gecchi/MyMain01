#ifndef GGAFDX9COLLISIONAREA_H_
#define GGAFDX9COLLISIONAREA_H_
namespace GgafDx9Core {

/**
 * �����蔻��̈�N���X .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * �����蔻��v�f �E�E�E �P�� �� or AAB or �v���Y�� �̓����蔻��B<BR>
 * �����蔻��̈� �E�E�E �����̓����蔻��v�f���W�܂��āA�O���[�v��������<BR>
 * �{�N���X�͓����蔻��u�̈�v�����������N���X�ł��B<BR>
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class GgafDx9CollisionArea : public GgafCore::GgafObject {

public:
    /** 8���ؓo�^�̂��߂̑S�����蔻��v�f�܂ޑS�̂̊O���̎����s���E������ */
    coord _AABB_X1, _AABB_Y1, _AABB_Z1, _AABB_X2, _AABB_Y2, _AABB_Z2;
    //AABB(�����s���E������:Axis-Aligned Bounding Box)

    /** �����蔻��̈�v�f�̔z�� */
    GgafDx9CollisionPart** _papColliPart;
    /** �����蔻��̈�v�f�� */
    int _nColliPart;

    /**
     * �R���X�g���N�^ .
     * @param prm_nColliPart �����蔻��̈�v�f��
     * @return
     */
    GgafDx9CollisionArea(int prm_nColliPart);

    /**
     * �S�����蔻��v�f�܂ލŊO��̎����s���E�����̂��Čv�Z .
     */
    virtual void updateAABB();

    virtual ~GgafDx9CollisionArea();
};

}
#endif /*GGAFDX9HITAREA_H_*/
