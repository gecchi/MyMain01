#ifndef GGAF_LIB_DEFAULTD3DXMESHACTOR_H_
#define GGAF_LIB_DEFAULTD3DXMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/D3DXMeshActor.h"

namespace GgafLib {

/**
 * ���b�V���A�N�^�[�̋�ۃN���X .
 * GgafDx::D3DXMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>callVecDriver()</TD><TD>�͎ԁB�ړ���]�x��</TD><TD>GgafDx::VecDriver</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultD3DXMeshActor : public GgafDx::D3DXMeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

public:
    DefaultD3DXMeshActor(const char* prm_name, const char* prm_model);

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

    virtual ~DefaultD3DXMeshActor();
};

}
#endif /*GGAF_LIB_DEFAULTD3DXMESHACTOR_H_*/
