class Veartex
  attr_accessor :X ,:Y, :Z
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
  end
end

class Box
  attr_accessor :X ,:Y, :Z
  def initialize
    @X = 0
    @Y = 0
    @Z = 0
  end
end

class ExteriorArea
  attr_accessor :width ,:height, :len
  attr_accessor :area

  KARA_VAL = " "
  KABE_VAL = "x"
  FULL_VAL = "~"

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


  def getAnalyze
     ret = ExteriorArea.new(@len, @height, @width)

     for x in 0..@len-1
      for y in 0..@height-1
        for z in 0..@width-1
          type = 0b111111
          if @area[x][y][z] == KARA_VAL then
            ret.area[x][y][z] = "   "
          elsif @area[x][y][z] == FULL_VAL then
            ret.area[x][y][z] = "[] "

          elsif @area[x][y][z] == KABE_VAL then
            #6面の開き具合を調べる

            #abcdef

            #    c
            # a b d f
            #      e

            if (x-1 >= 0 && @area[x-1][y][z] == FULL_VAL) then #bが開いている
              #               abcdef
              type = type ^ 0b010000
            end

            if (x+1 <= @len-1 && @area[x+1][y][z] == FULL_VAL) then #fが開いている
              #               abcdef
              type = type ^ 0b000001
            end

            if (y-1 >= 0 && @area[x][y-1][z] == FULL_VAL) then #dが開いている
              #               abcdef
              type = type ^ 0b000100
            end

            if (y+1 <= @height-1 && @area[x][y+1][z] == FULL_VAL) then #aが開いている
              #               abcdef
              type = type ^ 0b100000
            end

            if (z-1 >= 0         && @area[x][y][z-1] == FULL_VAL) then #cが開いている
              #               abcdef
              type = type ^ 0b001000
            end

            if (z+1 <= @width-1  && @area[x][y][z+1] == FULL_VAL) then #eが開いている
              #               abcdef
              type = type ^ 0b000010
            end
            ret.area[x][y][z] = sprintf("%02d ", type)

          end
        end
      end
    end

    return ret

  end




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
              #スタックオーバーを潰す
              print "."
            end

          end

        end
      end
    end
    print "\n"

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


  def dump
    for l in 0..@len-1
      print l,")------------------\n"
      for h in 0..@height-1
        for w in 0..@width-1
          print @area[l][h][w]
        end
        print  "\n"
      end
    end
  end


end
