/*
	gr-scan - A GNU Radio signal scanner
	Copyright (C) 2012  Nicholas Tomlinson

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <cmath>
#include <stdint.h>
#include <stdio.h>

#include <boost/foreach.hpp>
#include <gnuradio/top_block.h>
#include <osmosdr/source.h>
#include <gnuradio/soapy/source.h>
#include <gnuradio/blocks/stream_to_vector.h>
#include <gnuradio/fft/fft_v.h>
#include <gnuradio/blocks/complex_to_mag_squared.h>
#include <gnuradio/filter/single_pole_iir_filter_ff.h>
#include <gnuradio/blocks/nlog10_ff.h>
#include "scanner_sink.hpp"

class TopBlock : public gr::top_block
{
	public:
		TopBlock(double centre_freq_1, double centre_freq_2, double sample_rate, double fft_width, double bandwidth1, double bandwidth2,
				double step, unsigned int avg_size, double spread, double threshold, double ptime, FILE *outcsv);

		virtual ~TopBlock();

	private:
		/* http://en.wikipedia.org/w/index.php?title=Window_function&oldid=508445914 */
		std::vector<float> GetWindow(size_t n);
		double GetWindowPower();

		size_t vector_length;
		std::vector<float> window;

		osmosdr::source::sptr source;
		gr::blocks::stream_to_vector::sptr stv;
		gr::fft::fft_v<float, true>::sptr fft;
		gr::blocks::complex_to_mag_squared::sptr ctf;
		gr::filter::single_pole_iir_filter_ff::sptr iir;
		gr::blocks::nlog10_ff::sptr lg;
		scanner_sink::sptr sink;
};
