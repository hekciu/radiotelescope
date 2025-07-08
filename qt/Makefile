all: main

main: main.cpp mainwindow.h mainwindow_ui.h mainwindow.cpp # mainwindow.ui
	/usr/lib/qt6/libexec/moc mainwindow.h > moc_mainwindow.cpp
	/usr/lib/qt6/libexec/moc event_handler.h > moc_event_handler.cpp
	/usr/lib/qt6/libexec/moc usb_worker.h > moc_usb_worker.cpp
#	/usr/lib/qt6/libexec/uic mainwindow.ui > ui_mainwindow.h
	g++ main.cpp \
	mainwindow.cpp moc_mainwindow.cpp \
	event_handler.cpp moc_event_handler.cpp \
	usb_worker.cpp moc_usb_worker.cpp \
	-I /usr/include/x86_64-linux-gnu/qt6 \
	-lQt6Widgets -lQt6Core -lQt6Gui -lQt6SerialPort \
	-o radiotelescope
	rm ./moc_*
