
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
    @pos_info = 0
  end
end

class ExteriorArea
  attr_accessor :width ,:height, :len
  attr_accessor :area

  #KARA_VAL：全くの未設定
  KARA_VAL = -1
  #KABE_BOX_VAL:0＝BOX、0より大きい＝@pos_infoの値
  KABE_BOX_VAL = 0   #Box.@pos_infoの値
  #fullfullにより、BOXでもプリズムでもないけど当たり判定が設定済み
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

  def isPrismXpositive(pos)
    if ((pos == POS_PRISM_XY_PP) ||
        (pos == POS_PRISM_XY_PN) ||
        (pos == POS_PRISM_ZX_PP) ||
        (pos == POS_PRISM_ZX_NP)   ) then
      return true
    else
      return false
    end
  end

  def isPrismXnegative(pos)
    if ((pos == POS_PRISM_XY_NP) ||
        (pos == POS_PRISM_XY_NN) ||
        (pos == POS_PRISM_ZX_PN) ||
        (pos == POS_PRISM_ZX_NN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismYpositive(pos)
    if ((pos == POS_PRISM_XY_PP) ||
        (pos == POS_PRISM_XY_NP) ||
        (pos == POS_PRISM_YZ_PP) ||
        (pos == POS_PRISM_YZ_PN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismYnegative(pos)
    if ((pos == POS_PRISM_XY_PN) ||
        (pos == POS_PRISM_XY_NN) ||
        (pos == POS_PRISM_YZ_NP) ||
        (pos == POS_PRISM_YZ_NN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismZpositive(pos)
    if ((pos == POS_PRISM_YZ_PP) ||
        (pos == POS_PRISM_YZ_NP) ||
        (pos == POS_PRISM_ZX_PP) ||
        (pos == POS_PRISM_ZX_PN)   ) then
      return true
    else
      return false
    end
  end

  def isPrismZnegative(pos)
    if ((pos == POS_PRISM_YZ_PN) ||
        (pos == POS_PRISM_YZ_NN) ||
        (pos == POS_PRISM_ZX_NP) ||
        (pos == POS_PRISM_ZX_NN)   ) then
      return true
    else
      return false
    end
  end

  #BOX６面の内、最低限描画しなければいけない面を解析
  def getAnalyze01
     ret = ExteriorArea.new(@len, @height, @width)

     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          type = 0b111111
          if @area[x][y][z] == KARA_VAL then
            ret.area[x][y][z] = KARA_VAL
          elsif @area[x][y][z] == FULL_VAL then
            ret.area[x][y][z] = FULL_VAL
          elsif @area[x][y][z] == KABE_BOX_VAL then
            #自身がBOXの場合
            
            #6面の開き具合を調べる
            #開いているビットがアンセットされる
            # 0b 00abcdef 
            #    c
            # a b d f
            #      e

            #BOX(自身)とBOXが隣り合わせ
            if (x-1 >= 0 && (@area[x-1][y][z] == KABE_BOX_VAL || @area[x-1][y][z] == FULL_VAL)) then #bが開いている
              type = type ^ FACE_B_BIT
            end

            if (x+1 <= @len-1 && (@area[x+1][y][z] == KABE_BOX_VAL || @area[x+1][y][z] == FULL_VAL)) then #fが開いている
              type = type ^ FACE_F_BIT
            end

            if (y-1 >= 0 && (@area[x][y-1][z] == KABE_BOX_VAL || @area[x][y-1][z] == FULL_VAL)) then #dが開いている
              type = type ^ FACE_D_BIT
            end

            if (y+1 <= @height-1 && (@area[x][y+1][z] == KABE_BOX_VAL || @area[x][y+1][z] == FULL_VAL)) then #aが開いている
              type = type ^ FACE_A_BIT
            end

            if (z-1 >= 0         && (@area[x][y][z-1] == KABE_BOX_VAL || @area[x][y][z-1] == FULL_VAL)) then #eが開いている
              type = type ^ FACE_E_BIT
            end

            if (z+1 <= @width-1  && (@area[x][y][z+1] == KABE_BOX_VAL || @area[x][y][z+1] == FULL_VAL)) then #cが開いている
              type = type ^ FACE_C_BIT
            end

            #BOX(自身)とプリズムと隣り合わせ
            #    c
            # a b d f
            #      e
            if (x-1 >= 0 && isPrism(@area[x-1][y][z]) ) then #bが開けれるか
              #bが開けれるプリズムか判断
              if (isPrismXpositive(@area[x-1][y][z])) then
                type = type ^ FACE_B_BIT
              end
            end

            if (x+1 <= @len-1 && isPrism(@area[x+1][y][z]) ) then #fが開けれるか
              if (isPrismXnegative(@area[x+1][y][z])) then
                type = type ^ FACE_F_BIT
              end
            end

            if (y-1 >= 0 && isPrism(@area[x][y-1][z]) ) then #dが開けれるか
              if (isPrismYpositive(@area[x][y-1][z])) then
                type = type ^ FACE_D_BIT
              end
            end

            if (y+1 <= @height-1 && isPrism(@area[x][y+1][z]) ) then #aが開けれるか
              if (isPrismYnegative(@area[x][y+1][z])) then
                type = type ^ FACE_A_BIT
              end
            end

            if (z-1 >= 0         && isPrism(@area[x][y][z-1]) ) then #eが開けれるか
              if (isPrismZpositive(@area[x][y][z-1])) then
                type = type ^ FACE_E_BIT
              end
            end

            if (z+1 <= @width-1  && isPrism(@area[x][y][z+1]) ) then #cが開けれるか
              if (isPrismZnegative(@area[x][y][z+1])) then
                type = type ^ FACE_C_BIT
              end
            end

#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type

          elsif (isPrism(@area[x][y][z])) then
            #自身がプリズムの場合
            #    c
            # a b d f
            #      e
            
            #プリズム(自身)とBOXが隣り合わせ
            if (x-1 >= 0 && (@area[x-1][y][z] == KABE_BOX_VAL || @area[x-1][y][z] == FULL_VAL)) then #bが開けれるか
              if (isPrismYZ(@area[x][y][z]) || isPrismXnegative(@area[x][y][z])) then
                type = type ^ FACE_B_BIT
              end
            end

            if (x+1 <= @len-1 && (@area[x+1][y][z] == KABE_BOX_VAL || @area[x+1][y][z] == FULL_VAL)) then #fが開けれるか
              if (isPrismYZ(@area[x][y][z]) || isPrismXpositive(@area[x][y][z])) then
                type = type ^ FACE_F_BIT
              end
            end

            if (y-1 >= 0 && (@area[x][y-1][z] == KABE_BOX_VAL || @area[x][y-1][z] == FULL_VAL)) then #dが開けれるか
              if (isPrismZX(@area[x][y][z]) || isPrismYnegative(@area[x][y][z])) then
                type = type ^ FACE_D_BIT
              end
            end

            if (y+1 <= @height-1 && (@area[x][y+1][z] == KABE_BOX_VAL || @area[x][y+1][z] == FULL_VAL)) then #aが開けれるか
              if (isPrismZX(@area[x][y][z]) || isPrismYpositive(@area[x][y][z])) then
                type = type ^ FACE_A_BIT
              end
            end

            if (z-1 >= 0         && (@area[x][y][z-1] == KABE_BOX_VAL || @area[x][y][z-1] == FULL_VAL)) then #eが開けれるか
              if (isPrismXY(@area[x][y][z]) || isPrismZnegative(@area[x][y][z])) then
                type = type ^ FACE_E_BIT
              end
            end

            if (z+1 <= @width-1  && (@area[x][y][z+1] == KABE_BOX_VAL || @area[x][y][z+1] == FULL_VAL)) then #cが開けれるか
              if (isPrismXY(@area[x][y][z]) || isPrismZpositive(@area[x][y][z])) then
                type = type ^ FACE_C_BIT
              end
            end

            #プリズム（自身）とプリズムが隣り合わせ
            #    c
            # a b d f
            #      e
            if (x-1 >= 0 && isPrism(@area[x-1][y][z]) ) then #bが開けれるか
              #bが開けれるプリズムか判断
              if (isPrismXnegative(@area[x][y][z]) && isPrismXpositive(@area[x-1][y][z])) then
                #bをあける為には 自身がXnegative 相手が Xpositive であればOK
                type = type ^ FACE_B_BIT
              elsif (isPrismYZ(@area[x][y][z]) && isPrismXpositive(@area[x-1][y][z])) then
                #自身がYZで相手が Xpositive であればOK
                type = type ^ FACE_B_BIT
              elsif (isPrismYZ(@area[x][y][z]) && isPrismYZ(@area[x-1][y][z]) && @area[x][y][z] == @area[x-1][y][z]) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_B_BIT
              end
            end

            if (x+1 <= @len-1 && isPrism(@area[x+1][y][z]) ) then #fが開けれるか
              #fが開けれるプリズムか判断
              if (isPrismXpositive(@area[x][y][z]) && isPrismXnegative(@area[x+1][y][z])) then
                #fをあける為には 自身が Xpositive 相手が Xnegative であればOK
                type = type ^ FACE_F_BIT
              elsif (isPrismYZ(@area[x][y][z]) && isPrismXnegative(@area[x+1][y][z])) then
                #自身がYZで相手が Xnegative であればOK
                type = type ^ FACE_F_BIT
              elsif (isPrismYZ(@area[x][y][z]) && isPrismYZ(@area[x+1][y][z]) && @area[x][y][z] == @area[x+1][y][z]) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_F_BIT
              end
            end

            if (y-1 >= 0 && isPrism(@area[x][y-1][z]) ) then #dが開けれるか
              #dが開けれるプリズムか判断
              if (isPrismYnegative(@area[x][y][z]) && isPrismYpositive(@area[x][y-1][z])) then
                #dをあける為には 自身が Ynegative  相手が Ypositive であればOK
                type = type ^ FACE_D_BIT
              elsif (isPrismZX(@area[x][y][z]) && isPrismYpositive(@area[x][y-1][z])) then
                #自身がZXで相手が Ypositive であればOK
                type = type ^ FACE_D_BIT
              elsif (isPrismZX(@area[x][y][z]) && isPrismZX(@area[x][y-1][z]) && @area[x][y][z] == @area[x][y-1][z]) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_D_BIT
              end
            end

            if (y+1 <= @height-1 && isPrism(@area[x][y+1][z]) ) then #aが開けれるか
              #aが開けれるプリズムか判断
              if (isPrismYpositive(@area[x][y][z]) && isPrismYnegative(@area[x][y+1][z])) then
                #aをあける為には 自身が Ypositive 相手が Ynegative であればOK
                type = type ^ FACE_A_BIT
              elsif (isPrismZX(@area[x][y][z]) && isPrismYnegative(@area[x][y+1][z])) then
                #自身がZXで相手が Ynegative であればOK
                type = type ^ FACE_A_BIT
              elsif (isPrismZX(@area[x][y][z]) && isPrismZX(@area[x][y+1][z]) && @area[x][y][z] == @area[x][y+1][z]) then
                #YZ同士で同じプリズムであってもOK
                type = type ^ FACE_A_BIT
              end
            end

            if (z-1 >= 0         && isPrism(@area[x][y][z-1]) ) then #eが開けれるか
              #eが開けれるプリズムか判断
              if (isPrismZnegative(@area[x][y][z]) && isPrismZpositive(@area[x][y][z-1])) then
                #eをあける為には 自身が Znegative  相手が Zpositive であればOK
                type = type ^ FACE_E_BIT
              elsif (isPrismXY(@area[x][y][z]) && isPrismZpositive(@area[x][y][z-1])) then
                #自身がXYで相手が Ypositive であればOK
                type = type ^ FACE_E_BIT
              elsif (isPrismXY(@area[x][y][z]) && isPrismXY(@area[x][y][z-1]) && @area[x][y][z] == @area[x][y][z-1]) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_E_BIT
              end
            end

            if (z+1 <= @width-1  && isPrism(@area[x][y][z+1]) ) then #cが開けれるか
              #cが開けれるプリズムか判断
              if (isPrismZpositive(@area[x][y][z]) && isPrismZnegative(@area[x][y][z+1])) then
                #cをあける為には 自身が Zpositive 相手が Znegative であればOK
                type = type ^ FACE_C_BIT
              elsif (isPrismXY(@area[x][y][z]) && isPrismZnegative(@area[x][y][z+1])) then
                #自身がXYで相手が Ynegative であればOK
                type = type ^ FACE_C_BIT
              elsif (isPrismXY(@area[x][y][z]) && isPrismXY(@area[x][y][z+1]) && @area[x][y][z] == @area[x][y][z+1]) then
                #XY同士で同じプリズムであってもOK
                type = type ^ FACE_C_BIT
              end
            end
            
            
            #プリズム（自身）とピラミッドが隣り合わせ
            #    c
            # a b d f
            #      e
#POS_PRISM_YZ_NN = (0x21) #0b 00100001
#POS_PRISM_YZ_NP = (0x22) #0b 00100010
#POS_PRISM_YZ_PN = (0x24) #0b 00100100
#POS_PRISM_YZ_PP = (0x28) #0b 00101000

#POS_PYRAMID_NNN = (0x8000) #0b  10000000 00000000
#POS_PYRAMID_NNP = (0x8100) #0b  10000001 00000000
#POS_PYRAMID_NPN = (0x8200) #0b  10000010 00000000
#POS_PYRAMID_NPP = (0x8300) #0b  10000011 00000000
#POS_PYRAMID_PNN = (0x8400) #0b  10000100 00000000
#POS_PYRAMID_PNP = (0x8500) #0b  10000101 00000000
#POS_PYRAMID_PPN = (0x8600) #0b  10000110 00000000
#POS_PYRAMID_PPP = (0x8700) #0b  10000111 00000000

            if (x-1 >= 0 && isPyramid(@area[x-1][y][z])) then #bが開けれるか
              if (isPrismYZ(@area[x][y][z]) ) then
                if (@area[x][y][z] == POS_PRISM_YZ_NN) then
                  b_p = @area[x-1][y][z]
                  if (b_p == POS_PRISM_YZ_NN) then
                  
                  
                  end
                end


              end
            end 







#            ret.area[x][y][z] = sprintf("%02d ", type)
            ret.area[x][y][z] = type

          elsif (isPyramid(@area[x][y][z]) ) then
            #自身がピラミッドの場合
            
            
            
            
            
            
            
            
          end
        end
      end
    end

    return ret

  end

  #+Y -Y +Z -Z 方向についてBOXの描画不要の面（開いている面と呼ぶ）方向に、
  #当たり判定AABを伸ばせるかどうか解析
  def getAnalyze02(exArea)
    ret = ExteriorArea.new(@len, @height, @width)

    nobashi_zumi = ExteriorArea.new(@len, @height, @width)

    
    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          ret.area[x][y][z] = [0,0,0,0,0,0]
          if exArea.area[x][y][z] == KARA_VAL then
            ret.area[x][y][z] = [0,0,0,0,0,0]
          elsif exArea.area[x][y][z] == FULL_VAL then
             next
          elsif exArea.area[x][y][z] == KABE_BOX_VAL then
            #自身がBOXの場合
            ret.area[x][y][z] = [1,1,1,1,1,1]
            nobashi_zumi.area[x][y][z] = SUMI_FLG

            #6面の開いている方向の当たり判定長さを設定
            #abcdef

            #    c
            # a b d f
            #      e

            #dが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_D_BIT == 0 then
              #d方向にどのぐらい当たり判定を伸ばせばいいか？
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (y-hitarea_idx >= 0 &&  @area[x][y-hitarea_idx][z] == FULL_VAL && nobashi_zumi.area[x][y-hitarea_idx][z] != SUMI_FLG) then
                  nobashi_zumi.area[x][y-hitarea_idx][z] = SUMI_FLG
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_D_IDX] = hitarea_len
            end

            #aが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_A_BIT == 0 then
              #a方向にどのぐらい当たり判定を伸ばせばいいか？
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (y+hitarea_idx <= @height-1 &&  @area[x][y+hitarea_idx][z] == FULL_VAL && nobashi_zumi.area[x][y+hitarea_idx][z] != SUMI_FLG) then
                  nobashi_zumi.area[x][y+hitarea_idx][z] = SUMI_FLG
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_A_IDX] = hitarea_len
            end

            #eが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_E_BIT == 0 then
              #e方向にどのぐらい当たり判定を伸ばせばいいか？
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (z-hitarea_idx >= 0 &&  @area[x][y][z-hitarea_idx] == FULL_VAL && nobashi_zumi.area[x][y][z-hitarea_idx] != SUMI_FLG) then
                  nobashi_zumi.area[x][y][z-hitarea_idx] = SUMI_FLG
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
              ret.area[x][y][z][FACE_E_IDX] = hitarea_len
            end

            #cが開いている        543210
            #                     abcdef
            if @area[x][y][z] & FACE_C_BIT == 0 then
              #e方向にどのぐらい当たり判定を伸ばせばいいか？
              hitarea_idx = 1
              hitarea_len = 1
              while true
                if (z+hitarea_idx <= @width-1 &&  @area[x][y][z+hitarea_idx] == FULL_VAL && nobashi_zumi.area[x][y][z+hitarea_idx] != SUMI_FLG) then
                  nobashi_zumi.area[x][y][z+hitarea_idx] = SUMI_FLG
                  hitarea_len += 1
                else
                  break;
                end
                hitarea_idx += 1
              end
#              p "hitarea_len=",hitarea_len
#              p "befor ",ret.area[x][y][z]
              ret.area[x][y][z][FACE_C_IDX] = hitarea_len
#              p "after ",ret.area[x][y][z]
            end


#           print "@area[",x,"][",y,"][",z,"]=",@area[x][y][z],"\n"
#           print "@area[",x,"][",y,"][",z,"] & FACE_C_BIT=",(@area[x][y][z] & FACE_C_BIT),"\n"
          elsif exArea.area[x][y][z] <= POS_PRISM_MAXVALUE  then
            #自身がプリズムの場合
            ret.area[x][y][z] = [1,1,1,1,1,1]
          end

        end
      end
    end
    return ret
  end



  #getAnalyze02 で開いている面方向に伸びた当たり判定を
  #+Y -Y +Z -Z 方向に連結できるかどうか解析
  def getAnalyze03(exArea)
    ret = ExteriorArea.new(@len, @height, @width)
    nobashi_zumi = ExteriorArea.new(@len, @height, @width)
    

    for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          if @area[x][y][z] == KARA_VAL then
             next
          elsif @area[x][y][z] == FULL_VAL then
             next
          elsif  @area[x][y][z] == [0,0,0,0,0,0] then
             ret.area[x][y][z] = @area[x][y][z]
             next
          elsif ret.area[x][y][z] == [0,0,0,0,0,0] then
             next
          #elsif exArea.area[x][y][z] == KABE_BOX_VAL then
          else
            ret.area[x][y][z] = @area[x][y][z]
            #    c
            # a b d f
            #      e

            # 543210
            # abcdef

            #+Y -Y +Z -Z の当たり判定と連結できるか考える

            #+Y方向の検討
            same_Y_inc = 0
            if (y+1 <= @height-1) then
              (y+1).upto(@height-1) do |iy|
                if nobashi_zumi.area[x][iy][z] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] == @area[x][iy][z] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][iy][z])
                    ) then #同じ大きさならば連結
                  same_Y_inc += 1
                elsif (ret.area[x][y][z][FACE_B_IDX] == @area[x][iy][z][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][iy][z][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][iy][z][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][iy][z][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][iy][z][FACE_F_IDX] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][iy][z]) ) then

                  same_Y_inc += @area[x][iy][z][FACE_A_IDX]
                else
                  break
                end
              end
            end
            if (same_Y_inc > 0) then
              #面a方向にも広がりを持たせる
              ret.area[x][y][z][FACE_A_IDX] += same_Y_inc
              #面a方向広がりによってまかなわれる残りの当たり判定は不要
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              (y+1).upto((y+1)+(same_Y_inc-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
                nobashi_zumi.area[x][iy][z] = SUMI_FLG
              end
            end

            #-Y方向の検討
            same_Y_dec = 0
            if (y-1 >= 0) then
              (y-1).downto(0) do |iy|
                if nobashi_zumi.area[x][iy][z] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] ==  @area[x][iy][z] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][iy][z]) ) then
                  same_Y_dec += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][iy][z][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][iy][z][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][iy][z][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][iy][z][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][iy][z][FACE_F_IDX] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][iy][z]) ) then

                  same_Y_dec += @area[x][iy][z][FACE_D_IDX]
                else
                  break
                end
              end
            end
            if (same_Y_dec > 0) then
              #面d方向にも広がりを持たせる
              ret.area[x][y][z][FACE_D_IDX] += same_Y_dec
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              #面d方向広がりによってまかなわれる残りの当たり判定は不要
              (y-1).downto((y-1)-(same_Y_dec-1)) do |iy|
                ret.area[x][iy][z] = [0,0,0,0,0,0]
                nobashi_zumi.area[x][iy][z] = SUMI_FLG
              end
            end

            #Y方向に連結したならば、Z軸方向へは単純連結出来ないのでこれで終了とする
            if same_Y_dec > 0 || same_Y_inc > 0 then
              next
            end

            #+Z方向の検討
            same_Z_inc = 0
            if (z+1 <= @width-1) then
              (z+1).upto(@width-1) do |iz|
                if nobashi_zumi.area[x][y][iz] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] ==  @area[x][y][iz] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][y][iz]) ) then
                  same_Z_inc += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][y][iz][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][y][iz][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][y][iz][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_E_IDX] == @area[x][y][iz][FACE_E_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][y][iz][FACE_F_IDX] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][y][iz]) ) then

                  same_Z_inc += @area[x][y][iz][FACE_C_IDX]
                else
                  break
                end
              end
            end
            if (same_Z_inc > 0) then
              #面c方向にも広がりを持たせる
              ret.area[x][y][z][FACE_C_IDX] += same_Z_inc
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              #面c方向広がりによってまかなわれる残りの当たり判定は不要
              (z+1).upto((z+1)+(same_Z_inc-1)) do |iz|
                ret.area[x][y][iz] = [0,0,0,0,0,0]
                nobashi_zumi.area[x][y][iz] = SUMI_FLG
              end
            end

            #-Z方向の検討
            same_Z_dec = 0
            if (z-1 >= 0) then
              (z-1).downto(0) do |iz|
                if nobashi_zumi.area[x][y][iz] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] ==  @area[x][y][iz] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][y][iz]) ) then
                  same_Z_dec += 1
                elsif (ret.area[x][y][z][FACE_A_IDX] == @area[x][y][iz][FACE_A_IDX] &&
                       ret.area[x][y][z][FACE_B_IDX] == @area[x][y][iz][FACE_B_IDX] &&
                       ret.area[x][y][z][FACE_C_IDX] == @area[x][y][iz][FACE_C_IDX] &&
                       ret.area[x][y][z][FACE_D_IDX] == @area[x][y][iz][FACE_D_IDX] &&
                       ret.area[x][y][z][FACE_F_IDX] == @area[x][y][iz][FACE_F_IDX] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[x][y][iz]) ) then

                  same_Z_dec += @area[x][y][iz][FACE_E_IDX]
                else
                  break
                end
              end
            end
            if (same_Z_dec > 0) then
              #面e方向にも広がりを持たせる
              ret.area[x][y][z][FACE_E_IDX] += same_Z_dec
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              #面e方向広がりによってまかなわれる残りの当たり判定は不要
              (z-1).downto((z-1)-(same_Z_dec-1)) do |iz|
                ret.area[x][y][iz] = [0,0,0,0,0,0]
                nobashi_zumi.area[x][y][iz] = SUMI_FLG
              end
            end

          #elsif exArea.area[x][y][z] <= POS_PRISM_MAXVALUE then

          end
#           print "@area[",x,"][",y,"][",z,"]=",@area[x][y][z],"\n"
#           print "@area[",x,"][",y,"][",z,"] & FACE_C_BIT=",(@area[x][y][z] & FACE_C_BIT),"\n"
        end
      end
    end
    return ret
  end


  #getAnalyze03 により連結された当たり判定AABについて
  #+X -X 方向に連結できるかどうか解析
  #引数：最大連結数
  def getAnalyze04(prm_max_x_colliwall_num, exArea)

    max_x_colliwall_num = prm_max_x_colliwall_num
    ret = ExteriorArea.new(@len, @height, @width)
    nobashi_zumi = ExteriorArea.new(@len, @height, @width)
    
    
    (@len-1).downto(0) do |x| #お尻からループ
      for y in 0..@height-1
        for z in 0..@width-1
          if @area[x][y][z] == [0,0,0,0,0,0] then
            ret.area[x][y][z] = @area[x][y][z]
            next
          elsif ret.area[x][y][z] == [0,0,0,0,0,0] then
            next
          else
            ret.area[x][y][z] = @area[x][y][z]

            #    c
            # a b d f
            #      e

            # 543210
            # abcdef

            #+X -X の当たり判定と連結できるか考える
            #-X方向の検討
            same_X_dec = 0
            if (x-1 >= 0) then
              (x-1).downto(0) do |ix|
                if nobashi_zumi.area[ix][y][z] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] ==  @area[ix][y][z] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[ix][y][z]) ) then
                  same_X_dec += 1
                  if same_X_dec >= max_x_colliwall_num then
                    break #最高 max_x_colliwall_num 個までしか連結しないようにする
                  end
                else
                  break
                end
              end
            end
            if (same_X_dec > 0) then
              #面b方向にも広がりを持たせる
              ret.area[x][y][z][FACE_B_IDX] += same_X_dec
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              #面b方向広がりによってまかなわれる残りの当たり判定は不要
              (x-1).downto((x-1)-(same_X_dec-1)) do |ix|
                ret.area[ix][y][z] = [0,0,0,0,0,0]
                nobashi_zumi.area[ix][y][z] = SUMI_FLG
              end
            end

            #+X方向の検討
            same_X_inc = 0
            if (x+1 <= @len-1) then
              (x+1).upto(@len-1) do |ix|
                if nobashi_zumi.area[ix][y][z] == SUMI_FLG then
                  break
                elsif (ret.area[x][y][z] == @area[ix][y][z] &&
                    ( exArea.area[x][y][z] < KABE_BOX_VAL || exArea.area[x][y][z] == exArea.area[ix][y][z])) then
                  same_X_inc += 1
                  if same_X_inc >= max_x_colliwall_num then
                    break #最高 max_x_colliwall_num 個までしか連結しないようにする
                  end
                else
                  break
                end
              end
            end
            if (same_X_inc > 0) then
              #面f方向にも広がりを持たせる
              ret.area[x][y][z][FACE_F_IDX] += same_X_inc
              nobashi_zumi.area[x][y][z] = SUMI_FLG
              #面f方向広がりによってまかなわれる残りの当たり判定は不要
              (x+1).upto((x+1)+(same_X_inc-1)) do |ix|
                ret.area[ix][y][z] = [0,0,0,0,0,0]
                nobashi_zumi.area[ix][y][z] = SUMI_FLG
              end
            end

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
      fullfull(x-1, y, z, val)
    end

    if x+1 <= @len-1    && @area[x+1][y][z] == KARA_VAL then
      fullfull(x+1, y, z, val)
    end

    if y-1 >= 0         && @area[x][y-1][z] == KARA_VAL then
      fullfull(x, y-1, z, val)
    end

    if y+1 <= @height-1 && @area[x][y+1][z] == KARA_VAL then
      fullfull(x, y+1, z, val)
    end

    if z-1 >= 0         && @area[x][y][z-1] == KARA_VAL then
      fullfull(x, y, z-1, val)
    end

    if z+1 <= @width-1  && @area[x][y][z+1] == KARA_VAL then
      fullfull(x, y, z+1, val)
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
