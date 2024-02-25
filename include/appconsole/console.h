#pragma once

#include <ldv/screen.h>
#include <ldv/box_representation.h>
#include <ldv/ttf_representation.h>
#include <ldv/color.h>
#include <ldv/rect.h>
#include <ldi/sdl_input.h>
#include <functional>
#include <sstream>
#include <string>

namespace appconsole {

class console {

	public:

							console(ldv::rect, const ldv::ttf_font&, std::function<void(const std::string&)>);

	void                    draw(ldv::screen&);

	std::ostream&           get_output() {return output_stream;}

	void                    input(ldi::sdl_input&);

	console&                set_position(ldv::point);
	console&                set_width(unsigned);
	console&                set_height(unsigned);
	console&                set_background_color(ldv::rgba_color);
	console&                set_text_color(ldv::rgba_color);

	private:

	std::function<void(const std::string&)> onenter;
	ldv::box_representation rect;
	ldv::ttf_representation input_view,
	                        output_view;
	std::ostringstream      output_stream;
	long                    output_stream_position{0};
	unsigned                w, h;
	int                     enter_input;
	std::string             current_command;

};
}
