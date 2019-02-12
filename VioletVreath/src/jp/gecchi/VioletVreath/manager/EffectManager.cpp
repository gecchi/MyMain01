#include "EffectManager.h"

#include "jp/gecchi/VioletVreath/effect/HoshiboshiEffect.h"



using namespace GgafLib;
using namespace VioletVreath;

EffectManager::EffectManager(const char* prm_manager_name) :
        DefaultEffectManager(prm_manager_name) {
}

GgafDx::Effect* EffectManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1);
    if (names.size() != 2) {
        throwCriticalException("�����́A���̌`���ŗ^���Ă��������B�w�G�t�F�N�g�^�C�v1����  + \",\" + fx�t�@�C����(�g���q .fx ������������)�x\n"
                "���ۂ̈����́Aprm_idstr="<<prm_idstr);
    }
    char effect_type = (names[0])[0];
    const char* effect_name = names[1].c_str();
    GgafDx::Effect* pResourceEffect = nullptr;
    switch (effect_type) {
    case '*':
        pResourceEffect = NEW HoshiboshiEffect(effect_name);
        break;
    default:
        pResourceEffect = DefaultEffectManager::processCreateResource(prm_idstr, prm_pConnector);
        break;
    }
    return  pResourceEffect;
}


