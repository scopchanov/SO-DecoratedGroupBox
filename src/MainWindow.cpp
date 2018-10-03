/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MainWindow.h"
#include "DecoratedGroupBox.h"
#include <QBoxLayout>
#include <QRadioButton>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{
	auto *groupBox = new DecoratedGroupBox(tr("Test"), this);
	auto *l = new QVBoxLayout(groupBox);
	auto *radio1 = new QRadioButton(tr("Icon 1"), this);
	auto *radio2 = new QRadioButton(tr("Icon 2"), this);
	auto *radio3 = new QRadioButton(tr("Icon 3"), this);

	radio1->setChecked(true);

	l->addWidget(radio1);
	l->addWidget(radio2);
	l->addWidget(radio3);

	groupBox->setPixmap(QPixmap(":/pix/images/home.png"));
//	groupBox->setOffset(27);
//	groupBox->setSpaces(15, 15);

	setCentralWidget(groupBox);
	setContentsMargins(12, 12, 12, 12);
	resize(300, 200);

	connect(radio1, &QRadioButton::toggled, [groupBox](bool checked){
		if (checked)
			groupBox->setPixmap(QPixmap(":/pix/images/home.png"));
	});

	connect(radio2, &QRadioButton::toggled, [groupBox](bool checked){
		if (checked)
			groupBox->setPixmap(QPixmap(":/pix/images/next.png"));
	});

	connect(radio3, &QRadioButton::toggled, [groupBox](bool checked){
		if (checked)
			groupBox->setPixmap(QPixmap(":/pix/images/export.png"));
	});
}
