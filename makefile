event.o: src/dui/event.c src/dui/event.h src/dui/../dutil/dutil.h \
 src/dui/window.h src/dui/widget/widget.h
	gcc -c -o $@ $<
widget.o: src/dui/widget/widget.c src/dui/widget/widget.h \
 src/dui/widget/../config.h src/dui/widget/../font.h
	gcc -c -o $@ $<
button.o: src/dui/widget/button.c src/dui/widget/button.h \
 src/dui/widget/widget.h src/dui/widget/../window.h \
 src/dui/widget/../config.h src/dui/widget/../event.h \
 src/dui/widget/../font.h
	gcc -c -o $@ $<
range.o: src/dui/widget/range.c src/dui/widget/range.h \
 src/dui/widget/widget.h src/dui/widget/../window.h \
 src/dui/widget/../config.h src/dui/widget/../../dutil/dutil.h \
 src/dui/widget/../event.h src/dui/widget/../font.h
	gcc -c -o $@ $<
radio.o: src/dui/widget/radio.c src/dui/widget/radio.h \
 src/dui/widget/widget.h src/dui/widget/../window.h \
 src/dui/widget/../config.h src/dui/widget/../event.h \
 src/dui/widget/../font.h
	gcc -c -o $@ $<
font.o: src/dui/font.c src/dui/font.h
	gcc -c -o $@ $<
window.o: src/dui/window.c src/dui/window.h src/dui/../dutil/dutil.h \
 src/dui/config.h src/dui/event.h
	gcc -c -o $@ $<
dutil.o: src/dutil/dutil.c src/dutil/dutil.h
	gcc -c -o $@ $<
track.o: src/dstudio/track/track.c src/dstudio/track/track.h
	gcc -c -o $@ $<
main.o: src/dstudio/main.c src/dstudio/../dui/config.h \
 src/dstudio/../dutil/dutil.h src/dstudio/../dui/window.h \
 src/dstudio/../dui/event.h
	gcc -c -o $@ $<
uitest.o: src/dstudio/uitest/uitest.c src/dstudio/uitest/uitest.h \
 src/dstudio/uitest/../../dui/font.h src/dstudio/uitest/../../dui/event.h \
 src/dstudio/uitest/../../dutil/dutil.h \
 src/dstudio/uitest/../../dui/widget/widgets.h \
 src/dstudio/uitest/../../dui/widget/widget.h \
 src/dstudio/uitest/../../dui/widget/button.h \
 src/dstudio/uitest/../../dui/widget/radio.h \
 src/dstudio/uitest/../../dui/widget/range.h
	gcc -c -o $@ $<
dstudio.o: src/dstudio/dstudio.c src/dstudio/../dui/event.h \
 src/dstudio/../dutil/dutil.h src/dstudio/../dui/font.h \
 src/dstudio/../dui/config.h src/dstudio/../dui/widget/widgets.h \
 src/dstudio/../dui/widget/widget.h src/dstudio/../dui/widget/button.h \
 src/dstudio/../dui/widget/radio.h src/dstudio/../dui/widget/range.h \
 src/dstudio/info/info.h src/dstudio/scene/scene.h \
 src/dstudio/track/track.h src/dstudio/pref/pref.h \
 src/dstudio/uitest/uitest.h
	gcc -c -o $@ $<
pref.o: src/dstudio/pref/pref.c src/dstudio/pref/pref.h \
 src/dstudio/pref/../../dui/font.h src/dstudio/pref/../../dui/event.h \
 src/dstudio/pref/../../dutil/dutil.h \
 src/dstudio/pref/../../dui/widget/widgets.h \
 src/dstudio/pref/../../dui/widget/widget.h \
 src/dstudio/pref/../../dui/widget/button.h \
 src/dstudio/pref/../../dui/widget/radio.h \
 src/dstudio/pref/../../dui/widget/range.h
	gcc -c -o $@ $<
info.o: src/dstudio/info/info.c src/dstudio/info/info.h \
 src/dstudio/info/../../dui/config.h src/dstudio/info/../../dutil/dutil.h \
 src/dstudio/info/../../dui/widget/widgets.h \
 src/dstudio/info/../../dui/widget/widget.h \
 src/dstudio/info/../../dui/widget/button.h \
 src/dstudio/info/../../dui/widget/radio.h \
 src/dstudio/info/../../dui/widget/range.h
	gcc -c -o $@ $<
scene.o: src/dstudio/scene/scene.c src/dstudio/scene/scene.h
	gcc -c -o $@ $<

