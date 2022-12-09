#pragma once
#include "render.h"

class LightArc : public RenderElement {
	virtual void Render(void);
	class Field* field = nullptr;
public:
	void Bind(Field* _field);
	static const int COUNT_QUADS = 20;
	void Prepare(Vert start, Vert end);
	void Animate(float deltaTime);

	Vert upSideCoords  [COUNT_QUADS];
	Vert downSideCoords[COUNT_QUADS];

	float tex[COUNT_QUADS];
};
