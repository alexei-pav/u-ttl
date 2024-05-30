#include "main.hpp"
#include <gtkmm/application.h>

HelloWorld::HelloWorld()
: m_button("Hello World")   // creates a new button with label "Hello World".
{
  set_title("Basic application");
  set_default_size(200, 200);
  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));

  set_child(m_button);
  // The final step is to display this newly created widget...
  m_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}

int main(int argc, char *argv[])
{
  std::cout << "привет, мир!" << std::endl;
  auto app = Gtk::Application::create("org.gagagoose.uttl");  /* create app */

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<HelloWorld>(argc, argv);
}