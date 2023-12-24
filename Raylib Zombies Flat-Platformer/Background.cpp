#include "Background.h"

Background::Background() {}
Background::Background(Texture2D texture, Vector2 pos, float scale)
	: texture(texture), pos(pos), scale(scale) {}
Vector2 Background::getScaledSize() { return { texture.width * scale, scale * texture.height }; }
void Background::draw(Vector2 cameraPos)
{
	//Reposition background so that it appears as if the background never runs out
	if (cameraPos.x >= texture.width * scale + pos.x) pos = { cameraPos.x, 0 };
	if (cameraPos.x <= -1 * texture.width * scale + pos.x) pos = { cameraPos.x, 0 };

	Vector2 posFarLeft = { pos.x - 2 * texture.width * scale, pos.y };
	DrawTextureEx(texture, { posFarLeft.x - cameraPos.x, posFarLeft.y - cameraPos.y }, 0, scale, WHITE);

	Vector2 posLeft = { pos.x - texture.width * scale, pos.y };
	DrawTextureEx(texture, { posLeft.x - cameraPos.x, posLeft.y - cameraPos.y }, 0, scale, WHITE);

	DrawTextureEx(texture, { pos.x - cameraPos.x, pos.y - cameraPos.y }, 0, scale, WHITE);

	Vector2 posRight = { pos.x + texture.width * scale, pos.y };
	DrawTextureEx(texture, { posRight.x - cameraPos.x, posRight.y - cameraPos.y }, 0, scale, WHITE);

	Vector2 posFarRight = { pos.x + 2 * texture.width * scale, pos.y };
	DrawTextureEx(texture, { posFarRight.x - cameraPos.x, posFarRight.y - cameraPos.y }, 0, scale, WHITE);
}
void Background::unloadTexture() { UnloadTexture(texture); }

