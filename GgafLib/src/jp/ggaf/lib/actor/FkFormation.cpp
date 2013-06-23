#include "stdafx.h"
#include "jp/ggaf/lib/actor/FkFormation.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

FkFormation::FkFormation(const char* prm_name, frame prm_offset_frames_end) :
        GgafDxFkFormation(prm_name, prm_offset_frames_end)
{
}

FkFormation::~FkFormation() {
}
