#include "HgrCaretaker.h"

#include "actor/camera/HgrCamera.h"
#include "scene/HgrSpacetime.h"

using namespace Hogera;

HgrCaretaker::HgrCaretaker() :
        GgafLib::DefaultCaretaker() {
}

GgafCore::Spacetime* HgrCaretaker::createSpacetime() {
    //���̐��̍쐬�̃T���v��
    HgrCamera* pCam = NEW HgrCamera("HOGERA_HGRCAMERA");                  //�J�����쐬���A
    HgrSpacetime* pSpacetime = NEW HgrSpacetime("HOGERA_SPACETIME", pCam); //���̐��𐶐��B
    return pSpacetime;
}

HgrCaretaker::~HgrCaretaker() {
}

