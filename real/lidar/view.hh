#ifndef VIEW_HH
#define VIEW_HH

#include <vector>

#include <gtkmm/drawingarea.h>

#include "lidar.hh"

int start_view(int argc, char* argv[], Lidar* lidar_device);

class ViewArea : public Gtk::DrawingArea
{
public:
    ViewArea(Lidar* lidar_);
    virtual ~ViewArea();

    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    bool on_timeout();

public:
    Lidar* lidar;
    std::vector<LidarRay> rays;
};

#endif
