#ifndef GGAF_DX_CHECKER_H_
#define GGAF_DX_CHECKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafDx {

/**
 * �`�F�b�N�Ɋւ���F�X�ȋ@�\���������N���X .
 * �i��GeometryChecker�j
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class Checker : public GgafCore::Object {

public:
//    /** �����蔻��̈�̋��E�̈�(AABB)���Čv�Z���邩�ǂ����̃t���O */
//    bool _need_update_aabb;
    /** �ΏۃA�N�^�[ */
    GeometricActor* const _pActor;
    /** �����蔻��̈� */
    CollisionArea* _pCollisionArea;
//    /** ���������蔻�肪�K�v���ǂ����B�p�[�g�̏��Ȃ��Ƃ���� _is_valid_flg == true �̏ꍇ true */
//    bool _is_enable;
public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    explicit Checker(GeometricActor* prm_pActor);

    /**
     * �����蔻��̈���X�V���A���̗̈���c���[�ɓo�^ .
     */
    virtual void updateHitArea() = 0;

    /**
     * �����蔻��̈���쐬����i�������蔻��̈�v�f�̔z����쐬����j .
     * �����ŗ̈�̔z��𐶐����܂��B
     * �ŏ��ɕK�����s���Ă��������B
     * @param prm_colli_part_num �����蔻��̈�̓����蔻��̈�v�f��(1�`n)
     */
    virtual void createCollisionArea(int prm_colli_part_num);

    /**
     * �q�b�g���Ă��邩�ǂ���
     * @param prm_pOtherChecker ����̃`�F�b�J�[
     * @return
     */
    virtual bool isHit(const Checker* const prm_pOtherChecker) = 0;

    virtual GeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptr�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    inline CollisionArea* getArea() {
        return _pCollisionArea;
    }

    /**
     * �����蔻��̈�̗v�f��L���ɂ���B
     * �f�t�H���g�͗L����ԂɂȂ��Ă��܂��B
     * @param prm_index �L���ɂ��铖���蔻��̈�̗v�f�ԍ�
     */
    virtual void enable(int prm_index);

    /**
     * �����蔻��̈�̗v�f�𖳌��ɂ���B
     * @param prm_index �����ɂ��铖���蔻��̈�̗v�f�ԍ�
     */
    virtual void disable(int prm_index);
//    virtual void disable(int prm_index1, int prm_index2);
//    virtual void disable(int prm_index1, int prm_index2, int prm_index3);

    /**
     * �����蔻��̈�̗v�f���L�������ׂ�B
     * @param prm_index ���ׂ��������蔻��̈�̗v�f�ԍ�
     * @return true:�L�� / false:����
     */
    virtual bool isEnable(int prm_index);

    virtual ~Checker();
};

}
#endif /*GGAF_DX_CHECKER_H_*/

