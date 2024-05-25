#include "main.hpp"
#include <gtkmm/application.h>

int main(int argc, char *argv[])
{
  std::cout << "привет, мир!" << std::endl;
  auto app = Gtk::Application::create("org.gagagoose.uttl");  /* create app */

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<MainWindow>(argc, argv);
}