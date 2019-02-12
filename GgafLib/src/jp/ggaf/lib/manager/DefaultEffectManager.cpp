#include "jp/ggaf/lib/manager/DefaultEffectManager.h"

#include "jp/ggaf/lib/effect/MassWallEffect.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"



using namespace GgafLib;


DefaultEffectManager::DefaultEffectManager(const char* prm_manager_name) :
        GgafDx::EffectManager(prm_manager_name) {
}

GgafDx::Effect* DefaultEffectManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, ",", 1);
    if (names.size() != 2) {
        throwCriticalException("引数は、次の形式で与えてください。『エフェクトタイプ1文字  + \",\" + fxファイル名(拡張子 .fx を除いたもの)』\n"
                "実際の引数は、prm_idstr="<<prm_idstr);
    }
    char effect_type = (names[0])[0];
    const char* effect_name = names[1].c_str();
    GgafDx::Effect* pResourceEffect = nullptr;
    switch (effect_type) {
    case TYPE_MASSWALL_EFFECT:
        pResourceEffect = NEW MassWallEffect(effect_name);
        break;
    case TYPE_SINGLELASER_EFFECT:
        pResourceEffect = NEW SingleLaserEffect(effect_name);
        break;
    default:
        pResourceEffect = GgafDx::EffectManager::processCreateResource(prm_idstr, prm_pConnector);
        break;
    }
    return  pResourceEffect;
}


