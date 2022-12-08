#pragma once
#include "render.h"

class LightArc : public RenderElement {
	virtual void Render(void);
	static const int COUNT_QUADS = 10;

public:
	void CalcNew(Vert start, Vert end);
	void Animate(float deltaTime);

	Vert upSide  [COUNT_QUADS];
	Vert downSide[COUNT_QUADS];
};

