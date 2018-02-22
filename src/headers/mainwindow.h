#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define WINDOW_TITLE "BITS-DIC"

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include "dic.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private slots:
		void on_actionLoad_Reference_Image_triggered();
		void on_actionLoad_Current_Image_s_triggered();

		void on_prevImage_clicked();

		void on_nextImage_clicked();

private:
		Ui::MainWindow *ui;
		Dic *dic;
		int currImgIndex;
		void setCurrentImageIndex(int);
		void loadImage(QImage *, QLabel *, int);
};

#endif // MAINWINDOW_H
