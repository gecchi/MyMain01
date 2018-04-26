#include "jp/ggaf/lib/manager/DefaultEffectManager.h"

#include "jp/ggaf/lib/effect/MassWallEffect.h"
#include "jp/ggaf/lib/effect/SingleLaserEffect.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;


DefaultEffectManager::DefaultEffectManager(const char* prm_manager_name) :
        GgafDxEffectManager(prm_manager_name) {
}

GgafDxEffect* DefaultEffectManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) {
    std::string idstr = std::string(prm_idstr);
    std::vector<std::string> names = UTIL::split(idstr, "/", 1);
    if (names.size() != 2) {
        throwGgafCriticalException("引数は、次の形式で与えてください。『エフェクトタイプ1文字  + \"/\" + fxファイル名(拡張子 .fx を除いたもの)』\n"
                "実際の引数は、prm_idstr="<<prm_idstr);
    }
    char effect_type = (names[0])[0];
    const char* effect_name = names[1].c_str();
    GgafDxEffect* pResourceEffect = nullptr;
    switch (effect_type) {
    case '@':
        pResourceEffect = NEW MassWallEffect(effect_name);
        break;
    case '-':
        pResourceEffect = NEW SingleLaserEffect(effect_name);
        break;
    default:
        pResourceEffect = GgafDxEffectManager::processCreateResource(prm_idstr, prm_pConnector);
        break;
    }
    return  pResourceEffect;
}


