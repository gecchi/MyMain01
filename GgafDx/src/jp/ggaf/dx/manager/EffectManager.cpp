#include "jp/ggaf/dx/manager/EffectManager.h"

#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/manager/EffectConnection.h"
#include "jp/ggaf/dx/effect/D3DXAniMeshEffect.h"
#include "jp/ggaf/dx/effect/MeshSetEffect.h"
#include "jp/ggaf/dx/effect/MassMeshEffect.h"
#include "jp/ggaf/dx/effect/MorphMeshEffect.h"
#include "jp/ggaf/dx/effect/MassMorphMeshEffect.h"
#include "jp/ggaf/dx/effect/SpriteEffect.h"
#include "jp/ggaf/dx/effect/SpriteSetEffect.h"
#include "jp/ggaf/dx/effect/MassSpriteEffect.h"
#include "jp/ggaf/dx/effect/BoardEffect.h"
#include "jp/ggaf/dx/effect/BoardSetEffect.h"
#include "jp/ggaf/dx/effect/MassBoardEffect.h"
#include "jp/ggaf/dx/effect/PointSpriteEffect.h"
#include "jp/ggaf/dx/effect/MassPointSpriteEffect.h"
#include "jp/ggaf/dx/effect/PointSpriteSetEffect.h"
#include "jp/ggaf/dx/effect/FramedBoardEffect.h"
#include "jp/ggaf/dx/effect/FramedSpriteEffect.h"
#include "jp/ggaf/dx/effect/RegularPolygonSpriteEffect.h"
#include "jp/ggaf/dx/effect/RegularPolygonBoardEffect.h"
#include "jp/ggaf/dx/effect/BoneAniMeshEffect.h"
#include "jp/ggaf/dx/effect/SkinAniMeshEffect.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshEffect.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMeshSetEffect.h"
#include "jp/ggaf/dx/effect/ex/CubeMapMorphMeshEffect.h"
#include "jp/ggaf/dx/effect/ex/WorldBoundEffect.h"


using namespace GgafDx;

Effect* EffectManager::_pEffect_active = nullptr;

EffectManager::EffectManager(const char* prm_manager_name) :
    GgafCore::ResourceManager<Effect> (prm_manager_name) {
}

Effect* EffectManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1);
    if (names.size() != 2) {
        throwCriticalException("�����́A���̌`���ŗ^���Ă��������B�w�G�t�F�N�g�^�C�v1����  + \",\" + fx�t�@�C����(�g���q .fx ������������)�x\n"
                "���ۂ̈����́Aprm_idstr="<<prm_idstr);
    }
    char effect_type = (names[0])[0];
    const char* effect_name = names[1].c_str();
    Effect* pResourceEffect = nullptr;
    switch (effect_type) {
        case TYPE_MESH_EFFECT:
            pResourceEffect = NEW MeshEffect(effect_name);
            break;
        case TYPE_MESHSET_EFFECT:
            pResourceEffect = NEW MeshSetEffect(effect_name);
            break;
        case TYPE_MASSMESH_EFFECT:
            pResourceEffect = NEW MassMeshEffect(effect_name);
            break;
        case TYPE_CUBEMAPMESH_EFFECT:
            pResourceEffect = NEW CubeMapMeshEffect(effect_name);
            break;
        case TYPE_CUBEMAPMESHSET_EFFECT:
            pResourceEffect = NEW CubeMapMeshSetEffect(effect_name);
            break;
        case TYPE_D3DXANIMESH_EFFECT:
            pResourceEffect = NEW D3DXAniMeshEffect(effect_name);
            break;
        case TYPE_MORPHMESH_EFFECT:
            pResourceEffect = NEW MorphMeshEffect(effect_name);
            break;
        case TYPE_MASSMORPHMESH_EFFECT:
            pResourceEffect = NEW MassMorphMeshEffect(effect_name);
            break;
        case TYPE_CUBEMAPMORPHMESH_EFFECT:
            pResourceEffect = NEW CubeMapMorphMeshEffect(effect_name);
            break;
        case TYPE_WORLDBOUND_EFFECT:
            pResourceEffect = NEW WorldBoundEffect(effect_name);
            break;
        case TYPE_SPRITE_EFFECT:
            pResourceEffect = NEW SpriteEffect(effect_name);
            break;
        case TYPE_SPRITESET_EFFECT:
            pResourceEffect = NEW SpriteSetEffect(effect_name);
            break;
        case TYPE_MASSSPRITE_EFFECT:
            pResourceEffect = NEW MassSpriteEffect(effect_name);
            break;
        case TYPE_BOARD_EFFECT:
            pResourceEffect = NEW BoardEffect(effect_name);
            break;
        case TYPE_BOARDSET_EFFECT:
            pResourceEffect = NEW BoardSetEffect(effect_name);
            break;
        case TYPE_MASSBOARD_EFFECT:
            pResourceEffect = NEW MassBoardEffect(effect_name);
            break;
        case TYPE_POINTSPRITE_EFFECT:
            pResourceEffect = NEW PointSpriteEffect(effect_name);
            break;
        case TYPE_MASSPOINTSPRITE_EFFECT:
            pResourceEffect = NEW MassPointSpriteEffect(effect_name);
            break;
        case TYPE_POINTSPRITESET_EFFECT:
            pResourceEffect = NEW PointSpriteSetEffect(effect_name);
            break;
        case TYPE_FRAMEDBOARD_EFFECT:
            pResourceEffect = NEW FramedBoardEffect(effect_name);
            break;
        case TYPE_FRAMEDSPRITE_EFFECT:
            pResourceEffect = NEW FramedSpriteEffect(effect_name);
            break;
        case TYPE_REGULARPOLYGONSPRITE_EFFECT:
            pResourceEffect = NEW RegularPolygonSpriteEffect(effect_name);
            break;
        case TYPE_REGULARPOLYGONBOARD_EFFECT:
            pResourceEffect = NEW RegularPolygonBoardEffect(effect_name);
            break;
        case TYPE_BONEANIMESH_EFFECT:
            pResourceEffect = NEW BoneAniMeshEffect(effect_name);
            break;
        case TYPE_SKINANIMESH_EFFECT:
            pResourceEffect = NEW SkinAniMeshEffect(effect_name);
            break;
        default:
            throwCriticalException("prm_idstr="<<prm_idstr<<" �� '"<<effect_type<<"' �E�E�E����ȃG�b�t�F�N�g��ʂ͒m��܂���");
            pResourceEffect = nullptr;
            break;
    }
    _TRACE3_("prm_idstr="<<prm_idstr);
    return  pResourceEffect;
}

void EffectManager::onDeviceLostAll() {
    _TRACE3_("start-->");
    GgafCore::ResourceConnection<Effect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnLostDevice();
        checkDxException(hr, D3D_OK, "OnLostDevice() �Ɏ��s���܂����B");
        _TRACE3_("onDeviceLostAll pCurrent="<<pCurrent->getIdStr() << " OnLostDevice() execute");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}

void EffectManager::restoreAll() {
    _TRACE3_("start-->");
    GgafCore::ResourceConnection<Effect>* pCurrent = _pConn_first;
    HRESULT hr;
    while (pCurrent) {
        hr = pCurrent->peek()->_pID3DXEffect->OnResetDevice();
        checkDxException(hr, D3D_OK, "OnResetDevice() �Ɏ��s���܂����B");
        _TRACE3_("restoreAll pCurrent="<<pCurrent->getIdStr() << " restoreAll() execute");
        pCurrent = pCurrent->getNext();
    }
    _TRACE3_("end<--");
}
void EffectManager::setParamPerFrameAll() {
    //�ʏ�`�掞�P�t���[���ɂP��ASpacetime::draw()�ŕ`��O�ɌĂ΂��B
    GgafCore::ResourceConnection<Effect>* pCurrent = _pConn_first;
    while (pCurrent) {
        pCurrent->peek()->setParamPerFrame();
        pCurrent = pCurrent->getNext();
    }
}
GgafCore::ResourceConnection<Effect>* EffectManager::processCreateConnection(const char* prm_idstr,
                                                                                   Effect* prm_pResource) {
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��J�n�B");
    EffectConnection* pConne = NEW EffectConnection(prm_idstr, prm_pResource);
    _TRACE3_("prm_idstr="<<prm_idstr<<" �𐶐��I���B");
    return pConne;
}

