#pragma once
#include <zenilib.h>
//#include "Play_State.h"

class Instructions_State : public Zeni::Widget_Gamestate {
	Instructions_State(const Instructions_State &);
	Instructions_State operator=(const Instructions_State &);
	class Goals_button : public Zeni::Text_Button {
	private:

	public:
		Goals_button() : Zeni::Text_Button(Zeni::Point2f(100.0f, 10.0f), Zeni::Point2f(220.0f, 30.0f), "system_36_800x600", "Goals") { }

		void on_hover() {
			set_image("goals");
		}
	} g;

	class Controls_button : public Zeni::Text_Button {
	private:

	public:
		Controls_button() : Zeni::Text_Button(Zeni::Point2f(230.0f, 10.0f), Zeni::Point2f(350.0f, 30.0f), "system_36_800x600", "Controls") { }

		void on_hover() {
			set_image("controls");
		}
	} c;

	class Terrains_button : public Zeni::Text_Button {
	private:

	public:
		Terrains_button() : Zeni::Text_Button(Zeni::Point2f(360.0f, 10.0f), Zeni::Point2f(480.0f, 30.0f), "system_36_800x600", "Terrains") { }

		void on_hover() {
			set_image("terrains");
		}
	} t;

	class Powerups_button : public Zeni::Text_Button {
	private:

	public:
		Powerups_button() : Zeni::Text_Button(Zeni::Point2f(490.0f, 10.0f), Zeni::Point2f(610.0f, 30.0f), "system_36_800x600", "Powerups") { }

		void on_hover() {
			set_image("powerups");
		}
	} p;
	//Controls_button c;
	//Terrains_button t;
	//Powerups_button p;
	//Goals_button g;

public:
	Instructions_State()
		: Zeni::Widget_Gamestate(std::make_pair(Zeni::Point2f(0.0f, 0.0f), Zeni::Point2f(800.0f, 600.0f))), c(), t(), p(), g() {
			m_widgets.lend_Widget(c);
			m_widgets.lend_Widget(p);
			m_widgets.lend_Widget(t);
			m_widgets.lend_Widget(g);
			Zeni::get_Video().set_clear_Color(Zeni::Color(0, 0, 1, 1));
	}
	static void set_image(Zeni::String image_name_) { image_name = image_name_; }
private:
	static Zeni::String image_name;
	void render();
};