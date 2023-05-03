#include "game.h"

int main(int argc, char* argv[])
{
    Game* mGame = new Game();

    if(mGame->Init())
    {
        mGame->Run();
    }

    delete mGame;
    return 0;
}
