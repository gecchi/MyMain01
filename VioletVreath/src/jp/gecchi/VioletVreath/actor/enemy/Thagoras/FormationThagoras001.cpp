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
        "25 113 16 1 ",
        "  c #07020C",
        ". c #230437",
        "X c #391053",
        "o c #4C2B5D",
        "O c #4E1871",
        "+ c #563070",
        "@ c #67447C",
        "# c #725484",
        "$ c #7E658C",
        "% c #8C6DA0",
        "& c #A38BB1",
        "* c #B7A3C1",
        "= c #CDBBD4",
        "- c #D7CBE0",
        "; c #EBE1F2",
        ": c None",
        /* pixels */
        ":::::::::::::::::::   :::",
        "::::::::::::::::::  .  ::",
        ":::::::::::::::::: .o. ::",
        "::::::::::::::::   XoX ::",
        ":::::::::::::    .XooX ::",
        ":::::::::::    XoooXo. ::",
        "::::::::   ..O@@ooo.oX ::",
        "::::::   .X@$:$#ooXXoX ::",
        ":::   ..O%-=*:$@ooXOoX ::",
        ":   .X@&;;;-*%@oX. .+. ::",
        "  .o+#&=;;;*@X..   .oX ::",
        " .oXo#&==&+X.   :: .oX ::",
        "  XXo#:#OX.   ::::  +X ::",
        ":  ..X@&%+..   ::: .+X ::",
        ":::   .Xo&&#X.   : .oX ::",
        ":::::   ..X#$#o..  .+. ::",
        "::: ::::   .Xo@#@X..@X ::",
        ":          . ..Xo@@oo. ::",
        ": .+.. ....@. ...XOXoX ::",
        ": Xo+##$%%&=X.o@@..XoX ::",
        ": .Xo#&=;;;=#X@@#. .+X ::",
        ": .oOXXXOoOoO.X+X. .+. ::",
        ": .X. ... .        .oX ::",
        ":   ..X++X.  :   : .oX ::",
        ":: .o#&*--&o. :::: .oX ::",
        ": .Xo@%&*=-=O  ::: .+. ::",
        ": XXOXX.XXX#%. ::: .oX ::",
        ": X+X     .X#. ::: .oX ::",
        ": X@o.....X+#. ::: .oX ::",
        ": .X@$%%&&=*o  ::: .+. ::",
        ":  .O@&=;;*O. ::   .oX ::",
        ":  .XXO+@OX        .+. ::",
        ": .o...X...... .X+..+X ::",
        ": Xo@@#$%%%%###@+#X.oX ::",
        ": .Xo#&=-;;-&:##oo@.+X ::",
        ": .oOXoOo+OoOOoXXXXXoX ::",
        ": .X. ... .        .oX ::",
        ":  ..XXooX.   :::: .oX ::",
        ":  .o#&=--&O. :::: .oX ::",
        ": .oo#%&&=**o  ::: .+X ::",
        ": XXo+OXO%XO%. ::: .oX ::",
        ": XXoX  X%XO#. ::: .+. ::",
        ": .X@X. O*@%#. :::  +X ::",
        ": .X+#..O;-&X  ::: .+X ::",
        "::  Xo+.X%OX. :::: .oX ::",
        "::  ..X.XXXXo.  :: .+. ::",
        ": .Xo@@####%&#X  : .+X ::",
        ": .oo#&=;;;-*:%o.  .oX ::",
        ": XXoOo++@+@%OO+. .XoX ::",
        ": .X@..   .+$.    .oo. ::",
        ":  X+.     X+.   XXXoX ::",
        "::     :::      XXoXX  ::",
        ":::   :::::  :: Xo..  :::",
        ":::::::::::::::     :::::",
        "::::::::::::::::  :    ::",
        "::::::::::::::::::  X. ::",
        ":::::::::::::::::  .@. ::",
        ":::::::::::::::   .ooX ::",
        "::::::::::::   ..oX.oX ::",
        ":::::::::   ..oo@ooXo. ::",
        ":::::::   .Xo#$@ooo.oX ::",
        ":::::  ..X$&&:$@ooXXoX ::",
        "::   .X+&;;-*%$@oX.X+X ::",
        "  ..X@%=;;;=&#O..  .+. ::",
        " .Xoo#&-;;*@X.     .oX ::",
        " .oXo$&&%O..   ::: .+X ::",
        "   XX+%$OX.  ::::: .oX ::",
        "::   .X@&&+..   :: .+. ::",
        "::::   ..+%&#X.    .+X ::",
        "::   ::   .X+$#@.. .oX ::",
        ":  ..     ...XX+#@oooX ::",
        ": .@X..X.XO%.  .XXooo. ::",
        ": .o@$&*=--=O.    XXoX ::",
        ": XXo@%&*-=*#  ::  XoX ::",
        ": .oX....O%%X. ::: .oX ::",
        ": .X    ..%-%. :::  +X ::",
        ":        X=-%. ::: .oX ::",
        ":::   ...X@#X  ::: .oX ::",
        ":: .X+$&&%OX. :::: .oX ::",
        ":  Xo#&=;;;%. :::: .+X ::",
        ": Xoo@@o+%@%#. :::  +X ::",
        ": XXoO..O%XO$. ::: .+. ::",
        ": .XoX  O%XO$. ::: .oX ::",
        ": .o++. O-=*o  ::: .+X ::",
        ":  .O#+.X-&+. :::: .oX ::",
        "::  .XX.XOX.  ::::  +X ::",
        ":  .OOX.O#+X  :::: .oX ::",
        ": .oo$%O#;;%. :::: .oX ::",
        ": XXo+$&O@@%+  ::: .oX ::",
        ": XoO.X@@X.O$. ::: .+. ::",
        ": .O@XXX%XX+%. ::: .oX ::",
        ": .+o$&*=-==%. ::: .+X ::",
        ": XXo@%**==%X  ::: .oX ::",
        ": Xo@X.X.X... :::: .o. ::",
        ":  XO......XX.  :: .+X ::",
        ":  XO++++@@#&@.  : .oX ::",
        ": XXo$&=;;;-*:$O.  .oX ::",
        ": XXoO@@###$%+++.  .+. ::",
        ": .O+X. . .O%..    .+X ::",
        ": .X@.    .O+.   . .oX ::",
        ": .@O......XX...X@ .+X ::",
        ": Xo@#$&&*&&%$$@@@X.+. ::",
        ": .Xo@&*=-;*&$#@oo@X+X ::",
        ": XOXXXXXO+&OXXXXXX.+X ::",
        ": .X..  . X@$.     .+. ::",
        ": .@X.....X%&. ::: .+X ::",
        ": .o@$%&**==$. ::  XoX ::",
        ": XXo@&*=-=$X  :  .Xo. ::",
        ": .oXXXXXX..  :  .XooX ::",
        ": ..         :: .oXXX. ::",
        "::   :::::::::: XoX.   ::",
        ":::::::::::::::  .   ::::",
        ":::::::::::::::   :::::::"
        };


FormationThagoras001::FormationThagoras001(const char* prm_name) :
        FormationThagoras(prm_name, FormationThagoras001::xpmFormationThagoras001_) {
    _class_name = "FormationThagoras001";

    papSplManufConn_ = NEW SplineManufactureConnection*[pXpmHd_->columns_];
    for (int i = 0; i < pXpmHd_->columns_; i++) {
        papSplManufConn_[i] = connect_SplineManufactureManager("FormationThagoras001");
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
                                      createKurokoLeader(pThagoras->_pKurokoA);
    }
    pThagoras->pKurokoLeader_->fixStartPosition(entry_pos_._X                      ,
                                                entry_pos_._Y + (prm_col*PX_C(30)) ,
                                                entry_pos_._Z                       );

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

