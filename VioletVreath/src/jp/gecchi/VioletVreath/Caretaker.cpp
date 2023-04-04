#include "Caretaker.h"

#include "jp/ggaf/lib/util/VirtualButton.h"
#include "jp/ggaf/lib/util/VBReplayRecorder.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/XpmManager.h"
#include "jp/gecchi/VioletVreath/Config.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"

using namespace GgafLib;
using namespace VioletVreath;

VirtualButton* Caretaker::pVbtn_PLAY_ = nullptr;
VirtualButton* Caretaker::pVbtn_UI_ = nullptr;
VirtualButton* Caretaker::pVbtn_active_ = nullptr;
VirtualButton* Caretaker::pVbtn_active_next_frame_ = nullptr;
bool Caretaker::g_should_reboot_ = false;

Caretaker::Caretaker() :
      DefaultCaretaker() {

    pDepoManager_ = NEW DepositoryManager("DepositoryManager");
    pXpmManager_ = NEW XpmManager("XpmManager");
    Caretaker::pVbtn_PLAY_ = NEW VirtualButton(FILE_INPUT_PLAY_REPLAY);
    Caretaker::pVbtn_UI_   = NEW VirtualButton(FILE_INPUT_UI_REPLAY);
#ifdef MY_DEBUG
    pVbtn_PLAY_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_PLAY_REPLAY);
    pVbtn_UI_->_pRpy->setRealtimeOutputFile(FILE_REALTIME_OUTPUT_UI_REPLAY);
    _TRACE_("デバッグリアルタイムリプレイ記録モード○");
#endif
    Caretaker::pVbtn_active_ = Caretaker::pVbtn_UI_;
    Caretaker::pVbtn_active_next_frame_ = Caretaker::pVbtn_UI_;

    if (pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報○、UIリプレイ情報○");
        _TRACE_("→リプレイ再生モードです。");
    } else if (!pVbtn_PLAY_->_is_replaying && pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報×、UIリプレイ情報○");
        _TRACE_("→UIのみ再生モードです。っていうか意味あるのん？");
    } else if (pVbtn_PLAY_->_is_replaying && !pVbtn_UI_->_is_replaying) {
        _TRACE_("プレイリプレイ情報○、UIリプレイ情報×");
        _TRACE_("→リプレイ再生モードです。但し、プレイリプレイから PAUSE情報を切り取ります。");
        //プレイリプレイあり、かつUIリプレイ無しの場合のみ、プレイリプレイのPAUSE情報を除去する
        VBReplayRecorder* pRepPlay = pVbtn_PLAY_->_pRpy;
        VBReplayRecorder::VBRecordNote* pRecNote = pRepPlay->_pFirstVBNote;
        vb_sta vb_pause_not_mask = ~((vb_sta)VB_PAUSE);
        while (pRecNote) {
            pRecNote->_p1_state = (pRecNote->_p1_state & vb_pause_not_mask);
            pRecNote = pRecNote->_pNext;
        }
    } else {
        _TRACE_("プレイリプレイ情報×、UIリプレイ情報×");
        _TRACE_("リプレイ登録モードです。");
    }

    //ランキング情報読み込み
    G_RANKING_TABLE.init();
    initVB();
}

HRESULT Caretaker::initDevice() {
    MyStgUtil::init();  //ユーティリティ準備
    return DefaultCaretaker::initDevice();
}

void Caretaker::initVB() {
    //仮想ボタンを本ゲーム用に上書きして再定義
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON1   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT1      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT1      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON2   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT2      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT2      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON3   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_OPTION     ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_OPTION     ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON4   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW       ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON5   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_TURBO      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_TURBO      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON6   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_POWERUP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_POWERUP    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON7   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON7    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON7    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_BUTTON8   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON8    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON8    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_PAUSE     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_PAUSE      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_PAUSE      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UP        , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UP         ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UP         ]);
    Caretaker::pVbtn_PLAY_->remap(VB_DOWN      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_DOWN       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_DOWN       ]);
    Caretaker::pVbtn_PLAY_->remap(VB_LEFT      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_LEFT       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_LEFT       ]);
    Caretaker::pVbtn_PLAY_->remap(VB_RIGHT     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_RIGHT      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_RIGHT      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_S1_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_UP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_UP    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_S1_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_DOWN  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_DOWN  ]);
    Caretaker::pVbtn_PLAY_->remap(VB_S1_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_LEFT  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_LEFT  ]);
    Caretaker::pVbtn_PLAY_->remap(VB_S1_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_RIGHT ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_RIGHT ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_UP      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_UP      ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DOWN    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_DOWN    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_LEFT    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_LEFT    ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_RIGHT   ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_RIGHT   ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_EXECUTE, VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_EXECUTE ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_EXECUTE ]);
    Caretaker::pVbtn_PLAY_->remap(VB_UI_CANCEL , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_CANCEL  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_CANCEL  ]);
    Caretaker::pVbtn_PLAY_->remapK(VB_UI_DEBUG  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DEBUG   ]  );

    Caretaker::pVbtn_UI_->remap(VB_BUTTON1   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT1      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT1      ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON2   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_SHOT2      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_SHOT2      ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON3   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_OPTION     ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_OPTION     ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON4   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW       ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON5   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_TURBO      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_TURBO      ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON6   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_POWERUP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_POWERUP    ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON7   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON7    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON7    ]);
    Caretaker::pVbtn_UI_->remap(VB_BUTTON8   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_BUTTON8    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_BUTTON8    ]);
    Caretaker::pVbtn_UI_->remap(VB_PAUSE     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_PAUSE      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_PAUSE      ]);
    Caretaker::pVbtn_UI_->remap(VB_UP        , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UP         ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UP         ]);
    Caretaker::pVbtn_UI_->remap(VB_DOWN      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_DOWN       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_DOWN       ]);
    Caretaker::pVbtn_UI_->remap(VB_LEFT      , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_LEFT       ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_LEFT       ]);
    Caretaker::pVbtn_UI_->remap(VB_RIGHT     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_RIGHT      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_RIGHT      ]);
    Caretaker::pVbtn_UI_->remap(VB_S1_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_UP    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_UP    ]);
    Caretaker::pVbtn_UI_->remap(VB_S1_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_DOWN  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_DOWN  ]);
    Caretaker::pVbtn_UI_->remap(VB_S1_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_LEFT  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_LEFT  ]);
    Caretaker::pVbtn_UI_->remap(VB_S1_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_VIEW_RIGHT ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_VIEW_RIGHT ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_UP     , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_UP      ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_UP      ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_DOWN   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DOWN    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_DOWN    ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_LEFT   , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_LEFT    ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_LEFT    ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_RIGHT  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_RIGHT   ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_RIGHT   ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_EXECUTE, VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_EXECUTE ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_EXECUTE ]);
    Caretaker::pVbtn_UI_->remap(VB_UI_CANCEL , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_CANCEL  ], VirtualButton::_mapStr2VBJ[ CONFIG::MY_JOY_UI_CANCEL  ]);
    Caretaker::pVbtn_UI_->remapK(VB_UI_DEBUG  , VirtualButton::_mapStr2VBK[ CONFIG::MY_KEY_UI_DEBUG   ] );

}

GgafCore::Spacetime* Caretaker::createSpacetime() {
    Camera* pCamera = NEW Camera("CAMERA");
    Spacetime* pSpacetime = NEW Spacetime("MYSPACETIME", pCamera);
    return (GgafCore::Spacetime*)pSpacetime;
}

void Caretaker::clean() {
    if (!_was_cleaned) {
        if (VB_PLAY->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_REPADD.rep");
#endif
        } else {
            VB_PLAY->_pRpy->outputFile(FILE_OUTPUT_PLAY_REPLAY);
        }
        if (VB_UI->_is_replaying) {
#ifdef MY_DEBUG
            VB_PLAY->_pRpy->outputFile("VB_UI_LAST_REPADD.rep");
#endif
        } else {
            VB_UI->_pRpy->outputFile(FILE_OUTPUT_UI_REPLAY);
        }
        _TRACE_(FUNC_NAME<<" begin");
        DefaultCaretaker::clean();
        GGAF_DELETE(pVbtn_PLAY_);
        GGAF_DELETE(pVbtn_UI_);
        GGAF_DELETE(pDepoManager_);
        GGAF_DELETE(pXpmManager_);
        _TRACE_(FUNC_NAME<<" end");
    }
}

void Caretaker::reboot() {
    Caretaker::g_should_reboot_ = true; //再起動フラグセット
    ::PostQuitMessage(0); //終了！
}

void Caretaker::oops() {
    VB_PLAY->_pRpy->outputFile("VB_PLAY_LAST_Oops.rep");
    VB_UI->_pRpy->outputFile("VB_UI_LAST_Oops.rep");
    DefaultCaretaker::oops(); //上位の「しまった！」へ
}

EffectManager* Caretaker::createEffectManager() {
    EffectManager* p = NEW EffectManager("EffectManager");
    return p;
}
CurveSourceManagerEx* Caretaker::createCurveSourceManager() {
    CurveSourceManagerEx* p = NEW CurveSourceManagerEx("CurveSourceManagerEx");
    return p;
}
CurveManufactureManagerEx* Caretaker::createCurveManufactureManager() {
    CurveManufactureManagerEx* p = NEW CurveManufactureManagerEx("CurveManufactureManagerEx");
    return p;
}

Caretaker::~Caretaker() {
    calmDown();
    if (getSpacetime()) {
        World* pWorld = getSpacetime()->getWorld();
        if (pWorld) {
            pWorld->throwEventLowerTree(EVENT_CARETAKER_WILL_DEMISE); //全シーンに通知
        }
    }
    clean();
    _was_cleaned = true;
}

