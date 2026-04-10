#pragma once

class Animation{
    public:
        Animation(int frameStart, int frameEnd, float frameTime);

        int getFrameStart();
        int getFrameEnd();
        float getFrameTime();
        
        void setFrameStart(int frameStart);
        void setFrameEnd(int frameEnd);
        void setFrameTime(float frameTime);

    private:
        int frameStart;
        int frameEnd;
        float frameTime;
};