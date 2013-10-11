#include "stdafx.h"
#include "jp/ggaf/core/util/GgafRgb.h"
#include <map>

using namespace GgafCore;

bool GgafRgb::_is_init = false;
std::map<std::string, std::string> GgafRgb::_cname;

GgafRgb::GgafRgb() : GgafObject(),
        _allowedChars("0123456789abcdefABCDEF#") , _RED(0), _GREEN(0), _BLUE(0), _r(0), _g(0), _b(0), _hex(""), _is_valid(true) {
    init();
}

GgafRgb::GgafRgb(std::string prm_str_color) : GgafObject(),
        _allowedChars("0123456789abcdefABCDEF#") , _RED(0), _GREEN(0), _BLUE(0), _r(0), _g(0), _b(0), _hex(""), _is_valid(true) {
    init();
    set(prm_str_color);
}
void GgafRgb::init() {
    if (GgafRgb::_is_init) {
        return;
    }
    GgafRgb::_cname["snow"] = "#FFFAFA";
    GgafRgb::_cname["ghost white"] = "#F8F8FF";
    GgafRgb::_cname["GhostWhite"] = "#F8F8FF";
    GgafRgb::_cname["white smoke"] = "#F5F5F5";
    GgafRgb::_cname["WhiteSmoke"] = "#F5F5F5";
    GgafRgb::_cname["gainsboro"] = "#DCDCDC";
    GgafRgb::_cname["floral white"] = "#FFFAF0";
    GgafRgb::_cname["FloralWhite"] = "#FFFAF0";
    GgafRgb::_cname["old lace"] = "#FDF5E6";
    GgafRgb::_cname["OldLace"] = "#FDF5E6";
    GgafRgb::_cname["linen"] = "#FAF0E6";
    GgafRgb::_cname["antique white"] = "#FAEBD7";
    GgafRgb::_cname["AntiqueWhite"] = "#FAEBD7";
    GgafRgb::_cname["papaya whip"] = "#FFEFD5";
    GgafRgb::_cname["PapayaWhip"] = "#FFEFD5";
    GgafRgb::_cname["blanched almond"] = "#FFEBCD";
    GgafRgb::_cname["BlanchedAlmond"] = "#FFEBCD";
    GgafRgb::_cname["bisque"] = "#FFE4C4";
    GgafRgb::_cname["peach puff"] = "#FFDAB9";
    GgafRgb::_cname["PeachPuff"] = "#FFDAB9";
    GgafRgb::_cname["navajo white"] = "#FFDEAD";
    GgafRgb::_cname["NavajoWhite"] = "#FFDEAD";
    GgafRgb::_cname["moccasin"] = "#FFE4B5";
    GgafRgb::_cname["cornsilk"] = "#FFF8DC";
    GgafRgb::_cname["ivory"] = "#FFFFF0";
    GgafRgb::_cname["lemon chiffon"] = "#FFFACD";
    GgafRgb::_cname["LemonChiffon"] = "#FFFACD";
    GgafRgb::_cname["seashell"] = "#FFF5EE";
    GgafRgb::_cname["honeydew"] = "#F0FFF0";
    GgafRgb::_cname["mint cream"] = "#F5FFFA";
    GgafRgb::_cname["MintCream"] = "#F5FFFA";
    GgafRgb::_cname["azure"] = "#F0FFFF";
    GgafRgb::_cname["alice blue"] = "#F0F8FF";
    GgafRgb::_cname["AliceBlue"] = "#F0F8FF";
    GgafRgb::_cname["lavender"] = "#E6E6FA";
    GgafRgb::_cname["lavender blush"] = "#FFF0F5";
    GgafRgb::_cname["LavenderBlush"] = "#FFF0F5";
    GgafRgb::_cname["misty rose"] = "#FFE4E1";
    GgafRgb::_cname["MistyRose"] = "#FFE4E1";
    GgafRgb::_cname["white"] = "#FFFFFF";
    GgafRgb::_cname["black"] = "#000000";
    GgafRgb::_cname["dark slate gray"] = "#2F4F4F";
    GgafRgb::_cname["DarkSlateGray"] = "#2F4F4F";
    GgafRgb::_cname["dark slate grey"] = "#2F4F4F";
    GgafRgb::_cname["DarkSlateGrey"] = "#2F4F4F";
    GgafRgb::_cname["dim gray"] = "#696969";
    GgafRgb::_cname["DimGray"] = "#696969";
    GgafRgb::_cname["dim grey"] = "#696969";
    GgafRgb::_cname["DimGrey"] = "#696969";
    GgafRgb::_cname["slate gray"] = "#708090";
    GgafRgb::_cname["SlateGray"] = "#708090";
    GgafRgb::_cname["slate grey"] = "#708090";
    GgafRgb::_cname["SlateGrey"] = "#708090";
    GgafRgb::_cname["light slate gray"] = "#778899";
    GgafRgb::_cname["LightSlateGray"] = "#778899";
    GgafRgb::_cname["light slate grey"] = "#778899";
    GgafRgb::_cname["LightSlateGrey"] = "#778899";
    GgafRgb::_cname["gray"] = "#BEBEBE";
    GgafRgb::_cname["grey"] = "#BEBEBE";
    GgafRgb::_cname["light grey"] = "#D3D3D3";
    GgafRgb::_cname["LightGrey"] = "#D3D3D3";
    GgafRgb::_cname["light gray"] = "#D3D3D3";
    GgafRgb::_cname["LightGray"] = "#D3D3D3";
    GgafRgb::_cname["midnight blue"] = "#191970";
    GgafRgb::_cname["MidnightBlue"] = "#191970";
    GgafRgb::_cname["navy"] = "#000080";
    GgafRgb::_cname["navy blue"] = "#000080";
    GgafRgb::_cname["NavyBlue"] = "#000080";
    GgafRgb::_cname["cornflower blue"] = "#6495ED";
    GgafRgb::_cname["CornflowerBlue"] = "#6495ED";
    GgafRgb::_cname["dark slate blue"] = "#483D8B";
    GgafRgb::_cname["DarkSlateBlue"] = "#483D8B";
    GgafRgb::_cname["slate blue"] = "#6A5ACD";
    GgafRgb::_cname["SlateBlue"] = "#6A5ACD";
    GgafRgb::_cname["medium slate blue"] = "#7B68EE";
    GgafRgb::_cname["MediumSlateBlue"] = "#7B68EE";
    GgafRgb::_cname["light slate blue"] = "#8470FF";
    GgafRgb::_cname["LightSlateBlue"] = "#8470FF";
    GgafRgb::_cname["medium blue"] = "#0000CD";
    GgafRgb::_cname["MediumBlue"] = "#0000CD";
    GgafRgb::_cname["royal blue"] = "#4169E1";
    GgafRgb::_cname["RoyalBlue"] = "#4169E1";
    GgafRgb::_cname["blue"] = "#0000FF";
    GgafRgb::_cname["dodger blue"] = "#1E90FF";
    GgafRgb::_cname["DodgerBlue"] = "#1E90FF";
    GgafRgb::_cname["deep sky blue"] = "#00BFFF";
    GgafRgb::_cname["DeepSkyBlue"] = "#00BFFF";
    GgafRgb::_cname["sky blue"] = "#87CEEB";
    GgafRgb::_cname["SkyBlue"] = "#87CEEB";
    GgafRgb::_cname["light sky blue"] = "#87CEFA";
    GgafRgb::_cname["LightSkyBlue"] = "#87CEFA";
    GgafRgb::_cname["steel blue"] = "#4682B4";
    GgafRgb::_cname["SteelBlue"] = "#4682B4";
    GgafRgb::_cname["light steel blue"] = "#B0C4DE";
    GgafRgb::_cname["LightSteelBlue"] = "#B0C4DE";
    GgafRgb::_cname["light blue"] = "#ADD8E6";
    GgafRgb::_cname["LightBlue"] = "#ADD8E6";
    GgafRgb::_cname["powder blue"] = "#B0E0E6";
    GgafRgb::_cname["PowderBlue"] = "#B0E0E6";
    GgafRgb::_cname["pale turquoise"] = "#AFEEEE";
    GgafRgb::_cname["PaleTurquoise"] = "#AFEEEE";
    GgafRgb::_cname["dark turquoise"] = "#00CED1";
    GgafRgb::_cname["DarkTurquoise"] = "#00CED1";
    GgafRgb::_cname["medium turquoise"] = "#48D1CC";
    GgafRgb::_cname["MediumTurquoise"] = "#48D1CC";
    GgafRgb::_cname["turquoise"] = "#40E0D0";
    GgafRgb::_cname["cyan"] = "#00FFFF";
    GgafRgb::_cname["light cyan"] = "#E0FFFF";
    GgafRgb::_cname["LightCyan"] = "#E0FFFF";
    GgafRgb::_cname["cadet blue"] = "#5F9EA0";
    GgafRgb::_cname["CadetBlue"] = "#5F9EA0";
    GgafRgb::_cname["medium aquamarine"] = "#66CDAA";
    GgafRgb::_cname["MediumAquamarine"] = "#66CDAA";
    GgafRgb::_cname["aquamarine"] = "#7FFFD4";
    GgafRgb::_cname["dark green"] = "#006400";
    GgafRgb::_cname["DarkGreen"] = "#006400";
    GgafRgb::_cname["dark olive green"] = "#556B2F";
    GgafRgb::_cname["DarkOliveGreen"] = "#556B2F";
    GgafRgb::_cname["dark sea green"] = "#8FBC8F";
    GgafRgb::_cname["DarkSeaGreen"] = "#8FBC8F";
    GgafRgb::_cname["sea green"] = "#2E8B57";
    GgafRgb::_cname["SeaGreen"] = "#2E8B57";
    GgafRgb::_cname["medium sea green"] = "#3CB371";
    GgafRgb::_cname["MediumSeaGreen"] = "#3CB371";
    GgafRgb::_cname["light sea green"] = "#20B2AA";
    GgafRgb::_cname["LightSeaGreen"] = "#20B2AA";
    GgafRgb::_cname["pale green"] = "#98FB98";
    GgafRgb::_cname["PaleGreen"] = "#98FB98";
    GgafRgb::_cname["spring green"] = "#00FF7F";
    GgafRgb::_cname["SpringGreen"] = "#00FF7F";
    GgafRgb::_cname["lawn green"] = "#7CFC00";
    GgafRgb::_cname["LawnGreen"] = "#7CFC00";
    GgafRgb::_cname["green"] = "#00FF00";
    GgafRgb::_cname["chartreuse"] = "#7FFF00";
    GgafRgb::_cname["medium spring green"] = "#00FA9A";
    GgafRgb::_cname["MediumSpringGreen"] = "#00FA9A";
    GgafRgb::_cname["green yellow"] = "#ADFF2F";
    GgafRgb::_cname["GreenYellow"] = "#ADFF2F";
    GgafRgb::_cname["lime green"] = "#32CD32";
    GgafRgb::_cname["LimeGreen"] = "#32CD32";
    GgafRgb::_cname["yellow green"] = "#9ACD32";
    GgafRgb::_cname["YellowGreen"] = "#9ACD32";
    GgafRgb::_cname["forest green"] = "#228B22";
    GgafRgb::_cname["ForestGreen"] = "#228B22";
    GgafRgb::_cname["olive drab"] = "#6B8E23";
    GgafRgb::_cname["OliveDrab"] = "#6B8E23";
    GgafRgb::_cname["dark khaki"] = "#BDB76B";
    GgafRgb::_cname["DarkKhaki"] = "#BDB76B";
    GgafRgb::_cname["khaki"] = "#F0E68C";
    GgafRgb::_cname["pale goldenrod"] = "#EEE8AA";
    GgafRgb::_cname["PaleGoldenrod"] = "#EEE8AA";
    GgafRgb::_cname["light goldenrod yellow"] = "#FAFAD2";
    GgafRgb::_cname["LightGoldenrodYellow"] = "#FAFAD2";
    GgafRgb::_cname["light yellow"] = "#FFFFE0";
    GgafRgb::_cname["LightYellow"] = "#FFFFE0";
    GgafRgb::_cname["yellow"] = "#FFFF00";
    GgafRgb::_cname["gold"] = "#FFD700";
    GgafRgb::_cname["light goldenrod"] = "#EEDD82";
    GgafRgb::_cname["LightGoldenrod"] = "#EEDD82";
    GgafRgb::_cname["goldenrod"] = "#DAA520";
    GgafRgb::_cname["dark goldenrod"] = "#B8860B";
    GgafRgb::_cname["DarkGoldenrod"] = "#B8860B";
    GgafRgb::_cname["rosy brown"] = "#BC8F8F";
    GgafRgb::_cname["RosyBrown"] = "#BC8F8F";
    GgafRgb::_cname["indian red"] = "#CD5C5C";
    GgafRgb::_cname["IndianRed"] = "#CD5C5C";
    GgafRgb::_cname["saddle brown"] = "#8B4513";
    GgafRgb::_cname["SaddleBrown"] = "#8B4513";
    GgafRgb::_cname["sienna"] = "#A0522D";
    GgafRgb::_cname["peru"] = "#CD853F";
    GgafRgb::_cname["burlywood"] = "#DEB887";
    GgafRgb::_cname["beige"] = "#F5F5DC";
    GgafRgb::_cname["wheat"] = "#F5DEB3";
    GgafRgb::_cname["sandy brown"] = "#F4A460";
    GgafRgb::_cname["SandyBrown"] = "#F4A460";
    GgafRgb::_cname["tan"] = "#D2B48C";
    GgafRgb::_cname["chocolate"] = "#D2691E";
    GgafRgb::_cname["firebrick"] = "#B22222";
    GgafRgb::_cname["brown"] = "#A52A2A";
    GgafRgb::_cname["dark salmon"] = "#E9967A";
    GgafRgb::_cname["DarkSalmon"] = "#E9967A";
    GgafRgb::_cname["salmon"] = "#FA8072";
    GgafRgb::_cname["light salmon"] = "#FFA07A";
    GgafRgb::_cname["LightSalmon"] = "#FFA07A";
    GgafRgb::_cname["orange"] = "#FFA500";
    GgafRgb::_cname["dark orange"] = "#FF8C00";
    GgafRgb::_cname["DarkOrange"] = "#FF8C00";
    GgafRgb::_cname["coral"] = "#FF7F50";
    GgafRgb::_cname["light coral"] = "#F08080";
    GgafRgb::_cname["LightCoral"] = "#F08080";
    GgafRgb::_cname["tomato"] = "#FF6347";
    GgafRgb::_cname["orange red"] = "#FF4500";
    GgafRgb::_cname["OrangeRed"] = "#FF4500";
    GgafRgb::_cname["red"] = "#FF0000";
    GgafRgb::_cname["hot pink"] = "#FF69B4";
    GgafRgb::_cname["HotPink"] = "#FF69B4";
    GgafRgb::_cname["deep pink"] = "#FF1493";
    GgafRgb::_cname["DeepPink"] = "#FF1493";
    GgafRgb::_cname["pink"] = "#FFC0CB";
    GgafRgb::_cname["light pink"] = "#FFB6C1";
    GgafRgb::_cname["LightPink"] = "#FFB6C1";
    GgafRgb::_cname["pale violet red"] = "#DB7093";
    GgafRgb::_cname["PaleVioletRed"] = "#DB7093";
    GgafRgb::_cname["maroon"] = "#B03060";
    GgafRgb::_cname["medium violet red"] = "#C71585";
    GgafRgb::_cname["MediumVioletRed"] = "#C71585";
    GgafRgb::_cname["violet red"] = "#D02090";
    GgafRgb::_cname["VioletRed"] = "#D02090";
    GgafRgb::_cname["magenta"] = "#FF00FF";
    GgafRgb::_cname["violet"] = "#EE82EE";
    GgafRgb::_cname["plum"] = "#DDA0DD";
    GgafRgb::_cname["orchid"] = "#DA70D6";
    GgafRgb::_cname["medium orchid"] = "#BA55D3";
    GgafRgb::_cname["MediumOrchid"] = "#BA55D3";
    GgafRgb::_cname["dark orchid"] = "#9932CC";
    GgafRgb::_cname["DarkOrchid"] = "#9932CC";
    GgafRgb::_cname["dark violet"] = "#9400D3";
    GgafRgb::_cname["DarkViolet"] = "#9400D3";
    GgafRgb::_cname["blue violet"] = "#8A2BE2";
    GgafRgb::_cname["BlueViolet"] = "#8A2BE2";
    GgafRgb::_cname["purple"] = "#A020F0";
    GgafRgb::_cname["medium purple"] = "#9370DB";
    GgafRgb::_cname["MediumPurple"] = "#9370DB";
    GgafRgb::_cname["thistle"] = "#D8BFD8";
    GgafRgb::_cname["snow1"] = "#FFFAFA";
    GgafRgb::_cname["snow2"] = "#EEE9E9";
    GgafRgb::_cname["snow3"] = "#CDC9C9";
    GgafRgb::_cname["snow4"] = "#8B8989";
    GgafRgb::_cname["seashell1"] = "#FFF5EE";
    GgafRgb::_cname["seashell2"] = "#EEE5DE";
    GgafRgb::_cname["seashell3"] = "#CDC5BF";
    GgafRgb::_cname["seashell4"] = "#8B8682";
    GgafRgb::_cname["AntiqueWhite1"] = "#FFEFDB";
    GgafRgb::_cname["AntiqueWhite2"] = "#EEDFCC";
    GgafRgb::_cname["AntiqueWhite3"] = "#CDC0B0";
    GgafRgb::_cname["AntiqueWhite4"] = "#8B8378";
    GgafRgb::_cname["bisque1"] = "#FFE4C4";
    GgafRgb::_cname["bisque2"] = "#EED5B7";
    GgafRgb::_cname["bisque3"] = "#CDB79E";
    GgafRgb::_cname["bisque4"] = "#8B7D6B";
    GgafRgb::_cname["PeachPuff1"] = "#FFDAB9";
    GgafRgb::_cname["PeachPuff2"] = "#EECBAD";
    GgafRgb::_cname["PeachPuff3"] = "#CDAF95";
    GgafRgb::_cname["PeachPuff4"] = "#8B7765";
    GgafRgb::_cname["NavajoWhite1"] = "#FFDEAD";
    GgafRgb::_cname["NavajoWhite2"] = "#EECFA1";
    GgafRgb::_cname["NavajoWhite3"] = "#CDB38B";
    GgafRgb::_cname["NavajoWhite4"] = "#8B795E";
    GgafRgb::_cname["LemonChiffon1"] = "#FFFACD";
    GgafRgb::_cname["LemonChiffon2"] = "#EEE9BF";
    GgafRgb::_cname["LemonChiffon3"] = "#CDC9A5";
    GgafRgb::_cname["LemonChiffon4"] = "#8B8970";
    GgafRgb::_cname["cornsilk1"] = "#FFF8DC";
    GgafRgb::_cname["cornsilk2"] = "#EEE8CD";
    GgafRgb::_cname["cornsilk3"] = "#CDC8B1";
    GgafRgb::_cname["cornsilk4"] = "#8B8878";
    GgafRgb::_cname["ivory1"] = "#FFFFF0";
    GgafRgb::_cname["ivory2"] = "#EEEEE0";
    GgafRgb::_cname["ivory3"] = "#CDCDC1";
    GgafRgb::_cname["ivory4"] = "#8B8B83";
    GgafRgb::_cname["honeydew1"] = "#F0FFF0";
    GgafRgb::_cname["honeydew2"] = "#E0EEE0";
    GgafRgb::_cname["honeydew3"] = "#C1CDC1";
    GgafRgb::_cname["honeydew4"] = "#838B83";
    GgafRgb::_cname["LavenderBlush1"] = "#FFF0F5";
    GgafRgb::_cname["LavenderBlush2"] = "#EEE0E5";
    GgafRgb::_cname["LavenderBlush3"] = "#CDC1C5";
    GgafRgb::_cname["LavenderBlush4"] = "#8B8386";
    GgafRgb::_cname["MistyRose1"] = "#FFE4E1";
    GgafRgb::_cname["MistyRose2"] = "#EED5D2";
    GgafRgb::_cname["MistyRose3"] = "#CDB7B5";
    GgafRgb::_cname["MistyRose4"] = "#8B7D7B";
    GgafRgb::_cname["azure1"] = "#F0FFFF";
    GgafRgb::_cname["azure2"] = "#E0EEEE";
    GgafRgb::_cname["azure3"] = "#C1CDCD";
    GgafRgb::_cname["azure4"] = "#838B8B";
    GgafRgb::_cname["SlateBlue1"] = "#836FFF";
    GgafRgb::_cname["SlateBlue2"] = "#7A67EE";
    GgafRgb::_cname["SlateBlue3"] = "#6959CD";
    GgafRgb::_cname["SlateBlue4"] = "#473C8B";
    GgafRgb::_cname["RoyalBlue1"] = "#4876FF";
    GgafRgb::_cname["RoyalBlue2"] = "#436EEE";
    GgafRgb::_cname["RoyalBlue3"] = "#3A5FCD";
    GgafRgb::_cname["RoyalBlue4"] = "#27408B";
    GgafRgb::_cname["blue1"] = "#0000FF";
    GgafRgb::_cname["blue2"] = "#0000EE";
    GgafRgb::_cname["blue3"] = "#0000CD";
    GgafRgb::_cname["blue4"] = "#00008B";
    GgafRgb::_cname["DodgerBlue1"] = "#1E90FF";
    GgafRgb::_cname["DodgerBlue2"] = "#1C86EE";
    GgafRgb::_cname["DodgerBlue3"] = "#1874CD";
    GgafRgb::_cname["DodgerBlue4"] = "#104E8B";
    GgafRgb::_cname["SteelBlue1"] = "#63B8FF";
    GgafRgb::_cname["SteelBlue2"] = "#5CACEE";
    GgafRgb::_cname["SteelBlue3"] = "#4F94CD";
    GgafRgb::_cname["SteelBlue4"] = "#36648B";
    GgafRgb::_cname["DeepSkyBlue1"] = "#00BFFF";
    GgafRgb::_cname["DeepSkyBlue2"] = "#00B2EE";
    GgafRgb::_cname["DeepSkyBlue3"] = "#009ACD";
    GgafRgb::_cname["DeepSkyBlue4"] = "#00688B";
    GgafRgb::_cname["SkyBlue1"] = "#87CEFF";
    GgafRgb::_cname["SkyBlue2"] = "#7EC0EE";
    GgafRgb::_cname["SkyBlue3"] = "#6CA6CD";
    GgafRgb::_cname["SkyBlue4"] = "#4A708B";
    GgafRgb::_cname["LightSkyBlue1"] = "#B0E2FF";
    GgafRgb::_cname["LightSkyBlue2"] = "#A4D3EE";
    GgafRgb::_cname["LightSkyBlue3"] = "#8DB6CD";
    GgafRgb::_cname["LightSkyBlue4"] = "#607B8B";
    GgafRgb::_cname["SlateGray1"] = "#C6E2FF";
    GgafRgb::_cname["SlateGray2"] = "#B9D3EE";
    GgafRgb::_cname["SlateGray3"] = "#9FB6CD";
    GgafRgb::_cname["SlateGray4"] = "#6C7B8B";
    GgafRgb::_cname["LightSteelBlue1"] = "#CAE1FF";
    GgafRgb::_cname["LightSteelBlue2"] = "#BCD2EE";
    GgafRgb::_cname["LightSteelBlue3"] = "#A2B5CD";
    GgafRgb::_cname["LightSteelBlue4"] = "#6E7B8B";
    GgafRgb::_cname["LightBlue1"] = "#BFEFFF";
    GgafRgb::_cname["LightBlue2"] = "#B2DFEE";
    GgafRgb::_cname["LightBlue3"] = "#9AC0CD";
    GgafRgb::_cname["LightBlue4"] = "#68838B";
    GgafRgb::_cname["LightCyan1"] = "#E0FFFF";
    GgafRgb::_cname["LightCyan2"] = "#D1EEEE";
    GgafRgb::_cname["LightCyan3"] = "#B4CDCD";
    GgafRgb::_cname["LightCyan4"] = "#7A8B8B";
    GgafRgb::_cname["PaleTurquoise1"] = "#BBFFFF";
    GgafRgb::_cname["PaleTurquoise2"] = "#AEEEEE";
    GgafRgb::_cname["PaleTurquoise3"] = "#96CDCD";
    GgafRgb::_cname["PaleTurquoise4"] = "#668B8B";
    GgafRgb::_cname["CadetBlue1"] = "#98F5FF";
    GgafRgb::_cname["CadetBlue2"] = "#8EE5EE";
    GgafRgb::_cname["CadetBlue3"] = "#7AC5CD";
    GgafRgb::_cname["CadetBlue4"] = "#53868B";
    GgafRgb::_cname["turquoise1"] = "#00F5FF";
    GgafRgb::_cname["turquoise2"] = "#00E5EE";
    GgafRgb::_cname["turquoise3"] = "#00C5CD";
    GgafRgb::_cname["turquoise4"] = "#00868B";
    GgafRgb::_cname["cyan1"] = "#00FFFF";
    GgafRgb::_cname["cyan2"] = "#00EEEE";
    GgafRgb::_cname["cyan3"] = "#00CDCD";
    GgafRgb::_cname["cyan4"] = "#008B8B";
    GgafRgb::_cname["DarkSlateGray1"] = "#97FFFF";
    GgafRgb::_cname["DarkSlateGray2"] = "#8DEEEE";
    GgafRgb::_cname["DarkSlateGray3"] = "#79CDCD";
    GgafRgb::_cname["DarkSlateGray4"] = "#528B8B";
    GgafRgb::_cname["aquamarine1"] = "#7FFFD4";
    GgafRgb::_cname["aquamarine2"] = "#76EEC6";
    GgafRgb::_cname["aquamarine3"] = "#66CDAA";
    GgafRgb::_cname["aquamarine4"] = "#458B74";
    GgafRgb::_cname["DarkSeaGreen1"] = "#C1FFC1";
    GgafRgb::_cname["DarkSeaGreen2"] = "#B4EEB4";
    GgafRgb::_cname["DarkSeaGreen3"] = "#9BCD9B";
    GgafRgb::_cname["DarkSeaGreen4"] = "#698B69";
    GgafRgb::_cname["SeaGreen1"] = "#54FF9F";
    GgafRgb::_cname["SeaGreen2"] = "#4EEE94";
    GgafRgb::_cname["SeaGreen3"] = "#43CD80";
    GgafRgb::_cname["SeaGreen4"] = "#2E8B57";
    GgafRgb::_cname["PaleGreen1"] = "#9AFF9A";
    GgafRgb::_cname["PaleGreen2"] = "#90EE90";
    GgafRgb::_cname["PaleGreen3"] = "#7CCD7C";
    GgafRgb::_cname["PaleGreen4"] = "#548B54";
    GgafRgb::_cname["SpringGreen1"] = "#00FF7F";
    GgafRgb::_cname["SpringGreen2"] = "#00EE76";
    GgafRgb::_cname["SpringGreen3"] = "#00CD66";
    GgafRgb::_cname["SpringGreen4"] = "#008B45";
    GgafRgb::_cname["green1"] = "#00FF00";
    GgafRgb::_cname["green2"] = "#00EE00";
    GgafRgb::_cname["green3"] = "#00CD00";
    GgafRgb::_cname["green4"] = "#008B00";
    GgafRgb::_cname["chartreuse1"] = "#7FFF00";
    GgafRgb::_cname["chartreuse2"] = "#76EE00";
    GgafRgb::_cname["chartreuse3"] = "#66CD00";
    GgafRgb::_cname["chartreuse4"] = "#458B00";
    GgafRgb::_cname["OliveDrab1"] = "#C0FF3E";
    GgafRgb::_cname["OliveDrab2"] = "#B3EE3A";
    GgafRgb::_cname["OliveDrab3"] = "#9ACD32";
    GgafRgb::_cname["OliveDrab4"] = "#698B22";
    GgafRgb::_cname["DarkOliveGreen1"] = "#CAFF70";
    GgafRgb::_cname["DarkOliveGreen2"] = "#BCEE68";
    GgafRgb::_cname["DarkOliveGreen3"] = "#A2CD5A";
    GgafRgb::_cname["DarkOliveGreen4"] = "#6E8B3D";
    GgafRgb::_cname["khaki1"] = "#FFF68F";
    GgafRgb::_cname["khaki2"] = "#EEE685";
    GgafRgb::_cname["khaki3"] = "#CDC673";
    GgafRgb::_cname["khaki4"] = "#8B864E";
    GgafRgb::_cname["LightGoldenrod1"] = "#FFEC8B";
    GgafRgb::_cname["LightGoldenrod2"] = "#EEDC82";
    GgafRgb::_cname["LightGoldenrod3"] = "#CDBE70";
    GgafRgb::_cname["LightGoldenrod4"] = "#8B814C";
    GgafRgb::_cname["LightYellow1"] = "#FFFFE0";
    GgafRgb::_cname["LightYellow2"] = "#EEEED1";
    GgafRgb::_cname["LightYellow3"] = "#CDCDB4";
    GgafRgb::_cname["LightYellow4"] = "#8B8B7A";
    GgafRgb::_cname["yellow1"] = "#FFFF00";
    GgafRgb::_cname["yellow2"] = "#EEEE00";
    GgafRgb::_cname["yellow3"] = "#CDCD00";
    GgafRgb::_cname["yellow4"] = "#8B8B00";
    GgafRgb::_cname["gold1"] = "#FFD700";
    GgafRgb::_cname["gold2"] = "#EEC900";
    GgafRgb::_cname["gold3"] = "#CDAD00";
    GgafRgb::_cname["gold4"] = "#8B7500";
    GgafRgb::_cname["goldenrod1"] = "#FFC125";
    GgafRgb::_cname["goldenrod2"] = "#EEB422";
    GgafRgb::_cname["goldenrod3"] = "#CD9B1D";
    GgafRgb::_cname["goldenrod4"] = "#8B6914";
    GgafRgb::_cname["DarkGoldenrod1"] = "#FFB90F";
    GgafRgb::_cname["DarkGoldenrod2"] = "#EEAD0E";
    GgafRgb::_cname["DarkGoldenrod3"] = "#CD950C";
    GgafRgb::_cname["DarkGoldenrod4"] = "#8B6508";
    GgafRgb::_cname["RosyBrown1"] = "#FFC1C1";
    GgafRgb::_cname["RosyBrown2"] = "#EEB4B4";
    GgafRgb::_cname["RosyBrown3"] = "#CD9B9B";
    GgafRgb::_cname["RosyBrown4"] = "#8B6969";
    GgafRgb::_cname["IndianRed1"] = "#FF6A6A";
    GgafRgb::_cname["IndianRed2"] = "#EE6363";
    GgafRgb::_cname["IndianRed3"] = "#CD5555";
    GgafRgb::_cname["IndianRed4"] = "#8B3A3A";
    GgafRgb::_cname["sienna1"] = "#FF8247";
    GgafRgb::_cname["sienna2"] = "#EE7942";
    GgafRgb::_cname["sienna3"] = "#CD6839";
    GgafRgb::_cname["sienna4"] = "#8B4726";
    GgafRgb::_cname["burlywood1"] = "#FFD39B";
    GgafRgb::_cname["burlywood2"] = "#EEC591";
    GgafRgb::_cname["burlywood3"] = "#CDAA7D";
    GgafRgb::_cname["burlywood4"] = "#8B7355";
    GgafRgb::_cname["wheat1"] = "#FFE7BA";
    GgafRgb::_cname["wheat2"] = "#EED8AE";
    GgafRgb::_cname["wheat3"] = "#CDBA96";
    GgafRgb::_cname["wheat4"] = "#8B7E66";
    GgafRgb::_cname["tan1"] = "#FFA54F";
    GgafRgb::_cname["tan2"] = "#EE9A49";
    GgafRgb::_cname["tan3"] = "#CD853F";
    GgafRgb::_cname["tan4"] = "#8B5A2B";
    GgafRgb::_cname["chocolate1"] = "#FF7F24";
    GgafRgb::_cname["chocolate2"] = "#EE7621";
    GgafRgb::_cname["chocolate3"] = "#CD661D";
    GgafRgb::_cname["chocolate4"] = "#8B4513";
    GgafRgb::_cname["firebrick1"] = "#FF3030";
    GgafRgb::_cname["firebrick2"] = "#EE2C2C";
    GgafRgb::_cname["firebrick3"] = "#CD2626";
    GgafRgb::_cname["firebrick4"] = "#8B1A1A";
    GgafRgb::_cname["brown1"] = "#FF4040";
    GgafRgb::_cname["brown2"] = "#EE3B3B";
    GgafRgb::_cname["brown3"] = "#CD3333";
    GgafRgb::_cname["brown4"] = "#8B2323";
    GgafRgb::_cname["salmon1"] = "#FF8C69";
    GgafRgb::_cname["salmon2"] = "#EE8262";
    GgafRgb::_cname["salmon3"] = "#CD7054";
    GgafRgb::_cname["salmon4"] = "#8B4C39";
    GgafRgb::_cname["LightSalmon1"] = "#FFA07A";
    GgafRgb::_cname["LightSalmon2"] = "#EE9572";
    GgafRgb::_cname["LightSalmon3"] = "#CD8162";
    GgafRgb::_cname["LightSalmon4"] = "#8B5742";
    GgafRgb::_cname["orange1"] = "#FFA500";
    GgafRgb::_cname["orange2"] = "#EE9A00";
    GgafRgb::_cname["orange3"] = "#CD8500";
    GgafRgb::_cname["orange4"] = "#8B5A00";
    GgafRgb::_cname["DarkOrange1"] = "#FF7F00";
    GgafRgb::_cname["DarkOrange2"] = "#EE7600";
    GgafRgb::_cname["DarkOrange3"] = "#CD6600";
    GgafRgb::_cname["DarkOrange4"] = "#8B4500";
    GgafRgb::_cname["coral1"] = "#FF7256";
    GgafRgb::_cname["coral2"] = "#EE6A50";
    GgafRgb::_cname["coral3"] = "#CD5B45";
    GgafRgb::_cname["coral4"] = "#8B3E2F";
    GgafRgb::_cname["tomato1"] = "#FF6347";
    GgafRgb::_cname["tomato2"] = "#EE5C42";
    GgafRgb::_cname["tomato3"] = "#CD4F39";
    GgafRgb::_cname["tomato4"] = "#8B3626";
    GgafRgb::_cname["OrangeRed1"] = "#FF4500";
    GgafRgb::_cname["OrangeRed2"] = "#EE4000";
    GgafRgb::_cname["OrangeRed3"] = "#CD3700";
    GgafRgb::_cname["OrangeRed4"] = "#8B2500";
    GgafRgb::_cname["red1"] = "#FF0000";
    GgafRgb::_cname["red2"] = "#EE0000";
    GgafRgb::_cname["red3"] = "#CD0000";
    GgafRgb::_cname["red4"] = "#8B0000";
    GgafRgb::_cname["DeepPink1"] = "#FF1493";
    GgafRgb::_cname["DeepPink2"] = "#EE1289";
    GgafRgb::_cname["DeepPink3"] = "#CD1076";
    GgafRgb::_cname["DeepPink4"] = "#8B0A50";
    GgafRgb::_cname["HotPink1"] = "#FF6EB4";
    GgafRgb::_cname["HotPink2"] = "#EE6AA7";
    GgafRgb::_cname["HotPink3"] = "#CD6090";
    GgafRgb::_cname["HotPink4"] = "#8B3A62";
    GgafRgb::_cname["pink1"] = "#FFB5C5";
    GgafRgb::_cname["pink2"] = "#EEA9B8";
    GgafRgb::_cname["pink3"] = "#CD919E";
    GgafRgb::_cname["pink4"] = "#8B636C";
    GgafRgb::_cname["LightPink1"] = "#FFAEB9";
    GgafRgb::_cname["LightPink2"] = "#EEA2AD";
    GgafRgb::_cname["LightPink3"] = "#CD8C95";
    GgafRgb::_cname["LightPink4"] = "#8B5F65";
    GgafRgb::_cname["PaleVioletRed1"] = "#FF82AB";
    GgafRgb::_cname["PaleVioletRed2"] = "#EE799F";
    GgafRgb::_cname["PaleVioletRed3"] = "#CD6889";
    GgafRgb::_cname["PaleVioletRed4"] = "#8B475D";
    GgafRgb::_cname["maroon1"] = "#FF34B3";
    GgafRgb::_cname["maroon2"] = "#EE30A7";
    GgafRgb::_cname["maroon3"] = "#CD2990";
    GgafRgb::_cname["maroon4"] = "#8B1C62";
    GgafRgb::_cname["VioletRed1"] = "#FF3E96";
    GgafRgb::_cname["VioletRed2"] = "#EE3A8C";
    GgafRgb::_cname["VioletRed3"] = "#CD3278";
    GgafRgb::_cname["VioletRed4"] = "#8B2252";
    GgafRgb::_cname["magenta1"] = "#FF00FF";
    GgafRgb::_cname["magenta2"] = "#EE00EE";
    GgafRgb::_cname["magenta3"] = "#CD00CD";
    GgafRgb::_cname["magenta4"] = "#8B008B";
    GgafRgb::_cname["orchid1"] = "#FF83FA";
    GgafRgb::_cname["orchid2"] = "#EE7AE9";
    GgafRgb::_cname["orchid3"] = "#CD69C9";
    GgafRgb::_cname["orchid4"] = "#8B4789";
    GgafRgb::_cname["plum1"] = "#FFBBFF";
    GgafRgb::_cname["plum2"] = "#EEAEEE";
    GgafRgb::_cname["plum3"] = "#CD96CD";
    GgafRgb::_cname["plum4"] = "#8B668B";
    GgafRgb::_cname["MediumOrchid1"] = "#E066FF";
    GgafRgb::_cname["MediumOrchid2"] = "#D15FEE";
    GgafRgb::_cname["MediumOrchid3"] = "#B452CD";
    GgafRgb::_cname["MediumOrchid4"] = "#7A378B";
    GgafRgb::_cname["DarkOrchid1"] = "#BF3EFF";
    GgafRgb::_cname["DarkOrchid2"] = "#B23AEE";
    GgafRgb::_cname["DarkOrchid3"] = "#9A32CD";
    GgafRgb::_cname["DarkOrchid4"] = "#68228B";
    GgafRgb::_cname["purple1"] = "#9B30FF";
    GgafRgb::_cname["purple2"] = "#912CEE";
    GgafRgb::_cname["purple3"] = "#7D26CD";
    GgafRgb::_cname["purple4"] = "#551A8B";
    GgafRgb::_cname["MediumPurple1"] = "#AB82FF";
    GgafRgb::_cname["MediumPurple2"] = "#9F79EE";
    GgafRgb::_cname["MediumPurple3"] = "#8968CD";
    GgafRgb::_cname["MediumPurple4"] = "#5D478B";
    GgafRgb::_cname["thistle1"] = "#FFE1FF";
    GgafRgb::_cname["thistle2"] = "#EED2EE";
    GgafRgb::_cname["thistle3"] = "#CDB5CD";
    GgafRgb::_cname["thistle4"] = "#8B7B8B";
    GgafRgb::_cname["gray0"] = "#000000";
    GgafRgb::_cname["grey0"] = "#000000";
    GgafRgb::_cname["gray1"] = "#030303";
    GgafRgb::_cname["grey1"] = "#030303";
    GgafRgb::_cname["gray2"] = "#050505";
    GgafRgb::_cname["grey2"] = "#050505";
    GgafRgb::_cname["gray3"] = "#080808";
    GgafRgb::_cname["grey3"] = "#080808";
    GgafRgb::_cname["gray4"] = "#0A0A0A";
    GgafRgb::_cname["grey4"] = "#0A0A0A";
    GgafRgb::_cname["gray5"] = "#0D0D0D";
    GgafRgb::_cname["grey5"] = "#0D0D0D";
    GgafRgb::_cname["gray6"] = "#0F0F0F";
    GgafRgb::_cname["grey6"] = "#0F0F0F";
    GgafRgb::_cname["gray7"] = "#121212";
    GgafRgb::_cname["grey7"] = "#121212";
    GgafRgb::_cname["gray8"] = "#141414";
    GgafRgb::_cname["grey8"] = "#141414";
    GgafRgb::_cname["gray9"] = "#171717";
    GgafRgb::_cname["grey9"] = "#171717";
    GgafRgb::_cname["gray10"] = "#1A1A1A";
    GgafRgb::_cname["grey10"] = "#1A1A1A";
    GgafRgb::_cname["gray11"] = "#1C1C1C";
    GgafRgb::_cname["grey11"] = "#1C1C1C";
    GgafRgb::_cname["gray12"] = "#1F1F1F";
    GgafRgb::_cname["grey12"] = "#1F1F1F";
    GgafRgb::_cname["gray13"] = "#212121";
    GgafRgb::_cname["grey13"] = "#212121";
    GgafRgb::_cname["gray14"] = "#242424";
    GgafRgb::_cname["grey14"] = "#242424";
    GgafRgb::_cname["gray15"] = "#262626";
    GgafRgb::_cname["grey15"] = "#262626";
    GgafRgb::_cname["gray16"] = "#292929";
    GgafRgb::_cname["grey16"] = "#292929";
    GgafRgb::_cname["gray17"] = "#2B2B2B";
    GgafRgb::_cname["grey17"] = "#2B2B2B";
    GgafRgb::_cname["gray18"] = "#2E2E2E";
    GgafRgb::_cname["grey18"] = "#2E2E2E";
    GgafRgb::_cname["gray19"] = "#303030";
    GgafRgb::_cname["grey19"] = "#303030";
    GgafRgb::_cname["gray20"] = "#333333";
    GgafRgb::_cname["grey20"] = "#333333";
    GgafRgb::_cname["gray21"] = "#363636";
    GgafRgb::_cname["grey21"] = "#363636";
    GgafRgb::_cname["gray22"] = "#383838";
    GgafRgb::_cname["grey22"] = "#383838";
    GgafRgb::_cname["gray23"] = "#3B3B3B";
    GgafRgb::_cname["grey23"] = "#3B3B3B";
    GgafRgb::_cname["gray24"] = "#3D3D3D";
    GgafRgb::_cname["grey24"] = "#3D3D3D";
    GgafRgb::_cname["gray25"] = "#404040";
    GgafRgb::_cname["grey25"] = "#404040";
    GgafRgb::_cname["gray26"] = "#424242";
    GgafRgb::_cname["grey26"] = "#424242";
    GgafRgb::_cname["gray27"] = "#454545";
    GgafRgb::_cname["grey27"] = "#454545";
    GgafRgb::_cname["gray28"] = "#474747";
    GgafRgb::_cname["grey28"] = "#474747";
    GgafRgb::_cname["gray29"] = "#4A4A4A";
    GgafRgb::_cname["grey29"] = "#4A4A4A";
    GgafRgb::_cname["gray30"] = "#4D4D4D";
    GgafRgb::_cname["grey30"] = "#4D4D4D";
    GgafRgb::_cname["gray31"] = "#4F4F4F";
    GgafRgb::_cname["grey31"] = "#4F4F4F";
    GgafRgb::_cname["gray32"] = "#525252";
    GgafRgb::_cname["grey32"] = "#525252";
    GgafRgb::_cname["gray33"] = "#545454";
    GgafRgb::_cname["grey33"] = "#545454";
    GgafRgb::_cname["gray34"] = "#575757";
    GgafRgb::_cname["grey34"] = "#575757";
    GgafRgb::_cname["gray35"] = "#595959";
    GgafRgb::_cname["grey35"] = "#595959";
    GgafRgb::_cname["gray36"] = "#5C5C5C";
    GgafRgb::_cname["grey36"] = "#5C5C5C";
    GgafRgb::_cname["gray37"] = "#5E5E5E";
    GgafRgb::_cname["grey37"] = "#5E5E5E";
    GgafRgb::_cname["gray38"] = "#616161";
    GgafRgb::_cname["grey38"] = "#616161";
    GgafRgb::_cname["gray39"] = "#636363";
    GgafRgb::_cname["grey39"] = "#636363";
    GgafRgb::_cname["gray40"] = "#666666";
    GgafRgb::_cname["grey40"] = "#666666";
    GgafRgb::_cname["gray41"] = "#696969";
    GgafRgb::_cname["grey41"] = "#696969";
    GgafRgb::_cname["gray42"] = "#6B6B6B";
    GgafRgb::_cname["grey42"] = "#6B6B6B";
    GgafRgb::_cname["gray43"] = "#6E6E6E";
    GgafRgb::_cname["grey43"] = "#6E6E6E";
    GgafRgb::_cname["gray44"] = "#707070";
    GgafRgb::_cname["grey44"] = "#707070";
    GgafRgb::_cname["gray45"] = "#737373";
    GgafRgb::_cname["grey45"] = "#737373";
    GgafRgb::_cname["gray46"] = "#757575";
    GgafRgb::_cname["grey46"] = "#757575";
    GgafRgb::_cname["gray47"] = "#787878";
    GgafRgb::_cname["grey47"] = "#787878";
    GgafRgb::_cname["gray48"] = "#7A7A7A";
    GgafRgb::_cname["grey48"] = "#7A7A7A";
    GgafRgb::_cname["gray49"] = "#7D7D7D";
    GgafRgb::_cname["grey49"] = "#7D7D7D";
    GgafRgb::_cname["gray50"] = "#7F7F7F";
    GgafRgb::_cname["grey50"] = "#7F7F7F";
    GgafRgb::_cname["gray51"] = "#828282";
    GgafRgb::_cname["grey51"] = "#828282";
    GgafRgb::_cname["gray52"] = "#858585";
    GgafRgb::_cname["grey52"] = "#858585";
    GgafRgb::_cname["gray53"] = "#878787";
    GgafRgb::_cname["grey53"] = "#878787";
    GgafRgb::_cname["gray54"] = "#8A8A8A";
    GgafRgb::_cname["grey54"] = "#8A8A8A";
    GgafRgb::_cname["gray55"] = "#8C8C8C";
    GgafRgb::_cname["grey55"] = "#8C8C8C";
    GgafRgb::_cname["gray56"] = "#8F8F8F";
    GgafRgb::_cname["grey56"] = "#8F8F8F";
    GgafRgb::_cname["gray57"] = "#919191";
    GgafRgb::_cname["grey57"] = "#919191";
    GgafRgb::_cname["gray58"] = "#949494";
    GgafRgb::_cname["grey58"] = "#949494";
    GgafRgb::_cname["gray59"] = "#969696";
    GgafRgb::_cname["grey59"] = "#969696";
    GgafRgb::_cname["gray60"] = "#999999";
    GgafRgb::_cname["grey60"] = "#999999";
    GgafRgb::_cname["gray61"] = "#9C9C9C";
    GgafRgb::_cname["grey61"] = "#9C9C9C";
    GgafRgb::_cname["gray62"] = "#9E9E9E";
    GgafRgb::_cname["grey62"] = "#9E9E9E";
    GgafRgb::_cname["gray63"] = "#A1A1A1";
    GgafRgb::_cname["grey63"] = "#A1A1A1";
    GgafRgb::_cname["gray64"] = "#A3A3A3";
    GgafRgb::_cname["grey64"] = "#A3A3A3";
    GgafRgb::_cname["gray65"] = "#A6A6A6";
    GgafRgb::_cname["grey65"] = "#A6A6A6";
    GgafRgb::_cname["gray66"] = "#A8A8A8";
    GgafRgb::_cname["grey66"] = "#A8A8A8";
    GgafRgb::_cname["gray67"] = "#ABABAB";
    GgafRgb::_cname["grey67"] = "#ABABAB";
    GgafRgb::_cname["gray68"] = "#ADADAD";
    GgafRgb::_cname["grey68"] = "#ADADAD";
    GgafRgb::_cname["gray69"] = "#B0B0B0";
    GgafRgb::_cname["grey69"] = "#B0B0B0";
    GgafRgb::_cname["gray70"] = "#B3B3B3";
    GgafRgb::_cname["grey70"] = "#B3B3B3";
    GgafRgb::_cname["gray71"] = "#B5B5B5";
    GgafRgb::_cname["grey71"] = "#B5B5B5";
    GgafRgb::_cname["gray72"] = "#B8B8B8";
    GgafRgb::_cname["grey72"] = "#B8B8B8";
    GgafRgb::_cname["gray73"] = "#BABABA";
    GgafRgb::_cname["grey73"] = "#BABABA";
    GgafRgb::_cname["gray74"] = "#BDBDBD";
    GgafRgb::_cname["grey74"] = "#BDBDBD";
    GgafRgb::_cname["gray75"] = "#BFBFBF";
    GgafRgb::_cname["grey75"] = "#BFBFBF";
    GgafRgb::_cname["gray76"] = "#C2C2C2";
    GgafRgb::_cname["grey76"] = "#C2C2C2";
    GgafRgb::_cname["gray77"] = "#C4C4C4";
    GgafRgb::_cname["grey77"] = "#C4C4C4";
    GgafRgb::_cname["gray78"] = "#C7C7C7";
    GgafRgb::_cname["grey78"] = "#C7C7C7";
    GgafRgb::_cname["gray79"] = "#C9C9C9";
    GgafRgb::_cname["grey79"] = "#C9C9C9";
    GgafRgb::_cname["gray80"] = "#CCCCCC";
    GgafRgb::_cname["grey80"] = "#CCCCCC";
    GgafRgb::_cname["gray81"] = "#CFCFCF";
    GgafRgb::_cname["grey81"] = "#CFCFCF";
    GgafRgb::_cname["gray82"] = "#D1D1D1";
    GgafRgb::_cname["grey82"] = "#D1D1D1";
    GgafRgb::_cname["gray83"] = "#D4D4D4";
    GgafRgb::_cname["grey83"] = "#D4D4D4";
    GgafRgb::_cname["gray84"] = "#D6D6D6";
    GgafRgb::_cname["grey84"] = "#D6D6D6";
    GgafRgb::_cname["gray85"] = "#D9D9D9";
    GgafRgb::_cname["grey85"] = "#D9D9D9";
    GgafRgb::_cname["gray86"] = "#DBDBDB";
    GgafRgb::_cname["grey86"] = "#DBDBDB";
    GgafRgb::_cname["gray87"] = "#DEDEDE";
    GgafRgb::_cname["grey87"] = "#DEDEDE";
    GgafRgb::_cname["gray88"] = "#E0E0E0";
    GgafRgb::_cname["grey88"] = "#E0E0E0";
    GgafRgb::_cname["gray89"] = "#E3E3E3";
    GgafRgb::_cname["grey89"] = "#E3E3E3";
    GgafRgb::_cname["gray90"] = "#E5E5E5";
    GgafRgb::_cname["grey90"] = "#E5E5E5";
    GgafRgb::_cname["gray91"] = "#E8E8E8";
    GgafRgb::_cname["grey91"] = "#E8E8E8";
    GgafRgb::_cname["gray92"] = "#EBEBEB";
    GgafRgb::_cname["grey92"] = "#EBEBEB";
    GgafRgb::_cname["gray93"] = "#EDEDED";
    GgafRgb::_cname["grey93"] = "#EDEDED";
    GgafRgb::_cname["gray94"] = "#F0F0F0";
    GgafRgb::_cname["grey94"] = "#F0F0F0";
    GgafRgb::_cname["gray95"] = "#F2F2F2";
    GgafRgb::_cname["grey95"] = "#F2F2F2";
    GgafRgb::_cname["gray96"] = "#F5F5F5";
    GgafRgb::_cname["grey96"] = "#F5F5F5";
    GgafRgb::_cname["gray97"] = "#F7F7F7";
    GgafRgb::_cname["grey97"] = "#F7F7F7";
    GgafRgb::_cname["gray98"] = "#FAFAFA";
    GgafRgb::_cname["grey98"] = "#FAFAFA";
    GgafRgb::_cname["gray99"] = "#FCFCFC";
    GgafRgb::_cname["grey99"] = "#FCFCFC";
    GgafRgb::_cname["gray100"] = "#FFFFFF";
    GgafRgb::_cname["grey100"] = "#FFFFFF";
    GgafRgb::_cname["dark grey"] = "#A9A9A9";
    GgafRgb::_cname["DarkGrey"] = "#A9A9A9";
    GgafRgb::_cname["dark gray"] = "#A9A9A9";
    GgafRgb::_cname["DarkGray"] = "#A9A9A9";
    GgafRgb::_cname["dark blue"] = "#00008B";
    GgafRgb::_cname["DarkBlue"] = "#00008B";
    GgafRgb::_cname["dark cyan"] = "#008B8B";
    GgafRgb::_cname["DarkCyan"] = "#008B8B";
    GgafRgb::_cname["dark magenta"] = "#8B008B";
    GgafRgb::_cname["DarkMagenta"] = "#8B008B";
    GgafRgb::_cname["dark red"] = "#8B0000";
    GgafRgb::_cname["DarkRed"] = "#8B0000";
    GgafRgb::_cname["light green"] = "#90EE90";
    GgafRgb::_cname["LightGreen"] = "#90EE90";
    GgafRgb::_is_init = true;
}

bool GgafRgb::isValid() {
    if (_hex.length() != 6) {
        return false;
    } else {
        if (_hex.find_first_not_of(_allowedChars) != _hex.npos) {
            return false;
        } else {
            return true;
        }
    }
}

void GgafRgb::set(std::string prm_str_color) {
    _hex = prm_str_color;
    if (_hex[0] == '#') {
        _hex.erase(_hex.begin());
    }
    _is_valid = isValid();
    if (_is_valid) {
        _RED = UTIL::hex2dec(_hex.substr(0, 2));
        _GREEN = UTIL::hex2dec(_hex.substr(2, 2));
        _BLUE = UTIL::hex2dec(_hex.substr(4, 2));
        _r = _RED / 255.0f;
        _g = _GREEN / 255.0f;
        _b = _BLUE / 255.0f;
    } else {
        if (GgafRgb::_cname.find(prm_str_color) == GgafRgb::_cname.end()) {
            throwGgafCriticalException("GgafRgb::set HEX値(色名)からRGBに変換出来ません。prm_str_color="<<prm_str_color);
        } else {
            _hex = GgafRgb::_cname[prm_str_color];
            if (_hex[0] == '#') {
                _hex.erase(_hex.begin());
            }
            _is_valid = true;
            _RED = UTIL::hex2dec(_hex.substr(0, 2));
            _GREEN = UTIL::hex2dec(_hex.substr(2, 2));
            _BLUE = UTIL::hex2dec(_hex.substr(4, 2));
            _r = _RED / 255.0f;
            _g = _GREEN / 255.0f;
            _b = _BLUE / 255.0f;
        }

    }
}

std::string GgafRgb::toStr() {
    std::ostringstream oss;
    oss << "#" << UTIL::dec2hex(_RED,2) <<
                  UTIL::dec2hex(_GREEN,2) <<
                  UTIL::dec2hex(_BLUE,2);
    return oss.str();
}
