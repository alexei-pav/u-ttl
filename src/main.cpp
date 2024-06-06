#include "main.hpp"
#include <gtkmm/application.h>


MainWindow::MainWindow()
    : m_HBox(Gtk::Orientation::HORIZONTAL, 0),
      m_VBox(Gtk::Orientation::VERTICAL, 10),
      m_Button("Print Text"),
      m_Button2("test btn")
{
  set_title("U-TTL");                                     /* set application title */
  set_default_size(200, 200);               /* set default window size */

  set_child(m_VBox);

  m_HBox.append(m_Entry);
  m_HBox.append(m_Button);

  m_VBox.append(m_HBox);
  m_VBox.append(m_Button2);

  m_Button.signal_clicked()
        .connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

  m_VBox.show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
  if ( m_Entry.get_text() != "")
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