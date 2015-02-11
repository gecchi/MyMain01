#include <actor/Zako001.h>
#include "MgrWorld.h"

#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"
#include "jp/ggaf/lib/util/CollisionChecker3D.h"
#include "jp/ggaf/lib/util/LinearOctreeForActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "util/MgrUtil.h"
#include "jp/ggaf/core/util/GgafRepeatSeq.h"
#include "jp/ggaf/core/util/GgafTable.h"


using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace Mogera;

#define MGR_MIKATA (0x01U)
#define MGR_TEKI   (0x10U)

std::string MgrWorld::key_="ABCDEFG";


MgrWorld::MgrWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pTeki_ = NEW Zako("Zako");
    getSceneDirector()->addSubGroup(MGR_TEKI, pTeki_);

    vb_ = NEW VirtualButton();
    vb_->remap_VB_BUTTON1(VBK_SPACE, VBJ_BUTTON_01);
    vb_->remap_VB_UI_DEBUG(VBK_Q);
}

void MgrWorld::initialize() {
    pTeki_->position(0, PX_C(240)/2);
}

void MgrWorld::processBehavior() {
    //キャラをボタン入力で移動
    vb_->update(); //入力状況更新
    //ワイヤフレーム表示切替
    if (vb_->isPushedDown(VB_UI_DEBUG)) {
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }
}

void MgrWorld::processJudgement() {
    //当たり判定チェック
    CollisionChecker3D::_pLinearOctree->executeAllHitChk(MGR_MIKATA, MGR_TEKI);
    //executeAllHitChk は processJudgement() で呼ぶ必要あり
    //(processBehavior())ではまだ登録されていない)
}

MgrWorld::~MgrWorld() {
//    GGAF_DELETE(pBarVal_);
}

