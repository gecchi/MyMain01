#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;



GgafDx9Model::GgafDx9Model(char* prm_model_name) : GgafObject() {
    TRACE("GgafDx9Model::GgafDx9Model(" <<  prm_model_name << ")");
    _id = GgafDx9God::_pModelManager->getNextId();
    _model_name = NEW char[51];
	strcpy(_model_name, prm_model_name);
}

GgafDx9Model::~GgafDx9Model() {
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " start-->");
    DELETEARR_IMPOSSIBLE_NULL(_model_name);
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " <--end");
}

