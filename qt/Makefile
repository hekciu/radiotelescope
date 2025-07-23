all: main

build_dir = build
cpp_dir = cpp
inc_dir = inc

moc_arg = -p ../$(inc_dir)/

main: $(cpp_dir)/main.cpp $(inc_dir)/mainwindow_ui.h $(cpp_dir)/mainwindow.cpp $(cpp_dir)/event_handler.cpp $(cpp_dir)/usb_worker.cpp $(cpp_dir)/decoder.cpp
	mkdir -p $(build_dir) 
	/usr/lib/qt6/libexec/moc $(moc_arg) $(inc_dir)/mainwindow.h > $(build_dir)/moc_mainwindow.cpp
	/usr/lib/qt6/libexec/moc $(moc_arg) $(inc_dir)/event_handler.h > $(build_dir)/moc_event_handler.cpp
	/usr/lib/qt6/libexec/moc $(moc_arg) $(inc_dir)/usb_worker.h > $(build_dir)/moc_usb_worker.cpp
#	/usr/lib/qt6/libexec/uic mainwindow.ui > ui_mainwindow.h
	g++ $(cpp_dir)/main.cpp \
	$(cpp_dir)/mainwindow.cpp $(build_dir)/moc_mainwindow.cpp \
	$(cpp_dir)/event_handler.cpp $(build_dir)/moc_event_handler.cpp \
	$(cpp_dir)/usb_worker.cpp $(build_dir)/moc_usb_worker.cpp \
	$(cpp_dir)/decoder.cpp \
	-I /usr/include/x86_64-linux-gnu/qt6 \
	-I ../common \
	-I $(inc_dir) \
	-lQt6Widgets -lQt6Core -lQt6Gui -lQt6SerialPort -lQt6Charts \
	-o radiotelescope
	rm -r build
