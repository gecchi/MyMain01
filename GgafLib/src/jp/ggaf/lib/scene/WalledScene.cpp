#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;

WalledScene::WalledScene(const char* prm_name) : ScrolledScene(prm_name) {
    _class_name = "WalledScene";
    _pDepo_WallAAB = NULL;
    _pDepo_WallAAPrism = NULL;
    _pLastSectionScene = NULL;
    _is_all_active_section_scenes = false;
}

void WalledScene::buildWalledScene(
        coord prm_wall_dep, int prm_wall_width, int prm_wall_height,
        WalledSectionScene** prm_papSection, int prm_section_num,
        GgafActorDepository* prm_pDepo_WallAAB,
        GgafActorDepository* prm_pDepo_WallAAPrism) {
    _TRACE_("WalledScene::buildWalledScene ["<<getName()<<"] build...");
    _pDepo_WallAAB = prm_pDepo_WallAAB;
    _pDepo_WallAAPrism = prm_pDepo_WallAAPrism;
    if (_pDepo_WallAAB->getPlatformScene()) {
        //既に所属しているならばOK
    } else {
        getDirector()->addSubGroup(_pDepo_WallAAB); //仮所属 initialize() で本所属
    }
    if (_pDepo_WallAAPrism) {
        if (_pDepo_WallAAPrism->getPlatformScene()) {
            //既に所属しているならばOK
        } else {
            getDirector()->addSubGroup(_pDepo_WallAAPrism); //仮所属 initialize() で本所属
        }
    }
    for (int i = 0; i < prm_section_num; i++) {
        addSubLast(prm_papSection[i]); //配下シーンに所属
        prm_papSection[i]->config(_pDepo_WallAAB, _pDepo_WallAAPrism, prm_wall_dep, prm_wall_width, prm_wall_height);
        prm_papSection[i]->inactivateImmed();
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
            for (int j = 0; j < pSection->_paWallInfoLen[pSection->_area_len-1]; j++) {
                pSection->_papaWallInfo[pSection->_area_len-1][j]._wall_draw_face &= 62; //FACE_Fを潰す 0b111110
            }
        }
        //中間、最後、各セクションの最前ブロック面の全BOXのFACE_B描画を潰す
        for (int i = 1; i < prm_section_num; i++) {
            WalledSectionScene* pSection = prm_papSection[i];
            for (int j = 0; j < pSection->_paWallInfoLen[0]; j++) {
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
    if (_pDepo_WallAAB == NULL) {
        throwGgafCriticalException("WalledScene["<<getName()<<"] オブジェクトが未完成です。buildWalledScene()を実行し構築してください。");
    }
    //buildWalledScene が継承クラスのコンストラクタで実行された場合、getDirector() は世界シーンを返すため
    //壁デポジトリの所属シーンは世界シーン所属になっている可能性がある。、
    //スクロール制御を行うためにも、壁デポジトリ は this の配下に置く必要があるため、以下の様に
    //配下シーンに再設定する。
    getDirector()->addSubGroup(_pDepo_WallAAB->extract());
    if (_pDepo_WallAAPrism) {
        getDirector()->addSubGroup(_pDepo_WallAAPrism->extract());
    }
}

void WalledScene::onActive() {
    WalledSectionScene* pCurrentSection = _ringHoldSection.getCurrent();
    pCurrentSection->activate();
}

void WalledScene::processBehavior() {
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
    ScrolledScene::processBehavior();

    //_ringLoopEndSectionチェック
    //WallPartsActor::_pWalledSectionScene が不正ポインタにならないための考慮である。
    for (int i = 0; i < _ringLoopEndSection.length(); i++) {
        WalledSectionScene* pSection =_ringLoopEndSection.next();
        if (pSection->_pWallPartsLast->_pWalledSectionScene != pSection || !pSection->_pWallPartsLast->isActive() ) {
            //＜メモ＞
            //pSection->_pWallPartsLast->_pWalledSectionScene != pSection は、
            //pSection->_pWallPartsLast つまり最終壁の紐付くセクションはが自分でない、
            //つまり、他のセクションシーンに dispatchForce() されたからOK、と考えた。
            //また、!pSection->_pWallPartsLast->isActive() は
            //他のセクションシーンに dispatchForce() されずに、活動範囲外に消えたからOK、と考えた。
            pSection->end(60*10); //解放！
            _TRACE_("WalledScene::processBehavior() ["<<getName()<<"]シーンのセクション["<<pSection->getName()<<"]をend!!");
            _ringLoopEndSection.remove();
            if (pSection == _pLastSectionScene) {
                //最終セクションならば自身のシーンも解放
                end(60*20);
                _TRACE_("WalledScene::processBehavior() 最終セクションシーンだったため。["<<getName()<<"]シーン自身もend!!");
            }
        }
    }

}

void WalledScene::processFinal() {
}

WalledScene::~WalledScene() {
}
