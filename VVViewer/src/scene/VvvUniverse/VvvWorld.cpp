#include "stdafx.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker");
    getDirector()->addSubGroup(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor_");
    getDirector()->addSubGroup(pCursor_);

    vb_ = NEW VirtualButton();
}

void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新

    if (GgafDxInput::isPushedDownKey(DIK_F1)) {
        VvvCamera* pCam = P_CAM;
        pCamWorker_->move_target_X_CAM_ = 0;
        pCamWorker_->move_target_Y_CAM_ = 0;
        pCamWorker_->move_target_Z_CAM_ = DX_C(pCam->_cameraZ_org);
        pCamWorker_->move_target_X_VP_ =  0;
        pCamWorker_->move_target_Y_VP_ =  0;
        pCamWorker_->move_target_Z_VP_ =  0;
        pCamWorker_->move_target_XY_CAM_UP_ = D90ANG;
    } else if (GgafDxInput::isPushedDownKey(DIK_F2)) {
        if (_list.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(_list.getCurrent());
            } else {
                pCursor_->moveTo(_list.next());
            }
            _list.getCurrent()->effectFlush(30);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_RETURN)) {
        if (_list.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(_list.getCurrent());
            } else {
                pCursor_->moveTo(_list.next());
            }
            _list.getCurrent()->effectFlush(30);
        }
        GgafDxDrawableActor* pT = _list.getCurrent();
        pCamWorker_->move_target_X_VP_ =  pT->_X;
        pCamWorker_->move_target_Y_VP_ =  pT->_Y;
        pCamWorker_->move_target_Z_VP_ =  pT->_Z;
        pCamWorker_->move_target_XY_CAM_UP_ = D90ANG;
    } else if (GgafDxInput::isPushedDownKey(DIK_Q)) {
        if (_list.length() > 0) {
            _list.remove()->end();
        }
        if (_list.length() > 0) {
            pCursor_->moveTo(_list.getCurrent());
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_W)) {
        //ワイヤフレーム表示切替
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
    }


    if (_list.length() > 0) {
        GgafDxDrawableActor* pActor =  _list.getCurrent();
        int d = 1;
        if (GgafDxInput::isBeingPressedKey(DIK_SPACE) || GgafDxInput::isBeingPressedKey(DIK_LCONTROL) || GgafDxInput::isBeingPressedKey(DIK_RCONTROL)) {
            d = 10;
        } else {
            d = 1;
        }

        if (GgafDxInput::isBeingPressedKey(DIK_A)) {
            //α
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                if (pActor->getAlpha() > 1.00) {
                    pActor->setAlpha(1.00);
                } else {
                    pActor->addAlpha(0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                if (pActor->getAlpha() < 0.00) {
                    pActor->setAlpha(0.00);
                } else {
                    pActor->addAlpha(-0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                if (pActor->getAlpha() > 1.00) {
                    pActor->setAlpha(1.00);
                } else {
                    pActor->addAlpha(0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                if (pActor->getAlpha() < 0.00) {
                    pActor->setAlpha(0.00);
                } else {
                    pActor->addAlpha(-0.01);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->addAlpha(1.00);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_P)) {
            //スペキュラー
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_pModel->_specular += 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_pModel->_specular -= 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_pModel->_specular_power += 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_pModel->_specular_power -= 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_pModel->_specular = 0.00f;
                pActor->_pModel->_specular_power = 0.00f;
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_S)) {
            //拡大縮小
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->addScale(d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->addScale(-d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->addScale(d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->addScale(-d*10);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->setScaleR(1.0);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_R)) {
            //軸回転
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->_RX += D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_RX -= D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_RZ += D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_RZ -= D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_RY += D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_RY -= D_ANG(d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_RX = 0;
                pActor->_RY = 0;
                pActor->_RZ = 0;
            }
        } else {
            //平行移動
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->_Z += PX_C(d); //奥
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_Z -= PX_C(d); //手前
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_X += PX_C(d); //右
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_X -= PX_C(d); //左
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_Y += PX_C(d); //上
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_Y -= PX_C(d); //下
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_X = 0;
                pActor->_Y = 0;
                pActor->_Z = 0;
            }
        }

        if ( Obj_GgafDxMorphMeshActor & pActor->_obj_class) {
            DefaultMorphMeshActor* pMorphMeshActor = dynamic_cast<DefaultMorphMeshActor*>(pActor);
            if (pMorphMeshActor) {
                for (int i = 1; i <= pMorphMeshActor->_pMorphMeshModel->_morph_target_num; i++) {
                    if (GgafDxInput::isBeingPressedKey(DIK_1 + (i-1))) {
                        pMorphMeshActor->_pMorpher->addWeight(i, 0.01);
                    } else {
                        pMorphMeshActor->_pMorpher->addWeight(i, -0.01);
                    }
                }
                pMorphMeshActor->_pMorpher->behave();
            }
        }
    }

    if (VvvGod::is_wm_dropfiles_) {
        string dropfile_dir = GgafCore::GgafUtil::getFileDirName(VvvGod::dropfiles_) + "/";
        string model_id = GgafCore::GgafUtil::getFileBaseNameWithoutExt(VvvGod::dropfiles_);
        string model_type = GgafCore::GgafUtil::getFileExt(VvvGod::dropfiles_);
        _TRACE_("dropfile_dir="<<dropfile_dir);
        _TRACE_("model_id="<<model_id);
        _TRACE_("model_type="<<model_type);

        //プロパティ一時退避
        string dir_mesh_model0 = GGAF_PROPERTY(DIR_MESH_MODEL[0]);
        string dir_mesh_model1 = GGAF_PROPERTY(DIR_MESH_MODEL[1]);
        string dir_sprite_model0 = GGAF_PROPERTY(DIR_SPRITE_MODEL[0]);
        string dir_sprite_model1 = GGAF_PROPERTY(DIR_SPRITE_MODEL[1]);
        string dir_texture0 = GGAF_PROPERTY(DIR_TEXTURE[0]);
        string dir_texture1 = GGAF_PROPERTY(DIR_TEXTURE[1]);
        //プロパティ書き換え
        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = dropfile_dir;
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = dropfile_dir;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = dropfile_dir;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = dropfile_dir;
        GGAF_PROPERTY(DIR_TEXTURE[0])      = dropfile_dir;
        GGAF_PROPERTY(DIR_TEXTURE[1])      = dropfile_dir + "/../" + GGAF_PROPERTY(DIRNAME_RESOURCE_SKIN_XXX_TEXTURE) + "/";
        transform(model_type.begin(), model_type.end(), model_type.begin(), static_cast<int (*)(int)>(toupper));

        GgafDxDrawableActor* pActor = NULL;
        if (model_type == "X") {
            if (model_id.length() > 2 && model_id.substr(model_id.length()-2) == "_0") {
                //model_id = "donatu_0"
                string model_part = model_id.substr(0,model_id.length()-2);
                //model_part = "donatu"
                int targetnum = 0;
                while (true) {
                    string model_filenm = model_part + "_" + ITOS(targetnum+1) + ".x";
                    //model_filenm = "donatu_1.x"
                    string model_path = dropfile_dir + "/" + model_filenm;
                    if (PathFileExists(model_path.c_str())) {
                        targetnum++;
                    } else {
                        break;
                    }
                }
                pActor = createInFactory2(GgafLib::DefaultMorphMeshActor, "actor",
                                          string(ITOS(targetnum) + "/" +model_part).c_str());
                //モーフ
            } else {

//            if (model_id.find("WORLDBOUND") == string::npos) {
//                pActor = createInFactory2(GgafLib::WorldBoundActor, "actor", filename);
//            } else {
                pActor = createInFactory2(GgafLib::DefaultMeshActor, "actor", model_id.c_str());
//            }
            }
        } else if (model_type == "SPRX") {
            pActor = createInFactory2(GgafLib::DefaultSpriteActor, "actor", model_id.c_str());
        } else if (model_type == "PSPRX") {
            pActor = createInFactory2(GgafLib::DefaultPointSpriteActor, "actor", model_id.c_str());
        } else {

        }
        if (pActor) {
            getDirector()->addSubGroup(pActor);
            _list.addLast(pActor, false);
            VvvCamera* pCam = P_CAM;
            GgafDxGeometricActor* p = pCam->getViewPoint();

            pActor->locatedBy(p);
        }

        //プロパティ復帰
        GGAF_PROPERTY(DIR_MESH_MODEL[0])   = dir_mesh_model0;
        GGAF_PROPERTY(DIR_MESH_MODEL[1])   = dir_mesh_model1;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[0]) = dir_sprite_model0;
        GGAF_PROPERTY(DIR_SPRITE_MODEL[1]) = dir_sprite_model1;
        GGAF_PROPERTY(DIR_TEXTURE[0])      = dir_texture0;
        GGAF_PROPERTY(DIR_TEXTURE[1])      = dir_texture1;

        VvvGod::is_wm_dropfiles_ = false;
    }
}

VvvWorld::~VvvWorld() {
}
