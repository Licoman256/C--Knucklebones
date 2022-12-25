#pragma once
#include "render.h"

class LightArc : public RenderElement, public Animated {
	virtual void Render(void);
	void DebugRenderArc();
	class Field* field = nullptr;
public:
	virtual void Animate(float deltaTime);
	virtual bool DoneAnimating() { return false; }
	virtual void Reset() {}

	float GetTotalDistance();
	void Bind(Field* _field);
	static const int COUNT_QUADS = 50;
	void Prepare(Vert start, Vert end);
	void ChangeGravity(Vert& start);
	int GetGravitySign();
	Vert GetPoint(float travelDist);

private:
	float thickness = 0.f;
	float gravity = 0.f;
	float speed = 3.f;

	struct ArcElem {
		struct {
			Vert up;
			Vert md;
			Vert dn;
		} side;
		float tex;
		float trvDist;
	};
	ArcElem elems[COUNT_QUADS];

	Vert srcStart, srcEnd;

	void FillTrajectotyPoint(int i, const Vert& nextVel, const Vert& velocity, const Vert& nextPoint);
	void ConvertTravelDist(float travelDist, int& quadIdx, float& fraction);
};
