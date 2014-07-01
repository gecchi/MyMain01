#ifndef GGAFDXCORE_GGAFDXCOLLISIONAREA_H_
#define GGAFDXCORE_GGAFDXCOLLISIONAREA_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

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
class GgafDxCollisionArea : public GgafCore::GgafObject {

public:
    /** 8���ؓo�^�̂��߂̑S�����蔻��v�f�܂ޑS�̂̊O���̎����s���E������ */
    coord _aabb_x1, _aabb_y1, _aabb_z1, _aabb_x2, _aabb_y2, _aabb_z2;
    //AABB(�����s���E������:Axis-Aligned Bounding Box)

    /** �����蔻��̈�v�f�̔z�� */
    GgafDxCollisionPart** _papColliPart;
    /** �����蔻��̈�v�f�� */
    int _colli_part_num;

    int _hit_colli_part_index;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_colli_part_num �����蔻��̈�v�f��
     * @return
     */
    explicit GgafDxCollisionArea(int prm_colli_part_num);

    /**
     * �S�����蔻��v�f�܂ލŊO��̎����s���E�����̂��Čv�Z .
     */
    void updateAABB();


    inline GgafDxCollisionPart* getPart(int prm_index) {
        return _papColliPart[prm_index];
    }
    virtual ~GgafDxCollisionArea();
};

}
#endif /*GGAFDXCORE_GGAFDXHITAREA_H_*/
