#include "LightArc.h"
#include "field.h"
#include "random.h"

//#define DEBUG_ARC_RENDER

void LightArc::Bind(Field* _field) {
	field = _field;
}

void LightArc::Render() {
	MyColor color = colors::white;
	glColor3d(color.red, color.green, color.blue);

	field->ChangeTexture(E_LIGHTNING);
	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < COUNT_QUADS; i++) {
			glTexCoord2f(elems[i].tex, 0); glVertex2f(elems[i].side.dn.x, elems[i].side.dn.y);
			glTexCoord2f(elems[i].tex, 1); glVertex2f(elems[i].side.up.x, elems[i].side.up.y);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	DebugRenderArc();
}

void LightArc::DebugRenderArc() {
#ifdef DEBUG_ARC_RENDER
	glColor3d(0, 0, 0);

	glBegin(GL_LINES);
	for (int i = 0; i < COUNT_QUADS; i++) {
		glVertex2f(dnSide[i].x, dnSide[i].y);
		glVertex2f(upSide[i].x, upSide[i].y);

		if (i < COUNT_QUADS - 1) {
			auto midStart = GetPoint((float)i);
			auto midEnd = GetPoint((float)i + .95f);
			glVertex2f(midStart.x, midStart.y);
			glVertex2f(midEnd.x, midEnd.y);
		}
	}
	glEnd();
#endif // DEBUG_ARC_RENDER
}

Vert Field::GetSlotCenter(int groupIdx, int rowIdx, float ySlOrigin) {
	Vert slotCoords;
	slotCoords.x = xSlotOrigin + groupIdx * (xOffset + slotLen)     + slotLen    * .5f;
	slotCoords.y = ySlOrigin   - rowIdx   * (yOffset + slotHeight)  - slotHeight * .5f;

	return slotCoords;
}

void Field::PrepareArc(Player& player) {
	// start
	auto layout = GetLayout(&player);
	Vert boxCoords = {       xBoxOrigin + slotLen * .5f,
					  layout.yBoxOrigin - slotHeight * .5f };


	// end
	auto groupIdx = player.addingTo;
	auto rowIdx = player.groups[groupIdx].addingTo;
	Vert slotCoords = GetSlotCenter(groupIdx, rowIdx, layout.ySlotOrigin);

	// relay
	arc.Prepare(boxCoords, slotCoords);

	// assign dice
	movingDice.SetValue(player.boxDice.GetValue());

	// prepare shake
	int direction = arc.GetGravitySign();
	float maxTime = sqrtf(slotCoords.x - boxCoords.x);

	shakingSlot.Reset();
	shakingSlot.SetParams(player, rowIdx, groupIdx, layout.color, layout.ySlotOrigin, direction, maxTime);
}

int LightArc::GetGravitySign() {
	return gravity > 0 ? -1 : 1;
};

void LightArc::Prepare(Vert start, Vert end) {
	Vert target { (end.x - start.x) ,
				 (end.y - start.y) };

	thickness = target.x / 5;
	ChangeGravity(start);

	// calc initial velocity 
	// - we will simulate one sec in each loop iteration
	Vert velocity;
	float travelDist = (COUNT_QUADS - 1);
	velocity.x = target.x / travelDist;
	float verticalShift = gravity * 0.5f * travelDist * travelDist;
	velocity.y = (target.y + verticalShift) / travelDist;

	// current point is going to travel from start to end
	Vert curPoint = start;
	FillTrajectotyPoint(0, velocity, velocity, curPoint);
	elems[0].trvDist = 0;
	elems[0].tex = 0.0f;

	for (int i = 1; i < COUNT_QUADS; i++) {
		// step by velocity 
		curPoint.x += velocity.x * 1;
		curPoint.y += velocity.y * 1;

		// change velocity
		Vert nextVel{
			velocity.x,
			velocity.y - gravity * 1
		};

		// fill quad sides
		FillTrajectotyPoint(i, nextVel, velocity, curPoint);

		// update dist - used by moving dice
		Vert middleDelta = { elems[i].side.md.x - elems[i - 1].side.md.x,
						     elems[i].side.md.y - elems[i - 1].side.md.y };
		elems[i].trvDist = elems[i - 1].trvDist + middleDelta.Len();

		// tex coords
		elems[i].tex = elems[i - 1].tex + 0.1f;

		// iterate
		velocity = nextVel;
	}
}

void LightArc::ChangeGravity(Vert& start) {
	gravity = sqrtf(thickness) / 300;

	// random gravity for middle player
	if (abs(start.y) < 0.1f && random::Bool()) {
		gravity = -gravity;
		return;
	}

	// flip gravity for players that are high up
	if (start.y > 0) {
		gravity = -gravity;
	}
}

void LightArc::FillTrajectotyPoint(int i, const Vert& nextVel, const Vert& velocity, const Vert& nextPoint) {
	// calc ortho dir
	Vert ortho{
		nextVel.y + velocity.y,
		-nextVel.x - velocity.x
	};

	// narrow at the start and at the end
	float narrow = 1.f;
	auto countTail = COUNT_QUADS / 3;
	auto revIdx = COUNT_QUADS - i;
	if (i < countTail) {
		narrow = 0.1f + 0.9f * i / countTail;
	} else if (revIdx < countTail) {
		narrow = 0.1f + 0.9f * revIdx / countTail;
	}

	// calc side step
	float coeff = thickness * narrow * 0.5f / ortho.Len();
	Vert sideStep{
		ortho.x * coeff,
		ortho.y * coeff
	};

	// fill quad sides
	elems[i].side.md = nextPoint;
	elems[i].side.up = {
		nextPoint.x + sideStep.x,
		nextPoint.y + sideStep.y
	};
	elems[i].side.dn = {
		nextPoint.x - sideStep.x,
		nextPoint.y - sideStep.y
	};
}

void LightArc::Animate(float deltaTime) {
	float deltaTex = speed * deltaTime;

	for (int i = 0; i < COUNT_QUADS; i++) {
		elems[i].tex -= deltaTex;
	}
}
