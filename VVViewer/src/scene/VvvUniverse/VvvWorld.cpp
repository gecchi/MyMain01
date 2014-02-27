#include "stdafx.h"
#include "VvvWorld.h"

#include <algorithm>
#include "jp/ggaf/core/GgafFactory.h"
#include "jp/ggaf/core/actor/GgafSceneDirector.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"
#include "jp/ggaf/dxcore/actor/GgafDxMorphMeshActor.h"
#include "jp/ggaf/dxcore/actor/supporter/GgafDxMorpher.h"
#include "jp/ggaf/dxcore/model/GgafDxMorphMeshModel.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"
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

using namespace GgafCore;
using namespace GgafDxCore;
using namespace GgafLib;
using namespace VVViewer;
using namespace std;

VvvWorld::VvvWorld(const char* prm_name) : GgafLib::DefaultScene(prm_name) {
    pCamWorker_ = NEW VvvCamWorker("VvvCamWorker");
    getSceneDirector()->addSubGroup(pCamWorker_);
    pCursor_ = NEW VvvCursor("Cursor");
    getSceneDirector()->addSubGroup(pCursor_);
    pGrid_ = NEW VvvGrid("GRID");
    getSceneDirector()->addSubGroup(pGrid_);
    vb_ = NEW VirtualButton();
}

void VvvWorld::initialize() {
}

void VvvWorld::processBehavior() {
    vb_->update(); //入力状況更新

    if (GgafDxInput::isPushedDownKey(DIK_F1)) {
        //カメラを初期位置へ
        VvvCamera* pCam = P_CAM;
        pCamWorker_->slideMvCamTo(0,0,DX_C(pCam->_cameraZ_org),60);
        pCamWorker_->slideMvVpTo(0,0,0,60);
        pCam->slideUpCamTo(2);
    } else if (GgafDxInput::isPushedDownKey(DIK_F2)) {
        //ターゲット変更のみ
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(listActorInfo_.next()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_RETURN)) {
        //ターゲット変更＋カメラ向く
        if (listActorInfo_.length() > 0) {
            if (pCursor_->_pProg->get() == VvvCursor::CUR_SINK) {
                pCursor_->moveTo(listActorInfo_.getCurrent()->pActor_);
            } else {
                pCursor_->moveTo(listActorInfo_.next()->pActor_);
            }
            listActorInfo_.getCurrent()->pActor_->effectFlush(30);
            GgafDxDrawableActor* pT = listActorInfo_.getCurrent()->pActor_;
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
            GgafDxDrawableActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_is_temp_technique) {
                pA->effectDefault();
            } else {
                pA->effectBlendOne();
            }
        }
    } else if (GgafDxInput::isPushedDownKey(DIK_Z)) {
        //Zバッファは書き込み有り無し
        if (listActorInfo_.length() > 0) {
            GgafDxDrawableActor* pA = listActorInfo_.getCurrent()->pActor_;
            if (pA->_zwriteenable) {
                pA->setZWriteEnable(false); //Zバッファは書き込み無し
            } else {
                pA->setZWriteEnable(true);  //Zバッファは書き込み有り
            }
        }
    }

    if (listActorInfo_.length() > 0) {
        GgafDxDrawableActor* pActor =  listActorInfo_.getCurrent()->pActor_;
        int d = 1;
        if (GgafDxInput::isBeingPressedKey(DIK_SPACE) || GgafDxInput::isBeingPressedKey(DIK_LCONTROL) || GgafDxInput::isBeingPressedKey(DIK_RCONTROL)) {
            d = 10;
        } else {
            d = 1;
        }
        if (GgafDxInput::isBeingPressedKey(DIK_A)) {
            //α増減
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->addAlpha(0.01);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->addAlpha(-0.01);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->addAlpha(0.01);
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->addAlpha(-0.01);
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
                pActor->_rx = UTIL::simplifyAng(pActor->_rx + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_PGDN)) {
                pActor->_rx = UTIL::simplifyAng(pActor->_rx - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_RIGHT)) {
                pActor->_rz = UTIL::simplifyAng(pActor->_rz + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_LEFT)) {
                pActor->_rz = UTIL::simplifyAng(pActor->_rz - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_UP)) {
                pActor->_ry = UTIL::simplifyAng(pActor->_ry + D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_DOWN)) {
                pActor->_ry = UTIL::simplifyAng(pActor->_ry - D_ANG(d));
            }
            if (GgafDxInput::isBeingPressedKey(DIK_ESCAPE)) {
                pActor->_rx = 0;
                pActor->_ry = 0;
                pActor->_rz = 0;
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
        } else {
            //平行移動
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

        if (pActor->instanceOf(Obj_GgafDxMorphMeshActor)) {
            GgafDxMorphMeshActor* pMorphMeshActor = dynamic_cast<GgafDxMorphMeshActor*>(pActor);
            if (pMorphMeshActor) {
                for (int i = 1; i <= pMorphMeshActor->_morph_target_num; i++) {
                    if (GgafDxInput::isBeingPressedKey(DIK_1 + (i-1))) {
                        pMorphMeshActor->addMorphWeight(i, 0.01);
                    } else {
                        pMorphMeshActor->addMorphWeight(i, -0.01);
                    }
                }
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

        GgafDxDrawableActor* pActor = nullptr;
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
            getSceneDirector()->addSubGroup(pActor);
            ActorInfo* pActorInfo = NEW ActorInfo(pActor, string(VvvGod::dropfiles_));
            listActorInfo_.addLast(pActorInfo);
            listActorInfo_.last(); //カレントをlastへ
            VvvCamera* pCam = P_CAM;

            GgafDxGeometricActor* p = pCam->getViewPoint();
            pActor->positionAs(p);
        }

        if (!(file_name.find("cubemap") == std::string::npos &&
              file_name.find("CubeMap") == std::string::npos &&
              file_name.find("Cubemap") == std::string::npos)
        ) {
            if (listActorInfo_.getCurrent()) {
                GgafDxDrawableActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
                GgafDxDrawableActor* pNewActor = nullptr;
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
                    pNewActor = createInFactory2(GgafLib::CubeMapMorphMeshActor, "actor", pCurrentActor->_pModel->getName());
                    PROPERTY::DIR_TEXTURE[0]      = dir_texture_user; //dir_texture_userはデフォルトスキンディレクトリ
                    PROPERTY::DIR_TEXTURE[1]      = dropfile_dir + "/../" + PROPERTY::DIRNAME_RESOURCE_SKIN_XXX_TEXTURE + "/";
                    PROPERTY::DIR_TEXTURE[2]      = dropfile_dir;
                    ((CubeMapMorphMeshActor*)pNewActor)->setCubeMap(file_name.c_str(), 0.5);
                }
                pNewActor->positionAs(pCurrentActor);
                pNewActor->setFaceAngAs(pCurrentActor);
                pNewActor->scaleAs(pCurrentActor);
                getSceneDirector()->addSubGroup(pNewActor);
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
            GgafDxDrawableActor* pCurrentActor = listActorInfo_.getCurrent()->pActor_;
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
}

VvvWorld::~VvvWorld() {
}
