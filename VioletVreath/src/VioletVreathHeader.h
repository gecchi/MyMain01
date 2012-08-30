#ifndef VIOLETVREATHHEADER_H_
#define VIOLETVREATHHEADER_H_

//�uDirectX9���C�u�����v�𗘗p����ꍇ�i���p�҂͉��j
//����"GgafLibHeader.h"�w�b�_���C���N���[�h���܂��B

#include "GgafLibHeader.h"


#define KIND_EFFECT (0x0)   // 00000000000000000000000000000000
#define KIND_MY_SHOT_CHIKEI_HIT (0x8)   // 00000000000000000000000000001000
#define KIND_MY_SHOT_CHIKEI_THRU    (0x10)  // 00000000000000000000000000010000
#define KIND_MY_BODY_CHIKEI_HIT (0x20)  // 00000000000000000000000000100000
#define KIND_MY_BODY_CHIKEI_THRU    (0x40)  // 00000000000000000000000001000000
#define KIND_ENEMY_SHOT_CHIKEI_HIT  (0x80)  // 00000000000000000000000010000000
#define KIND_ENEMY_SHOT_CHIKEI_THRU (0x100) // 00000000000000000000000100000000
#define KIND_ENEMY_BODY_CHIKEI_HIT  (0x200) // 00000000000000000000001000000000
#define KIND_ENEMY_BODY_CHIKEI_THRU (0x400) // 00000000000000000000010000000000
#define KIND_ITEM_CHIKEI_HIT    (0x800) // 00000000000000000000100000000000
#define KIND_ITEM_CHIKEI_THRU   (0x1000)    // 00000000000000000001000000000000
#define KIND_CHIKEI_CHIKEI_HIT  (0x2000)    // 00000000000000000010000000000000
#define KIND_CHIKEI_CHIKEI_THRU (0x4000)    // 00000000000000000100000000000000





#define KIND_MY_SHOT    (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_SHOT_CHIKEI_THRU)
#define KIND_MY_BODY    (KIND_MY_BODY_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_SHOT (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_SHOT_CHIKEI_THRU)
#define KIND_ENEMY_BODY (KIND_ENEMY_BODY_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_THRU)

#define KIND_MY (KIND_MY_SHOT|KIND_MY_BODY)
#define KIND_ENEMRY (KIND_ENEMY_SHOT|KIND_ENEMY_BODY)

#define KIND_MY_CHIKEI_HIT  (KIND_MY_SHOT_CHIKEI_HIT|KIND_MY_BODY_CHIKEI_HIT)
#define KIND_MY_CHIKEI_THRU (KIND_MY_SHOT_CHIKEI_THRU|KIND_MY_BODY_CHIKEI_THRU)
#define KIND_ENEMY_CHIKEI_HIT   (KIND_ENEMY_SHOT_CHIKEI_HIT|KIND_ENEMY_BODY_CHIKEI_HIT)
#define KIND_ENEMY_CHIKEI_THRU  (KIND_ENEMY_SHOT_CHIKEI_THRU|KIND_ENEMY_BODY_CHIKEI_THRU)

#define KIND_ITEM   (KIND_ITEM_CHIKEI_HIT|KIND_ITEM_CHIKEI_THRU)

#define KIND_CHIKEI (KIND_CHIKEI_CHIKEI_HIT|KIND_CHIKEI_CHIKEI_THRU)

#define ATTRIBUTE_NOMAL       (0x0)    //000
#define ATTRIBUTE_GU          (0x1)    //001
#define ATTRIBUTE_CHOKI       (0x2)    //010
#define ATTRIBUTE_PA          (0x4)    //100






//#define KIND_EFFECT                  (0x0)       //0b 00000000000000000000000000000000
//#define KIND_MY_SHOT_NOMAL           (0x8)       //0b 00000000000000000000000000001000
//#define KIND_MY_SHOT_GU              (0x11)      //0b 00000000000000000000000000010001
//#define KIND_MY_SHOT_CHOKI           (0x22)      //0b 00000000000000000000000000100010
//#define KIND_MY_SHOT_PA              (0x44)      //0b 00000000000000000000000001000100
//#define KIND_ENEMY_SHOT_NOMAL        (0x80)      //0b 00000000000000000000000010000000
//#define KIND_ENEMY_SHOT_GU           (0x101)     //0b 00000000000000000000000100000001
//#define KIND_ENEMY_SHOT_CHOKI        (0x202)     //0b 00000000000000000000001000000010
//#define KIND_ENEMY_SHOT_PA           (0x404)     //0b 00000000000000000000010000000100
//#define KIND_MY_BODY_NOMAL           (0x800)     //0b 00000000000000000000100000000000
//#define KIND_MY_BODY_GU              (0x1001)    //0b 00000000000000000001000000000001
//#define KIND_MY_BODY_CHOKI           (0x2002)    //0b 00000000000000000010000000000010
//#define KIND_MY_BODY_PA              (0x4004)    //0b 00000000000000000100000000000100
//#define KIND_ENEMY_BODY_NOMAL        (0x8000)    //0b 00000000000000001000000000000000
//#define KIND_ENEMY_BODY_GU           (0x10001)   //0b 00000000000000010000000000000001
//#define KIND_ENEMY_BODY_CHOKI        (0x20002)   //0b 00000000000000100000000000000010
//#define KIND_ENEMY_BODY_PA           (0x40004)   //0b 00000000000001000000000000000100
//#define KIND_ENEMY_BODY_CHIKEI_NOMAL (0x80000)   //0b 00000000000010000000000000000000
//#define KIND_ENEMY_BODY_CHIKEI_GU    (0x100001)  //0b 00000000000100000000000000000001
//#define KIND_ENEMY_BODY_CHIKEI_CHOKI (0x200002)  //0b 00000000001000000000000000000010
//#define KIND_ENEMY_BODY_CHIKEI_PA    (0x400004)  //0b 00000000010000000000000000000100
//#define KIND_CHIKEI                  (0x800000)  //0b 00000000100000000000000000000000
//#define KIND_OTHER                   (0x1000000) //0b 00000001000000000000000000000000
//#define KIND_ITEM                    (0x2000000) //0b 00000010000000000000000000000000


//#define KIND_MY     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA|KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
//#define KIND_ENEMY  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA|KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA|KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA)
//#define KIND_MY_SHOT     (KIND_MY_SHOT_NOMAL|KIND_MY_SHOT_GU|KIND_MY_SHOT_CHOKI|KIND_MY_SHOT_PA)
//#define KIND_MY_BODY     (KIND_MY_BODY_NOMAL|KIND_MY_BODY_GU|KIND_MY_BODY_CHOKI|KIND_MY_BODY_PA)
//#define KIND_ENEMY_SHOT  (KIND_ENEMY_SHOT_NOMAL|KIND_ENEMY_SHOT_GU|KIND_ENEMY_SHOT_CHOKI|KIND_ENEMY_SHOT_PA)
//#define KIND_ENEMY_BODY  (KIND_ENEMY_BODY_NOMAL|KIND_ENEMY_BODY_GU|KIND_ENEMY_BODY_CHOKI|KIND_ENEMY_BODY_PA|KIND_ENEMY_BODY_CHIKEI_NOMAL|KIND_ENEMY_BODY_CHIKEI_GU|KIND_ENEMY_BODY_CHIKEI_CHOKI|KIND_ENEMY_BODY_CHIKEI_PA)
//
//#define ATTRIBUTE_NOMAL       (0x0)    //000
//#define ATTRIBUTE_GU          (0x1)    //001
//#define ATTRIBUTE_CHOKI       (0x2)    //010
//#define ATTRIBUTE_PA          (0x4)    //100

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


/** �A�N�^�[�X�e�[�^�X�F����(ATTRIBUTE_NOMAL/ATTRIBUTE_GU/ATTRIBUTE_CHOKI/ATTRIBUTE_PA) */
#define STAT_Attribute              (1)
/** �A�N�^�[�X�e�[�^�X�F���Z�X�R�A(int) */
#define STAT_AddScorePoint          (2)
/** �A�N�^�[�X�e�[�^�X�F���Z�����N�|�C���g(double) */
#define STAT_AddRankPoint           (3)
/** �A�N�^�[�X�e�[�^�X�F���Z�����N�|�C���g�́A�t���[����������(double) */
#define STAT_AddRankPoint_Reduction (4)
/** �A�N�^�[�X�e�[�^�X�F�A�N�^�[�̎c��̗�(int) */
#define STAT_Stamina                (5)
/** �A�N�^�[�X�e�[�^�X�F�A�N�^�[�̍U����(int) */
#define STAT_Attack                 (6)
/** �A�N�^�[�X�e�[�^�X�F�A�N�^�[�̊�{�h��\��(double) �B�����STAT_Attack�ɏ悶��(1.0��0%�h��,0.9��10%�h��) */
#define STAT_DefaultDefenceRate     (7)
/** �A�N�^�[�X�e�[�^�X�F�A�N�^�[�̗D���������h��\��(double) */
#define STAT_DominantDefenceRate    (8)
/** �A�N�^�[�X�e�[�^�X�F�A�N�^�[�̗򐫑������h��\��(double) */
#define STAT_RecessiveDefenceRate   (9)
/** �A�N�^�[�X�e�[�^�X�F���b�N�I����(0:�s�� 1:��) */
#define STAT_LockonAble             (10)
/** �A�N�^�[�X�e�[�^�X�F�o��G�t�F�N�g���(int) */
#define STAT_EntryEffectKind        (11)
/** �A�N�^�[�X�e�[�^�X�F�ޏo�G�t�F�N�g���(int) */
#define STAT_LeaveEffectKind        (12)
/** �A�N�^�[�X�e�[�^�X�F�����G�t�F�N�g���(int) */
#define STAT_ExplosionEffectKind    (13)
/** �A�N�^�[�X�e�[�^�X�F�ێ��A�C�e�����(int) */
#define STAT_ItemKind               (14)
/** �A�N�^�[�X�e�[�^�X�F�ԕ��i�z��v�f���Ɏg�p�����ASTAT_Sentry �͈�ԍŌ�̐��l�������Ă��邱�Ɓj*/
#define STAT_Sentry                 (15)

// �ȉ��� gen01 start �` end ��Excel�}�N���ɂ�莩���������ꂽ�R�[�h�ł��B
// �R�[�h�ύX�́uRankAdjuster.xls�v����s�����ƁB
// gen01 start
// EnemyEunomia �̃����N��
#define RR_EnemyEunomia_ShotWay(X)  (10+(X)*10)  //����WAY��
// FormationEunomia001 �̃����N��
#define RR_FormationEunomia001_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //��
#define RR_FormationEunomia001_Num(X)  (20 + (X)*10)  //����
#define RR_FormationEunomia001_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //�o���Ԋu
#define RR_FormationEunomia001_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// FormationEunomia002 �̃����N��
#define RR_FormationEunomia002_Col(X)  (5 + ((X)>1.0?1.0:(X))*2)  //��
#define RR_FormationEunomia002_Num(X)  (20 + (X)*10)  //����
#define RR_FormationEunomia002_LaunchInterval(X)  (2  + (10 - ((X)>1.0?1.0:(X))*10))  //�o���Ԋu
#define RR_FormationEunomia002_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// EnemyIris �̃����N��
#define RR_EnemyIris_ShotWay(X)  (10+(X)*10)  //����WAY��
// FormationIris001 �̃����N��
#define RR_FormationIris001_Num(X)  (7 + (X)*7)  //����
#define RR_FormationIris001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationIris001_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// FormationIris002 �̃����N��
#define RR_FormationIris002_Num(X)  (7 + (X)*7)  //����
#define RR_FormationIris002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationIris002_MvVelo(X)  (16000+(X)*1600)  //�ړ����x
// EnemyPallas �̃����N��
#define RR_EnemyPallas_ShotWay(X)  (10+(X)*10)  //����WAY��
// FormationPallas001 �̃����N��
#define RR_FormationPallas001_Num(X)  (12+(X)*8)  //����
#define RR_FormationPallas001_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationPallas001_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// FormationPallas002 �̃����N��
#define RR_FormationPallas002_Num(X)  (12+(X)*8)  //����
#define RR_FormationPallas002_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationPallas002_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
// EnemyThalia �̃����N��
#define RR_EnemyThalia_ShotWay(X)  (20+(X)*10)  //����WAY��
// FormationThalia �̃����N��
#define RR_FormationThalia_Num(X)  (7+(X)*4)  //����
#define RR_FormationThalia_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X)) *20))  //�o���Ԋu
#define RR_FormationThalia_MvVelo(X)  (14000+(X)*10000)  //�ړ����x
// EnemyVesta �̃����N��
#define RR_EnemyVesta_ShotInterval(X)  (2 + (25 - ((X)>1.0?1.0:(X)) * 25))  //���ˊԊu
// Shot001 �̃����N��
#define RR_Shot001_MvVelo(X)  (5000+(X)*5000)  //�ړ����x
#define RR_Shot001_AngVelo(X)  (6000+(X)*6000)  //�p���x
// Shot002 �̃����N��
#define RR_Shot002_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RR_Shot002_AngVelo(X)  (1000+(X)*1000)  //�p���x
// EnemyMassalia �̃����N��
#define RR_EnemyMassalia_ShotWay(X)  (4+(X)*4)  //����WAY��
// EnemyMassaliaFragment �̃����N��
// EnemyMassaliaFragment2 �̃����N��
// EnemyMassaliaFragment3 �̃����N��
// FormationMassalia �̃����N��
#define RR_FormationMassalia_LaunchInterval(X)  (10  + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationMassalia_MvVelo(X)  (8000+(X)*8000)  //�ړ����x
#define RR_FormationMassalia_DurationFrames(X)  (60*20)  //��������
// FormationHebe �̃����N��
#define RR_FormationHebe_Num(X)  (12+(X)*8)  //����
#define RR_FormationHebe_LaunchInterval(X)  (5 + (20 - ((X)>1.0?1.0:(X))*20))  //�o���Ԋu
#define RR_FormationHebe_MvVelo(X)  (10000 + (X)*10000)  //�ړ����x
#define RR_FormationHebe_ShotWay(X)  (4+(X)*4)  //����WAY��
// EnemyHesperia �̃����N��
#define RR_EnemyHesperia_ShotWay(X)  (6 + (((X)>1.0?1.0:(X)) * 4))  //����WAY��
#define RR_EnemyHesperia_Density(X)  (100000 - (((X)>1.0?1.0:(X)) * 50000))  //���x
// gen02 end

//1/��2
#define NANAME 0.70710

#undef P_GOD
#define P_GOD ((VioletVreath::God*)VioletVreath::God::_pGod)
#undef P_UNIVERSE
#define P_UNIVERSE ((VioletVreath::Universe*)(P_GOD->_pUniverse))

#define FADE_FRAMES 60

#define DRAW_DEPTH_LEVEL_HOSHIBOSHI (MAX_DRAW_DEPTH_LEVEL-1)
#define DRAW_DEPTH_LEVEL_BIGOBJ     (MAX_DRAW_DEPTH_LEVEL-2)

/** INT32�����_���֐��}�N���B__FROM__��__TO__���t�]���Ă͂����Ȃ�(����%���Z��VC++�ŕs��) */
#define RND(__FROM__,__TO__) ((INT32)(GgafCore::CmRandomNumberGenerator::getInstance()->genrand_int32() % ((__TO__) - (__FROM__)) ) + (__FROM__) )

//�C�x���g�p UINT32 ���l�錾
DECLARE_CONST(EVENT_GOD_WILL_DIE);
DECLARE_CONST(EVENT_PREPARE_TRANSIT_STAGE);
DECLARE_CONST(EVENT_PREPARE_NEXT_STAGE);
DECLARE_CONST(EVENT_JUST_GAME_OVER);
DECLARE_CONST(EVENT_STG01_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STG01_CTRLER_WAS_END);
DECLARE_CONST(EVENT_STG01_WAS_END);

DECLARE_CONST(EVENT_TRANSIT_WAS_END);
DECLARE_CONST(EVENT_RANKUP_WAS_END);
DECLARE_CONST(EVENT_RANKUP_ON_GARBAGED);

DECLARE_CONST(EVENT_STG02_01_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_02_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_03_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_CLIMAX_WAS_BROKEN);
DECLARE_CONST(EVENT_STG02_CTRLER_WAS_END);
DECLARE_CONST(EVENT_STG02_WAS_END);

DECLARE_CONST(EVENT_MY_SHIP_WAS_DESTROYED_BEGIN);
DECLARE_CONST(EVENT_MY_SHIP_WAS_DESTROYED_FINISH);
DECLARE_CONST(EVENT_ALL_MY_SHIP_WAS_DESTROYED);
DECLARE_CONST(EVENT_GAME_OVER_FINISH);

DECLARE_CONST(EVENT_PREGAMETITLESCENE_FINISH);
DECLARE_CONST(EVENT_GAMETITLESCENE_FINISH);
DECLARE_CONST(EVENT_GAMEDEMOSCENE_FINISH);
DECLARE_CONST(EVENT_GAMESTART);
DECLARE_CONST(EVENT_GOTO_GAMETITLE);
DECLARE_CONST(EVENT_GAMEMODE_DECIDE);


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
class GamePauseScene;


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
class Torus;
class VarietyTorus001;
class VarietyTorus002;
class VarietyTorus003;
class VarietyTorus004;


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
class EffectVreathMagic001;
class EffectSmileMagic001;

class EffectExplosion001;
class EffectExplosion002;
class EffectExplosion003;
class EffectLockon001;
class EffectLockon001_Main;
class EffectLockon001_Sub;
class EffectTurbo001;
class EffectTurbo002;
class EffectCondensation001;
class EffectLaserRefraction001;
class EffectWormhole;
class EffectWormhole001;
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

class TurboMeter;
class LabelGecchi8Font;
class LabelGecchi16Font;
class LabelRankFont;
class LabelRankingFont;
class SpriteLabelTest;

class TamagoActor;
class TestEnemy;
class TestGu;
class TestChoki;
class TestPa;
class TestNomal;

class EnemyTamago01Actor;
class MyUtil;
class GameGlobal;



class EnemyCeres;
class EnemyCeresShot001;
class FormationCeres001;
class FormationCeres002;

class EnemyPallas;
class FormationPallas001;
class FormationPallas001a;
class FormationPallas001b;
class FormationPallas001c;
class FormationPallas001d;
class FormationPallas002;

class EnemyEunomia;
class FormationEunomia;
class FormationEunomia001;
class FormationEunomia001a;
class FormationEunomia001b;
class FormationEunomia002;
class FormationEunomia002a;
class FormationEunomia002b;

class EnemyJuno;
class FormationJuno;
class FormationJuno001;

class EnemyMetis;
class FormationMetis001;
class EnemyAdrastea;
class FormationAdrastea001;

class EnemyAstraea;
class EnemyAstraeaLaserChip001;
class EnemyAstraeaLaserChip002;
class EnemyAstraeaLaserChip003;
class EnemyAstraeaLaserChip004;

class EnemyIris;
class FormationIris001;
class FormationIris002;

class EnemyVesta;

class EnemyCirce;

class EnemyThalia;
class FormationThalia;

class EnemyMassaliaBase;
class EnemyMassalia;
class EnemyMassaliaFragment;
class EnemyMassaliaFragment2;
class EnemyMassaliaFragment3;
class FormationMassalia;

class EnemyHebe;
class FormationHebe;
class FormationHebe001;

class EnemyThisbe;
class EnemyThisbeLaserChip001;
class EnemyThisbeLaserChip002;

class EnemyHesperia;
class EnemyHesperiaLaserChip001;

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

class Properties;
class MyStgUtil;

template<class T>
class Formation001;


class Planet001;
class Planet001Atmosphere;

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
class MenuBoardConfirm;
class CursorCofirmMenu;
class MenuBoardPause;
class CursorPauseMenu;
class MenuBoardTitle;
class CursorTitleMenu;

}

#include "jp/gecchi/VioletVreath/GameGlobal.h"
#include "jp/gecchi/VioletVreath/God.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerManager.h"
#include "jp/gecchi/VioletVreath/manager/CameraWorkerConnection.h"
#include "jp/gecchi/VioletVreath/actor/common/CameraWorker.h"
#include "jp/gecchi/VioletVreath/scene/Universe.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/PreDrawScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/MyShipScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GamePreTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameTitleScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameDemoScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameBeginningScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/CommonScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameEndingScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameOverScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GamePauseScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/TamagoScene.h"

#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUpStage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp001.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp002.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp003.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/RankUpStageController/RankUp100.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage03.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage04.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage05.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/TransitStage.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/Stage01PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_02.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_03.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01_Climax.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/Stage02PartController.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/part/Stage02_01.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage02/part/Stage02_Climax.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01WalledScene.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage01/part/Stage01WalledSection001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/wall/Wall001Prism.h"

#include "jp/gecchi/VioletVreath/actor/Camera.h"
#include "jp/gecchi/VioletVreath/actor/ViewPointGuide.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/TestCamWorker.h"


#include "jp/gecchi/VioletVreath/actor/common/DefaultCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/common/mesh/GroundMeshActor.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot001.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot002.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot003.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Blue.h"
#include "jp/gecchi/VioletVreath/actor/common/shot/Shot004Yellow.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/common/laserchip/EnemyStraightLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/camera_worker/VamSysCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/PauseCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/camera_worker/MyShipDivingCamWorker.h"
#include "jp/gecchi/VioletVreath/actor/my/MyShip.h"
#include "jp/gecchi/VioletVreath/actor/my/MyLockonController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerGizmo.h"
#include "jp/gecchi/VioletVreath/actor/my/MyOptionControllerDirectionVector.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Main.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001_Sub.h"

#include "jp/gecchi/VioletVreath/actor/my/MyShot001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyWave001.h"
#include "jp/gecchi/VioletVreath/actor/my/MyVreath.h"

#include "jp/gecchi/VioletVreath/actor/my/MyStraightLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectMyShipExplosion.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoController.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedo.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoTail.h"
#include "jp/gecchi/VioletVreath/actor/my/MyTorpedoBlast.h"

#include "jp/gecchi/VioletVreath/actor/my/_Test/TestGuShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestChokiShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestPaShot.h"
#include "jp/gecchi/VioletVreath/actor/my/_Test/TestNomalShot.h"

#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectExplosion003.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectTurbo002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectCondensation001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectLaserRefraction001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectWormhole001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry001.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry002.h"
#include "jp/gecchi/VioletVreath/actor/effect/EffectEntry003.h"

#include "jp/gecchi/VioletVreath/actor/my/option/MyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/EffectMyOption.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionWateringLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/my/option/MyOptionStraightLaserChip001.h"



#include "jp/gecchi/VioletVreath/actor/my/MagicMeter.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterStatus.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicMeterCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor002.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/MagicLvCursor003.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/GraphBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/EnergyBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/CostDispBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/VreathBar.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/DamageDispBar.h"

#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/Magic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/OptionMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LaserMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/LockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/TractorMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/VreathMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/SmileMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectSpeedMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectTorpedoMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectLockonMagic.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectVreathMagic001.h"
#include "jp/gecchi/VioletVreath/actor/my/MagicMeter/magic/effect/EffectSmileMagic001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestEnemy.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestGu.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestChoki.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestPa.h"
#include "jp/gecchi/VioletVreath/actor/enemy/_Test/TestNomal.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Tamago/TamagoActor.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Tamago/EnemyTamago01.h"

#include "jp/gecchi/VioletVreath/actor/title/TitleBoard.h"
#include "jp/gecchi/VioletVreath/actor/title/Cursor001.h"

#include "jp/gecchi/VioletVreath/actor/background/board/TurboMeter.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTransit.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi001.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi002.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshiTitle.h"

#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpaceTransit.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpace001.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpace002.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundSpaceRankUp.h"
#include "jp/gecchi/VioletVreath/actor/background/WorldBound/WorldBoundTitle.h"

#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi8Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelGecchi16Font.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankFont.h"
#include "jp/gecchi/VioletVreath/actor/label/LabelRankingFont.h"
#include "jp/gecchi/VioletVreath/actor/label/SpriteLabelTest.h"



#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeres.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/EnemyCeresShot001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/FormationCeres001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Ceres/FormationCeres002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/EnemyPallas.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001b.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001c.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas001d.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Pallas/FormationPallas002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/EnemyEunomia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia001b.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002a.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Eunomia/FormationEunomia002b.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Juno/EnemyJuno.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Juno/FormationJuno.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Juno/FormationJuno001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Metis/EnemyMetis.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Metis/FormationMetis001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adrastea/EnemyAdrastea.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Adrastea/FormationAdrastea001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraea.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip002.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip003.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Astraea/EnemyAstraeaLaserChip004.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Iris/EnemyIris.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Iris/FormationIris002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Vesta/EnemyVesta.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Circe/EnemyCirce.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/EnemyThalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thalia/FormationThalia.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaBase.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassalia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment2.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/EnemyMassaliaFragment3.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Massalia/FormationMassalia.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/EnemyHebe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/FormationHebe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hebe/FormationHebe001.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbe.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbeLaserChip001.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Thisbe/EnemyThisbeLaserChip002.h"

#include "jp/gecchi/VioletVreath/actor/enemy/Hesperia/EnemyHesperia.h"
#include "jp/gecchi/VioletVreath/actor/enemy/Hesperia/EnemyHesperiaLaserChip001.h"

#include "jp/gecchi/VioletVreath/actor/chikei/Torus/Torus.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus002.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus003.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Torus/VarietyTorus004.h"




#include "jp/gecchi/VioletVreath/actor/item/Item.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem001.h"
#include "jp/gecchi/VioletVreath/actor/item/MagicPointItem002.h"

#include "jp/gecchi/VioletVreath/Properties.h"
#include "jp/gecchi/VioletVreath/util/MyStgUtil.h"
#include "jp/gecchi/VioletVreath/util/VamSysCamPosition.h"

#include "jp/gecchi/VioletVreath/manager/DepositoryManager.h"
#include "jp/gecchi/VioletVreath/manager/DepositoryConnection.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineManager.h"
#include "jp/gecchi/VioletVreath/manager/SplineLineConnection.h"

#include "jp/gecchi/VioletVreath/actor/common/template/Formation001.hpp"

#include "jp/gecchi/VioletVreath/actor/common/TestDepository.h"

#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001.h"
#include "jp/gecchi/VioletVreath/actor/chikei/Planet/Planet001Atmosphere.h"


#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/CubeMapMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXAniMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultBoardSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultD3DXMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultMorphMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultPointSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/DefaultSpriteSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/HoshiBoshiTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/LaserChipTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SingleLaserTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/SpriteMeshSetTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/StringBoardTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAABTestActor.h"
#include "jp/gecchi/VioletVreath/actor/_predrawer/WallAAPrismTestActor.h"

#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/MenuBoardConfirm.h"
#include "jp/gecchi/VioletVreath/actor/menu/confirm/CursorConfirmMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/MenuBoardPause.h"
#include "jp/gecchi/VioletVreath/actor/menu/pause/CursorPauseMenu.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/MenuBoardTitle.h"
#include "jp/gecchi/VioletVreath/actor/menu/title/CursorTitleMenu.h"


#endif /*VIOLETVREATHHEADER_H_*/
