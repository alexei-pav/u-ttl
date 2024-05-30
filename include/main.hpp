#ifndef MAIN_H
#define MAIN_H

#include <iostream>

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();

protected:
  void on_button_clicked();
  //Member widgets:
  Gtk::Box m_VBox;
  Gtk::Entry m_Entry;
  Gtk::Button m_Button;
};

#endif