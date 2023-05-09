#include "LockonCursor001.h"

#include "jp/ggaf/dx/actor/supporter/SeTransmitterForActor.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"



using namespace GgafLib;
using namespace VioletVreath;

LockonCursor001::LockonCursor001(const char* prm_name, const char* prm_model) :
        DefaultMassSpriteActor(prm_name, prm_model) {
    _class_name = "LockonCursor001";
    pTarget_ = nullptr;
    pTarget_prev_ = nullptr;
    inactivate();
    defineRotMvWorldMatrix_Billboard(); //���[���h�ϊ��̓r���{�[�h��Rz��]�ɋ���
    effectBlendOne(); //�G�t�F�N�g�e�N�j�b�N�͉��Z�����ɋ���
    setZEnableDraw(false);      //Z�o�b�t�@�͍l�������ɋ���
    setZWriteEnable(false); //���g��Z�o�b�t�@���������݂��Ȃ��ɋ���
    setSpecialRenderDepthIndex(1); //�`�揇�����őO�ʕ`��ɋ����B���b�N�I���G�t�F�N�g���B��Ȃ��悤�ɂ��邽�߁B
    setCullingDraw(false);  //�����������邽�߁A�J�����O��OFF���邽�ߓ����I�u�W�F�N�g�����ɂ���B

    setHitAble(false); //�����蔻�薳��
    GgafDx::SeTransmitterForActor* pSeXmtr = getSeXmtr();
    pSeXmtr->set(0, "SE_LOCKON_001"); //���ʉ���`
}

void LockonCursor001::initialize() {
}


void LockonCursor001::onReset() {
    getPhase()->reset(LOCKON001_PHASE_RELEASE);
}

void LockonCursor001::onActive() {
    if (pTarget_ == nullptr) {
        inactivateImmed();
        return;
    }
}

void LockonCursor001::processBehavior() {
    pTarget_prev_ = pTarget_;
}

void LockonCursor001::processJudgement() {
}

void LockonCursor001::onInactive() {
}


LockonCursor001::~LockonCursor001() {
}

