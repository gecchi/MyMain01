
POS_PRISM_XY_NN = (0x11) #0b 00010001
POS_PRISM_XY_NP = (0x12) #0b 00010010
POS_PRISM_XY_PN = (0x14) #0b 00010100
POS_PRISM_XY_PP = (0x18) #0b 00011000
POS_PRISM_YZ_NN = (0x21) #0b 00100001
POS_PRISM_YZ_NP = (0x22) #0b 00100010
POS_PRISM_YZ_PN = (0x24) #0b 00100100
POS_PRISM_YZ_PP = (0x28) #0b 00101000
POS_PRISM_ZX_NN = (0x41) #0b 01000001
POS_PRISM_ZX_NP = (0x42) #0b 01000010
POS_PRISM_ZX_PN = (0x44) #0b 01000100
POS_PRISM_ZX_PP = (0x48) #0b 01001000
POS_PRISM_MAXVALUE = POS_PRISM_ZX_PP

POS_PRISM_xx_NN = (0x1)  #0b 00000001
POS_PRISM_xx_NP = (0x2)  #0b 00000010
POS_PRISM_xx_PN = (0x4)  #0b 00000100
POS_PRISM_xx_PP = (0x8)  #0b 00001000
POS_PRISM_XY_xx = (0x10) #0b 00010000
POS_PRISM_YZ_xx = (0x20) #0b 00100000
POS_PRISM_ZX_xx = (0x40) #0b 01000000


POS_PYRAMID_NNN = (0x8000) #0b  10000000 00000000
POS_PYRAMID_NNP = (0x8100) #0b  10000001 00000000
POS_PYRAMID_NPN = (0x8200) #0b  10000010 00000000
POS_PYRAMID_NPP = (0x8300) #0b  10000011 00000000
POS_PYRAMID_PNN = (0x8400) #0b  10000100 00000000
POS_PYRAMID_PNP = (0x8500) #0b  10000101 00000000
POS_PYRAMID_PPN = (0x8600) #0b  10000110 00000000
POS_PYRAMID_PPP = (0x8700) #0b  10000111 00000000
POS_PYRAMID_MAXVALUE = POS_PYRAMID_PPP

POS_PYRAMID_xxP = (0x100)  #0b  00000001 00000000
POS_PYRAMID_xPx = (0x200)  #0b  00000010 00000000
POS_PYRAMID_xPP = (0x300)  #0b  00000011 00000000
POS_PYRAMID_Pxx = (0x400)  #0b  00000100 00000000
POS_PYRAMID_PxP = (0x500)  #0b  00000101 00000000
POS_PYRAMID_PPx = (0x600)  #0b  00000110 00000000


class Veartex
  attr_accessor :X ,:Y, :Z
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
  end
end

class Box
  attr_accessor :X ,:Y, :Z, :pos_info
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
    #pos_info=0 の場合はBOX
    @pos_info = 0
  end
end

class ExteriorArea
  attr_accessor :width ,:height, :len
  attr_accessor :area

  #KARA_VAL：全くの未設定
  KARA_VAL = -1
  #KABE_BOX_VAL:0＝BOX、0より大きい場合は @pos_infoの値、つまりPRISMまたはPYRAMID
  KABE_BOX_VAL = 0   #Box.@pos_infoの値
  #fullfullにより、BOXでもプリズムでもないけど当たり判定が設定済み,6面とも描画不要
  FULL_VAL = -2
  #nobashi_zumi 専用フラグ。その座標はもう当たり判定伸ばし済み
  SUMI_FLG = -3

  FACE_A_BIT = 0b100000
  FACE_B_BIT = 0b010000
  FACE_C_BIT = 0b001000
  FACE_D_BIT = 0b000100
  FACE_E_BIT = 0b000010
  FACE_F_BIT = 0b000001

  FACE_A_IDX = 5
  FACE_B_IDX = 4
  FACE_C_IDX = 3
  FACE_D_IDX = 2
  FACE_E_IDX = 1
  FACE_F_IDX = 0


  def initialize(prm_len, prm_height, prm_width)
    @width = prm_width
    @height = prm_height
    @len = prm_len


    @area = Array.new( @len, KARA_VAL )
    @area.each_index { |x|
      @area[x] = Array.new( @height, KARA_VAL )
      @area[x].each_index { |y|
          @area[x][y] = Array.new( @width, KARA_VAL )
      }
    }
  end

  def isPrism(pos)
    if ((pos > KABE_BOX_VAL) && (pos <= POS_PRISM_MAXVALUE)) then
      return true
    else
      return false
    end
  end

  def isPyramid(pos)
    if ((pos > POS_PRISM_MAXVALUE) && (pos <= POS_PYRAMID_MAXVALUE)) then
      return true
    else
      return false
    end
  end

  def isPrismXY(pos)
    if ((pos == POS_PRISM_XY_NN) ||
        (pos == POS_PRISM_XY_NP) ||
        (pos == POS_PRISM_XY_PN) ||
        (pos == POS_PRISM_XY_PP)   ) then
      return true
    else
      return false
    end
  end

  def isPrismYZ(pos)
    if ((pos == POS_PRISM_YZ_NN) ||
        (pos == POS_PRISM_YZ_NP) ||
        (pos == POS_PRISM_YZ_PN) ||
        (pos == POS_PRISM_YZ_PP)   ) then
      return true
    else
      return false
    end
  end

  def isPrismZX(pos)
    if ((pos == POS_PRISM_ZX_NN) ||
        (pos == POS_PRISM_ZX_NP) ||
        (pos == POS_PRISM_ZX_PN) ||
        (pos == POS_PRISM_ZX_PP)   ) then
      return true
    else
      return false
    end
  end

  def isPrismXPosi(pos)
    if ((pos == POS_PRISM_XY_PP) ||
        (pos == POS_PRISM_XY_PN) ||
        (pos == POS_PRISM_ZX_PP) ||
        (pos == POS_PRISM_ZX_NP)   ) then
      return true
    else
      return false
    end
  end

  def isPrismXNega(pos)
    if ((pos == POS_PRISM_XY_NP) ||
        (pos == POS_PRISM_XY_NN) ||
        (pos == POS_PRISM_ZX_PN) ||
        (pos == POS_PRISM_ZX_NN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismYPosi(pos)
    if ((pos == POS_PRISM_XY_PP) ||
        (pos == POS_PRISM_XY_NP) ||
        (pos == POS_PRISM_YZ_PP) ||
        (pos == POS_PRISM_YZ_PN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismYNega(pos)
    if ((pos == POS_PRISM_XY_PN) ||
        (pos == POS_PRISM_XY_NN) ||
        (pos == POS_PRISM_YZ_NP) ||
        (pos == POS_PRISM_YZ_NN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismZPosi(pos)
    if ((pos == POS_PRISM_YZ_PP) ||
        (pos == POS_PRISM_YZ_NP) ||
        (pos == POS_PRISM_ZX_PP) ||
        (pos == POS_PRISM_ZX_PN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismZNega(pos)
    if ((pos == POS_PRISM_YZ_PN) ||
        (pos == POS_PRISM_YZ_NN) ||
        (pos == POS_PRISM_ZX_NP) ||
        (pos == POS_PRISM_ZX_NN)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidXPosi(pos)
    if ((pos == POS_PYRAMID_PNN) ||
        (pos == POS_PYRAMID_PNP) ||
        (pos == POS_PYRAMID_PPN) ||
        (pos == POS_PYRAMID_PPP)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidXNega(pos)
    if ((pos == POS_PYRAMID_NNN) ||
        (pos == POS_PYRAMID_NNP) ||
        (pos == POS_PYRAMID_NPN) ||
        (pos == POS_PYRAMID_NPP)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidYPosi(pos)
    if ((pos == POS_PYRAMID_NPN) ||
        (pos == POS_PYRAMID_NPP) ||
        (pos == POS_PYRAMID_PPN) ||
        (pos == POS_PYRAMID_PPP)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidYNega(pos)
    if ((pos == POS_PYRAMID_NNN) ||
        (pos == POS_PYRAMID_NNP) ||
        (pos == POS_PYRAMID_PNN) ||
        (pos == POS_PYRAMID_PNP)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidZPosi(pos)
    if ((pos == POS_PYRAMID_NNP) ||
        (pos == POS_PYRAMID_NPP) ||
        (pos == POS_PYRAMID_PNP) ||
        (pos == POS_PYRAMID_PPP)   ) then
      return true
    else
      return false
    end
  end

  def isPyramidZNega(pos)
    if ((pos == POS_PYRAMID_NNN) ||
        (pos == POS_PYRAMID_NPN) ||
        (pos == POS_PYRAMID_PNN) ||
        (pos == POS_PYRAMID_PPN)   ) then
      return true
    else
      return false
    end
  end

  #BOX６面の内、最低限描画しなければいけない面を解析
  def getAnalyzeDispFace
     ret = ExteriorArea.new(@len, @height, @width)

     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          type = 0b111111
          box_elem = @area[x][y][z]
          b_box = x-1 >= 0          ? @area[x-1][y][z] : -999
          f_box = x+1 <= @len-1     ? @area[x+1][y][z] : -999
          d_box = y-1 >= 0          ? @area[x][y-1][z] : -999
          a_box = y+1 <= @height-1  ? @area[x][y+1][z] : -999
          e_box = z-1 >= 0          ? @area[x][y][z-1] : -999
          c_box = z+1 <= @width-1   ? @area[x][y][z+1] : -999

          if box_elem == KARA_VAL then
            ret.area[x][y][z] = KARA_VAL
          elsif box_elem == FULL_VAL then
            ret.area[x][y][z] = FULL_VAL
          elsif box_elem == KABE_BOX_VAL then
            #自身がBOXの場合

            #6面の開き具合を調べる
            #開いているビットがアンセットされる
            # 0b 00abcdef
            #    c
            # a b d f
            #      e

            #BOX(自身)とBOXが隣り合わせ
            if ((b_box == KABE_BOX_VAL || b_box == FULL_VAL)) then #bが開いている
              type = type ^ FACE_B_BIT
            end

            if ((f_box == KABE_BOX_VAL || f_box == FULL_VAL)) then #fが開いている
              type = type ^ FACE_F_BIT
            end

            if ((d_box == KABE_BOX_VAL || d_box == FULL_VAL)) then #dが開いている
              type = type ^ FACE_D_BIT
            end

            if ((a_box == KABE_BOX_VAL || a_box == FULL_VAL)) then #aが開いている
              type = type ^ FACE_A_BIT
            end

            if ((e_box == KABE_BOX_VAL || e_box == FULL_VAL)) then #eが開いている
              type = type ^ FACE_E_BIT
            end

            if ((c_box == KABE_BOX_VAL || c_box == FULL_VAL)) then #cが開いている
              type = type ^ FACE_C_BIT
            end

            #BOX(自身)とプリズムと隣り合わせ
            #    c
            # a b d f
            #      e
            if (isPrism(b_box) ) then #bが開けれるか
              #bが開けれるプリズムか判断
              if (isPrismXPosi(b_box)) then
                type = type ^ FACE_B_BIT
              end
            end

            if (isPrism(f_box) ) then #fが開けれるか
              if (isPrismXNega(f_box)) then
                type = type ^ FACE_F_BIT
              end
            end

            if (isPrism(d_box) ) then #dが開けれるか
              if (isPrismYPosi(d_box)) then
                type = type ^ FACE_D_BIT
              end
            end

            if (isPrism(a_box) ) then #aが開けれるか
              if (isPrismYNega(a_box)) then
                type = type ^ FACE_A_BIT
              end
            end

            if (isPrism(e_box) ) then #eが開けれるか
              if (isPrismZPosi(e_box)) then
                type = type ^ FACE_E_BIT
              end
            end

            if (isPrism(c_box) ) then #cが開けれるか
              if (isPrismZNega(c_box)) then
                type = type ^ FACE_C_BIT
              end
            end

#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type

          elsif (isPrism(box_elem)) then
            #自身がプリズムの場合
            #    c
            # a b d f
            #      e

            #プリズム(自身)とBOXが隣り合わせ
            if ((b_box == KABE_BOX_VAL || b_box == FULL_VAL)) then #bが開けれるか
              if (isPrismYZ(box_elem) || isPrismXNega(box_elem)) then
                type = type ^ FACE_B_BIT
              end
            end

            if ((f_box == KABE_BOX_VAL || f_box == FULL_VAL)) then #fが開けれるか
              if (isPrismYZ(box_elem) || isPrismXPosi(box_elem)) then
                type = type ^ FACE_F_BIT
              end
            end

            if ((d_box == KABE_BOX_VAL || d_box == FULL_VAL)) then #dが開けれるか
              if (isPrismZX(box_elem) || isPrismYNega(box_elem)) then
                type = type ^ FACE_D_BIT
              end
            end

            if ((a_box == KABE_BOX_VAL || a_box == FULL_VAL)) then #aが開けれるか
              if (isPrismZX(box_elem) || isPrismYPosi(box_elem)) then
                type = type ^ FACE_A_BIT
              end
            end

            if ((e_box == KABE_BOX_VAL || e_box == FULL_VAL)) then #eが開けれるか
              if (isPrismXY(box_elem) || isPrismZNega(box_elem)) then
                type = type ^ FACE_E_BIT
              end
            end

            if ((c_box == KABE_BOX_VAL || c_box == FULL_VAL)) then #cが開けれるか
              if (isPrismXY(box_elem) || isPrismZPosi(box_elem)) then
                type = type ^ FACE_C_BIT
              end
            end

            #プリズム（自身）とプリズムが隣り合わせ
            #    c
            # a b d f
            #      e
            if (isPrism(b_box) ) then #bが開けれるか
              #bが開けれるプリズムか判断
              if (isPrismXNega(box_elem) && isPrismXPosi(b_box)) then
                #bをあける為には 自身がXnegative 相手が Xpositive であればOK
                type = type ^ FACE_B_BIT
              elsif (isPrismYZ(box_elem) && isPrismXPosi(b_box)) then
                #自身がYZで相手が Xpositive であればOK
                type = type ^ FACE_B_BIT
              elsif (isPrismYZ(box_elem) && isPrismYZ(b_box) && box_elem == b_box) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_B_BIT
              end
            end

            if (isPrism(f_box) ) then #fが開けれるか
              #fが開けれるプリズムか判断
              if (isPrismXPosi(box_elem) && isPrismXNega(f_box)) then
                #fをあける為には 自身が Xpositive 相手が Xnegative であればOK
                type = type ^ FACE_F_BIT
              elsif (isPrismYZ(box_elem) && isPrismXNega(f_box)) then
                #自身がYZで相手が Xnegative であればOK
                type = type ^ FACE_F_BIT
              elsif (isPrismYZ(box_elem) && isPrismYZ(f_box) && box_elem == f_box) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_F_BIT
              end
            end

            if (isPrism(d_box) ) then #dが開けれるか
              #dが開けれるプリズムか判断
              if (isPrismYNega(box_elem) && isPrismYPosi(d_box)) then
                #dをあける為には 自身が Ynegative  相手が Ypositive であればOK
                type = type ^ FACE_D_BIT
              elsif (isPrismZX(box_elem) && isPrismYPosi(d_box)) then
                #自身がZXで相手が Ypositive であればOK
                type = type ^ FACE_D_BIT
              elsif (isPrismZX(box_elem) && isPrismZX(d_box) && box_elem == d_box) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_D_BIT
              end
            end

            if (isPrism(a_box) ) then #aが開けれるか
              #aが開けれるプリズムか判断
              if (isPrismYPosi(box_elem) && isPrismYNega(a_box)) then
                #aをあける為には 自身が Ypositive 相手が Ynegative であればOK
                type = type ^ FACE_A_BIT
              elsif (isPrismZX(box_elem) && isPrismYNega(a_box)) then
                #自身がZXで相手が Ynegative であればOK
                type = type ^ FACE_A_BIT
              elsif (isPrismZX(box_elem) && isPrismZX(a_box) && box_elem == a_box) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_A_BIT
              end
            end

            if (isPrism(e_box) ) then #eが開けれるか
              #eが開けれるプリズムか判断
              if (isPrismZNega(box_elem) && isPrismZPosi(e_box)) then
                #eをあける為には 自身が Znegative  相手が Zpositive であればOK
                type = type ^ FACE_E_BIT
              elsif (isPrismXY(box_elem) && isPrismZPosi(e_box)) then
                #自身がXYで相手が Ypositive であればOK
                type = type ^ FACE_E_BIT
              elsif (isPrismXY(box_elem) && isPrismXY(e_box) && box_elem == e_box) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_E_BIT
              end
            end

            if (isPrism(c_box) ) then #cが開けれるか
              #cが開けれるプリズムか判断
              if (isPrismZPosi(box_elem) && isPrismZNega(c_box)) then
                #cをあける為には 自身が Zpositive 相手が Znegative であればOK
                type = type ^ FACE_C_BIT
              elsif (isPrismXY(box_elem) && isPrismZNega(c_box)) then
                #自身がXYで相手が Ynegative であればOK
                type = type ^ FACE_C_BIT
              elsif (isPrismXY(box_elem) && isPrismXY(c_box) && box_elem == c_box) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_C_BIT
              end
            end


            #プリズム（自身）とピラミッドが隣り合わせ
            #    c
            # a b d f
            #      e
            if (isPyramid(b_box)) then #bが開けれるか
              if    (box_elem == POS_PRISM_YZ_NN && b_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PRISM_YZ_NP && b_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PRISM_YZ_PN && b_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PRISM_YZ_PP && b_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_B_BIT
              end
            end

            if (isPyramid(f_box)) then #fが開けれるか
              if    (box_elem == POS_PRISM_YZ_NN && b_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PRISM_YZ_NP && b_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PRISM_YZ_PN && b_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PRISM_YZ_PP && b_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_F_BIT
              end
            end

            if (isPyramid(d_box)) then #dが開けれるか
              if    (box_elem == POS_PRISM_ZX_NN && b_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PRISM_ZX_NP && b_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PRISM_ZX_PN && b_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PRISM_ZX_PP && b_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_D_BIT
              end
            end

            if (isPyramid(a_box)) then #aが開けれるか
              if    (box_elem == POS_PRISM_ZX_NN && b_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PRISM_ZX_NP && b_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PRISM_ZX_PN && b_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PRISM_ZX_PP && b_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_A_BIT
              end
            end

            if (isPyramid(e_box)) then #eが開けれるか
              if    (box_elem == POS_PRISM_XY_NN && b_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PRISM_XY_NP && b_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PRISM_XY_PN && b_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PRISM_XY_PP && b_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_E_BIT
              end
            end

            if (isPyramid(c_box)) then #cが開けれるか
              if    (box_elem == POS_PRISM_XY_NN && b_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PRISM_XY_NP && b_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PRISM_XY_PN && b_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PRISM_XY_PP && b_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_C_BIT
              end
            end

#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type

          elsif (isPyramid(box_elem) ) then
            #自身がピラミッドの場合


            #ピラミッド（自身）と壁（かプリズムの面が壁）が隣り合わせ
            #    c
            # a b d f
            #      e
            if (b_box == KABE_BOX_VAL || b_box == FULL_VAL || (isPrism(b_box) && isPrismXPosi(b_box)) ) then #bが開けれるか
              if (isPyramidXNega(box_elem)) then
                type = type ^ FACE_B_BIT
              end
            end

            if (f_box == KABE_BOX_VAL || f_box == FULL_VAL || (isPrism(f_box) && isPrismXNega(f_box)) ) then #fが開けれるか
              if (isPyramidXPosi(box_elem)) then
                type = type ^ FACE_F_BIT
              end
            end

            if (d_box == KABE_BOX_VAL || d_box == FULL_VAL || (isPrism(d_box) && isPrismYPosi(d_box)) ) then #dが開けれるか
              if (isPyramidYNega(box_elem)) then
                type = type ^ FACE_D_BIT
              end
            end

            if (a_box == KABE_BOX_VAL || a_box == FULL_VAL || (isPrism(a_box) && isPrismYNega(a_box)) ) then #aが開けれるか
              if (isPyramidYPosi(box_elem)) then
                type = type ^ FACE_A_BIT
              end
            end

            if (e_box == KABE_BOX_VAL || e_box == FULL_VAL || (isPrism(e_box) && isPrismZPosi(e_box)) ) then #eが開けれるか
              if (isPyramidZNega(box_elem)) then
                type = type ^ FACE_E_BIT
              end
            end

            if (c_box == KABE_BOX_VAL || c_box == FULL_VAL || (isPrism(c_box) && isPrismZNega(c_box)) ) then #cが開けれるか
              if (isPyramidZPosi(box_elem)) then
                type = type ^ FACE_C_BIT
              end
            end

            #ピラミッド（自身）とプリズムの直角三角形面が隣り合わせ
            #    c
            # a b d f
            #      e
            if isPrism(b_box) then #bが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && b_box == POS_PRISM_YZ_NN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NNP && b_box == POS_PRISM_YZ_NP) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NPN && b_box == POS_PRISM_YZ_PN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NPP && b_box == POS_PRISM_YZ_PP) then
                type = type ^ FACE_B_BIT
              end
            end

            if isPrism(f_box) then #fが開けれるか
              if    (box_elem == POS_PYRAMID_PNN && f_box == POS_PRISM_YZ_NN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PNP && f_box == POS_PRISM_YZ_NP) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PPN && f_box == POS_PRISM_YZ_PN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PPP && f_box == POS_PRISM_YZ_PP) then
                type = type ^ FACE_F_BIT
              end
            end

            if isPrism(d_box) then #dが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && d_box == POS_PRISM_ZX_NN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_NNP && d_box == POS_PRISM_ZX_NP) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_PNN && d_box == POS_PRISM_ZX_PN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_PNP && d_box == POS_PRISM_ZX_PP) then
                type = type ^ FACE_D_BIT
              end
            end

            if isPrism(a_box) then #aが開けれるか
              if    (box_elem == POS_PYRAMID_NPN && a_box == POS_PRISM_ZX_NN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_NPP && a_box == POS_PRISM_ZX_NP) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_PPN && a_box == POS_PRISM_ZX_PN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_PPP && a_box == POS_PRISM_ZX_PP) then
                type = type ^ FACE_A_BIT
              end
            end

            if isPrism(e_box) then #eが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && e_box == POS_PRISM_XY_NN) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_NPN && e_box == POS_PRISM_XY_NP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_PNN && e_box == POS_PRISM_XY_PN) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_PPN && e_box == POS_PRISM_XY_PP) then
                type = type ^ FACE_E_BIT
              end
            end

            if isPrism(c_box) then #cが開けれるか
              if    (box_elem == POS_PYRAMID_NNP && c_box == POS_PRISM_XY_NN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_NPP && c_box == POS_PRISM_XY_NP) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_PNP && c_box == POS_PRISM_XY_PN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_PPP && c_box == POS_PRISM_XY_PP) then
                type = type ^ FACE_C_BIT
              end
            end

            #ピラミッド（自身）とピラミッドが隣り合わせ
            #    c
            # a b d f
            #      e
            if isPyramid(b_box) then #bが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && b_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NNP && b_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NPN && b_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_B_BIT
              elsif (box_elem == POS_PYRAMID_NPP && b_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_B_BIT
              end
            end

            if isPyramid(f_box) then #fが開けれるか
              if    (box_elem == POS_PYRAMID_PNN && f_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PNP && f_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PPN && f_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_F_BIT
              elsif (box_elem == POS_PYRAMID_PPP && f_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_F_BIT
              end
            end

            if isPyramid(d_box) then #dが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && d_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_NNP && d_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_PNN && d_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_D_BIT
              elsif (box_elem == POS_PYRAMID_PNP && d_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_D_BIT
              end
            end

            if isPrism(a_box) then #aが開けれるか
              if    (box_elem == POS_PYRAMID_NPN && a_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_NPP && a_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_PPN && a_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_A_BIT
              elsif (box_elem == POS_PYRAMID_PPP && a_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_A_BIT
              end
            end

            if isPrism(e_box) then #eが開けれるか
              if    (box_elem == POS_PYRAMID_NNN && e_box == POS_PYRAMID_NNP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_NPN && e_box == POS_PYRAMID_NPP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_PNN && e_box == POS_PYRAMID_PNP) then
                type = type ^ FACE_E_BIT
              elsif (box_elem == POS_PYRAMID_PPN && e_box == POS_PYRAMID_PPP) then
                type = type ^ FACE_E_BIT
              end
            end

            if isPrism(c_box) then #cが開けれるか
              if    (box_elem == POS_PYRAMID_NNP && c_box == POS_PYRAMID_NNN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_NPP && c_box == POS_PYRAMID_NPN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_PNP && c_box == POS_PYRAMID_PNN) then
                type = type ^ FACE_C_BIT
              elsif (box_elem == POS_PYRAMID_PPP && c_box == POS_PYRAMID_PPN) then
                type = type ^ FACE_C_BIT
              end
            end

#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type

          end
        end
      end
    end

    return ret

  end



  #BOXの当たり判定を最適化したものを得る
  def getAnalyzeBoxHitarea(prm_max_x_colliwall_num, exArea)
    ret = ExteriorArea.new(@len, @height, @width)

    nobashi_zumi = ExteriorArea.new(@len, @height, @width)

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1

          if exArea.area[x][y][z] == KARA_VAL then
            ret.area[x][y][z] = [0,0,0,0,0,0]
            next
          elsif exArea.area[x][y][z] == FULL_VAL then
            next
          elsif isPrism(exArea.area[x][y][z])  then
            #自身がプリズムの場合
            ret.area[x][y][z] = [1,1,1,1,1,1]
            next
          elsif isPyramid(exArea.area[x][y][z])  then
            #自身がピラミッドの場合
            ret.area[x][y][z] = [1,1,1,1,1,1]
            next
          elsif exArea.area[x][y][z] == KABE_BOX_VAL then
            #自身がBOXの場合
            if nobashi_zumi.area[x][y][z] == SUMI_FLG then
              ret.area[x][y][z] = [0,0,0,0,0,0]
              next
            end

            ret.area[x][y][z] = [1,1,1,1,1,1]

            #    c
            # a b d f
            #      e

            #543210
            #abcdef
#############################
            # Z+ 方向(c方向)に伸ばせれるだけ伸ばす。　
            hitarea_c_len = @width - z
            for z_idx in 0..@width - z - 1
              if nobashi_zumi.area[x][y][z+z_idx] == SUMI_FLG then
                #伸ばし終わり
                hitarea_c_len = z_idx
                break
              else
                if exArea.area[x][y][z+z_idx] == FULL_VAL || exArea.area[x][y][z+z_idx] == KABE_BOX_VAL then
                  #のびる
                  nobashi_zumi.area[x][y][z+z_idx] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_c_len = z_idx
                  break
                end
              end
            end

#############################
            # Z- 方向（e方向）に伸ばせれるだけ伸ばす。　
            hitarea_e_len = z + 1
            for z_idx in 0..z
              if z_idx != 0 && nobashi_zumi.area[x][y][z-z_idx] == SUMI_FLG then
                #伸ばし終わり
                hitarea_e_len = z_idx
                break
              else
                if exArea.area[x][y][z-z_idx] == FULL_VAL || exArea.area[x][y][z-z_idx] == KABE_BOX_VAL then
                  #のびる
                  nobashi_zumi.area[x][y][z-z_idx] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_e_len = z_idx
                  break
                end
              end
            end
            if hitarea_c_len == 0 && hitarea_e_len == 0 then
              next
            end
            ret.area[x][y][z][FACE_C_IDX] = hitarea_c_len
            ret.area[x][y][z][FACE_E_IDX] = hitarea_e_len

            z_idx_begin = -(hitarea_e_len-1)
            z_idx_end   = hitarea_c_len-1
#############################
            #今度は伸びた Z 方向の全てについて Y 方向に方向に伸ばせれるだけ伸ばす
            #まず Y+ 方向（a方向）に伸ばせれるだけ伸ばす。　
            is_finish_flg = false
            hitarea_a_len = @height - y

            for y_idx in 0..@height - y - 1
              for z_idx in z_idx_begin..z_idx_end

                if y_idx != 0 && nobashi_zumi.area[x][y+y_idx][z+z_idx] == SUMI_FLG then
                  #伸ばし終わり
                  is_finish_flg = true
                  break
                else
                  if exArea.area[x][y+y_idx][z+z_idx] == FULL_VAL || exArea.area[x][y+y_idx][z+z_idx] == KABE_BOX_VAL then
                    #伸びる可能性あり
                  else
                    #伸ばし終わり
                    is_finish_flg = true
                    break
                  end
                end

              end  #z_idx

              if is_finish_flg then
                #伸び数確定、一つ前の値
                hitarea_a_len = y_idx
                break
              else
                #伸びるが確定、済を埋める。
                for z_idx in z_idx_begin..z_idx_end
                  nobashi_zumi.area[x][y+y_idx][z+z_idx] = SUMI_FLG
                end
              end

            end  #y_idx
            ret.area[x][y][z][FACE_A_IDX] = hitarea_a_len

#############################
            #次に Y- 方向（d方向）に伸ばせれるだけ伸ばす。　
            is_finish_flg = false
            hitarea_d_len = y + 1

            for y_idx in 0..y
              for z_idx in z_idx_begin..z_idx_end

                if y_idx != 0 && nobashi_zumi.area[x][y-y_idx][z+z_idx] == SUMI_FLG then
                  #伸ばし終わり
                  is_finish_flg = true
                  break
                else
                  if exArea.area[x][y-y_idx][z+z_idx] == FULL_VAL || exArea.area[x][y-y_idx][z+z_idx] == KABE_BOX_VAL then
                    #伸びる可能性あり
                  else
                    #伸ばし終わり
                    is_finish_flg = true
                    break
                  end
                end

              end  #z_idx

              if is_finish_flg then
                #伸び数確定、一つ前の値
                hitarea_d_len = y_idx
                break
              else
                #伸びるが確定、済を埋める。
                for z_idx in z_idx_begin..z_idx_end
                  nobashi_zumi.area[x][y-y_idx][z+z_idx] = SUMI_FLG
                end
              end

            end  #y_idx
            ret.area[x][y][z][FACE_D_IDX] = hitarea_d_len

            y_idx_begin = -(hitarea_d_len-1)
            y_idx_end   = hitarea_a_len-1

#############################
            #今度は伸びた Z+ Y+方向の全てについて X+ 方向に方向に伸ばせれるだけ伸す
            #まず X+ 方向（f方向）に伸ばせれるだけ伸ばす。　

            is_finish_flg = false
            f_len = @len - x
            if f_len > prm_max_x_colliwall_num then
              f_len = prm_max_x_colliwall_num
            end
            hitarea_f_len = f_len

            for x_idx in 0..f_len - 1
              for y_idx in y_idx_begin..y_idx_end
                for z_idx in z_idx_begin..z_idx_end

                  if x_idx != 0 && nobashi_zumi.area[x+x_idx][y+y_idx][z+z_idx] == SUMI_FLG then
                    #伸ばし終わり
                    is_finish_flg = true
                    break
                  else
                    if exArea.area[x+x_idx][y+y_idx][z+z_idx] == FULL_VAL || exArea.area[x+x_idx][y+y_idx][z+z_idx] == KABE_BOX_VAL then
                      #伸びる可能性あり
                    else
                      #伸ばし終わり
                      is_finish_flg = true
                      break
                    end
                  end

                end  #z_idx

                if is_finish_flg then
                  break
                end

              end  #y_idx

              if is_finish_flg then
                #伸び数確定、一つ前の値
                hitarea_f_len = x_idx
                break
              else
                #伸びるが確定、済を埋める。
                for y_idx in y_idx_begin..y_idx_end
                  for z_idx in z_idx_begin..z_idx_end
                    nobashi_zumi.area[x+x_idx][y+y_idx][z+z_idx] = SUMI_FLG
                  end
                end
              end

            end  #x_idx
            ret.area[x][y][z][FACE_F_IDX] = hitarea_f_len

#######################
            #次に X- 方向（b方向）に伸ばせれるだけ伸ばす。
            is_finish_flg = false
            b_len = x + 1
            if b_len > prm_max_x_colliwall_num then
              b_len = prm_max_x_colliwall_num
            end
            hitarea_b_len = b_len

            for x_idx in 0..b_len - 1
              for y_idx in y_idx_begin..y_idx_end
                for z_idx in z_idx_begin..z_idx_end

                  if x_idx != 0 && nobashi_zumi.area[x-x_idx][y+y_idx][z+z_idx] == SUMI_FLG then
                    #伸ばし終わり
                    is_finish_flg = true
                    break
                  else
                    if exArea.area[x-x_idx][y+y_idx][z+z_idx] == FULL_VAL || exArea.area[x-x_idx][y+y_idx][z+z_idx] == KABE_BOX_VAL then
                      #伸びる可能性あり
                    else
                      #伸ばし終わり
                      is_finish_flg = true
                      break
                    end
                  end

                end  #z_idx

                if is_finish_flg then
                  break
                end

              end  #y_idx

              if is_finish_flg then
                #伸び数確定、一つ前の値
                hitarea_b_len = x_idx
                break
              else
                #伸びるが確定、済を埋める。
                for y_idx in y_idx_begin..y_idx_end
                  for z_idx in z_idx_begin..z_idx_end
                    nobashi_zumi.area[x-x_idx][y+y_idx][z+z_idx] = SUMI_FLG
                  end
                end
              end

            end  #x_idx
            ret.area[x][y][z][FACE_B_IDX] = hitarea_b_len
#####################
          end
        end
      end
    end
    return ret
  end



  #PRISMの当たり判定結合
 def getAnalyzePrizmHitarea(prm_max_x_colliwall_num, exArea)
    ret = ExteriorArea.new(@len, @height, @width)

    nobashi_zumi = ExteriorArea.new(@len, @height, @width)

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          ret.area[x][y][z] = @area[x][y][z]
          if isPrism(exArea.area[x][y][z]) == false then
            #プリズム以外はそのまま
            next
          end
            pos = exArea.area[x][y][z]
            x_pos = pos & POS_PRISM_YZ_xx
            y_pos = pos & POS_PRISM_ZX_xx
            z_pos = pos & POS_PRISM_XY_xx


            if z_pos > 0 then
              # Z+ 方向(c方向)に同じプリズム（POS_PRISM_XY_xx）ならば伸ばせれるだけ伸ばす。
              hitarea_c_len = @width - z
              for z_idx in 0..@width - z - 1
                if nobashi_zumi.area[x][y][z+z_idx] != SUMI_FLG && @area[x][y][z+z_idx] == z_pos then
                  #のびる
                  nobashi_zumi.area[x][y][z+z_idx] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_c_len = z_idx
                  break
                end
              end #z_idx
              ret.area[x][y][z][FACE_C_IDX] = hitarea_c_len

              # Z- 方向（e方向）に伸ばせれるだけ伸ばす。　
              hitarea_e_len = z + 1
              for z_idx in 0..z
                if z_idx != 0 && nobashi_zumi.area[x][y][z-z_idx] != SUMI_FLG && @area[x][y][z-z_idx] == z_pos then
                  #のびる
                  nobashi_zumi.area[x][y][z-z_idx] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_c_len = z_idx
                  break
                end
              end
              ret.area[x][y][z][FACE_E_IDX] = hitarea_e_len

            elsif y_pos > 0 then

              # Y+ 方向(a方向)に同じプリズム（POS_PRISM_ZX_xx）ならば伸ばせれるだけ伸ばす。
              hitarea_a_len = @height - y
              for y_idx in 0..@height - y - 1
                if nobashi_zumi.area[x][y+y_idx][z] != SUMI_FLG && @area[x][y+y_idx][z] == y_pos then
                  #のびる
                  nobashi_zumi.area[x][y+y_idx][z] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_a_len = y_idx
                  break
                end
              end #y_idx
              ret.area[x][y][z][FACE_A_IDX] = hitarea_a_len

              # Y- 方向（d方向）に伸ばせれるだけ伸ばす。　
              hitarea_d_len = y + 1
              for y_idx in 0..y
                if y_idx != 0 && nobashi_zumi.area[x][y+y_idx][z] != SUMI_FLG && @area[x][y+y_idx][z] == y_pos then
                  #のびる
                  nobashi_zumi.area[x][y+y_idx][z] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_d_len = y_idx
                  break
                end
              end
              ret.area[x][y][z][FACE_D_IDX] = hitarea_d_len

            elsif x_pos > 0 then

              # X+ 方向(f方向)に同じプリズム（POS_PRISM_ZX_xx）ならば伸ばせれるだけ伸ばす。
              hitarea_f_len = @len - x
              for x_idx in 0..@len - x - 1
                if nobashi_zumi.area[x+x_idx][y][z] != SUMI_FLG && @area[x+x_idx][y][z] == x_pos then
                  #のびる
                  nobashi_zumi.area[x+x_idx][y][z] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_f_len = x_idx
                  break
                end
              end #x_idx
              ret.area[x][y][z][FACE_F_IDX] = hitarea_f_len

              # X- 方向（b方向）に伸ばせれるだけ伸ばす。　
              hitarea_b_len = x + 1
              for x_idx in 0..x
                if x_idx != 0 && nobashi_zumi.area[x+x_idx][y][z] != SUMI_FLG && @area[x+x_idx][y][z] == x_pos then
                  #のびる
                  nobashi_zumi.area[x+x_idx][y][z] = SUMI_FLG
                else
                  #伸ばし終わり
                  hitarea_b_len = x_idx
                  break
                end
              end
              ret.area[x][y][z][FACE_B_IDX] = hitarea_b_len

            end



        end
      end
    end
    return ret
 end


  #[0][0][0]から FULL_VAL で塗りつぶす
  def fullfull

    @area[0][0][0] = FULL_VAL
     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1

          if @area[x][y][z] == KARA_VAL && (
               (x-1 >= 0 && @area[x-1][y][z] == FULL_VAL) ||
               (x+1 <= @len-1 && @area[x+1][y][z] == FULL_VAL) ||
               (y-1 >= 0 && @area[x][y-1][z] == FULL_VAL) ||
               (y+1 <= @height-1 && @area[x][y+1][z] == FULL_VAL) ||
               (z-1 >= 0         && @area[x][y][z-1] == FULL_VAL) ||
               (z+1 <= @width-1  && @area[x][y][z+1] == FULL_VAL)  ) then

            begin
              full(x, y, z, FULL_VAL)
            rescue Exception
              #再帰によるスタックオーバー例外を無理やり潰している
            end

          end
        end
      end
    end

  end

  def full(x, y, z, val)
    return if x < 0 || x > @len-1
    return if y < 0 || y > @height-1
    return if z < 0 || z > @width-1
    return if @area[x][y][z] != KARA_VAL

    @area[x][y][z] = val
    if x-1 >= 0         && @area[x-1][y][z] == KARA_VAL then
      full(x-1, y, z, val)
    end

    if x+1 <= @len-1    && @area[x+1][y][z] == KARA_VAL then
      full(x+1, y, z, val)
    end

    if y-1 >= 0         && @area[x][y-1][z] == KARA_VAL then
      full(x, y-1, z, val)
    end

    if y+1 <= @height-1 && @area[x][y+1][z] == KARA_VAL then
      full(x, y+1, z, val)
    end

    if z-1 >= 0         && @area[x][y][z-1] == KARA_VAL then
      full(x, y, z-1, val)
    end

    if z+1 <= @width-1  && @area[x][y][z+1] == KARA_VAL then
      full(x, y, z+1, val)
    end
  end


  #デバッグ用出力その１
  def dump01
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y軸は下から上が正
        (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
           printf("%02d ", @area[l][h][w])
#          print "(",@area[l][h][w],")"
#          print "[",l,"][",h,"][",w,"]="
#          p @area[l][h][w]
        end
        printf(" [%02d] ", h)
        print  "\n"
      end
      (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
        printf("%02d,", w)
      end
      print  "\n"
    end
  end

  #デバッグ用出力その２
  def dump02
    for l in 0..@len-1
      print l,")------------------\n"
      #for h in (@height-1..0).include?(-1)
      (@height-1).downto(0) do |h| #Y軸は下から上が正
         (@width-1).downto(0) do |w| #Z軸は右から左が正(正面から見た場合)
#          printf("%02d", @area[l][h][w])
#          print "(",@area[l][h][w],")"
          print "[",l,"][",h,"][",w,"]="
          p @area[l][h][w]
        end
        print  "\n"
      end
    end
  end


end
