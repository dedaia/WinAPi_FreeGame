#include "Framework.h"

Animation::Animation(POINT imageFrame, float speed)
    : imageFrame(imageFrame), speed(speed)
{
    intervalTime = 1.0f / FRAME_PER_SECOND;

    frames.reserve(imageFrame.x * imageFrame.y);
    for (int y = 0; y < imageFrame.y; y++)
    {
        for (int x = 0; x < imageFrame.x; x++)
        {
            frames.push_back({ x, y });
        }
    }
}

void Animation::Update()
{
    if (!isPlay) return;

    playTime += speed * DELTA;

    if (playTime >= intervalTime)
    {
        playTime -= intervalTime;

        curFrameNum++;

        if (curFrameNum > action.size() - 1)
        {
            if (isLoop)
                curFrameNum = 0;
            else
            {
                curFrameNum--;
                Stop();
            }
        }
    }
}

void Animation::SetDefault(bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (UINT i = 0; i < frames.size(); i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (UINT i = start; i <= end; i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPingpong()
{
    for (int i = action.size() - 2; i >= 0; i--)
        action.push_back(action[i]);
}

void Animation::Stop()
{
    isPlay = false;

    if (endEvent)
        endEvent();
}
