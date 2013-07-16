#include "stdafx.h"
#include "XpmHeader.h"

#include "jp/ggaf/core/util/GgafRgb.h"
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

XpmHeader::XpmHeader(const char** prm_xpm) : GgafObject() {
    xpm_hd_ = prm_xpm;
    std::istringstream line0(xpm_hd_[0]); //"16 491 5 1 "
    line0 >> columns_ >> rows_ >> colors_;
    for (int i = 0; i < colors_; i++) {
        char c = xpm_hd_[i + 1][0];
        c_px.push_back(c); //  0123456789
        if (xpm_hd_[i + 1][4] == '#') {
            std::string strcolor = std::string(&(xpm_hd_[i + 1][4])); // "X c #E08000",
            c_rgb_[c] = NEW GgafCore::GgafRgb(strcolor);
        } else {
            std::string strcolor = std::string(&(xpm_hd_[i + 1][4])); // "X c None",“™
            if (strcolor == "None" || strcolor == "none") {
                c_px_non_ = c;
                c_rgb_[c] = NEW GgafCore::GgafRgb("#000000");
            } else {
                c_rgb_[c] = NEW GgafCore::GgafRgb(strcolor); //ƒGƒ‰[‚Ì‰Â”\«‚ª‘å
            }
        }
    }
    //
    pixels_ = &(prm_xpm[1+colors_+1 -1]);
}
XpmHeader::~XpmHeader(){
    for (int i = 0; i < colors_; i++) {
        GgafCore::GgafRgb* pRgb = c_rgb_[c_px[i]];
        GGAF_DELETE(pRgb);
    }
}

//static const char* ttt[] = {
///* columns rows colors chars-per-pixel */
//"16 491 5 1 ",               [0]
//"  c #000000",               [1]
//". c #008000",               [2]
//"X c #E08000",               [3]
//"o c #4665A2",               [4]
//"O c None",                  [5]
///* pixels */
//"OOOOOOOOOOOOOOOO",          [6]
//"OOOOOOOOOOOOOOOO",
//"OOOOOOOOOOOOOOOO",
//"OOOOOOOOOOOOOOOO",
//"OOOXXXXXXXOXXOOO",
//"OOOOOOOOOOOOOOOO"
//...
//}

