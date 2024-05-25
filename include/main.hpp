#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class MainWindow: public Gtk::Window
{
    public:
        MainWindow();           /* define class constructor */
        virtual ~MainWindow();  /* define class destructor */

    protected:
        Gtk::Button btn1;       /* create button */
};

#endif
