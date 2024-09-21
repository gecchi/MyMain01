#ifndef GGAF_DX_COLLISIONAREA_H_
#define GGAF_DX_COLLISIONAREA_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * �����蔻��̈�N���X .
 * �����蔻��v�f�A�����蔻��̈�A�Ƃ����Q�̌��t�����̂悤�ɒ�`���܂��B<BR>
 * a)�����蔻��v�f �E�E�E �P�� �� or AAB or �v���Y�� �̓����蔻��̗��̐}�`�B<BR>
 * b)�����蔻��̈� �E�E�E ��L�̕����̓����蔻��v�f���W�܂��āA�O���[�v���������B<BR>
 * �{�N���X�� b) �����蔻��u�̈�v�����������N���X�ł��B<BR>
 * @version 1.00
 * @since 2010/01/21
 * @author Masatoshi Tsuge
 */
class CollisionArea : public GgafCore::Object {

public:
    /** 8���ؓo�^�̂��߂̑S�����蔻��v�f�܂ޑS�̂̊O���̎����s���E������(Actor���[�J�����W) */
    coord _aabb_x1, _aabb_y1, _aabb_z1, _aabb_x2, _aabb_y2, _aabb_z2;
    //AABB(�����s���E������:Axis-Aligned Bounding Box)

    /** �����蔻��̈�v�f�̔z�� */
    CollisionPart** _papColliPart;
    /** �����蔻��̈�v�f�� */
    int _colli_part_num;
    /** �q�b�g�`�F�b�N�Ńq�b�g�����p�[�g�C���f�b�N�X������(isHit �Őݒ�) */
    int _hit_colli_part_index;
    /** �����蔻��̈�̋��E�̈�(AABB)���Čv�Z���邩�ǂ����̃t���O */
    bool _need_update_aabb;

    int _rotate_part_num;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_colli_part_num �����蔻��v�f��
     * @return
     */
    explicit CollisionArea(int prm_colli_part_num);

    /**
     * �S�����蔻��v�f�܂ލŊO��̎����s���E�����̂��Čv�Z .
     */
    void updateAABB(angle prm_rx, angle prm_ry, angle prm_rz);

    inline CollisionPart* getPart(int prm_index) {
        return _papColliPart[prm_index];
    }
    inline CollisionPart* getHitPart() {
        return _papColliPart[_hit_colli_part_index];
    }

    virtual ~CollisionArea();
};

}
#endif /*GGAF_DX_HITAREA_H_*/
