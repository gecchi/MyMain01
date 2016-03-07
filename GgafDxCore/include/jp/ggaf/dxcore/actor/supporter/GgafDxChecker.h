#ifndef GGAFDXCORE_GGAFDXCHECKER_H_
#define GGAFDXCORE_GGAFDXCHECKER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �`�F�b�N�Ɋւ���F�X�ȋ@�\���������N���X .
 * �i��GgafDxGeometryChecker�j
 * @version 1.00
 * @since 2008/08/20
 * @author Masatoshi Tsuge
 */
class GgafDxChecker : public GgafCore::GgafObject {

public:
    /** �ΏۃA�N�^�[ */
    GgafDxGeometricActor* const _pActor;
    /** �����蔻��̈� */
    GgafDxCollisionArea* _pCollisionArea;

public:
    /**
     * �R���X�g���N�^<BR>
     * @param	prm_pActor	�K�pActor
     */
    explicit GgafDxChecker(GgafDxGeometricActor* prm_pActor);

    virtual void updateHitArea() = 0;

    /**
     * �����蔻��̈���쐬����i�������蔻��̈�v�f�̔z����쐬����j .
     * �����ŗ̈�̔z��𐶐����܂��B
     * �ŏ��ɕK�����s���Ă��������B
     * @param prm_colli_part_num �����蔻��̈�̓����蔻��̈�v�f��(1�`n)
     */
    virtual void createCollisionArea(int prm_colli_part_num);

    /**
     * �q�b�g�V���Ă��邩�ǂ���
     * @param prm_pOtherChecker ����̃`�F�b�J�[
     * @return
     */
    virtual bool isHit(const GgafDxChecker* const prm_pOtherChecker) = 0;

    virtual GgafDxGeometricActor* getTargetActor() {
        if (_pActor == nullptr) {
            _TRACE_(FUNC_NAME<<" nullptr�ł��邪�悢�̂��I");
        }
        return _pActor;
    }

    inline GgafDxCollisionArea* getArea() {
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

    /**
     * �����蔻��̈�̗v�f���L�������ׂ�B
     * @param prm_index ���ׂ��������蔻��̈�̗v�f�ԍ�
     * @return true:�L�� / false:����
     */
    virtual bool isEnable(int prm_index);

    virtual ~GgafDxChecker();
};

}
#endif /*GGAFDXCORE_GGAFDXCHECKER_H_*/

