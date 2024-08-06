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

#include <stdio.h>
#include <ctime>
#include <set>
#include <utility>

#include <gnuradio/block.h>
#include <gnuradio/io_signature.h>
#include <osmosdr/source.h>

class scanner_sink : public gr::block
{
	public:
		typedef std::shared_ptr<scanner_sink> sptr;

		scanner_sink(osmosdr::source::sptr source, unsigned int vector_length, double centre_freq_1, double centre_freq_2, double bandwidth0, double bandwidth1, double bandwidth2,
				double step, unsigned int avg_size, double spread, double threshold, double ptime, FILE *outcsv);

		virtual ~scanner_sink();

		static sptr make(osmosdr::source::sptr source, unsigned int vector_length, double centre_freq_1, double centre_freq_2, double bandwidth0, double bandwidth1, double bandwidth2,
					  	 double step, unsigned int avg_size, double spread, double threshold, double ptime, FILE *outcsv);
		
	private:
		int general_work(int noutput_items, gr_vector_int &ninput_items, gr_vector_const_void_star &input_items, gr_vector_void_star &output_items);
		int ProcessVector(float *input);
		void PrintSignals(double *freqs, float *bands1, float *bands2);
		bool TrySignal(double min, double max);
		void Rearrange(float *bands, double *freqs, double centre, double bandwidth);
		void GetBands(float *powers, float *bands, unsigned int bandwidth);
		void ZeroBuffer();
		void CloseCSV();
		void WriteCSV(float freq, float width, float peak, float diff);
		
		//std::set<std::pair<double, double>> m_signals;
		std::set<double> m_signals;
		osmosdr::source::sptr m_source;
		float *m_buffer;
		unsigned int m_vector_length;
		unsigned int m_count;
		unsigned int m_wait_count;
		unsigned int m_avg_size;
		double m_step;
		double m_centre_freq_1;
		double m_centre_freq_2;
		double m_bandwidth0;
		double m_bandwidth1;
		double m_bandwidth2;
		double m_threshold;
		double m_spread;
		double m_time;
		FILE  *m_outcsv;
		time_t m_start_time;
};
