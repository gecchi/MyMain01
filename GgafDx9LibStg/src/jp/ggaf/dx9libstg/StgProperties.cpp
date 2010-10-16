#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

string* StgProperties::DIR_SCENE_DATA = NULL;


void StgProperties::load(string prm_ini_filename) {
    GgafDx9Properties::load(prm_ini_filename);
    DIR_SCENE_DATA      = getStr("DIR_SCENE_DATA");


    _TRACE_("STG_PROPERTY(DIR_SCENE_DATA)="<<STG_PROPERTY(DIR_SCENE_DATA));
}

void StgProperties::clean() {
    GgafDx9Properties::clean();
    DELETE_IMPOSSIBLE_NULL(DIR_SCENE_DATA);
}
