#include "GgafEffectConst.fxh" 

////////////////////////////////////////////////////////////////////////////////
// MassWallActor�p�V�F�[�_�[
// �y�T�v�z
// �O�ǃv���Y���̕`����s���B
// ���_�o�b�t�@�ɁA�O�ǃv���Y����񂪁A10���J��Ԃ��l�ߍ���ł���B
// �X�e�[�g�⃌�W�X�^�̍X�V���s�킸�A�P��� �`��ŁA�ő�
// 10�I�u�W�F�N�g�܂ŕ`��B��������_���B
// author : Masatoshi Tsuge
// date:2011/01/10
////////////////////////////////////////////////////////////////////////////////
//�G���[����̂��߂ɂƂ肠�����ǉ���ł����Ƃ���
float3 g_posCam_World;
float g_specular;
float g_specular_power;

float g_distance_AlphaTarget;
float g_wall_dep;    //�ǃu���b�N�̒����iX���W�������j
float g_wall_height; //�ǃu���b�N�̍����iY���W�������j
float g_wall_width;  //�ǃu���b�N�̕��iZ���W������)

float g_ah_POS_ZX;
float g_fh_POS_ZX;
float g_ah_POS_YZ;
float g_fh_POS_YZ;
float g_ah_POS_XY;
float g_fh_POS_XY;


float g_zf;
float g_tex_blink_power;   
float g_tex_blink_threshold;
float g_alpha_master;
// ���C�g�̕���
float3 g_vecLightFrom_World;
// Ambien���C�g�F�i���ːF�j
float4 g_colLightAmbient;
// Diffuse���C�g�F�i���ːF�j  
float4 g_colLightDiffuse;  
//View�ϊ��s��
float4x4 g_matView; 
//�ˉe�ϊ��s��  
float4x4 g_matProj;  

//�v���Y���p��(�ʒu)�萔

#define POS_PRISM_XY_NN   17
#define POS_PRISM_XY_NP   18
#define POS_PRISM_XY_PN   20
#define POS_PRISM_XY_PP   24
#define POS_PRISM_YZ_NN   33
#define POS_PRISM_YZ_NP   34
#define POS_PRISM_YZ_PN   36
#define POS_PRISM_YZ_PP   40
#define POS_PRISM_ZX_NN   65
#define POS_PRISM_ZX_NP   66
#define POS_PRISM_ZX_PN   68
#define POS_PRISM_ZX_PP   72

#define POS_PRISM_xx_NN    1
#define POS_PRISM_xx_NP    2
#define POS_PRISM_xx_PN    4
#define POS_PRISM_xx_PP    8
#define POS_PRISM_XY_xx    16
#define POS_PRISM_YZ_xx    32
#define POS_PRISM_ZX_xx    64

#define POS_PYRAMID_NNN   32768
#define POS_PYRAMID_NNP   33024
#define POS_PYRAMID_NPN   33280
#define POS_PYRAMID_NPP   33536
#define POS_PYRAMID_PNN   33792
#define POS_PYRAMID_PNP   34048
#define POS_PYRAMID_PPN   34304
#define POS_PYRAMID_PPP   34560

#define POS_PYRAMID_xxP   256
#define POS_PYRAMID_xPx   512
#define POS_PYRAMID_xPP   768
#define POS_PYRAMID_Pxx   1024
#define POS_PYRAMID_PxP   1280
#define POS_PYRAMID_PPx   1536

//�e�N�X�`���̃T���v��(s0���W�X�^)
sampler MyTextureSampler : register(s0);

//���_�V�F�[�_�[�A�o�͍\����
struct OUT_VS
{
    float4 posModel_Proj    : POSITION;
	float2 uv     : TEXCOORD0;
	float4 color    : COLOR0;
};


///////////////////////////////////////////////////////////////////////////

//���_�V�F�[�_�[
OUT_VS GgafDxVS_MassWall(
      float4 prm_posModel_Local   : POSITION,      // ���f���̒��_
      float3 prm_vecNormal_Local  : NORMAL,        // ���f���̒��_�̖@��
      float2 prm_uv               : TEXCOORD0 ,    // ���f���̒��_��UV

      float4 prm_world0           : TEXCOORD1,
      float4 prm_world1           : TEXCOORD2,
      float4 prm_world2           : TEXCOORD3,
      float4 prm_world3           : TEXCOORD4,
      float4 prm_color            : TEXCOORD5,
      float2 prm_info             : TEXCOORD6
) {
	OUT_VS out_vs = (OUT_VS)0;

	int draw_face = (int)(prm_info.x);
    //UV�ɂ��ǂ̖ʂ̒��_�����f���A
    //�`��s�v�Ȗʂ̒��_�̏ꍇ�͉��Ƃ�����i�W�I���g���V�F�[�_�[�g�������G�j

    //draw_face�͕Ǖ����Ƀr�b�g�������Ă���
    //&b 00abcdef
    //
    //���}��BOX�̓W�J������Ԃ̐}
    //
    //                   ^y
    //              z��  | 
    //                 \ | 
    //                  c| 
    // ----���@��--- a b d f ---- -> x
    //                   |e
    //                   | \
    //                   |  \   
	//  u v
	// (0,0)      0.25                     ��u
	//       +------+------+------+------+
	//       |      |        Z+          |
	//       |      |       ��c          |
	//  0.25 +  X+  +--------------------+
	//       | ��f  |        Y-          |
	//       |      |       ��d          |
	//   0.5 +------+--------------------+
	//       |      |        Y+          |
	//       |      |       ��a          |
	//  0.75 +  X-  +--------------------+
	//       | ��b  |        Z-          |
	//       |      |       ��e          |
	//       +------+------+------+------+
	//    ��                                (1,1)
	//    v

    //                          00abcdef
  	if (draw_face >= 32) {  //&b00100000
        draw_face -= 32;
    } else {
        //���(��a)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
            0.5  < prm_uv.y && prm_uv.y < 0.75 ) 
		{
            return out_vs;
        }
    }

    //                          00abcdef
  	if (draw_face >= 16) {  //&b00010000
        draw_face -= 16;
    } else {
        //����(��b)���`��s�v�̏ꍇ
        if (                   prm_uv.x < 0.25 &&
            0.5  < prm_uv.y                       ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 8) {   //&b00001000
        draw_face -= 8;
    } else {
        //������(��c)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x && 
                               prm_uv.y < 0.25 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
   	if (draw_face >= 4) {   //&b00000100
        draw_face -= 4;
    } else {
        //���(��d)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.25 < prm_uv.y && prm_uv.y < 0.5 ) 
		{
            return out_vs;
        }
    }
    //                          00abcdef
  	if (draw_face >= 2) {   //&b00000010
        draw_face -= 2;
    } else {
        //�E����(��e)���`��s�v�̏ꍇ
        if (0.25 < prm_uv.x &&
            0.75 < prm_uv.y                    ) 
		{
            return out_vs;
        } 
    }
    //                          00abcdef
  	if (draw_face >= 1) {   //&b00000001
       // draw_face -= 1;
    } else {
        //����������(��f)���`��s�v�̏ꍇ
        if (                    prm_uv.x < 0.25 &&
                                prm_uv.y < 0.5    ) 
		{
            return out_vs;
        }
    }

	int pos_info = (int)(prm_info.y);

	if (pos_info == 0) {
        //BOX
	} else if (POS_PRISM_XY_NN <= pos_info && pos_info <= POS_PRISM_ZX_PP) {
		//�v���Y���̏ꍇ

		if (pos_info >= POS_PRISM_ZX_xx) {   
	        //BOX�̂P�ʂ𖳗������ăv���Y���^�ɕό`������
			//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
			// ZX �� XZ���ʂƌ���
			pos_info -= POS_PRISM_ZX_xx;
			if (pos_info == POS_PRISM_xx_PP) {
				prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
			} else if (pos_info == POS_PRISM_xx_PN) {
				prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
			} else if (pos_info == POS_PRISM_xx_NP) { 
				prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
			} else { //if (pos_info == POS_PRISM_xx_NN) {
				prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
			}
		} else if (pos_info >= POS_PRISM_YZ_xx) {   
			//�{Z -Z �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
			pos_info -= POS_PRISM_YZ_xx;
			if (pos_info == POS_PRISM_xx_PP) {
				prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
			} else if (pos_info == POS_PRISM_xx_PN) {
				prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
			} else if (pos_info == POS_PRISM_xx_NP) { 
				prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
			} else { //if (pos_info == POS_PRISM_xx_NN) {
				prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
			}
		} else { //if (pos_info >= POS_PRISM_XY_xx) {   
			pos_info -= POS_PRISM_XY_xx;
			//�{X -X �̖ʂ��v���Y���̎΂ߖʂɂȂ�Ȃ��悤�ɂ���
			if (pos_info == POS_PRISM_xx_PP) {
				prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
			} else if (pos_info == POS_PRISM_xx_PN) {
				prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
			} else if (pos_info == POS_PRISM_xx_NP) { 
				prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
			} else { //if (pos_info == POS_PRISM_xx_NN) {
				prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
			}
		} 
		//����  ������
		// g_wall_dep = 20      �� 
		// fh = 20 / 2 = 10     ��(20)�̔���
		// ah = 1.0 * 0.5 = 0.5 �X��(1)�̔���
		// prm_posModel_Local.x = -10 �` 10
		
		//(prm_posModel_Local.y * ((prm_posModel_Local.x+fh)/g_wall_dep))   �E�E�E ��[���L���b�Ƃ܂Ƃ߂�v�Z
		//
		// 		//                 y
		//                ^
		//                |
		//                |
		//                |
		//         +------+------+-
		//         |      |      |
		//         |      |      |
		//   ------+------+------+---->x
		//      -10|     0|      |10
		//         |      |      |
		//         +------+------+-
		//                |
		//                |
		//                |
        //  
		//         <------------->
		//  r=    0.0             1.0
		//  r = (prm_posModel_Local.x+fh)/g_wall_dep)
		//	
		// ���̌�
		//  - ((fh-prm_posModel_Local.x)*ah);   �E�E�E ��[�𐅕��ɂ���v�Z

	} else {
		//�s���~�b�h�̏ꍇ 
		pos_info -= POS_PYRAMID_NNN;
		if (pos_info >= POS_PYRAMID_Pxx) {
			// Pxx
			pos_info -= POS_PYRAMID_Pxx;
			if (pos_info >= POS_PYRAMID_xPx) {
				// PPx
				pos_info -= POS_PYRAMID_xPx;
				if (pos_info >= POS_PYRAMID_xxP) {
					// PPP
					prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
				} else {
					// PPN
					prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       + ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
				}
			} else {
				// PNx
				if (pos_info >= POS_PYRAMID_xxP) {
					// PNP
					prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       + ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
				} else {
					// PNN
					prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) + ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))       - ((g_fh_POS_XY-prm_posModel_Local.x)*g_ah_POS_XY);
				}
			}
		} else {
			// Nxx
			pos_info -= POS_PYRAMID_Pxx;
			if (pos_info >= POS_PYRAMID_xPx) {
				// NPx
				pos_info -= POS_PYRAMID_xPx;
				if (pos_info >= POS_PYRAMID_xxP) {
					// NPP
					prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       + ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
					
				} else {
					// NPN
					prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) + ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) + ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
				}
			} else {
				// NNx
				if (pos_info >= POS_PYRAMID_xxP) {
					// NNP
					prm_posModel_Local.z = (prm_posModel_Local.z * ((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))       - ((g_fh_POS_ZX-prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * ((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))       - ((g_fh_POS_YZ-prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
				} else {
					// NNN
					prm_posModel_Local.z = (prm_posModel_Local.z * (1.0-((prm_posModel_Local.x+g_fh_POS_ZX)/g_wall_dep))) - ((g_fh_POS_ZX+prm_posModel_Local.x)*g_ah_POS_ZX);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.z+g_fh_POS_YZ)/g_wall_width))) - ((g_fh_POS_YZ+prm_posModel_Local.z)*g_ah_POS_YZ);
					prm_posModel_Local.y = (prm_posModel_Local.y * (1.0-((prm_posModel_Local.x+g_fh_POS_XY)/g_wall_dep))) - ((g_fh_POS_XY+prm_posModel_Local.x)*g_ah_POS_XY);
				}
			}
		}
	}

	float4x4 matWorld = {prm_world0, prm_world1, prm_world2, prm_world3};
	               
    const float4 posModel_View = mul(mul( prm_posModel_Local, matWorld ), g_matView ); //World*View
	out_vs.posModel_Proj = mul(posModel_View, g_matProj); //�ˉe�ϊ�  

	//UV�͂��̂܂�
	out_vs.uv = prm_uv;
	//�@���� World �ϊ����Đ��K��
    float3 vecNormal_World = normalize(mul(prm_vecNormal_Local, matWorld)); 	
    vecNormal_World.x+=0.5; //�l0.5�͕ǖʂɂ����������𓖂Ă邽��
                   //���C�g�x�N�g���� XYZ=0.819232,-0.573462,0
    //�@���ƁADiffuse���C�g�����̓��ς��v�Z���A�ʂɑ΂��郉�C�g�����̓��ˊp�ɂ�錸��������߂�B
	float power = max(dot(vecNormal_World, float3(-0.819232,0.573462,0)), 0);      
	//Ambient���C�g�F�ADiffuse���C�g�F�ADiffuse���C�g���� ���l�������J���[�쐬�B      
	out_vs.color = (g_colLightAmbient + (g_colLightDiffuse*power)) * prm_color;
	out_vs.color.a = prm_color.a;
    //���@����O�̓�
	if (posModel_View.z < g_distance_AlphaTarget) {
		//out_vs.color.a *= ((posModel_View.z  / (g_distance_AlphaTarget*2)) + 0.5f); //1.0�`0.5
		out_vs.color.a *= (posModel_View.z  / g_distance_AlphaTarget); //1.0�`0.0
	}
    if (out_vs.posModel_Proj.z > out_vs.posModel_Proj.w) {
        out_vs.posModel_Proj.z = out_vs.posModel_Proj.w; //�`��O��Z�ł��A�`����������邽�߂ɏ㏑���A
    }
	//�����FposModel_Proj.w = 1.0 �̏ꍇ posModel_Proj �� X���WY���W -1 �` +1�A�[�xZ  0 �` +1

	return out_vs;
}

//���b�V���W���s�N�Z���V�F�[�_�[�i�e�N�X�`���L��j
float4 GgafDxPS_MassWall(
	float2 prm_uv	  : TEXCOORD0,
	float4 prm_color    : COLOR0
) : COLOR  {
    if (prm_color.a == 0) {
        discard;
    }
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	const float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color;

    //Blinker���l��
	if (colTex.r >= g_tex_blink_threshold || colTex.g >= g_tex_blink_threshold || colTex.b >= g_tex_blink_threshold) {
		colOut *= g_tex_blink_power; //�����ă����{�����|����B�_�ł�ڗ�������B
	} 
	//�}�X�^�[��
	colOut.a *= g_alpha_master;
	return colOut;
}


float4 PS_Flush( 
	float2 prm_uv	  : TEXCOORD0,
    float4 prm_color    : COLOR0
) : COLOR  {
	//�e�N�X�`�����T���v�����O���ĐF�擾�i���F���擾�j
	const float4 colTex = tex2D( MyTextureSampler, prm_uv);        
	float4 colOut = colTex * prm_color * FLUSH_COLOR;
    colOut.a *= g_alpha_master;
	return colOut;
}

technique MassWallTechnique
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_MassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_MassWall();
	}
}

technique DestBlendOne
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;   
		DestBlend = One; //���Z����
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_MassWall();
		PixelShader  = compile PS_VERSION GgafDxPS_MassWall();
	}
}

technique Flush
{
	pass P0 {
		AlphaBlendEnable = true;
        //SeparateAlphaBlendEnable = true;
		SrcBlend  = SrcAlpha;
		DestBlend = InvSrcAlpha;
        //SrcBlendAlpha = One;      //default
        //DestBlendAlpha = Zero;    //default
		//BlendOpAlpha = Add;       //default
		VertexShader = compile VS_VERSION GgafDxVS_MassWall();
		PixelShader  = compile PS_VERSION PS_Flush();
	}
}
