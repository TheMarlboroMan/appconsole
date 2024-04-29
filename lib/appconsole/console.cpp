#include <appconsole/console.h>
#include <iostream>

using namespace appconsole;

console::console(
	ldv::rect _position, 
	const ldv::ttf_font& _ttf_font,  
	std::function<void(const std::string&)> _onenter
):
	onenter{_onenter},
	rect(_position, ldv::rgba8(0, 0, 0, 255)),
	input_view(_ttf_font, ldv::rgba8(255, 255, 255, 255)),
	output_view(_ttf_font, ldv::rgba8(255, 255, 255, 255)),
	w{_position.w},
	h{_position.h}
{

	rect.set_blend(ldv::representation::blends::alpha);

//TODO: More options...
	input_view.set_blend(ldv::representation::blends::alpha);
	output_view.set_blend(ldv::representation::blends::alpha);

	input_view.set_max_width(w);
	output_view.set_max_width(w);
}

void console::draw(
	ldv::screen& _display
) {

	if(output_stream_position!=output_stream.tellp()) {

		output_view.set_text(output_stream.str());
		output_stream.str("");
		output_stream_position=output_stream.tellp();
	}

	rect.draw(_display);

	input_view.align(
		rect, 
		{
			ldv::representation_alignment::h::inner_left,
			ldv::representation_alignment::v::inner_bottom,
			4, 4
		}
	);

	output_view.align(
		rect,
		{
			ldv::representation_alignment::h::inner_left,
			ldv::representation_alignment::v::inner_top,
			4, 4
		}
	);

	input_view.draw(_display);
	output_view.draw(_display);
}

void console::input(
	ldi::sdl_input& _input
) {
	//Will restore original values on exit.
	struct restorer {

		restorer(ldi::sdl_input& _input)
			:keydown_control{_input.get_keydown_control_text_filter()}, 
			input{_input} {

			input.set_keydown_control_text_filter(false); //Do not pass enter or backspace, let us process it.
		}

		~restorer() {

			input.set_keydown_control_text_filter(keydown_control);
		};

		bool keydown_control;
		ldi::sdl_input& input;
	} r{_input};

	if(_input.is_key_down(42)) {//backspace...

		if(current_command.size()) {

			current_command.pop_back();
			input_view.set_text(current_command);
		}

		return;
	}

	if(_input.is_key_down(40)) { //40 is enter

		input_view.set_text("");	//Will restore original values on exit.
		onenter(current_command);
		current_command="";
		return;
	}

	if(_input.is_event_text()) {

		current_command+=_input.get_text_input();
		_input.clear_text_input();
		input_view.set_text(current_command);
		return;
	}
}

console& console::set_position(
	ldv::point _point
) {

	rect.go_to(_point);
	return *this;
}

console& console::set_width(
	unsigned _w
) {

	w=_w;
	rect.set_dimensions(w, h);
	input_view.set_max_width(w);
	output_view.set_max_width(w);
	return *this;
}

console& console::set_height(
	unsigned _h
) {

	h=_h;
	rect.set_dimensions(w, h);
	return *this;
}

console& console::set_background_color(
	ldv::rgba_color _color
) {

	rect.set_color(_color);
	return *this;
}

console& console::set_text_color(
	ldv::rgba_color _color
) {

	input_view.set_color(_color);
	output_view.set_color(_color);
	return *this;
}
