#!/bin/bash

libs="/usr/lib/x86_64-linux-gnu/liblog4cpp.so /usr/lib/x86_64-linux-gnu/libgnuradio-analog.so /usr/lib/x86_64-linux-gnu/libgnuradio-filter.so   /usr/lib/x86_64-linux-gnu/libgnuradio-trellis.so /usr/lib/x86_64-linux-gnu/libgnuradio-audio.so     /usr/lib/x86_64-linux-gnu/libgnuradio-iio.so      /usr/lib/x86_64-linux-gnu/libgnuradio-uhd.so /usr/lib/x86_64-linux-gnu/libgnuradio-blocks.so    /usr/lib/x86_64-linux-gnu/libgnuradio-network.so  /usr/lib/x86_64-linux-gnu/libgnuradio-video-sdl.so /usr/lib/x86_64-linux-gnu/libgnuradio-channels.so  /usr/lib/x86_64-linux-gnu/libgnuradio-pdu.so /usr/lib/x86_64-linux-gnu/libgnuradio-vocoder.so /usr/lib/x86_64-linux-gnu/libgnuradio-digital.so /usr/lib/x86_64-linux-gnu/libgnuradio-pmt.so /usr/lib/x86_64-linux-gnu/libgnuradio-wavelet.so /usr/lib/x86_64-linux-gnu/libgnuradio-dtv.so /usr/lib/x86_64-linux-gnu/libgnuradio-qtgui.so /usr/lib/x86_64-linux-gnu/libgnuradio-zeromq.so /usr/lib/x86_64-linux-gnu/libgnuradio-fec.so /usr/lib/x86_64-linux-gnu/libgnuradio-runtime.so /usr/lib/x86_64-linux-gnu/libgnuradio-fft.so /usr/lib/x86_64-linux-gnu/libgnuradio-soapy.so"

while test -n "$1"; do
    sym=$1
    shift
    for lib in $libs; do
        if nm -D $lib | c++filt | grep -q "[^U] $sym"; then
            echo "symbol $sym found in $lib"
        fi
    done
done