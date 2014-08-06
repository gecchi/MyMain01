#include "stdafx.h"
#include "FormationThagoras002.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thagoras/EnemyThagoras.h"
#include "jp/gecchi/VioletVreath/util/XpmHeader.h"
#include "jp/ggaf/lib/util/spline/SplineKurokoLeader.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;


/* XPM */
const char* FormationThagoras002::xpmFormationThagoras002_[] = {
                                                                /* columns rows colors chars-per-pixel */
                                                                "30 79 27 1 ",
                                                                "  c black",
                                                                ". c #5F3F3F",
                                                                "X c #5F5F3F",
                                                                "o c #5F7F3F",
                                                                "O c #7F7F3F",
                                                                "+ c #9F3F3F",
                                                                "@ c #FF3F3F",
                                                                "# c #FF7F3F",
                                                                "$ c #7FFF3F",
                                                                "% c #5F9F7F",
                                                                "& c #FFDF5F",
                                                                "* c navy",
                                                                "= c #3F3F9F",
                                                                "- c #3F3FBF",
                                                                "; c #5F5F9F",
                                                                ": c #5F7FBF",
                                                                "> c blue",
                                                                ", c cyan",
                                                                "< c #808080",
                                                                "1 c #9F9F9F",
                                                                "2 c #A0A0A4",
                                                                "3 c #C0C0C0",
                                                                "4 c gainsboro",
                                                                "5 c #EEEEEE",
                                                                "6 c #FFFBF0",
                                                                "7 c gray100",
                                                                "8 c None",
                                                                /* pixels */
                                                                "888888888888*<88<X888888888888",
                                                                "888888888888=3883:888888888888",
                                                                "88888888888X=7883:;88888888888",
                                                                "88888888888X=7883:;88888888888",
                                                                "88888888888==7883::88888888888",
                                                                "88888888888==7883::88888888888",
                                                                "8888888888X==7883::;8888888888",
                                                                "8888888888X=278832::8888888888",
                                                                "8888888888==378833::8888888888",
                                                                "8888888888==478834::8888888888",
                                                                "888888888X==478834::;888888888",
                                                                "888888888X==478834:::888888888",
                                                                "888888888===478834:::888888888",
                                                                "888888888==*478834:::888888888",
                                                                "88888888X==44788344::;88888888",
                                                                "88888888X=*447>-344::;88888888",
                                                                "88888888==4447>>3444::88888888",
                                                                "88888888=*4447>,3444::88888888",
                                                                "8888888X=444OXXXXO444:;8888888",
                                                                "8888888X*4442OOOO2444:;8888888",
                                                                "8888888X44442357324444;8888888",
                                                                "8888888X44442357324444;8888888",
                                                                "888888824444235732444428888888",
                                                                "888888X4244423573244424O888888",
                                                                "888888444244235732442444888888",
                                                                "88888X444424235732424444O88888",
                                                                "888884444424235732424444488888",
                                                                "8888X44444242357324244444O8888",
                                                                "$8882444442433573342444445888$",
                                                                "%8833444442443573442444445O88%",
                                                                "o88<3444442444444442444445588o",
                                                                ":8<<3442332332432332332445548:",
                                                                ":<<<344O<OOO<O43O<OOO<O445574:",
                                                                "O<<<344O.....O43O.....O4455777",
                                                                "O<<<344OXXXXXO43OXXXXXO4455777",
                                                                "O<<<344OO...OO43OO...OO4455777",
                                                                "O<<<344O2X X2O43O2X X2O4455777",
                                                                "O<<<344O22O21O43O22O21O4455777",
                                                                ":<<<344O24741O43O24741O445577:",
                                                                ":.<<344O24741O22O24741O44557.:",
                                                                "o8.<344XO241OX43XO141OX4455.8o",
                                                                "%88.344O24741O43O24741O445.88%",
                                                                "8888.O4O24741O43O24741O4O.8888",
                                                                "888888.O24741O43O24741O.888888",
                                                                "8888888X24741O43O24741X8888888",
                                                                "8888888O24741O43O24741O8888888",
                                                                "8888888O24741X**X24741O8888888",
                                                                "8888888O24741O88O24741O8888888",
                                                                "8888888O24741O88O24741O8888888",
                                                                "8888888O24741O88O24741O8888888",
                                                                "888888888666888888666888888888",
                                                                "88888888&666&8888&666&88888888",
                                                                "88888888&666&8888&666&88888888",
                                                                "8888888#&666&#88#&666&#8888888",
                                                                "8888888#&666&#88#&666&#8888888",
                                                                "8888888#&&6&&#88#&&6&&#8888888",
                                                                "8888888#&&6&&#88#&&6&&#8888888",
                                                                "8888888##&&&##88##&&&##8888888",
                                                                "8888888@#&&&#@88@#&&&#@8888888",
                                                                "8888888@#&&&#@88@#&&&#@8888888",
                                                                "8888888+@#&#@+88+@#&#@+8888888",
                                                                "8888888+@#&#@+88+@#&#@+8888888",
                                                                "8888888+@###@+88+@###@+8888888",
                                                                "8888888+@@#@@+88+@@#@@+8888888",
                                                                "8888888.+@@@+.88.+@@@+.8888888",
                                                                "8888888.+@@@+.88.+@@@+.8888888",
                                                                "8888888.++@++.88.++@++.8888888",
                                                                "8888888..+@+..88..+@+..8888888",
                                                                "8888888..+++..88..+++..8888888",
                                                                "88888888.+++.8888.+++.88888888",
                                                                "88888888..+..8888..+..88888888",
                                                                "88888888..+..8888..+..88888888",
                                                                "888888888.+.888888.+.888888888",
                                                                "888888888...888888...888888888",
                                                                "888888888...888888...888888888",
                                                                "888888888...888888...888888888",
                                                                "8888888888.88888888.8888888888",
                                                                "8888888888.88888888.8888888888",
                                                                "8888888888.88888888.8888888888"
                                                                };


FormationThagoras002::FormationThagoras002(const char* prm_name) :
        FormationThagoras(prm_name, FormationThagoras002::xpmFormationThagoras002_) {
    _class_name = "FormationThagoras002";

    papSplManufConn_ = NEW SplineManufactureConnection*[pXpmHd_->columns_];
    for (int i = 0; i < pXpmHd_->columns_; i++) {
        papSplManufConn_[i] = getConnection_SplineManufactureManager("FormationThagoras001");
    }
}

void FormationThagoras002::processBehavior() {
    FormationThagoras::processBehavior();
}

void FormationThagoras002::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) {
    EnemyThagoras* pThagoras = (EnemyThagoras*)prm_pActor;
    if (pThagoras->pKurokoLeader_) {
        throwGgafCriticalException("FormationThagoras002::onCallUp pThagoras->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpThagoras="<<pThagoras<<"("<<pThagoras->getName()<<")");
    } else {
        pThagoras->pKurokoLeader_ = papSplManufConn_[prm_col]->peek()->
                                      createKurokoLeader(pThagoras->getKuroko());
    }
    pThagoras->pKurokoLeader_->fixStartPosition(entry_pos_.x                      ,
                                                entry_pos_.y + (prm_col*PX_C(30)) ,
                                                entry_pos_.z                       );

    pThagoras->position( RND(PX_C(-2600), PX_C(2600)),
                         RND(PX_C(-2600), PX_C(2600)),
                         RND(PX_C(-2600), PX_C(2600)) );
}

FormationThagoras002::~FormationThagoras002() {
    for (int i = 0; i < pXpmHd_->columns_; i++) {
        papSplManufConn_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

