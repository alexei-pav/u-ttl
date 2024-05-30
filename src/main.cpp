#include "main.hpp"
#include "gtkmm/enums.h"
#include <gtkmm/application.h>


MainWindow::MainWindow()
    : m_VBox(Gtk::Orientation::VERTICAL),
      m_Button("Print Text")
{
  set_title("U-TTL");                       /* set application title */
  set_default_size(200, 200); /* set default window size */

  set_child(m_VBox);

  m_VBox.append(m_Entry);
  m_VBox.append(m_Button);
  m_VBox.set_valign(Gtk::Align::CENTER);
  m_VBox.set_halign(Gtk::Align::CENTER);

  m_Button.signal_clicked()
        .connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

  m_VBox.show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
  std::cout << "Entered text: " 
      << m_Entry.get_text() << std::endl;
}

int main(int argc, char *argv[])
{

  std::cout << "привет, мир!" << std::endl;
  auto app = Gtk::Application::create("org.gagagoose.uttl");  /* create app */

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<MainWindow>(argc, argv);
}