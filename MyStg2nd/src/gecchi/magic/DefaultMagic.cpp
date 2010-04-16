#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

DefaultMagic::DefaultMagic(const char* prm_name,
             GgafDx9GeometricActor* prm_pCaster,
             GgafDx9GeometricActor* prm_pReceiver) : Magic(prm_name, prm_pCaster, prm_pReceiver) {

}

DefaultMagic::~DefaultMagic() {
}
