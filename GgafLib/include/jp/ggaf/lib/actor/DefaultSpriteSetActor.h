#ifndef GGAFLIB_DEFAULTSPRITESETACTOR_H_
#define GGAFLIB_DEFAULTSPRITESETACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxSpriteSetActor.h"

namespace GgafLib {

/**
 * �X�v���C�g�Z�b�g�A�N�^�[�̋�ۃN���X.
 * GgafDxCore::GgafDxSpriteSetActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�Q�ƕϐ�</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>getKuroko()</TD><TD>���߁B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>_pUvFlipper</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDxCore::GgafDxUvFlipper</TD></TR>
 * <TR><TD>getSeTx()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/07/15
 * @author Masatoshi Tsuge
 */
class DefaultSpriteSetActor : public GgafDxCore::GgafDxSpriteSetActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultSpriteSetActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat=nullptr);

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker3D* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~DefaultSpriteSetActor();

};

}
#endif /*GGAFLIB_DEFAULTSPRITESETACTOR_H_*/
