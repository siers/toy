#include "models.h"
#include "timer.h"
#include "scene.h"
#include "log.h"

int loglvl = 0;
int FPS    = 60;

int
main()
{
    Scene scene;

    scene.run();

    return 0;
}
