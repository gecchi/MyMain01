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
    if (line0.fail()) {
        throwGgafCriticalException("XpmHeader::XpmHeader �s���ȃw�b�_�f�[�^�ł� line0=["<<line0<<"]");
    }
    for (int i = 0; i < colors_; i++) {
        char c = xpm_hd_[i + 1][0];
        c_px.push_back(c);
        if (xpm_hd_[i + 1][4] == '#') {                             //                   0123456789
            std::string strcolor = std::string(&(xpm_hd_[i+1][4])); //"#"�ȍ~�𕶎���� "X c #E08000",
            c_rgb_[c] = NEW GgafCore::GgafRgb(strcolor);
        } else {
            std::string strcolor = std::string(&(xpm_hd_[i+1][4]));
            if (strcolor == "None" || strcolor == "none") {
                c_px_non_ = c;
                c_rgb_[c] = NEW GgafCore::GgafRgb("#000000");
            } else {
                c_rgb_[c] = NEW GgafCore::GgafRgb(strcolor);
            }
        }
    }
    //pixels_�̓w�b�_�[�ȍ~�̔z��
    pixels_ = &(prm_xpm[1+colors_+1 -1]);//1+       :�ŏ��̂P�s�ڂ��΂��Ӗ��B("16 491 5 1 ", )
                                         //colors_+1:�c�̎��̍s���炾��Ƃ����ӁB
                                         //-1       :�z�񂾂���Y����-1
    num_color_pixels_ = 0;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < columns_; j++) {
            if (pixels_[i][j] != c_px_non_) {
                num_color_pixels_++;
            }
        }
    }
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

