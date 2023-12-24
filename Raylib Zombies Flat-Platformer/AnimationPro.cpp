#include "AnimationPro.h"

AnimationPro::AnimationPro() {}
AnimationPro::AnimationPro(Texture texture, float scale, float updateTime, int rowFrames, int colFrames, int totalFrames)
	: texture(texture), scale(scale), updateTime(updateTime), rowFrames(rowFrames), colFrames(colFrames), totalFrames(totalFrames)
{
	float frameWidth = texture.width / colFrames;
	float frameHeight = texture.height / rowFrames;
	source = Rectangle{ 0, 0,  frameWidth, frameHeight };

	width = scale * frameWidth;
	height = scale * frameHeight;

	runningTime = 0.0f;
	frame = 0;
}

float AnimationPro::getWidth() { return width; }
float AnimationPro::getHeight() { return height; }
float AnimationPro::getRunningTime() { return runningTime; }
int AnimationPro::getFrame() { return frame; }

void AnimationPro::draw(Vector2 pos, bool flip, Color color)
{
	Rectangle tempSource = source;
	if (flip) tempSource.width *= -1;
	DrawTexturePro(texture, tempSource, { pos.x, pos.y, width, height }, { 0,0 }, 0, color);
}

void AnimationPro::updateFrame()
{
	runningTime += GetFrameTime();
	if (runningTime >= updateTime)
	{
		runningTime = 0;
		if (frame == totalFrames) frame = 0;
		source.x = frame * source.width;
		source.y = frame * source.height;
		frame++;
	}
}

bool AnimationPro::atLastFrame() { return frame == totalFrames; }

void AnimationPro::unloadTexture() { UnloadTexture(texture); }