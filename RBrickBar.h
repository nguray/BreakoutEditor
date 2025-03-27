#pragma once
#include <QtGui>
#include <QWidget>
#include <vector>
#include "editorconsts.h"

class RBrickBar :
	public QWidget
{

	Q_OBJECT

public:

	RBrickBar(QWidget *parent,QImage *img = Q_NULLPTR);
	~RBrickBar();

	int				YtoIndex(int y);
	void			drawSelectedMark(QPainter &qp);

	QImage			*m_imgBricks;

	int					m_id_brick;
	std::vector<QRect> 	m_listBricks;

signals:
	void			brickChanged(int typBrick);


protected:

	void	paintEvent(QPaintEvent *e) override;
	void	mousePressEvent(QMouseEvent* event) override;


};