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

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>
#include <QCommonStyle>
#include <QStyleOptionGroupBox>

class StyleOptionDecoratedGroupBox : public QStyleOptionGroupBox
{
public:
	explicit StyleOptionDecoratedGroupBox();

	QPixmap pixmap;
	int offset;
	int leftSpace;
	int rightSpace;
};

class CustomStyle : public QCommonStyle
{
	Q_OBJECT
public:
	explicit CustomStyle();

	void drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const override;
};

class DecoratedGroupBox : public QGroupBox
{
	Q_OBJECT
public:
	explicit DecoratedGroupBox(const QString &title, QWidget *parent = nullptr);

	QPixmap pixmap() const;
	void setPixmap(const QPixmap &pixmap);

	int offset() const;
	void setOffset(int offset);
	int leftSpace() const;
	void setLeftSpace(int leftSpace);
	int rightSpace() const;
	void setRightSpace(int rightSpace);
	void setSpaces(int leftSpace, int rightSpace);

protected:
	void paintEvent(QPaintEvent *) override;

private:
	QPixmap m_pixmap;
	int m_offset;
	int m_leftSpace;
	int m_rightSpace;
};

#endif // GROUPBOX_H
