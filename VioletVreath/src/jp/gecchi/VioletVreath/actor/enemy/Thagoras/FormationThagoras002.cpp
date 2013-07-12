#include "stdafx.h"
#include "FormationThagoras002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

FormationThagoras002::FormationThagoras002(const char* prm_name) : FormationThagoras(prm_name,1) {
    _class_name = "FormationThagoras002";
}


FormationThagoras002::~FormationThagoras002() {
}
