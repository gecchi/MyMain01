/////////////////////////////////////////////////////////
// Frm_Material.h
//
//
/////////////////////////////////////////////////////////

#ifndef FRM_MATERIAL_H
#define FRM_MATERIAL_H
#include "GgafDxCommonHeader.h"

#include "jp/ggaf/dx/util/XFile/framework/frm_types.h"
#include <stdio.h>
#include <string>
#include <string.h>
namespace Frm {

class Material {
public:
    //tsuge add bigin --->
    Material() {
    }
    //<--- tsuge add bigin

    bool IsName(std::string &pText) {
        if (strcmp(pText.c_str(), _Name.c_str()) == 0)
            return true;
        return false;
    }
    std::string _Name;
    Color4 _FaceColor;
    float _power;
    Color3 _SpecularColor, _EmissiveColor;
    uint32_t _TextID;
    std::string _TextureName;
};

}
#endif
