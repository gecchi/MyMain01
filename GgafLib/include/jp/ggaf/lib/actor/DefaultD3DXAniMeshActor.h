#ifndef GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_
#define GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_
#include "jp/ggaf/dxcore/actor/GgafDxD3DXAniMeshActor.h"

namespace GgafLib {

/**
 * �t���[���A�j���[�V�������b�V���A�N�^�[�̋�ۃN���X .
 * GgafDxCore::GgafDxD3DXAniMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�Q�ƕϐ�</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>_pProg</TD><TD>�i���Ǘ�</TD><TD>GgafCore::GgafProgress</TD></TR>
 * <TR><TD>_pKroko</TD><TD>���߁B�ړ���]�x��</TD><TD>GgafDxCore::GgafDxKuroko</TD></TR>
 * <TR><TD>_pPuppeteer</TD><TD>�t���[���A�j���[�V�����x��</TD><TD>GgafDxCore::GgafDxPuppeteer</TD></TR>
 * <TR><TD>_pSeTx</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDxCore::GgafDxSeTransmitter</TD></TR>
 * <TR><TD>_pColliChecker</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshActor : public GgafDxCore::GgafDxD3DXAniMeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker3D* _pColliChecker;

public:
    DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

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


    virtual ~DefaultD3DXAniMeshActor();
};

}
#endif /*GGAFLIB_DEFAULTD3DXANIMESHACTOR_H_*/
