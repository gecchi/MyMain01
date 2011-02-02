#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace  GgafDx9LibStg;

QuantityUnit::QuantityUnit(float prm_max_val_px, float prm_max_val) : GgafObject() {
    _max_val_px = prm_max_val_px;
    _max_val = prm_max_val;
    _val = 0.0f;
    _val_px = 0.0f;
}
QuantityUnit::QuantityUnit() : GgafObject() {
    _max_val_px = 100.0f;
    _max_val = 100.0f;
    _val = 0.0f;
    _val_px = 0.0f;
}

void QuantityUnit::config(float prm_max_val_px, float prm_max_val) {
    _max_val_px = prm_max_val_px;
    _max_val = prm_max_val;
}

QuantityUnit::~QuantityUnit() {
}
