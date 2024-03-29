/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>
#include "Game_States/Play_State.h"
#include "Game_States/Instructions_State.h"
#include "Game_States/Level_Select_State.h"

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

class Blue_Title_State : public Title_State<Level_Select_State, Instructions_State> {
public:
	void render() {
		Title_State::render();
	}
	Blue_Title_State(Zeni::String title) : Title_State<Level_Select_State, Instructions_State>(title) {
		Zeni::get_Video().set_clear_Color(Zeni::Color(0, 0, 1, 1));
	}
};

class Bootstrap {
  class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
    virtual Gamestate_Base * operator()() {
      Window::set_title("Sputter");

	  get_Controllers();
      get_Video();
      get_Textures();
      get_Fonts();
      get_Sounds();

	  return new Blue_Title_State("Sputter");
	  //return new Title_State<Test_State, Instructions_State>("Placeholder");
	  //return new Title_State<Tutorial_State, Instructions_State>("Putt-putt\nHell");
	}
  } m_goi;

public:
  Bootstrap() {
    g_gzi = &m_goi;
  }
} g_bootstrap;

int main(int argc, char **argv) {
  return zenilib_main(argc, argv);
}
