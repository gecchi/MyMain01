#include "stdafx.h"
#include "FormationThagoras001.h"

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
const char* FormationThagoras001::xpmFormationThagoras001_[] = {
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
                                                                "= c #3F3FBF",
                                                                "- c #5F5F9F",
                                                                "; c #5F7FBF",
                                                                ": c blue",
                                                                "> c cyan",
                                                                ", c #808080",
                                                                "< c #9F9F9F",
                                                                "1 c #A0A0A4",
                                                                "2 c gray75",
                                                                "3 c #A6CAF0",
                                                                "4 c #C0C0C0",
                                                                "5 c gainsboro",
                                                                "6 c #FFFBF0",
                                                                "7 c gray100",
                                                                "8 c None",
                                                                /* pixels */
                                                                "888888888888*X88X*888888888888",
                                                                "888888888888*-88:-888888888888",
                                                                "88888888888**;88;:*88888888888",
                                                                "88888888888**7882::88888888888",
                                                                "88888888888**7882::88888888888",
                                                                "88888888888*-7882;:88888888888",
                                                                "8888888888**-7882;:*8888888888",
                                                                "8888888888**-7882;::8888888888",
                                                                "8888888888**-7882;::8888888888",
                                                                "8888888888**-7882;::8888888888",
                                                                "888888888**-<78827;:*888888888",
                                                                "888888888**-<78827;::888888888",
                                                                "888888888**-<78827;::888888888",
                                                                "888888888**-<78827;::888888888",
                                                                "88888888**-<<788277;:*88888888",
                                                                "88888888**-<<7==277;::88888888",
                                                                "88888888**-<7=::=27;::88888888",
                                                                "88888888**-<7=:>=27;::88888888",
                                                                "8888888***-<7=:>=27;::*8888888",
                                                                "8888888**-<<7=::=277;::8888888",
                                                                "8888888**-<<7=::=277;::8888888",
                                                                "8888888.*-<<5=**=577;:.8888888",
                                                                "8888888*X-<<7*=3*277;O*8888888",
                                                                "888888***X<<7*==*277O::*888888",
                                                                "888888****,<7*==*272::::888888",
                                                                "88888****2,<<<**22727:::*88888",
                                                                "88888****<,<X....O727::::88888",
                                                                "8888****<<,<,XXOO27277:::*8888",
                                                                "$888****<<,<,<44727277::::888$",
                                                                "%88****<<<<,,<447227777::::88%",
                                                                "o88:***<<<<<X<447<77777:::*88o",
                                                                ";8*:**<<<<<<,<4472777777::**8;",
                                                                ";8:::*<<<<<<,<--72777777:***8;",
                                                                ";*:::2<X     <--7.....O72****;",
                                                                ";*:::2<,XXXXX<--7OOOOO272****;",
                                                                ";*::72<,,<<<<<--777772272<***;",
                                                                ";*::72<,,<<<<<--777772272<***;",
                                                                ";*::72<X,<<<<<--777772<72<***;",
                                                                ";*:772<,X<<<<<--77777<272<<**;",
                                                                ";.:772<,,,,,,<--722222272<<*.;",
                                                                "o8.772<,,<<<,<::727772272<<.8o",
                                                                "%88.72<,,<<<,<::727772272<.88%",
                                                                "8888..<,,<<<,<::72777222..888.",
                                                                "888888.,,<<<,<::7277722.888888",
                                                                "8888888.X<<<,<::72777X.8888888",
                                                                "8888888X1575<X::X<575<X8888888",
                                                                "8888888X1575<X::X<575<X8888888",
                                                                "8888888X1575<X88X<575<X8888888",
                                                                "8888888X1575<X88X<575<X8888888",
                                                                "8888888X1575<X88X<575<X8888888",
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


FormationThagoras001::FormationThagoras001(const char* prm_name) :
        FormationThagoras(prm_name, FormationThagoras001::xpmFormationThagoras001_) {
    _class_name = "FormationThagoras001";

    papSplManufConn_ = NEW SplineManufactureConnection*[pXpmHd_->columns_];
    for (int i = 0; i < pXpmHd_->columns_; i++) {
        papSplManufConn_[i] = getConnection_SplineManufactureManager("FormationThagoras001");
    }
}

void FormationThagoras001::processBehavior() {
    FormationThagoras::processBehavior();
}

void FormationThagoras001::onCallUp(GgafDxCore::GgafDxDrawableActor* prm_pActor, int prm_row, int prm_col) {
    EnemyThagoras* pThagoras = (EnemyThagoras*)prm_pActor;
    if (pThagoras->pKurokoLeader_) {
        throwGgafCriticalException("FormationThagoras001::onCallUp pThagoras->pKurokoLeader_Ç™ê›íËÇ≥ÇÍÇƒÇ‹Ç∑ÅBpThagoras="<<pThagoras<<"("<<pThagoras->getName()<<")");
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

FormationThagoras001::~FormationThagoras001() {
    for (int i = 0; i < pXpmHd_->columns_; i++) {
        papSplManufConn_[i]->close();
    }
    GGAF_DELETEARR(papSplManufConn_);
}

