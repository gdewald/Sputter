#pragma once

#include <zenilib.h>
#include <utility>
#include <list>
#include "Play_State.h"

extern int level_num;
const int num_levels = 3;
const Zeni::String level_name[num_levels] = { "level_1", "level_2", "level_3" };

class Accept_button : public Zeni::Text_Button {
private:

public:
	Accept_button() : Zeni::Text_Button(Zeni::Point2f(500.0f, 480.0f), Zeni::Point2f(700.0f, 530.0f), "system_36_800x600", "Accept") { }
	void on_accept() {
		//for (int i = level_num; i < num_levels; i++) {

			Zeni::get_Game().push_state(new Play_State(level_name[level_num]));
		//}
	}
};

class Back_button : public Zeni::Text_Button {
public:
	Back_button() : Zeni::Text_Button(Zeni::Point2f(200.0f, 380.0f), Zeni::Point2f(280.0f, 430.0f), "system_36_800x600", "Prev") { }

	void on_accept() {
		level_num--;
		if (level_num < 0) level_num = 0;
	}
};

class Forward_button : public Zeni::Text_Button {
public:
	Forward_button() : Zeni::Text_Button(Zeni::Point2f(300.0f, 380.0f), Zeni::Point2f(380.0f, 430.0f), "system_36_800x600", "Next") { }

	void on_accept() {
		level_num = (level_num + 1) % num_levels;
	}
};

class Level_Select_State : public Zeni::Widget_Gamestate {
private:
	static std::list<Zeni::String> levels;
	std::list<Zeni::String>::iterator cur_level;
	Accept_button accept;
	Back_button back;
	Forward_button fwd;

public:
	Level_Select_State() : Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(), Zeni::Point2f(800.0f, 600.0f))) {
		level_num = 0;
		m_widgets.lend_Widget(accept);
		m_widgets.lend_Widget(fwd);
		m_widgets.lend_Widget(back);
	};

	static void push_next_level() {
		if (level_num + 1 >= num_levels) return;
		Zeni::get_Game().push_state(new Play_State(level_name[++level_num]));
	}
	static void push_current_level() {
		Zeni::get_Game().push_state(new Play_State(level_name[level_num]));
	}
	static Zeni::String get_current_level() {
		return level_name[level_num];
	}

	void render() {
		Zeni::Widget_Gamestate::render();
		//render_image(level_name[i], Zeni::Point2f(200.0f, 100.0f), Zeni::Point2f(380.0f, 360.0f), 0.0f, 1.0f, Zeni::Point2f(), false, Color());
		Zeni::get_Fonts()["system_36_800x600"].render_text(level_name[level_num], Zeni::Vector3f((380.0f + 200.0f)/2.0f, (100.0f + 360.0f)/2.0f, 0.0f), Zeni::Vector3f(1, 0, 0), Zeni::Vector3f(0, 1, 0), Zeni::get_Colors()["white"]);
		//get_Fonts()["system_36_800x600"].render_text(potato, Vector3f(50.0f, 130.0f, 0), Vector3f(1, 0, 0), Vector3f(0, 1, 0), cr["white"]);
	}
};
