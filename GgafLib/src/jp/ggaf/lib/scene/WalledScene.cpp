#include "jp/ggaf/lib/scene/WalledScene.h"

#include "jp/ggaf/core/actor/ex/GgafActorDepository.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/lib/scene/WalledSectionScene.h"
#include "jp/ggaf/lib/actor/WallPartsActor.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WalledScene::WalledScene(const char* prm_name) : DefaultScene(prm_name) {
    _obj_class |= Obj_WalledScene;
    _class_name = "WalledScene";
    _pDepo_wall = nullptr;
    _pDepo_prism = nullptr;
    _pLastSectionScene = nullptr;
    _is_all_active_section_scenes = false;
    _is_finished = false;
}

void WalledScene::buildWalledScene(
        coord prm_wall_dep, coord prm_wall_width, coord prm_wall_height,
        coord prm_wall_start_x,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_wall,
        GgafActorDepository* prm_pDepo_prism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    setScrollingFunction(WalledScene::scrollX);

    _pDepo_wall = prm_pDepo_wall;
    _pDepo_prism = prm_pDepo_prism;
    if (_pDepo_wall->getPlatformScene()) {
        //既に所属しているならばOK
    } else {
        getSceneDirector()->addSubGroup(_pDepo_wall); //仮所属 initialize() で本所属
    }
    if (_pDepo_prism) {
        if (_pDepo_prism->getPlatformScene()) {
            //既に所属しているならばOK
        } else {
            getSceneDirector()->addSubGroup(_pDepo_prism); //仮所属 initialize() で本所属
        }
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //配下シーンに所属
        prm_papSection[i]->config(_pDepo_wall, _pDepo_prism,
                                  prm_wall_start_x,
                                  prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivate();
        _ringHoldSection.addLast(prm_papSection[i], false);
    }
    // 0b 00abcdef
    //
    //    c
    // a b d f
    //      e
    //
    //    FACE_A_BIT = 0b100000
    //    FACE_B_BIT = 0b010000
    //    FACE_C_BIT = 0b001000
    //    FACE_D_BIT = 0b000100
    //    FACE_E_BIT = 0b000010
    //    FACE_F_BIT = 0b000001
    //    A          = 0b111110 = 62
    //    A          = 0b101111 = 47

    //セクションつなぎ目のBOX描画の処理
    if (prm_section_num >= 2) {
        //最初、中間、各セクションの最末尾ブロック面の全BOXのFACE_F描画を潰す
        for (int i = 0; i < prm_section_num-1; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[pSection->_area_len-1];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_Fを潰す 0b111110
            }
        }
        //中間、最後、各セクションの最前ブロック面の全BOXのFACE_B描画を潰す
        for (int i = 1; i < prm_section_num; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            int len = pSection->_paWallInfoLen[0];
            for (int j = 0; j < len; j++) {
                pSection->_papaWallInfo[0][j]._wall_draw_face &= 47; //FACE_Bを潰す 0b111110
            }
        }
    }
    _ringHoldSection.first();
    _is_all_active_section_scenes = false;
    _pLastSectionScene = prm_papSection[prm_section_num-1];
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] done");
}

void WalledScene::initialize() {
    if (_pDepo_wall == nullptr) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] オブジェクトが未完成です。buildWalledScene()を実行し構築してください。");
    }
    //buildWalledScene が継承クラスのコンストラクタで実行された場合、getSceneDirector() は世界シーンを返すため
    //壁デポジトリの所属シーンは世界シーン所属になっている可能性がある。、
    //スクロール制御を行うためにも、壁デポジトリ は this の配下に置く必要があるため、以下の様に
    //配下シーンに再設定する。
    getSceneDirector()->addSubGroup(_pDepo_wall->extract());
    if (_pDepo_prism) {
        getSceneDirector()->addSubGroup(_pDepo_prism->extract());
    }
}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {

    if (!_is_finished) {
        if (!_is_all_active_section_scenes) {

            WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
            if (!pCurrentSection->isLast()) {
                if (pCurrentSection->_is_loop_end) {
                    WalledSectionScene* pNewSection = _ringHoldSection.next();
                    pNewSection->activate();
                    pNewSection->_pWallPartsLast = pCurrentSection->getLastWallParts();
                    _ringLoopEndSection.addLast(pCurrentSection, false);
                }
            } else {
                if (pCurrentSection->_is_loop_end) {
                    _ringLoopEndSection.addLast(pCurrentSection, false);
                    _is_all_active_section_scenes = true;
                }
            }
        }

        //_ringLoopEndSectionチェック
        //WallPartsActor::_pWalledSectionScene が不正ポインタにならないための考慮である。
        for (int i = 0; i < _ringLoopEndSection.length(); i++) { //_ringLoopEndSection.length()をローカル変数に置き換えてはいけません
            WalledSectionScene* pSection =_ringLoopEndSection.next();
            if (pSection->_pWallPartsLast->_pWalledSectionScene != pSection || !pSection->_pWallPartsLast->isActive() ) {
                //＜メモ＞
                //pSection->_pWallPartsLast->_pWalledSectionScene != pSection は、
                //pSection->_pWallPartsLast つまり最終壁の紐付くセクションはが自分でない、
                //つまり、他のセクションシーンに dispatchForce() されたからOK、と考えた。
                //また、!pSection->_pWallPartsLast->isActive() は
                //他のセクションシーンに dispatchForce() されずに、活動範囲外に消えたからOK、と考えた。
                _TRACE_("WalledScene::processBehavior() ["<<getName()<<"] シーンのセクション["<<pSection->getName()<<"]inactivate!!");
                pSection->inactivateDelay(60*60);
                _ringLoopEndSection.remove();
                if (pSection == _pLastSectionScene) {
                    //最終セクションならば一度コールバックを行い、処理を任せる。
                    //（以前はここでsayonara()をしていた）
                    _TRACE_("WalledScene::processBehavior() ["<<getName()<<"] 最終セクションシーンだったためonFinishedAllSection() コールバック");
                    _is_finished = true;
                    onFinishedAllSection(); //コールバック
                }
            }
        }
    } else {
    }

}

void WalledScene::processFinal() {
}

void WalledScene::scrollX(GgafObject* pThat, void* p1, void* p2) {
    if (pThat->instanceOf(Obj_GgafDxGeometricActor)) {
        GgafDxGeometricActor* pActor = (GgafDxGeometricActor*)pThat;
        if (pActor->_is_active_flg && !pActor->_was_paused_flg && pActor->_can_live_flg) {
            pActor->_x -= (*((coord*)p1));
        }
    }
}

WalledScene::~WalledScene() {
}
