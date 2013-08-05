#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_

//�uDirectX9���C�u�����v�𗘗p����i���p�҂͉��I�j�ꍇ
//����"GgafLibCommonHeader.h"�w�b�_���C���N���[�h���܂��B

#include "GgafLibCommonHeader.h"

//��ʒ萔
//�Ӗ��͎����u��ʑ��֒�`�R�s�y�c�[��.xls�v���Q��
#define KIND_EFFECT                 (0x0U)     // 00000000000000000000000000000000
#define KIND_MY_SHOT_CHIKEI_HIT     (0x8U)     // 00000000000000000000000000001000
#define KIND_MY_SHOT_CHIKEI_THRU    (0x10U)    // 00000000000000000000000000010000
#define KIND_MY_BODY_CHIKEI_HIT     (0x20U)    // 00000000000000000000000000100000
#define KIND_MY_BODY_CHIKEI_THRU    (0x40U)    // 00000000000000000000000001000000
#define KIND_ENEMY_SHOT_CHIKEI_HIT  (0x80U)    // 00000000000000000000000010000000
#define KIND_ENEMY_SHOT_CHIKEI_THRU (0x100U)   // 00000000000000000000000100000000
#define KIND_ENEMY_BODY_CHIKEI_HIT  (0x200U)   // 00000000000000000000001000000000
#define KIND_ENEMY_BODY_CHIKEI_THRU (0x400U)   // 00000000000000000000010000000000
#define KIND_ITEM_CHIKEI_HIT        (0x800U)   // 00000000000000000000100000000000
#define KIND_ITEM_CHIKEI_THRU       (0x1000U)  // 00000000000000000001000000000000
#define KIND_CHIKEI_CHIKEI_HIT      (0x2000U)  // 00000000000000000010000000000000
#define KIND_CHIKEI_CHIKEI_THRU     (0x4000U)  // 00000000000000000100000000000000
//��ʒ萔�i���@�E�G�A�����ޕʁj
#define KIND_MY_SHOT    (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_SHOT_CHIKEI_THRU)
#define KIND_MY_BODY    (KIND_MY_BODY_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_SHOT (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_SHOT_CHIKEI_THRU)
#define KIND_ENEMY_BODY (KIND_ENEMY_BODY_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_THRU)
//��ʒ萔�i���@�E�G�A�啪�ޕʁj
#define KIND_MY (KIND_MY_SHOT|KIND_MY_BODY)
#define KIND_ENEMRY (KIND_ENEMY_SHOT|KIND_ENEMY_BODY)
//��ʒ萔�i���̑��A���ޕʁj
#define KIND_MY_CHIKEI_HIT  (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_HIT)
#define KIND_MY_CHIKEI_THRU (KIND_MY_SHOT_CHIKEI_THRU|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_CHIKEI_HIT   (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_HIT)
#define KIND_ENEMY_CHIKEI_THRU  (KIND_ENEMY_SHOT_CHIKEI_THRU|KIND_ENEMY_BODY_CHIKEI_THRU)
#define KIND_ITEM   (KIND_ITEM_CHIKEI_HIT|KIND_ITEM_CHIKEI_THRU)
#define KIND_CHIKEI (KIND_CHIKEI_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_THRU)

#define ATTRIBUTE_NOMAL       (0x0U)    //000
#define ATTRIBUTE_GU          (0x1U)    //001
#define ATTRIBUTE_CHOKI       (0x2U)    //010
#define ATTRIBUTE_PA          (0x4U)    //100

//VirtualButton.h �� define �̕ʖ����`
#define VB_SHOT1    VB_BUTTON1
#define VB_SHOT2    VB_BUTTON2
#define VB_OPTION   VB_BUTTON3
#define VB_VIEW     VB_BUTTON4
#define VB_TURBO    VB_BUTTON5
#define VB_POWERUP  VB_BUTTON6
//#define VB_VIEW_01  VB_BUTTON7
//#define VB_VIEW_02  VB_BUTTON8


//STAT_DEFAULT_ACTOR_KIND��0
enum {
    STAT_Attribute = 1,                   //����(uint)
    STAT_LockonAble,                      //���b�N�I����
    STAT_AddDestroyScorePoint,            //�j�󎞉��Z���_
    STAT_AddDamagedScorePoint,            //�_���[�W�����Z���_
    STAT_FlushAble,                       //�_���[�W���t���b�V���v��
    STAT_AddRankPoint,                    //�j�󎞉��Z�����N
    STAT_AddRankPoint_Reduction,          //�j�󎞉��Z�����N������
    STAT_Stamina,                         //�̗�
    STAT_Attack,                          //�U����
    STAT_DefaultDefenceRate,              //��h�䗦
    STAT_DominantDefenceRate,             //�D�����̖h�䗦
    STAT_RecessiveDefenceRate,            //�򐫎��̖h�䗦
    STAT_EntryEffectKind,                 //�o���G�t�F�N�g���
    STAT_LeaveEffectKind,                 //�ޏo�G�t�F�N�g���
    STAT_ExplosionEffectKind,             //�����G�t�F�N�g���
    STAT_DamagedEffectKind,               //�_���[�W���G�t�F�N�g���
    STAT_DestroyedEffectKind,             //����G�t�F�N�g���
    STAT_ItemKind,                        //����A�C�e�����
    STAT_FormationDestroyedAddScorePoint, //�ґ��S�Ŏ����Z���_
    STAT_FormationDestroyedEffectKind,    //�ґ��S�Ŏ��G�t�F�N�g
    STAT_ProperEffect01Kind,              //���̑��ŗL�G�t�F�N�g�O�P
    STAT_FormationDestroyedItemKind,      //�ґ��S�Ŏ��A�C�e�����
    STAT_AttackShotKind,                  //�V���b�g���
    STAT_RevengeShotKind,                 //�ł��Ԃ����

    STAT_BANPEI,   //�ԕ��i�z��v�f���Ɏg�p�����A��ԍŌ�ɋL�q���邱�Ɓj
};


// �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́u�����N��`Creater.xls�v����s�����ƁB
// gen01 start
// �E�m�~�A(EnemyUnomia) �̃����N��
#define RF_EnemyUnomia_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// �E�m�~�A�ґ�001(FormationUnomia001) �̃����N��
#define RF_FormationUnomia001_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //��
#define RF_FormationUnomia001_Num(X)  (20 + (X)*10)  //����
#define RF_FormationUnomia001_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //�o���Ԋu
#define RF_FormationUnomia001_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// �E�m�~�A�ґ�002(FormationUnomia002) �̃����N��
#define RF_FormationUnomia002_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //��
#define RF_FormationUnomia002_Num(X)  (20 + (X)*10)  //����
#define RF_FormationUnomia002_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //�o���Ԋu
#define RF_FormationUnomia002_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// ���X(EnemyRis) �̃����N��
#define RF_EnemyRis_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// ���X�ґ�001(FormationRis001) �̃����N��
#define RF_FormationRis001_Num(X)  (7 + (X)*7)  //����
#define RF_FormationRis001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationRis001_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// ���X�ґ�002(FormationRis002) �̃����N��
#define RF_FormationRis002_Num(X)  (7 + (X)*7)  //����
#define RF_FormationRis002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationRis002_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// �A���X(EnemyAllas) �̃����N��
#define RF_EnemyAllas_ShotWay(X)  (10+(X)*10)  //���˒e(Way)��
// �A���X�ґ�001(FormationAllas001) �̃����N��
#define RF_FormationAllas001_Num(X)  (12+(X)*8)  //����
#define RF_FormationAllas001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationAllas001_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// �A���X�ґ�002(FormationAllas002) �̃����N��
#define RF_FormationAllas002_Num(X)  (12+(X)*8)  //����
#define RF_FormationAllas002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationAllas002_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// �n���A(EnemyHalia) �̃����N��
#define RF_EnemyHalia_ShotWay(X)  (20+(X)*10)  //���˒e(Way)��
// �n���A�ґ�(FormationHalia) �̃����N��
#define RF_FormationHalia_Num(X)  (7+(X)*4)  //����
#define RF_FormationHalia_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X)) *20))  //�o���Ԋu
#define RF_FormationHalia_MvVelo(X)  (14000+(X)*10000)  //�ړ����x
// �I�����X(EnemyOmulus) �̃����N��
#define RF_EnemyOmulus_ShotMvVelo(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //���˒e���x
#define RF_EnemyOmulus_ShotInterval(X)  (10 + (10 - ((X)>1.0?1.0:(X)) * 10))  //���˒e�Ԋu
// �ėp�V���b�g001(Shot001) �̃����N��
#define RF_Shot001_MvVelo(X)  (5000+(X)*5000)  //�ړ����x
#define RF_Shot001_AngVelo(X)  (6000+(X)*6000)  //�p���x
// �ėp�V���b�g002(Shot002) �̃����N��
#define RF_Shot002_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RF_Shot002_AngVelo(X)  (1000+(X)*1000)  //�p���x
// �G�~���A(EnemyEmilia) �̃����N��
#define RF_EnemyEmilia_ShotWay(X)  (4+(X)*4)  //���˒e(Way)��
// �G�~���A�f��(EnemyEmiliaFragment) �̃����N��
// �G�~���A�f�Ђ̒f��(EnemyEmiliaFragment2) �̃����N��
// �G�~���A�f�Ђ̒f�Ђ̒f��(EnemyEmiliaFragment3) �̃����N��
// �G�~���A�Q(FormationEmilia) �̃����N��
#define RF_FormationEmilia_LaunchInterval(X)  (10  + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationEmilia_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RF_FormationEmilia_DurationFrames(X)  (60*20)  //��������
// �G�[�x�ґ�(FormationEbe) �̃����N��
#define RF_FormationEbe_Num(X)  (12+(X)*8)  //����
#define RF_FormationEbe_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RF_FormationEbe_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
#define RF_FormationEbe_ShotWay(X)  (4+(X)*4)  //���˒e(Way)��
// �G�X�y���A(EnemyEsperia) �̃����N��
#define RF_EnemyEsperia_Density(X)  (90000 - (((X)>1.0?1.0:(X)) * 50000))  //���x
#define RF_EnemyEsperia_ShotWay(X)  (7 + (((X)>1.0?1.0:(X)) * 4))  //���˒e(Way)��
// �A�b�t�H�[(EnemyAppho) �̃����N��
#define RF_EnemyAppho_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyAppho_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyAppho_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �A�b�t�H�[�ґ�001(FormationAppho001) �̃����N��
#define RF_FormationAppho001_Num(X)  (10+(X)*5)  //����
#define RF_FormationAppho001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
// �A�e���e�B�I�y(EnemyAntiope) �̃����N��
#define RF_EnemyAntiope_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyAntiope_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyAntiope_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �A�e���e�B�I�y�ґ�001(FormationAntiope001) �̃����N��
#define RF_FormationAntiope001_Num(X)  (300+(X)*300)  //����
#define RF_FormationAntiope001_LaunchInterval(X)  (2 + (2 - ((X)>1.0?1.0:(X))*2))  //�o���Ԋu
// �f���n�C�h�ґ�(FormationDelheid) �̃����N��
#define RF_FormationDelheid_Num(X)  (30+(X)*10)  //����
#define RF_FormationDelheid_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
#define RF_FormationDelheid_ShotWay(X)  (7+(X)*5)  //���˒e(Way)��
// �ł��Ԃ��e����(SHOT_RV) �̃����N��
#define RF_SHOT_RV_ShotMvVelo(X)  (3000+((X)*5000))  //���˒e���x
#define RF_SHOT_RV_ShotMvAcce(X)  (100+((X)*400))  //���˒e�����x
// �m�[�}���ł��Ԃ��e001(SHOT_RV_NOMAL001) �̃����N��
#define RF_SHOT_RV_NOMAL001_Density(X)  (D_ANG(15)-((X)*D_ANG(5)))  //���x
#define RF_SHOT_RV_NOMAL001_ShotWay(X)  (3+(2*((X)*2)))  //���˒e(Way)��
#define RF_SHOT_RV_NOMAL001_ShotSetNum(X)  (1+((X)*3))  //���˒e(Way)�e�̃Z�b�g��
// �I���g�D�i(EnemyOrtuna) �̃����N��
#define RF_EnemyOrtuna_MvVelo(X)  (15000 + (X)*10000)  //�ړ����x
#define RF_EnemyOrtuna_ShotWay(X)  (2+(X)*4)  //���˒e(Way)��
#define RF_EnemyOrtuna_ShotMvVelo(X)  (1000+(X)*5000)  //���˒e���x
// �I���g�D�i�ґ�001(FormationOrtuna001) �̃����N��
#define RF_FormationOrtuna001_Num(X)  (10+(X)*5)  //����
#define RF_FormationOrtuna001_LaunchInterval(X)  (3 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
// gen02 end

//1/��2
#define NANAME2D_RATE 0.70710
//1/��3
#define NANAME3D_RATE 0.57735

#define FADE_FRAMES 60

#define DRAW_DEPTH_LEVEL_HOSHIBOSHI (MAX_DRAW_DEPTH_LEVEL-1)
#define DRAW_DEPTH_LEVEL_BIGOBJ     (MAX_DRAW_DEPTH_LEVEL-2)


#define VV_DEFAULT_CONFIG_FILE ".\\default_config.properties"
#define VV_CONFIG_FILE         ".\\config.properties"


#define Obj_RankUpStage              (0x81000000U)     //0b 10000001 00000000 00000000 00000000


namespace VioletVreath {

//���̑��̃w�b�_�t�@�C���͂����ɋL�q

class God;
class World;

class CommonScene;

class TitleBoard;
class Cursor001;

class PreDrawScene;
class LaserChipTestActor;
class DefaultMeshTestActor;



class GameScene;
class MyShipScene;
class GamePreTitleScene;
class GameTitleScene;
class GameDemoScene;
class GameBeginningScene;
class GameMainScene;
class GameEndingScene;
class GameOverScene;
class NameEntryScene;

class RankUpStage;
class RankUp001;
class RankUp002;
class RankUp003;
class RankUp004;
class RankUp005;
class RankUp006;
class RankUp007;


class StageWorld;
class StageController;
class Stage;
class Stage01;
class Stage02;
class Stage03;
class Stage04;
class Stage05;
class TransitStage;
class RankUpStageController;
class RankUpStage;
class RankUp001;
class RankUp002;
class RankUp100;
class TamagoScene;

class StagePartController;
class Stage01PartController;
class Stage01_01;
class Stage01_02;
class Stage01_03;
class Stage01_Climax;
class Stage01WalledSection001;
class Stage01WalledScene;
class Wall001;
class Wall001Prism;

class Stage02PartController;
class Stage02_01;
class Stage02_Climax;

class Camera;
class ViewPointGuide;
class CameraWorker;
class DefaultCamWorker;
class TestCamWorker;

class GroundMeshActor;
class Ratislavia;
class VarietyRatislavia001;
class VarietyRatislavia002;
class VarietyRatislavia003;
class VarietyRatislavia004;
class EnemyRatislavia;
class EnemyRatislaviaEye;
class EnemyRatislaviaEyeStraightLaserChip001;
class EffectRatislaviaEye001;


class SingleLaser;
class Shot001;
class Shot002;
class Shot003;
class Shot004;
class Shot004Blue;
class Shot004Yellow;
class EnemyWateringLaserChip001;
class EnemyStraightLaserChip001;

class VamSysCamWorker;
class PauseCamWorker;
class MyShipDivingCamWorker;
class MyOptionWateringLaserChip001;
class MyOptionStraightLaserChip001;
class MyStraightLaserChip001;
class MyShip;
class MyLockonController;
class MyOptionController;
class MyOptionControllerGizmo;
class MyOptionControllerDirectionVector;
class MyOption;
class EffectMyOption;
class MyTorpedoController;
class MyTorpedoTail;
class MyTorpedo;
class MyTorpedoBlast;
class MyShot001;
class MyWave001;
class MyVreath;
class EffectMyShipExplosion;

class TestGuShot;
class TestChokiShot;
class TestPaShot;
class TestNomalShot;

class MagicMeter;
class MagicMeterStatus;
class MagicMeterCursor001;
class MagicLvCursor;
class MagicLvCursor001;
class MagicLvCursor002;
class MagicLvCursor003;
class GraphBar;
class EnergyBar;
class CostDispBar;
class VreathBar;
class DamageDispBar;

class Magic;
class OptionMagic;
class LaserMagic;
class SpeedMagic;
class LockonMagic;
class TorpedoMagic;
class TractorMagic;
class VreathMagic;
class SmileMagic;
class EffectMagic001;
class EffectSpeedMagic;
class EffectTorpedoMagic;
class EffectLockonMagic;
class EffectLaserMagic;
class EffectOptionMagic001;
class EffectVreathMagic001;
class EffectSmileMagic001;

class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectExplosion004;
class EffectLockon001;
class EffectLockon001_Main;
class EffectLockon001_Sub;
class EffectTurbo001;
class EffectTurbo002;
class EffectCondensation001;
class EffectLaserRefraction001;
class EffectWormhole;
class EffectWormhole001;
class EffectEntry;
class EffectEntry001;
class EffectEntry002;
class EffectEntry003;

class HoshiBoshiTransit;
class HoshiBoshiRankUp;
class HoshiBoshi001;
class HoshiBoshi002;
class HoshiBoshiTitle;
class WorldBoundSpaceTransit;
class WorldBoundSpace001;
class WorldBoundSpace002;
class WorldBoundSpaceRankUp;
class WorldBoundTitle;
class WorldBoundNameEntry;

class TurboMeter;
class LabelFix16Font01;
class LabelGecchi8Font;
class LabelGecchi16Font;
class LabelGecchi32Font;
class LabelMenuTitleFont01;
class LabelMenuItemFont01;
class LabelRankFont;
class LabelRankingFont;
class SpriteLabelTest;
class SpriteLabelGecchi32Font;
class SpriteLabelBonus001;
class LabelSceneSymbol;

class TamagoActor;
class TestEnemy;
class TestGu;
class TestChoki;
class TestPa;
class TestNomal;

class EnemyTamago01Actor;
class GameGlobal;



class EnemyEres;
class EnemyEresShot001;
class FormationEres001;
class FormationEres002;

class EnemyAllas;
class FormationAllas001;
class FormationAllas001a;
class FormationAllas001b;
class FormationAllas001c;
class FormationAllas001d;
class FormationAllas002;

class EnemyUnomia;
class FormationUnomia;
class FormationUnomia001;
class FormationUnomia001a;
class FormationUnomia001b;
class FormationUnomia002;
class FormationUnomia002a;
class FormationUnomia002b;

class EnemyGeria;
class FormationGeria;
class FormationGeria001;

class EnemyEtis;
class FormationEtis001;
class EnemyDrastea;
class FormationDrastea001;

class EnemyStraea;
class EnemyStraeaLaserChip001;
class EnemyStraeaLaserChip002;
class EnemyStraeaLaserChip003;
class EnemyStraeaLaserChip004;

class EnemyRis;
class FormationRis001;
class FormationRis002;

class EnemyOmulus;

class EnemyOrtuna;
class FormationOrtuna001;
class FormationOrtuna001a;
class FormationOrtuna001b;

class EnemyEmus;
class EnemyEmusLaserChip001;

class EnemyIrce;

class EnemyHalia;
class FormationHalia;

class EnemyEmiliaBase;
class EnemyEmilia;
class EnemyEmiliaFragment;
class EnemyEmiliaFragment2;
class EnemyEmiliaFragment3;
class FormationEmilia;

class EnemyEbe;
class FormationEbe;
class FormationEbe001;

class EnemyHisbe;
class EnemyHisbe002;
class EnemyHisbeLaserChip001;
class EnemyHisbeLaserChip002;
class EnemyHisbeLaserChip003;

class EnemyEsperia;
class EnemyEsperiaLaserChip001;

class EnemyTalante;

class EnemyErmione;
class EnemyErmioneArm;
class EnemyErmioneArmBody;
class EnemyErmioneArmHead;
class EnemyErmioneArmWeak;

class EnemyAppho;
class FormationAppho001;
class FormationAppho001a;
class FormationAppho001b;

class EnemyAntiope;
class EnemyAntiopeP;
class EnemyAntiopeN;
class FormationAntiope001;

class EnemyDelheid;
class FormationDelheid;
class FormationDelheid001;

class EnemyAlisana;

class EnemyIda;
class EnemyIdaBase;
class EnemyIdaBase001;
class FormationIda;
class FormationIda001;

class EnemyThagoras;
class FormationThagoras;
class FormationThagoras001;
class FormationThagoras002;

//"VVEnemysHeader.h" ���킷���ȁ`

class DepositoryConnection;
class DepositoryManager;


class SplineLineConnection;
class SplineLineManager;


class CameraWorkerManager;
class CameraWorkerConnection;

class TestDepository;

class Item;
class MagicPointItem;
class MagicPointItem001;
class MagicPointItem002;
class ScoreItem;
class ScoreItem001;
class VreathItem;
class VreathItem001;

class Properties;
class QueryRanking;
class MyStgUtil;

template<class T>
class Formation001;


class Planet001;
class Planet001Atmosphere;
class Horizon001;

class CubeMapMeshTestActor;
class CubeMapMeshSetTestActor;
class CubeMapMorphMeshTestActor;
class DefaultD3DXAniMeshTestActor;
class DefaultBoardTestActor;
class DefaultBoardSetTestActor;
class DefaultMeshTestActor;
class DefaultD3DXMeshTestActor;
class DefaultMeshSetTestActor;
class DefaultMorphMeshTestActor;
class DefaultPointSpriteTestActor;
class DefaultSpriteTestActor;
class DefaultSpriteSetTestActor;
class GroundMeshTestActor;
class HoshiBoshiTestActor;
class LaserChipTestActor;
class SingleLaserTestActor;
class SpriteMeshTestActor;
class SpriteMeshSetTestActor;
class StringBoardTestActor;
class WallAABTestActor;
class WallAAPrismTestActor;

class VamSysCamPosition;
class MenuBoard;
class CursorCofirmMenu;
class MenuBoardConfirm;
class CursorPauseMenu;
class MenuBoardPause;
class CursorTitleMenu;
class MenuBoardTitle;

class CursorConfigMenu;
class MenuBoardConfig;
class CursorKeyConfigMenu;
class MenuBoardKeyConfig;
class CursorSoundConfigMenu;
class MenuBoardSoundConfig;
class CursorScreenConfigMenu;
class MenuBoardScreenConfig;

class MenuBoardNameEntry;
class CursorNameEntryMenu;
class SupCursorScreenConfigMenu;

class XpmHeader;

}


#endif /*VIOLETVREATHHEADER_H_*/
