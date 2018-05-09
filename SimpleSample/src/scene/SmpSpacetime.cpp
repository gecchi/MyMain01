#include "SmpSpacetime.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "SmpGod.h"
#include "actor/SmpCamera.h"
#include "SmpSpacetime/SmpWorld.h"

using GgafLib::VirtualButton;
using namespace SimpleSample;

SmpSpacetime::SmpSpacetime(const char* prm_name, SmpCamera* prm_pCam) :
        GgafLib::DefaultSpacetime(prm_name, prm_pCam) {
    //SmpWorld�V�[���̍쐬
    wantScene(0, SmpWorld);
    //���̐�(Spacetime)�R���X�g���N�^���ŁA
    //���̃V�[���̏���( addSubLast(GgafScene*) )�͎��s���Ȃ��ł��������B
}

void SmpSpacetime::initialize() {
    //���E�V�[��(SmpWorld)��z���ɏ���������
    addSubLast(grantScene(0));
}

void SmpSpacetime::processBehavior() {
    //���z�{�^���̏�Ԃ��X�V
    VirtualButton* vb = pGOD->getVB();
    vb->update();
}

SmpSpacetime::~SmpSpacetime() {
}

