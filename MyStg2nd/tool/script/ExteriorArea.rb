class ExteriorBox
  attr_accessor :X ,:Y, :Z

end



class ExteriorArea
  attr_accessor :width ,:height, :len
  attr_accessor :area
  def initialize(prm_width, prm_height, prm_len)
    @width = prm_width
    @height = prm_height
    @len = prm_len
    @area = Array.new( @width, 0 )
    @area.each_index { |x|
      @area[x] = Array.new( @height, 0 )
      @area[x].each_index { |y|
          @area[x][y] = Array.new( @len, 0 )
      }
    }


    for x in prm_len
      for y in prm_width
        for z in prm_height
          @area[x][y][z] = ExteriorBox.new
        end
      end
    end

  end

end
