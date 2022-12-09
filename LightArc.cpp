#include "LightArc.h"
#include "field.h"

void LightArc::Bind(Field* _field) {
	field = _field;
}

void LightArc::Render() {
	MyColor color = colors::white;
	glColor3d(color.red, color.green, color.blue);

	field->ChangeTexture(E_LIGHTNING);
	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i < COUNT_QUADS; i++) {
			glTexCoord2f(tex[i], 0); glVertex2f(downSideCoords[i].x, downSideCoords[i].y);
			glTexCoord2f(tex[i], 1); glVertex2f(upSideCoords  [i].x, upSideCoords  [i].y);
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
}

void LightArc::Prepare(Vert start, Vert end) {
	static float thickness = 0.15f;

	// start point
	upSideCoords  [0] = downSideCoords[0] = start;
	downSideCoords[0].y -= thickness * 0.1f;
	tex[0] = 0.0f;

	// middle points
	float stepX = (end.x - start.x) / COUNT_QUADS;
	float stepY = 0.05f;
	for (int i = 1; i < COUNT_QUADS; i++) {
		upSideCoords[i] = { upSideCoords[i - 1].x + stepX, start.y + stepY * (i * (i - (COUNT_QUADS - 1))) / 4 };
		downSideCoords[i] = { upSideCoords[i].x, upSideCoords[i].y - thickness };

		tex[i] = tex[i - 1] + 0.1f;
	}

	// end point
	upSideCoords  [COUNT_QUADS - 1] = downSideCoords[COUNT_QUADS - 1] = end;
	downSideCoords[COUNT_QUADS - 1].y -= thickness * 0.1f;
	//downSideCoords[COUNT_QUADS - 1] = { end.x, end.y - thickness };
}

void LightArc::Animate(float deltaTime) {
	static float speed = 1.f;
	float deltaTex = speed * deltaTime;

	for (int i = 0; i < COUNT_QUADS; i++) {
		tex[i] -= deltaTex;
	}
}

/*
	Vert txStart{ 0.0, 0.0 };
	Vert txFinish{ 1.0, 1.0 };
	field->RenderTexture(upSideCoords[0], upSideCoords[COUNT_QUADS - 1], colors::fieldBackground, E_FIELD, txStart, txFinish);
	//field->RenderTexture(upSideCoords[0], downSideCoords[COUNT_QUADS - 1], colors::fieldBackground, E_FIELD, txStart, txFinish);
	//field->RenderTexture(downSideCoords[0], downSideCoords[COUNT_QUADS-1], colors::fieldBackground, E_FIELD, txStart, txFinish);

	return;
*/