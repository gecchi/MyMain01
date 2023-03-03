#ifndef GGAF_DX_COLLISIONCHECKER_H_
#define GGAF_DX_COLLISIONCHECKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include <vector>

namespace GgafDx {

/**
 * �Փˁi�����蔻��j�`�F�b�J�[�N���X .
 * �i��GeometryCollisionChecker�j
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class CollisionChecker : public GgafCore::Object {
public:
    /** �ΏۃA�N�^�[ */
    GeometricActor* const _pActor;
    /** �����蔻��̈� */
    CollisionArea* _pCollisionArea;

    std::vector<CollisionArea*> _vecCollisionArea;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    explicit CollisionChecker(GeometricActor* prm_pActor);

    /**
     * �����蔻��̈���X�V���A���̗̈���c���[�ɓo�^ .
     */
    virtual void updateHitArea() = 0;

    /**
     * �����蔻��̈�i���ݗL���ƂȂ��Ă�����́j���擾 .
     * @return �L���ȓ����蔻��̈�
     */
    inline CollisionArea* getCollisionArea() {
        return _pCollisionArea;
    }

    /**
     * �����蔻��̈���P�������Ēǉ�����B .
     * ���߂Ė{���\�b�h�����s����ƁA�������X�g�ɕێ�����A���̓����蔻��̈悪�L���ɂȂ�܂��B
     * �Q��ڈȍ~�̎��s�́A�������������蔻��̈��������X�g�̖����ɒǉ����܂��B�i�L���ɂȂ�܂���j
     * @param prm_colli_part_num �����蔻��̈���́A�����蔻��v�f��(1�`n)
     */
    virtual void addCollisionArea(int prm_colli_part_num);

    /**
     * �����蔻��̈��؂�ւ��� .
     * @param prm_index �����蔻��̈惊�X�g�̃C���f�b�N�X�B
     *                  �ŏ���   addCollisionArea() �ɐ؂�ւ� => 0 ��ݒ�
     *                  �Q��ڂ� addCollisionArea() �ɐ؂�ւ� => 1 ��ݒ�
     *                  �R��ڂ� addCollisionArea() �ɐ؂�ւ� => 2 ��ݒ�
     *                  �c
     */
    virtual void changeCollisionArea(int prm_index);

    /**
     * �q�b�g���Ă��邩�ǂ���
     * @param prm_pOtherCollisionChecker ����̃`�F�b�J�[
     * @return
     */
    virtual bool isHit(const CollisionChecker* const prm_pOtherCollisionChecker) = 0;

    /**
     * �����蔻��̈悪�K�p����Ă���A�N�^�[���擾 .
     * @return �����蔻��̈悪�K�p����Ă���A�N�^�[
     */
    virtual GeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptr�ł��邪�悢�̂��I");
        }
        return _pActor;
    }



    virtual ~CollisionChecker();
};

}
#endif /*GGAF_DX_COLLISIONCHECKER_H_*/

