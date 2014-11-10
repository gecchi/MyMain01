#include "XpmManager.h"

#include "jp/gecchi/VioletVreath/manager/XpmConnection.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"

#include "jp/ggaf/core/util/GgafXpm.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

XpmManager::XpmManager(const char* prm_manager_name) :
    GgafResourceManager<GgafCore::GgafXpm> (prm_manager_name) {
}

GgafXpm* XpmManager::processCreateResource(char* prm_idstr, void* prm_pConnector) {
    GgafXpm* pResource = nullptr;

    if (UTIL::strcmp_ascii("jiki", prm_idstr) == 0) {
        /* XPM */
        static const char *jiki[] = {
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

        pResource = NEW GgafXpm(jiki);
    }
    if (UTIL::strcmp_ascii("jikir", prm_idstr) == 0) {
        /* XPM */
        static const char *jikir[] = {
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

        pResource = NEW GgafXpm(jikir);
    }

    if (UTIL::strcmp_ascii("FormationOebius002_Xpm", prm_idstr) == 0) {
        /* XPM */
        static const char *xpm_FormationOebius002[] = {
                "6 20 2 1",
                " 	c None",
                ".	c #ED1C24",
                "......",
                "   .  ",
                "   .  ",
                "......",
                "      ",
                " .... ",
                ".    .",
                ".    .",
                " .... ",
                "      ",
                " .... ",
                ".    .",
                ". .  .",
                " .. . ",
                "      ",
                "......",
                ".  . .",
                ".  . .",
                ".    .",
                "      "};

        pResource = NEW GgafXpm(xpm_FormationOebius002);
    }
    if (pResource == nullptr) {
        throwGgafCriticalException("XpmManager::processCreateResource("<<prm_idstr<<") 想定外のIDです。GgafXpmが作成できません。");
    }
    return pResource;
}

GgafResourceConnection<GgafCore::GgafXpm>* XpmManager::processCreateConnection(char* prm_idstr, GgafXpm* prm_pResource) {
    _TRACE3_(" XpmManager::processCreateConnection "<<prm_idstr<<" を生成開始。");
    XpmConnection* pConne = NEW XpmConnection(prm_idstr, prm_pResource);
    _TRACE3_(" XpmManager::processCreateConnection "<<prm_idstr<<" を生成終了。");
    return pConne;
}

