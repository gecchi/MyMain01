#ifndef GGAF_LIB_DEFAULTMESHACTOR_H_
#define GGAF_LIB_DEFAULTMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafLib {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X .
 * GgafDx::MeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�t�F�[�Y�Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocusVehicle()</TD><TD>�ړ��ԗ��B�ړ���]�x��</TD><TD>GgafDx::LocusVehicle</TD></TR>
 * <TR><TD>getSeXmtr()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/02/19
 * @author Masatoshi Tsuge
 */
class DefaultMeshActor : public GgafDx::MeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    WorldCollisionChecker* _pWorldCollisionChecker;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_model ���f����`
     */
    DefaultMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    virtual void drawHitArea() override;

    virtual GgafDx::CollisionChecker* createChecker(kind_t prm_kind = 0) override;

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pWorldCollisionChecker;
    }

    virtual ~DefaultMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTMESHACTOR_H_*/
