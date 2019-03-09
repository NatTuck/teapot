
require 'nokogiri'

class Path
  def initialize(x0 = 0, y0 = 0)
    @d = ["M", x0, y0]
  end

  def line_to(dx, dy)
    @d << ["l", dx, dy]
  end

  def arc_to(dx, dy, rx, ry, large = 0, sweep = 0)
    @d << ["a", rx, ry, 0, large, sweep, dx, dy]
  end

  def circle(r, sweep = 0)
    @d << ["m", -r, 0]
    arc_to(2 * r, 0, r, r, 1, sweep)
    arc_to(-2 * r, 0, r, r, 1, sweep)
  end

  def close()
    @d << ["z"]
  end

  def to_s
    @d.flatten.join(' ')
  end
end

class SVG
  def initialize(ww = 100, hh = 100)
    @ww = ww
    @hh = hh
    @paths = []
  end

  def path(x0, y0)
    pp = Path.new(x0, y0)
    yield(pp)
    @paths << pp
  end

  def add_circle(x, y, r)
    path(x, y) do |pp|
      pp.circle(r)
    end
  end

  def to_xml
    tmpl = <<-"ENDXML"
      <svg width="#{@ww}mm" height="#{@hh}mm"
           viewBox="0 0 #{@ww} #{@hh}"
           xmlns="http://www.w3.org/2000/svg" />
    ENDXML
    doc = Nokogiri::XML(tmpl)
    doc.remove_namespaces!
    root = doc.xpath("//svg")[0]

    @paths.each do |path|
      node = Nokogiri::XML::Node.new("path", doc)
      node["fill"] = "none"
      node["stroke"] = "black"
      node["stroke-width"] = 1
      node["d"] = path.to_s
      root.add_child(node)
    end

    root["xmlns"] = "http://www.w3.org/2000/svg"
    doc.to_xml
  end
end

