#include "scene.h"
#include "log.h"
#include "camera.h"

extern Timer timer;

static void
die_gracefully()
{
    SDL_Quit();
}

Scene::Scene()
{
    const SDL_VideoInfo *video_info;
    video_flags = 0;

    assert(SDL_Init(SDL_INIT_VIDEO) == 0, "Can't init SDL.");
    atexit(&die_gracefully);

    /* Fetch the video info */
    assert((video_info = SDL_GetVideoInfo()), "Video query failed: %s\n", SDL_GetError());

    /* the flags to pass to SDL_SetVideoMode */
    video_flags  = SDL_OPENGL;          /* Enable OpenGL in SDL */
    video_flags |= SDL_GL_DOUBLEBUFFER; /* Enable double buffering */
    video_flags |= SDL_HWPALETTE;       /* Store the palette in hardware */
    video_flags |= SDL_RESIZABLE;       /* Enable window resizing */

    /* This checks to see if surfaces can be stored in memory */
    if ( video_info->hw_available )
        video_flags |= SDL_HWSURFACE;
    else
        video_flags |= SDL_SWSURFACE;

    /* This checks if hardware blits can be done */
    if ( video_info->blit_hw )
        video_flags |= SDL_HWACCEL;

    /* Sets up OpenGL double buffering */
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    assert((surface = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP,
            video_flags)), "Video mode set failed: %s\n", SDL_GetError());

    init_gl();
}

void
Scene::init_gl()
{
    /* Enable Texture Mapping ( NEW )
    glEnable( GL_TEXTURE_2D ); */

    /* Enable smooth shading
    glShadeModel( GL_SMOOTH ); */

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void
Scene::draw_floor()
{
    static int
        size = 5,
        depth = -10.5;

    glLoadIdentity();
    glBegin(GL_QUADS);
    glColor3f(.3, .3, .3);
    glVertex3f(-size, -size, depth);
    glVertex3f(size, -size, depth);
    glVertex3f(size, size, depth);
    glVertex3f(-size, size, depth);
    glEnd();
}

void
Scene::run()
{
    SDL_Event event;
    char done = 0;

    while (!done) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_VIDEORESIZE:
                    // handle resize event
                    surface = SDL_SetVideoMode( event.resize.w,
                            event.resize.h,
                            16, video_flags );
                    assert(surface, "Couldn't get surface after resize: %s.",
                            SDL_GetError());
                    //resizeWindow( event.resize.w, event.resize.h );
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    /* handle key presses */
                    logic.feed_key(&event.key.keysym, event.type);
                    break;
                case SDL_QUIT:
                    /* handle quit requests */
                    done = 1;
                    break;
                default:
                    break;
            }
        }

        glClearColor(1, 1, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        logic.draw_frame();
        draw_floor();
        Camera::position(logic.v);
        SDL_GL_SwapBuffers();

        timer.wait();
    }
}
