#include "LightArc.h"
#include "field.h"
#include "random.h"

void LightArc::Bind(Field* _field) {
	field = _field;
}

void LightArc::Render() {
	MyColor color = colors::white;
	glColor3d(color.red, color.green, color.blue);

	field->ChangeTexture(E_LIGHTNING);
	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < COUNT_QUADS; i++) {
			glTexCoord2f(tex[i], 0); glVertex2f(dnSide[i].x, dnSide[i].y);
			glTexCoord2f(tex[i], 1); glVertex2f(upSide  [i].x, upSide  [i].y);
		}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Field::PrepareArc(Player& player) {
	// start
	auto layout = GetLayout(&player);
	Vert boxCoords = {       xBoxOrigin + slotLen / 2,
					  layout.yBoxOrigin - slotHeight / 2 };


	// end
	auto groupIdx = player.addingTo;
	auto slotIdx = player.groups[groupIdx].addingTo;
	Vert slotCoords = {       xSlotOrigin + groupIdx * (xOffset + slotLen)    + slotLen / 2,
					   layout.ySlotOrigin - slotIdx * (yOffset + slotHeight)  - slotHeight / 2};

	// relay
	arc.Prepare(boxCoords, slotCoords);

	// assign dice
	movingDice.SetValue(player.boxDice.GetValue());
}

void LightArc::Prepare(Vert start, Vert end) {
	tex[0] = 0.0f;
	Vert target{ (end.x - start.x) ,
				 (end.y - start.y) };

	thickness = target.x / 5;
	gravity = sqrtf(thickness) / 300;
	
	// flip gravity for players that are high up
	if (start.y > 0) {
		gravity *= -1;
	}

	// random gravity for middle player
	if (abs(start.y) < 0.1f && random::Bool()) {
		gravity *= -1;
	}

	// calc initial velocity 
	// -- we will simulate one sec in each loop iteration
	Vert velocity;
	float travelTime = (COUNT_QUADS - 1);
	velocity.x = target.x / travelTime;
	float verticalShift = gravity * 0.5f * travelTime * travelTime;
	velocity.y = (target.y + verticalShift) / travelTime;

	// current point gonna travel from start to end
	Vert curPoint = start;
	FillTrajectotyPoint(0, velocity, velocity, curPoint);
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

		// iterate
		velocity = nextVel;

		// tex coords
		tex[i] = tex[i - 1] + 0.1f;
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
	upSide[i] = {
		nextPoint.x + sideStep.x,
		nextPoint.y + sideStep.y
	};
	dnSide[i] = {
		nextPoint.x - sideStep.x,
		nextPoint.y - sideStep.y
	};
}

void LightArc::Animate(float deltaTime) {
	float deltaTex = speed * deltaTime;

	for (int i = 0; i < COUNT_QUADS; i++) {
		tex[i] -= deltaTex;
	}
}
