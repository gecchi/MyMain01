#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;

FormationActor::FormationActor(const char* prm_name, DWORD prm_frame_offset_adios) :
    GgafDx9GeometricActor(prm_name, NULL)
{
    _class_name = "FormationsActor";
    _frame_offset_adios = prm_frame_offset_adios;
    setBumpable(false);
}

FormationActor::~FormationActor() {
}
