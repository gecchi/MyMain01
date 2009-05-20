#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace GgafDx9LibStg;
using namespace MyStg2nd;

OptionMagic::OptionMagic(const char* prm_name,
             GgafDx9UntransformedActor* prm_pCaster,
             GgafDx9UntransformedActor* prm_pReceiver) : DefaultMagic(prm_name, prm_pCaster, prm_pReceiver) {

}

OptionMagic::~OptionMagic() {
}
