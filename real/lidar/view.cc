#include <ctime>
#include <cmath>
#include <cairomm/context.h>
#include <glibmm/main.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include "view.hh"

int
start_view(int argc, char* argv[], Lidar* lidar_device)
{
    auto app = Gtk::Application::create(argc, argv, "com.example.view-lidar");

    Gtk::Window win;
    win.set_title("LIDAR View");

    ViewArea c(lidar_device);
    win.add(c);
    c.show();

    return app->run(win);
}

ViewArea::ViewArea(Lidar* lidar_)
    : lidar(lidar_)
{
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &ViewArea::on_timeout), 100);
}

ViewArea::~ViewArea()
{
}

bool
ViewArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
    // the center of the window
    cr->scale(width, height);
    cr->translate(0.5, 0.5);
    cr->set_line_width(0.001);

    for (auto ray : this->rays) {
        float rr = ray.dst / 5.0;
        cr->save();
        //cr->set_line_width(1.0);
        cr->set_source_rgba(0.7, 0.7, 0.7, 0.8); // gray
        cr->move_to(0, 0);
        cr->line_to(rr * sin(ray.ang), rr * -cos(ray.ang));
        cr->stroke();
        cr->restore();
    }

    // draw a little dot in the middle
    cr->arc(0, 0, 0.005, 0, 2 * M_PI);
    cr->fill();

    return true;
}


bool
ViewArea::on_timeout()
{
    // force our program to redraw the entire clock.
    auto win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                         get_allocation().get_height());
        win->invalidate_rect(r, false);
    }

    this->rays = lidar->get_scan();

    return true;
}
