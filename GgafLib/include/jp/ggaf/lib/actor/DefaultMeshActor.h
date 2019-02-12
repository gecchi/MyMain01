#ifndef GGAF_LIB_DEFAULTMESHACTOR_H_
#define GGAF_LIB_DEFAULTMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/MeshActor.h"

namespace GgafLib {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X .
 * GgafDx::MeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>���߁B�ړ���]�x��</TD><TD>GgafDx::Kuroko</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/02/19
 * @author Masatoshi Tsuge
 */
class DefaultMeshActor : public GgafDx::MeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_model ���f����`
     * @param prm_pStat ��`�ς݂̃X�e�[�^�X��n���B���(STAT_DEFAULT_ACTOR_KIND)�͏Փ˔���Ŏg�p�����B
     */
    DefaultMeshActor(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat=nullptr);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTMESHACTOR_H_*/
