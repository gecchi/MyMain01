#ifndef GGAF_LIB_DEFAULTFRAMEDSPRITEACTOR_H_
#define GGAF_LIB_DEFAULTFRAMEDSPRITEACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/FramedSpriteActor.h"

namespace GgafLib {

/**
 * �g����X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx::FramedSpriteActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�t�F�[�Y�Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getVecVehicle()</TD><TD>�͎ԁB�ړ���]�x��</TD><TD>GgafDx::VecVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getWorldCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::WorldCollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/02/25
 * @author Masatoshi Tsuge
 */
class DefaultFramedSpriteActor : public GgafDx::FramedSpriteActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    WorldCollisionChecker* _pColliCollisionChecker;

public:
    DefaultFramedSpriteActor(const char* prm_name, const char* prm_model);

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

    inline WorldCollisionChecker* getWorldCollisionChecker() {
        return _pColliCollisionChecker;
    }

    virtual ~DefaultFramedSpriteActor();

};

}
#endif /*GGAF_LIB_DEFAULTFRAMEDSPRITEACTOR_H_*/
