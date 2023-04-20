#ifndef GGAF_LIB_DEFAULTSKINANIMESHACTOR_H_
#define GGAF_LIB_DEFAULTSKINANIMESHACTOR_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/SkinAniMeshActor.h"

namespace GgafLib {

/**
 * �X�L���A�j���[�V�������b�V���A�N�^�[�̋�ۃN���X .
 * GgafDx::SkinAniMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�t�F�[�Y�Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getLocoVehicle()</TD><TD>�ړ��ԗ��B�ړ���]�x��</TD><TD>GgafDx::LocoVehicle</TD></TR>
 * <TR><TD>_pPuppeteer</TD><TD>�t���[���A�j���[�V�����x��</TD><TD>GgafDx::Puppeteer</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2019/12/20
 * @author Masatoshi Tsuge
 */
class DefaultSkinAniMeshActor : public GgafDx::SkinAniMeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    WorldCollisionChecker* _pColliCollisionChecker;

public:
    DefaultSkinAniMeshActor(const char* prm_name, const char* prm_model);

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

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pColliCollisionChecker;
    }

    virtual ~DefaultSkinAniMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTSKINANIMESHACTOR_H_*/
