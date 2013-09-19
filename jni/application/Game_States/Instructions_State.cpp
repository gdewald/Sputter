#include "Instructions_State.h"

void Instructions_State::on_key(const SDL_KeyboardEvent &event)
 {
		if (event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
			get_Game().pop_state();
	}

void Instructions_State::render() {
	Widget_Gamestate::render();

	Zeni::Font &fr = get_Fonts()["title"];

	fr.render_text(
#if defined(_WINDOWS)
		"ALT+F4"
#elif defined(_MACOSX)
		"Apple+Q"
#else
		"Ctrl+Q"
#endif
		" to Quit",
		Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
		get_Colors()["title_text"],
		ZENI_CENTER);
}