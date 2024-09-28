#ifndef GGAF_LIB_SINGLELASER_H_
#define GGAF_LIB_SINGLELASER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshSetActor.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/manager/DefaultModelManager.h"

namespace GgafLib {

/**
 * �P�����[�U�[ .
 * GgafDx::MeshSetActor�Ɠ��l�ɕ������f���`��ɂ��A��������ژ_�ށB <BR>
 * �A���\�����ɁA�}�e���A���J���[�A�X�y�L�����[�̌v�Z���s��Ȃ��B<BR>
 * ���̑���ɁAGgafDx::MeshSetActor ��������ɑ����̃Z�b�g���i����26�j���T�|�[�g�B<BR>
 * ��ʕ\���p�ɍœK������Ă���B<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class SingleLaser : public GgafDx::MeshSetActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    SingleLaser(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {}

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker() override;
    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~SingleLaser();
};

}
#endif /*GGAF_LIB_SINGLELASER_H_*/

