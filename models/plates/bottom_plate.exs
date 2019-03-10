alias LaserPath, as: LP

defmodule BottomPlate do

  def sensor do
    hole_r = 2.1 / 2.0

    hole = LP.Shapes.circle(hole_r)

    [
      hole |> LP.translate(-10.0, 0),
      hole |> LP.translate(10.0, 0),
    ]
  end

  def both_sensors do
    s1x = 0
    s1y = -40

    s2x = s1x
    s2y = s1y + 80

    [
      sensor() |> LP.translate(s1x, s1y),
      sensor() |> LP.translate(s2x, s2y),
    ]
  end

  def rpi3bp do
    hole_r = 2.6 / 2.0
    sep_x = 49
    sep_y = 58

    hole = LP.Shapes.circle(hole_r)

    LP.rotate([
      hole |> LP.translate(-sep_x / 2, -sep_y / 2),
      hole |> LP.translate(sep_x / 2, -sep_y / 2),
      hole |> LP.translate(-sep_x / 2, sep_y / 2),
      hole |> LP.translate(sep_x / 2, sep_y / 2),
    ], 90, 0, 0)
  end

  def mils(x) do
    (x / 1000.0) * 25.4
  end

  def seeduino do
    hole_r = 3.1 / 2.0

    hole = LP.Shapes.circle(hole_r)

    # USB port facing up
    # Coordinates from top left
    holes = [
      hole |> LP.translate(mils(2000), mils(600)),
      hole |> LP.translate(mils(300), mils(2600)),
      hole |> LP.translate(mils(1400), mils(2600)),
    ]

    # Center
    LP.translate(holes, -mils(2100)/2.0, -mils(2600)/2.0)
  end

  def servo_board do
    hole_r = 2.6 / 2.0
    hole = LP.Shapes.circle(hole_r)

    holes = [
      hole |> LP.translate(mils(130), mils(130)),
      hole |> LP.translate(mils(880), mils(130)),
      hole |> LP.translate(mils(130), mils(2330)),
      hole |> LP.translate(mils(880), mils(2330)),
    ]

    LP.translate(holes, -mils(880+130)/2.0, -mils(2450)/2.0)
  end

  def lidar do
    hole_r = 3.1 / 2.0

    hole = LP.Shapes.circle(hole_r)
    dhole = LP.Shapes.circle(7.5)

    [
      dhole |> LP.translate(-29.5, 0),
      dhole |> LP.translate(29.5, 0),
      dhole |> LP.translate(0, 29.5),
      dhole |> LP.translate(0, -29.5),
      hole  |> LP.translate(20.86, 20.86),
      hole  |> LP.translate(-20.86, 20.86),
      hole  |> LP.translate(20.86, -20.86),
      hole  |> LP.translate(-20.86, -20.86),
    ] |> LP.rotate(45)
  end

  def plate_holes do
    # hole_r = 2.7   # 35mm up posts
    hole_r = 2.8

    hole = LP.Shapes.circle(hole_r)

    dx = 244.2 + 2 * hole_r
    dy = 102.2 + 2 * hole_r
    #x0 = 55
    #y0 = 16.5
    x0 = -dx / 2.0
    y0 = -dy / 2.0
    x1 = x0 + dx
    y1 = y0 + dy

    [
      hole |> LP.translate(x0, y0),
      hole |> LP.translate(x0, y1),
      hole |> LP.translate(x1, y0 - 0.5),
      hole |> LP.translate(x1, y1 + 0.5),
    ]
  end

  def wire_guides do
    hole = LP.Shapes.circle(10)

    [
      hole |> LP.translate(120, 15),
      hole |> LP.translate(120, 130),
      hole |> LP.translate(225, 15),
      hole |> LP.translate(225, 130),
    ]
  end

  def cutout_plate do
    x = 360
    y = 145
    LP.Shapes.rect(x, y) |> LP.translate(x/2.0, y/2.0)
  end

  def plate do
    c_y = 145 / 2.0

    # Plate mounting holes
    phx = 360 / 2.0
    phy = c_y

    # The RPLidar A2
    ldx = 305
    ldy = c_y

    # The Seeduino
    duino_x = 225
    duino_y = c_y

    # both sensors
    sensors_x = 170
    sensors_y = c_y

    # Wire Hole
    whx = 170
    why = c_y
    whr = 10

    # Servo Board
    sbx = 120
    sby = c_y

    # The RPI3B+
    rpx = 50
    rpy = c_y

    cuts = [
      plate_holes() |> LP.translate(phx, phy),
      wire_guides(),
      lidar() |> LP.translate(ldx, ldy),
      seeduino() |> LP.translate(duino_x, duino_y),
      both_sensors() |> LP.translate(sensors_x, sensors_y),
      LP.Shapes.circle(whr) |> LP.translate(whx, why),
      servo_board() |> LP.translate(sbx, sby),
      rpi3bp() |> LP.translate(rpx, rpy),
      cutout_plate(),
    ]

    LP.translate(cuts, 10, 10)
  end
end

# Size of plate is 360 * 135
IO.puts BottomPlate.plate |> LP.to_svg(380, 165)
