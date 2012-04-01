#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VioletVreath;

World::World(const char* prm_name) : DefaultScene(prm_name) {
    _class_name = "World";
    _TRACE_("World::World");
    is_create_GameScene_ = false;
    pLabel_Debug_ = NULL;
    pLabel_Aster_ = NULL;
    pLabel_Title_ = NULL;
    //�y�߂��z
    //������Actor��Scene��NEW���͂��Ă͂Ȃ�Ȃ��B
    //�܂��͂��̐�����邱�Ƃ�D�悵�Ȃ��ƁA���낢��ƕs�s��������B
}

void World::initialize() {
    _TRACE_("World::initialize()");
    pixcoord cx = GGAF_PROPERTY(GAME_BUFFER_WIDTH)/2;
    pixcoord cy = GGAF_PROPERTY(GAME_BUFFER_HEIGHT)/2;
    pLabel_Title_ = createInFactory(LabelGecchi16Font, "STR01");
    getDirector()->addSubGroup(pLabel_Title_);
    pLabel_Title_->update(PXCO(cx), PXCO(cy - 16),
                            "[ VIOLET VREATH ]", ALIGN_CENTER, VALIGN_MIDDLE);

    pLabel_Wait_ = createInFactory(LabelGecchi16Font, "STR02");
    getDirector()->addSubGroup(pLabel_Wait_);
    pLabel_Wait_->update(PXCO(cx), PXCO(cy + 16),
                            "WATE A MOMENT PLASE...", ALIGN_CENTER, VALIGN_MIDDLE);

    pLabel_Aster_ = createInFactory(LabelGecchi16Font, "ASTER");
    getDirector()->addSubGroup(pLabel_Aster_);
    pLabel_Aster_->update(PXCO(GGAF_PROPERTY(GAME_BUFFER_WIDTH)), 0, "*", ALIGN_RIGHT, VALIGN_TOP);
    pLabel_Aster_->_pFader->beat(60, 30, 0, 0, -1); //�`�J�`�J�_��
#ifdef MY_DEBUG
    ColliAABActor::get();     //�����蔻��̈�\���p�����́A�v�����[�h
    ColliAAPrismActor::get(); //�����蔻��̈�\���p�v���Y���A�v�����[�h
    ColliSphereActor::get();  //�����蔻��̈�\���p���A�v�����[�h
#endif
    pLabel_Debug_ = createInFactory(LabelGecchi16Font, "DebugStr");
    getDirector()->addSubGroup(pLabel_Debug_);

    orderSceneToFactory(1, PreDrawScene, "PreDraw");
    orderSceneToFactory(2, GameScene, "Game");
}

void World::processBehavior() {
    if (is_create_GameScene_) {
        //GameScene�쐬����
        VB->update(); //���͏��X�V
#ifdef MY_DEBUG
        if (P_GOD->_sync_frame_time) {
            _TEXT_("z");
        }
#endif
        if (GgafDxInput::isBeingPressedKey(DIK_Q)) {
            //TODO:�I������
        }
    } else {
        //GameScene�쐬�����܂ő҂�
        if (GgafFactory::chkProgress(1) == 2 && GgafFactory::chkProgress(2) == 2) {
            pPreDrawScene_ = (PreDrawScene*)obtainSceneFromFactory(1);
            addSubLast(pPreDrawScene_);
            pGameScene_ = (GameScene*)obtainSceneFromFactory(2);
            addSubLast(pGameScene_);
            is_create_GameScene_ = true;
            pLabel_Title_->end();
            pLabel_Wait_->end();
            pLabel_Aster_->end();
        } else {
            //�҂��ڂ���
            pLabel_Aster_->_pFader->behave();
        }
    }

#ifdef MY_DEBUG
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
//            ((GgafFactory::CREATING_ORDER->progress_==1) ? GgafFactory::CREATING_ORDER->pObject_Creation_->toString() : "NOTHING"),
            ((GgafFactory::CREATING_ORDER->_progress==1) ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    pLabel_Debug_->update(PXCO(1), PXCO(1), aBufDebug_);
    if (getActivePartFrame() % 60 == 0) {
        _TRACE_("aBufDebug_="<<aBufDebug_);
    }
#else
    sprintf(aBufDebug_, "%05uDRAW / %06uCHK / %07uF / %03.1fFPS / NEW=%d",
            GgafGod::_num_actor_drawing,
            CollisionChecker::_num_check,
            (unsigned int)askGod()->_frame_of_God,
            askGod()->_fps,
            ((GgafFactory::CREATING_ORDER->_progress==1)  ? GgafFactory::CREATING_ORDER->_id : 0)
            );
    pLabel_Debug_->update(PXCO(1), PXCO(1), aBufDebug_);
#endif


}

void World::processJudgement() {
}

World::~World() {
}

