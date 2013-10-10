#pragma once

#include <zenilib.h>

void save_score();

class Next_level_button : public Zeni::Text_Button {
private:

public:
	Next_level_button() : Zeni::Text_Button(Zeni::Point2f(500.0f, 480.0f), Zeni::Point2f(650.0f, 530.0f), "system_36_800x600", "Next level") { }
	void on_accept();
};

class Menu_button : public Zeni::Text_Button {
private:

public:
	Menu_button() : Zeni::Text_Button(Zeni::Point2f(300.0f, 480.0f), Zeni::Point2f(450.0f, 530.0f), "system_36_800x600", "Select level") { }
	void on_accept() {
		//for (int i = level_num; i < num_levels; i++) {
		save_score();
		Zeni::get_Game().pop_state();
		//}
	}
};

class Retry_button : public Zeni::Text_Button {
private:

public:
	Retry_button() : Zeni::Text_Button(Zeni::Point2f(100.0f, 480.0f), Zeni::Point2f(250.0f, 530.0f), "system_36_800x600", "Retry level") { }
	void on_accept();
};

class Scoreboard_State : public Zeni::Widget_Gamestate {
private:
	Next_level_button next;
	Menu_button back;
	Retry_button retry;
	Zeni::String level;
public:
	Scoreboard_State() : Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(), Zeni::Point2f(800.0f, 600.0f))), next(), back(), retry(){
		m_widgets.lend_Widget(next);
		m_widgets.lend_Widget(back);
		m_widgets.lend_Widget(retry);
		Zeni::get_Video().set_clear_Color(Zeni::Color(0, 0, 1, 1));

	};

	void render();
};
