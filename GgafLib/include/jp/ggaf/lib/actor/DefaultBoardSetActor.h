#ifndef GGAF_LIB_DEFAULTBOARDSETACTOR_H_
#define GGAF_LIB_DEFAULTBOARDSETACTOR_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/actor/BoardSetActor.h"

namespace GgafLib {

/**
 * ���W�ϊ��ς݃X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx::BoardSetActor �������������ۃA�N�^�[�ł��B
 * �{�N���X���p�����ĐF�X��ʕ\�����쐬���܂��傤�B<BR>
 * �ȉ��Ɏg�p�\�Ȏx���I�u�W�F�N�g���L���B<BR>
 * <TABLE border=1>
 * <TR bgcolor="#AABBCC"><TH>�I�u�W�F�N�g�ւ̃A�N�Z�X</TH><TH>�T�v</TH><TH>CLASS��</TH></TR>
 * <TR><TD>getProgress()</TD><TD>�i���Ǘ�</TD><TD>GgafCore::Progress</TD></TR>
 * <TR><TD>getVecVehicle()</TD><TD>�͎ԁB�ړ���]�x��</TD><TD>GgafDx::VecVehicle</TD></TR>
 * <TR><TD>getUvFlipper()</TD><TD>�p���p���A�j���[�V�����x��</TD><TD>GgafDx::UvFlipper</TD></TR>
 * <TR><TD>getSeTransmitter()</TD><TD>���ʉ������Ǘ�</TD><TD>GgafDx::SeTransmitter</TD></TR>
 * </TABLE>
 * <B>�y���Ӂz</B>�g��k���x��(GgafDx::Scaler)�͎g�p�o���܂���B
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class DefaultBoardSetActor : public GgafDx::BoardSetActor {
private:
    /**
     * �g�p�֎~ .
     * @return
     */
    GgafDx::Scaler* getScaler();

public:
    DefaultBoardSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual bool processHitChkLogic(GgafCore::Actor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual ~DefaultBoardSetActor();

};

}
#endif /*GGAF_LIB_DEFAULTBOARDSETACTOR_H_*/
