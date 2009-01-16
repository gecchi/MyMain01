#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDx9Core;

string GgafDx9Model::_s_modelname_lastdraw = "";

GgafDx9Model::GgafDx9Model(string prm_model_name) {
    TRACE("GgafDx9Model::GgafDx9Model(" <<  prm_model_name << ")");
	_model_name = prm_model_name;
}

GgafDx9Model::~GgafDx9Model() {
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " start-->");
    TRACE("GgafDx9Model::~GgafDx9Model() " <<  _model_name << " <--end");
}

