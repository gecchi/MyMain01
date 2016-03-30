#include "VvvWorld.h"

#include <algorithm>
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/actor/camera/GgafDxCameraViewPoint.h"
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"
#include "jp/ggaf/lib/GgafLibProperties.h"
#include "jp/ggaf/lib/util/VirtualButton.h"
#include "VvvGod.h"
#include "actor/CamWorker/VvvCamWorker.h"
#include "actor/VvvCursor.h"
#include "actor/VvvGrid.h"
#include "actor/VvvCamera.h"
#include "actor/Font01.h"
#include "jp/ggaf/dxcore/util/GgafDx26DirectionUtil.h"
using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker", P_GOD->getSpacetime()->getCamera());
    bringDirector()->addSubGroup(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor");
    bringDirector()->addSubGroup(pCursor_);
    pGrid_ = NEW VvvGrid("GRID");
    bringDirector()->addSubGroup(pGrid_);
    vb_ = NEW VirtualButton();
    pFont01_info_ =  NEW Font01("Font01");
    bringDirector()->addSubGroup(pFont01_info_);
    pFont01_help_ =  NEW Font01("Font01");
    bringDirector()->addSubGroup(pFont01_help_);
    view_help_ = true;
    view_info_ = true;
}

void VvvWorld::initialize() {
     pFont01_help_->setAlign(ALIGN_CENTER, VALIGN_MIDDLE);
     pFont01_help_->setMaterialColor(1.0,0.5,0.2);
     pFont01_help_->update(PX_C(-8), PX_C(8), PX_C(0),
             "[F1]:Move to the initial position the camera.\n"
             "[F2]:Target to next model, and directed camera.\n"
             "[F3]:Target to next model.\n"
             "[F4]:Directed camera toward active model.\n"
             "[DELETE]:Remove active model.\n"
             "[CursorKey]:Move model up/right/down/left.\n"
             "[PgUp/PgDown]: Move model near/far. (Z axis)\n"
             "[ESC]:Move to position (0, 0, 0).\n"
             "[R]+[CursorKey]:Z or Y Axial rotation model.\n"
             "[R]+[PgUp/PgDown]:X Axial rotation model.\n"
             "[S]+[PgUp/PgDown]:Scale inc or dec.\n"
             "[S]+[X]+[CursorKey]:X or Y Axial Scale inc or dec.\n"
             "[S]+[X]+[PgUp/PgDown]:Z Axial Scale inc or dec.\n"
             "[W]:Toggle effect Wireframe.\n"
             "[G]:Toggle display grid.\n"
             "[O]:Toggle effect \"DestBlend = One/InvSrcAlpha\".\n"
             "[Z]:Toggle effect \"Zwriteenable = True/False\".\n"
             "[A]+[CursorKey]:Effect AlphaBlend inc or dec.\n"
             "[P]+[RIGHT/LEFT]:Effect SpecularRange inc or dec.\n"
             "[P]+[UP/DOWN]:Effect SpecularPower inc or dec.\n"
             "[J/K/L]+[CursorKey]:Material red/green/blue Color inc or dec.\n"
             "[C]+[CursorKey]:Cube mapping reflectance inc or dec.\n"
             "[1]-[6]+[CursorKey]:Morph to taget No model, weight inc or dec.\n"
             "...+[SPACE or Ctrl]:Accretion inc or dec.\n"
             "...+[ESC]:Reset init.\n"
             "[I]:Toggle display active model properties infomation.\n"
             "[H]:Toggle display this help."
             );

     pFont01_info_->setAlign(ALIGN_LEFT, VALIGN_BOTTOM);
     pFont01_info_->update(0, PX_C(PROPERTY::GAME_BUFFER_HEIGHT), "");
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新

    if (GgafDxInput::isPushedDownKey(DIK_F1)) {
        //カメラを初期位置へ
        VvvCamera* const pCam = P_GOD->getSpacetime()->getCamera();;
        pCamWorker_->slideMvCamTo(0,0,DX_C(pCam->getZOrigin()),60);
        pCamWorker_->slideMvVpTo(0,0,0,60);
       // pCam->auto_up_wait_frames = 65;

    } else if (GgafDxInput::isPushedDownKey(DIK_F2)) {
        //ターゲット変更＋カメラ向く
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(listActorInfo_.next()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
            GgafDxFigureActor* pT = listActorInfo_.getCurrent()->pActor_;
            pCamWorker_->slideMvVpTo(pT->_x, pT->_y, pT->_z, 60);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_F3)) {
       //ターゲット変更のみ
       if (listActorInfo_.length() > 0) {
           if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
               pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
           } else {
               pCursor_->moveTo(listActorInfo_.next()->pActor_);
           }
           listActorInfo_.getCurrent()->pActor_->effectFlush(30);
       }
    } else if (GgafDxInput::isPushedDownKey(DIK_F4)) {
        //現ターゲットへカメラ向く
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
            GgafDxFigureActor* pT = listActorInfo_.getCurrent()->pActor_;
            pCamWorker_->slideMvVpTo(pT->_x, pT->_y, pT->_z, 60);
        }
     } else if (GgafDxInput::isPushedDownKey(DIK_DELETE)) {
        //選択を削除
        if (listActorInfo_.length() > 0) {
            listActorInfo_.getCurrent()->pActor_->end();
            listActorInfo_.remove();
        }
        if (listActorInfo_.length() > 0) {
            pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_W)) {
        //ワイヤフレーム表示切替
        if (GgafDxGod::_d3dfillmode == D3DFILL_WIREFRAME) {
            GgafDxGod::_d3dfillmode = D3DFILL_SOLID;
        } else {
            GgafDxGod::_d3dfillmode = D3DFILL_WIREFRAME;
        }
        GgafDxGod::_pID3DDevice9->SetRenderState(D3DRS_FILLMODE, GgafDxGod::_d3dfillmode);
    } else if (GgafDxInput::isPushedDownKey(DIK_G)) {
        //グリッド表示非表示
        if (pGrid_->isActive()) {
            pGrid_->inactivate();
        } else {
            pGrid_->activate();
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_O)) {
        //加算合成有り無し
        if (listActorInfo_.length() > 0) {
            GgafDxFigureActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_is_temp_technique) {
                pA->effectDefault();
            } else {
                pA->effectBlendOne();
            }
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_Z)) {
        //自身のZバッファを書き込みする無し
        if (listActorInfo_.length() > 0) {
            GgafDxFigureActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_zwriteenable) {
                pA->setZWriteEnable(false); //自身のZバッファを書き込みしない
            } else {
                pA->setZWriteEnable(true);  //自身のZバッファを書き込みする
            }
        }
    }

    if (listActorInfo_.length() > 0) {
        GgafDxFigureActor* pActor =  listActorInfo_.getCurrent()->pActor_;
        _TRACE_("pActor->isOutOfView()="<<pActor->isOutOfView());
        int d = 1;
        if (GgafDxInput::isBeingPressedKey(DIK_SPACE) || GgafDxInput::isBeingPressedKey(DIK_LCONTROL) || GgafDxInput::isBeingPressedKey(DIK_RCONTROL)) {
            d = 10;
        } else {
            d = 1;
        }
        if (GgafDxInput::isBeingPressedKey(DIK_A)) {
            //α増減
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->addAlpha(0.01*d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->addAlpha(-0.01*d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->addAlpha(0.01*d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->addAlpha(-0.01*d);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->addAlpha(1.00); //αリセット
            }
            if (pActor->getAlpha() < 0.00) {
                pActor->setAlpha(0.00);
            }
            if (pActor->getAlpha() > 1.00) {
                pActor->setAlpha(1.00);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_P)) {
            //スペキュラー
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->getModel()->_specular += 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->getModel()->_specular -= 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->getModel()->_specular_power += 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->getModel()->_specular_power -= 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->getModel()->_specular = 0.00f;
                pActor->getModel()->_specular_power = 0.00f;
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_P)) {
            //スペキュラー
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->getModel()->_specular += 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->getModel()->_specular -= 0.05*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->getModel()->_specular_power += 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->getModel()->_specular_power -= 0.01*d;
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->getModel()->_specular = 0.00f;
                pActor->getModel()->_specular_power = 0.00f;
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_S)) {
            if (GgafDxInput::isBeingPressedKey(DIK_X)) {
                //各軸拡大縮小
                if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                    pActor->addScaleX(d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                    pActor->addScaleX(-d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                    pActor->addScaleY(d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                    pActor->addScaleY(-d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                    pActor->addScaleZ(d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                    pActor->addScaleZ(-d*10);
                }
            } else {
                //全軸拡大縮小
                if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                    pActor->addScale(d*10);
                }
                if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                    pActor->addScale(-d*10);
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->setScaleR(1.0);
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_R)) {
            //軸回転
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->addRxFaceAng(D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->addRxFaceAng(-D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->addRyFaceAng(D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->addRyFaceAng(-D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->addRzFaceAng(D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->addRzFaceAng(-D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->setFaceAngZero();
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_C)) {
            //環境マップテクスチャ映りこみ率
            if (pActor->instanceOf(Obj_GgafDxCubeMapMeshActor)) {
                CubeMapMeshActor* pCubeMapActor = (CubeMapMeshActor*)pActor;
                if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                    pCubeMapActor->_reflectance += 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                    pCubeMapActor->_reflectance -= 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                    pCubeMapActor->_reflectance += 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                    pCubeMapActor->_reflectance -= 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                    pCubeMapActor->_reflectance = 0.00;
                }
                if (pCubeMapActor->_reflectance < 0.0) {
                    pCubeMapActor->_reflectance = 0.0;
                }
            }
            if (pActor->instanceOf(Obj_GgafDxCubeMapMorphMeshActor)) {
                CubeMapMorphMeshActor* pCubeMapActor = (CubeMapMorphMeshActor*)pActor;
                if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                    pCubeMapActor->_reflectance += 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                    pCubeMapActor->_reflectance -= 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                    pCubeMapActor->_reflectance += 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                    pCubeMapActor->_reflectance -= 0.01*d;
                }
                if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                    pCubeMapActor->_reflectance = 0.00;
                }
                if (pCubeMapActor->_reflectance < 0.0) {
                    pCubeMapActor->_reflectance = 0.0;
                }
                if (pCubeMapActor->_reflectance > 1.0) {
                    pCubeMapActor->_reflectance = 1.0;
                }
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_1) ||
                   GgafDxInput::isBeingPressedKey(DIK_2) ||
                   GgafDxInput::isBeingPressedKey(DIK_3) ||
                   GgafDxInput::isBeingPressedKey(DIK_4) ||
                   GgafDxInput::isBeingPressedKey(DIK_5) ||
                   GgafDxInput::isBeingPressedKey(DIK_6) ||
                   GgafDxInput::isBeingPressedKey(DIK_7)   )
        {
            if(pActor->instanceOf(Obj_GgafDxMorphMeshActor) ) {
                GgafDxMorphMeshActor* pMorphMeshActor = dynamic_cast<GgafDxMorphMeshActor*>(pActor);
                if (pMorphMeshActor) {
                    for (int i = 1; i <= pMorphMeshActor->_morph_target_num; i++) {
                        if (GgafDxInput::isBeingPressedKey(DIK_1 + (i-1))) {
                            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                                pMorphMeshActor->addMorphWeight(i, 0.01*d);
                                if (pMorphMeshActor->getMorphWeight(i) > 1.0) {
                                    pMorphMeshActor->setMorphWeight(i, 1.0);
                                }
                            }
                            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                                pMorphMeshActor->addMorphWeight(i, -0.01*d);
                                if (pMorphMeshActor->getMorphWeight(i) < 0) {
                                    pMorphMeshActor->setMorphWeight(i, 0);
                                }
                            }
                            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                                pMorphMeshActor->addMorphWeight(i, 0.01*d);
                                if (pMorphMeshActor->getMorphWeight(i) > 1.0) {
                                    pMorphMeshActor->setMorphWeight(i, 1.0);
                                }
                            }
                            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                                pMorphMeshActor->addMorphWeight(i, -0.01*d);
                                if (pMorphMeshActor->getMorphWeight(i) < 0) {
                                    pMorphMeshActor->setMorphWeight(i, 0);
                                }
                            }
                            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                                pMorphMeshActor->setMorphWeight(i, 0);
                            }

                        } else {
                            //何もしない
                        }
                    }
                }
            }
        } else if (GgafDxInput::isBeingPressedKey(DIK_J) ||
                   GgafDxInput::isBeingPressedKey(DIK_K) ||
                   GgafDxInput::isBeingPressedKey(DIK_L)   )
        {
            float r = pActor->_paMaterial[0].Ambient.r;
            float g = pActor->_paMaterial[0].Ambient.g;
            float b = pActor->_paMaterial[0].Ambient.b;
            //マテリアル赤色
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT) || GgafDxInput::isBeingPressedKey(DIK_UP)) {
                if (GgafDxInput::isBeingPressedKey(DIK_J)) {
                    pActor->setMaterialRed(r+(0.01*d));
                }
                if (GgafDxInput::isBeingPressedKey(DIK_K)) {
                    pActor->setMaterialGreen(g+(0.01*d));
                }
                if (GgafDxInput::isBeingPressedKey(DIK_L)) {
                    pActor->setMaterialBlue(b+(0.01*d));
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT) || GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                if (GgafDxInput::isBeingPressedKey(DIK_J)) {
                    pActor->setMaterialRed(r-(0.01*d));
                }
                if (GgafDxInput::isBeingPressedKey(DIK_K)) {
                    pActor->setMaterialGreen(g-(0.01*d));
                }
                if (GgafDxInput::isBeingPressedKey(DIK_L)) {
                    pActor->setMaterialBlue(b-(0.01*d));
                }
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->resetMaterialColor();
            }

        } else {       //平行移動
            if (GgafDxInput::isBeingPressedKey(DIK_PGUP)) {
                pActor->_z += PX_C(d); //奥
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_z -= PX_C(d); //手前
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_x += PX_C(d); //右
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_x -= PX_C(d); //左
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_y += PX_C(d); //上
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_y -= PX_C(d); //下
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_x = 0;
                pActor->_y = 0;
                pActor->_z = 0;
            }
        }
    }



    if (VvvGod::is_wm_dropfiles_) {
        string dropfile_dir = UTIL::getFileDirName(VvvGod::dropfiles_) + "/";
        string file_name = UTIL::getFileBaseName(VvvGod::dropfiles_);
        string model_id = UTIL::getFileBaseNameWithoutExt(VvvGod::dropfiles_);
        string model_type = UTIL::getFileExt(VvvGod::dropfiles_);
        _TRACE_("dropfile_dir="<<dropfile_dir);
        _TRACE_("model_id="<<model_id);
        _TRACE_("model_type="<<model_type);

        //プロパティ一時退避
        string dir_mesh_model_default = PROPERTY::DIR_MESH_MODEL[0];
        string dir_mesh_model_user = PROPERTY::DIR_MESH_MODEL[1];
        string dir_mesh_model_current = PROPERTY::DIR_MESH_MODEL[2];
        string dir_sprite_model_default = PROPERTY::DIR_SPRITE_MODEL[0];
        string dir_sprite_model_user = PROPERTY::DIR_SPRITE_MODEL[1];
        string dir_sprite_model_current = PROPERTY::DIR_SPRITE_MODEL[2];
        string dir_texture_default = PROPERTY::DIR_TEXTURE[0];
        string dir_texture_user = PROPERTY::DIR_TEXTURE[1];
        string dir_texture_current = PROPERTY::DIR_TEXTURE[2];
        //プロパティ書き換え
        PROPERTY::DIR_MESH_MODEL[2]   = dropfile_dir;
        PROPERTY::DIR_SPRITE_MODEL[2] = dropfile_dir;
        PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
        PROPERTY::DIR_TEXTURE[1]      = dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
        PROPERTY::DIR_TEXTURE[2]      = dropfile_dir;
        transform(model_type.begin(), model_type.end(), model_type.begin(), static_cast<int (*)(int)>(toupper));

        GgafDxFigureActor* pActor = nullptr;
        std::string modelfile = "";
        if (model_type == "X") {
            if (model_id.length() > 2 && model_id.substr(model_id.length()-2) == "_0") {
                //model_id = "donatu_0"
                string model_part = model_id.substr(0,model_id.length()-2);
                //model_part = "donatu"
                int targetnum = 0;
                while (true) {
                    string model_filenm = model_part + "_" + XTOS(targetnum+1) + ".x";
                    //model_filenm = "donatu_1.x"
                    string model_path = dropfile_dir + "/" + model_filenm;
                    if (PathFileExists(model_path.c_str())) {
                        targetnum++;
                    } else {
                        break;
                    }
                }
                pActor = createInFactory2(GgafLib::DefaultMorphMeshActor, "actor",
                                          string(XTOS(targetnum) + "/" +model_part).c_str());
            } else {
//            if (model_id.find("WORLDBOUND") == string::npos) {
//                pActor = createInFactory2(GgafLib::WorldBoundActor, "actor", filename);
//            } else {
                pActor = createInFactory2(GgafLib::DefaultMeshActor, "actor", model_id.c_str());
//            }
//                DefaultMeshActor* pDefaultMeshActor = (DefaultMeshActor*)pActor;
//                pDefaultMeshActor->setBumpMapTexture("normal.bmp");
            }
        } else if (model_type == "SPRX") {
            pActor = createInFactory2(GgafLib::DefaultSpriteActor, "actor", model_id.c_str());
        } else if (model_type == "PSPRX") {
            pActor = createInFactory2(GgafLib::DefaultPointSpriteActor, "actor", model_id.c_str());
        }

        if (pActor) {
            bringDirector()->addSubGroup(pActor);
            ActorInfo* pActorInfo = NEW ActorInfo(pActor, string(VvvGod::dropfiles_));
            listActorInfo_.addLast(pActorInfo);
            listActorInfo_.last(); //カレントをlastへ
            VvvCamera* pCam = P_GOD->getSpacetime()->getCamera();;

            GgafDxGeometricActor* p = pCam->getCameraViewPoint();
            pActor->positionAs(p);
        }

        if (!(file_name.find("cubemap") == std::string::npos &&
              file_name.find("CubeMap") == std::string::npos &&
              file_name.find("Cubemap") == std::string::npos)
        ) {
            if (listActorInfo_.getCurrent()) {
                GgafDxFigureActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
                GgafDxFigureActor* pNewActor = nullptr;
                if (pCurrentActor->instanceOf(Obj_GgafDxMeshActor)) {
                    string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->modelfile_.c_str()) + "/";
                    PROPERTY::DIR_MESH_MODEL[2]   = was_dropfile_dir;
                    PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
                    PROPERTY::DIR_TEXTURE[1]      = was_dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                    PROPERTY::DIR_TEXTURE[2]      = was_dropfile_dir;
                    string was_model_id = UTIL::getFileBaseNameWithoutExt(listActorInfo_.getCurrent()->modelfile_.c_str());
                    pNewActor = createInFactory2(GgafLib::CubeMapMeshActor, "actor", was_model_id.c_str());
                    PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
                    PROPERTY::DIR_TEXTURE[1]      = dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                    PROPERTY::DIR_TEXTURE[2]      = dropfile_dir;
                    ((CubeMapMeshActor*)pNewActor)->setCubeMap(file_name.c_str(), 0.5);

                } else if (pCurrentActor->instanceOf(Obj_GgafDxMorphMeshActor)) {
                    string was_dropfile_dir = UTIL::getFileDirName(listActorInfo_.getCurrent()->modelfile_.c_str()) + "/";
                    PROPERTY::DIR_MESH_MODEL[2]   = was_dropfile_dir;
                    PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
                    PROPERTY::DIR_TEXTURE[1]      = was_dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                    PROPERTY::DIR_TEXTURE[2]      = was_dropfile_dir;
                    pNewActor = createInFactory2(GgafLib::CubeMapMorphMeshActor, "actor", pCurrentActor->getModel()->getName());
                    PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
                    PROPERTY::DIR_TEXTURE[1]      = dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                    PROPERTY::DIR_TEXTURE[2]      = dropfile_dir;
                    ((CubeMapMorphMeshActor*)pNewActor)->setCubeMap(file_name.c_str(), 0.5);
                }
                pNewActor->positionAs(pCurrentActor);
                pNewActor->setFaceAngAs(pCurrentActor);
                pNewActor->scaleAs(pCurrentActor);
                bringDirector()->addSubGroup(pNewActor);
                ActorInfo* pActorInfoNew = NEW ActorInfo(pNewActor, listActorInfo_.getCurrent()->modelfile_);
                listActorInfo_.set(pActorInfoNew);
                pCurrentActor->end();
            }
        } else if (!(file_name.find("Nmap") == std::string::npos &&
            file_name.find("NMap") == std::string::npos &&
            file_name.find("nmap") == std::string::npos &&
            file_name.find("normalmap") == std::string::npos &&
            file_name.find("NormalMap") == std::string::npos &&
            file_name.find("Normalmap") == std::string::npos)
        ) {
            GgafDxFigureActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
            PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
            PROPERTY::DIR_TEXTURE[1]      = dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
            PROPERTY::DIR_TEXTURE[2]      = dropfile_dir;
            if (pCurrentActor->instanceOf(Obj_GgafDxMeshActor)) {
                ((GgafDxMeshActor*)pCurrentActor)->effectBumpMapping(file_name.c_str());
            }
        }

        //プロパティ復帰
        PROPERTY::DIR_MESH_MODEL[0]   = dir_mesh_model_default;
        PROPERTY::DIR_MESH_MODEL[1]   = dir_mesh_model_user;
        PROPERTY::DIR_MESH_MODEL[2]   = dir_mesh_model_current;
        PROPERTY::DIR_SPRITE_MODEL[0] = dir_sprite_model_default;
        PROPERTY::DIR_SPRITE_MODEL[1] = dir_sprite_model_user;
        PROPERTY::DIR_SPRITE_MODEL[2] = dir_sprite_model_current;
        PROPERTY::DIR_TEXTURE[0]      = dir_texture_default;
        PROPERTY::DIR_TEXTURE[1]      = dir_texture_user;
        PROPERTY::DIR_TEXTURE[2]      = dir_texture_current;
        VvvGod::is_wm_dropfiles_ = false;
    }

    if (GgafDxInput::isPushedDownKey(DIK_H)) {
        view_help_ = view_help_ ? false : true;
        if (view_help_) {
            pFont01_help_->activate();
        } else {
            pFont01_help_->inactivate();
        }
    }
    if (GgafDxInput::isPushedDownKey(DIK_I)) {
        view_info_ = view_info_ ? false : true;
        if (view_info_) {
            pFont01_info_->activate();
        } else {
            pFont01_info_->inactivate();
        }
    }
    if (view_info_) {
        if (listActorInfo_.length() > 0) {
            GgafDxFigureActor* p = listActorInfo_.getCurrent()->pActor_;
            float r = p->_paMaterial[0].Ambient.r;
            float g = p->_paMaterial[0].Ambient.g;
            float b = p->_paMaterial[0].Ambient.b;
            std::ostringstream oss;
            oss << "["<<listActorInfo_.getCurrentIndex()<<"] = \""<<listActorInfo_.getCurrent()->modelfile_<<"\"\n"<<
                   "Class : "<<p->_class_name<<"\n"<<
                   "(_x, _y, _z) = ("<<(p->_x)<<", "<<(p->_y)<<", "<<(p->_z)<<")\n"<<
                   "_rx, _ry, _rz = "<<(p->_rx)<<", "<<(p->_ry)<<", "<<(p->_rz)<<"\n"<<
                   "_sx, _sy, _sz = "<<(p->_sx)<<", "<<(p->_sy)<<", "<<(p->_sz)<<"\n"<<
                   "_bounding_sphere_radius = "<<(p->getModel()->_bounding_sphere_radius)<<" * "<<(p->_rate_of_bounding_sphere_radius)<<" = "<<
                            (p->getModel()->_bounding_sphere_radius * p->_rate_of_bounding_sphere_radius)<<" (="<<DX_C(p->getModel()->_bounding_sphere_radius * p->_rate_of_bounding_sphere_radius)<<" coord)"<<"\n"<<
                   "red/green/blue = "<<r<<"/"<<g<<"/"<<b<<"\n"<<
                   "_alpha = "<< (p->getAlpha())<<"\n";
            if (p->instanceOf(Obj_GgafDxCubeMapMorphMeshActor)) {
                CubeMapMorphMeshActor* p2 = (CubeMapMorphMeshActor*)p;
                oss << "_reflectance = "<< (p2->_reflectance)<<"\n";
                oss << "_cubemap_tex = \""<<(p2->_cubemap_tex)<<"\"\n";
            }
            oss << "renge,power = "<<(p->getModel()->_specular)<<", "<<(p->getModel()->_specular_power)<<"";

            pFont01_info_->update(oss.str().c_str());
        } else {
            pFont01_info_->update("empty");
        }
    } else {
    }
}

VvvWorld::~VvvWorld() {
}
