#ifndef GGAF_LIB_CUBEMAPMORPHMESHACTOR_H_
#define GGAF_LIB_CUBEMAPMORPHMESHACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/ex/CubeMapMorphMeshActor.h"

namespace GgafLib {

/**
 * ���}�b�v���[�t���b�V���A�N�^�[�̋�ۃN���X .
 * GgafDx::MorphMeshActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ăL�����N�^�[���쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getPhase()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::Phase</TD></TR>
 * <TR><TD>getVecVehicle()</TD><TD>�͎ԁB�ړ���]�x��</TD><TD>GgafDx::VecVehicle</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * <TR><TD>getMorpher()</TD><TD>���[�t�B���O�x��</TD><TD>GgafDx::Morpher</TD></TR>
 * <TR><TD>getCollisionChecker()</TD><TD>�Փ˔���x��</TD><TD>GgafLib::CollisionChecker3D</TD></TR>
 * </TABLE>
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshActor : public GgafDx::CubeMapMorphMeshActor {

public:
    /** �Փ˔���x���I�u�W�F�N�g */
    CollisionChecker* _pColliChecker;

public:
    CubeMapMorphMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    inline CollisionChecker* getCollisionChecker() {
        return _pColliChecker;
    }

    virtual ~CubeMapMorphMeshActor();
};

}
#endif /*GGAF_LIB_CUBEMAPMORPHMESHACTOR_H_*/
