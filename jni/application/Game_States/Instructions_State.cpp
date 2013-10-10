#include "Instructions_State.h"

using namespace Zeni;

void Instructions_State::on_key(const SDL_KeyboardEvent &event)
 {
		if (event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED)
			get_Game().pop_state();
	}

void Instructions_State::render() {
	Widget_Gamestate::render();

	Zeni::Font &fr = get_Fonts()["title"];
	Zeni::Video& vr = get_Video();
	int w = get_Window().get_height();

	fr.render_text("Controls",
		Point2f(400.0f, 300.0f - 0.5f * fr.get_text_height()),
		get_Colors()["title_text"],
		ZENI_CENTER);

	render_image("controls", Point2f(), Point2f(w, w));

}