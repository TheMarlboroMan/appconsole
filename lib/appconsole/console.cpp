#include <appconsole/console.h>

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
	input_view.set_blend(ldv::representation::blends::alpha);
	output_view.set_blend(ldv::representation::blends::alpha);
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
	input_view.draw(_display);
	output_view.draw(_display);
}

void console::input(
	ldi::sdl_input& _input
) {

	if(_input.is_event_text()) {

		input_view.set_text(_input.get_text_input());
		return;
	}

	if(_input.is_key_down(40)) { //40 is enter

		const auto str=_input.get_text_input();
		_input.clear_text_input();
		input_view.set_text("");
		onenter(str);
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
