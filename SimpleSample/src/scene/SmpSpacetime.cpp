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
    requestScene(0, SmpWorld);
    //���̐�(Spacetime)�R���X�g���N�^���ŁA
    //���̃V�[���̏���( appendChild(GgafScene*) )�͎��s���Ȃ��ł��������B
}

void SmpSpacetime::initialize() {
    //���E�V�[��(SmpWorld)��z���ɏ���������
    appendChild(receiveScene(0));
}

void SmpSpacetime::processBehavior() {
    //���z�{�^���̏�Ԃ��X�V
    VirtualButton* vb = pGOD->getVB();
    vb->update();
}

SmpSpacetime::~SmpSpacetime() {
}

