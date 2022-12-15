#pragma once
#include "render.h"

class LightArc : public RenderElement {
	virtual void Render(void);
	void DebugRenderArc();
	class Field* field = nullptr;
public:
	void Bind(Field* _field);
	static const int COUNT_QUADS = 50;
	void Prepare(Vert start, Vert end);
	void Animate(float deltaTime);

	Vert GetPoint(float travelDist);

private:
	float thickness = 0.f;
	float gravity = 0.f;
	float speed = 3.f;

	Vert upSide[COUNT_QUADS];
	Vert dnSide[COUNT_QUADS];
	float tex[COUNT_QUADS];
	void FillTrajectotyPoint(int i, const Vert& nextVel, const Vert& velocity, const Vert& nextPoint);
};
