all: main

main: main.cpp mainwindow.h mainwindow.cpp mainwindow.ui
	/usr/lib/qt6/libexec/moc mainwindow.h > moc_mainwindow.cpp
	/usr/lib/qt6/libexec/uic mainwindow.ui > ui_mainwindow.h
	g++ main.cpp mainwindow.cpp moc_mainwindow.cpp \
	-I /usr/include/qt6 -I /usr/include/qt6/QtWidgets \
	-lQt6Widgets -lQt6Core -lQt6Gui \
	-o radiotelescope
