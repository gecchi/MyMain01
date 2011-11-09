#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;


GgafDxEffect* GgafDxEffectManager::_pEffect_Active = NULL;

GgafDxEffectManager::GgafDxEffectManager(const char* prm_manager_name) :
    GgafResourceManager<GgafDxEffect> (prm_manager_name) {
}

GgafDxEffect* GgafDxEffectManager::processCreateResource(char* prm_idstr, void* prm_p) {
    //�U�蕪��
    char effect_type = *prm_idstr; //���ꕶ��
    char* effect_name = prm_idstr + 2; //�R�����ڈȍ~
    GgafDxEffect* pResourceEffect;
    switch (effect_type) {
        case 'D':
        case 'd':
        case 'X':
            pResourceEffect = NEW GgafDxMeshEffect(effect_name);
            break;
        case 'x':
            pResourceEffect = NEW GgafDxMeshSetEffect(effect_name);
            break;
        case 'G':
            pResourceEffect = NEW GgafDxCubeMapMeshEffect(effect_name);
            break;
        case 'g':
            pResourceEffect = NEW GgafDxCubeMapMeshSetEffect(effect_name);
            break;
        case 'A':
            pResourceEffect = NEW GgafDxD3DXAniMeshEffect(effect_name);
            break;
        case 'M':
            pResourceEffect = NEW GgafDxMorphMeshEffect(effect_name);
            break;
        case 'H':
            pResourceEffect = NEW GgafDxCubeMapMorphMeshEffect(effect_name);
            break;
        case 'W':
            pResourceEffect = NEW GgafDxWorldBoundEffect(effect_name);
            break;
        case 'S':
            pResourceEffect = NEW GgafDxSpriteEffect(effect_name);
            break;
        case 's':
            pResourceEffect = NEW GgafDxSpriteSetEffect(effect_name);
            break;
        case 'B':
            pResourceEffect = NEW GgafDxBoardEffect(effect_name);
            break;
        case 'b':
            pResourceEffect = NEW GgafDxBoardSetEffect(effect_name);
            break;
        case 'P':
            pResourceEffect = NEW GgafDxPointSpriteEffect(effect_name);
            break;
        default:
            TRACE("GgafDxEffectManager::processCreateResource("<<prm_idstr<<") ����Ȏ�ʂ͂���܂���");
            throwGgafCriticalException("GgafDxEffectManager::processCreateResource("<<prm_idstr<<") ����ȃG�b�t�F�N�g��ʂ͒m��܂���");
            pResourceEffect = NULL;
            break;
    }
    TRACE3("GgafDxEffectManager::processCreateResource("<<prm_idstr<<")");
    return  pResourceEffect;
}

void GgafDxEffectManager::onDeviceLostAll() {
    TRACE3("GgafDxEffectManager::onDeviceLostAll() start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pFirstConnection;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->use()->_pID3DXEffect->OnLostDevice();
        checkDxException(hr, D3D_OK, "GgafDxEffectManager::onDeviceLostAll �G�t�F�N�g["<<pCurrent->getIdStr()<<"]�� OnLostDevice() �Ɏ��s���܂����B");
        TRACE3("onDeviceLostAll pCurrent="<<pCurrent->getIdStr() << " OnLostDevice() execute");
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDxEffectManager::onDeviceLostAll() end<--");
}

void GgafDxEffectManager::restoreAll() {
    TRACE3("GgafDxEffectManager::restoreAll() start-->");
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pFirstConnection;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->use()->_pID3DXEffect->OnResetDevice();
        checkDxException(hr, D3D_OK, "GgafDxEffectManager::restoreAll() �G�t�F�N�g["<<pCurrent->getIdStr()<<"]�� OnResetDevice() �Ɏ��s���܂����B");
        TRACE3("restoreAll pCurrent="<<pCurrent->getIdStr() << " restoreAll() execute");
        pCurrent = pCurrent->getNext();
    }
    TRACE3("GgafDxEffectManager::restoreAll() end<--");
}
void GgafDxEffectManager::setParamPerFrameAll() {
    GgafResourceConnection<GgafDxEffect>* pCurrent = _pFirstConnection;
    while (pCurrent) {
        pCurrent->use()->setParamPerFrame();
        pCurrent = pCurrent->getNext();
    }
}
GgafResourceConnection<GgafDxEffect>* GgafDxEffectManager::processCreateConnection(char* prm_idstr,
                                                                                     GgafDxEffect* prm_pResource) {
    TRACE3(" GgafDxEffectManager::processCreateConnection "<<prm_idstr<<" �𐶐��J�n�B");
    GgafDxEffectConnection* pConnection = NEW GgafDxEffectConnection(prm_idstr, prm_pResource);
    TRACE3(" GgafDxEffectManager::processCreateConnection "<<prm_idstr<<" �𐶐��I���B");
    return pConnection;
}
