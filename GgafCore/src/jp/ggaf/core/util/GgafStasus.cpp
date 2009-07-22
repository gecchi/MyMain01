#include "stdafx.h"
using namespace std;

using namespace GgafCore;

int GgafStatus::get(int n) {
    return _pa_val[n];
}


void GgafStatus::set(int n, int val) {
    _pa_val[n] = val;
}
