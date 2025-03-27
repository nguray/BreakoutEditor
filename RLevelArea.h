#pragma once
#include <QtGui>
#include <QWidget>
#include <vector>
#include "editorconsts.h"


class RLevelArea :
	public QWidget
{

	Q_OBJECT

public:

	RLevelArea(QWidget *parent = Q_NULLPTR,QImage *img = Q_NULLPTR);
	~RLevelArea();

	void 	initLevel();
	void	LoadLevel(QString fileName);
	void	SaveLevel(QString fileName);

	QImage				*m_imgBricks;

	int					m_select_brick;
	std::vector<int>	m_tbl_bricks;
	int					m_index_last_input;

public slots:

	void setSelectedBrickSlot(int typBrick);

protected:

	void 	drawBricks(QPainter &qp);
	void 	drawGrid(QPainter &qp);
	void	paintEvent(QPaintEvent *e) override;
	void	mousePressEvent(QMouseEvent* event) override;
	void	mouseMoveEvent(QMouseEvent* event) override;


};

