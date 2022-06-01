#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#define qtdParticles 50

typedef struct {
    int x, y;
    int vx, vy;
} Particle;

void moveCursor(int x, int y) { printf("\033[%d;%df", y, x); }

void particle(int x, int y) {
    moveCursor(x, y);
    printf("*\n");
}

int main() {
    srand(time(NULL));
    Particle particles[qtdParticles];

    int cols, lines;
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    cols = w.ws_col;
    lines = w.ws_row;

    int i;
    for (i = 0; i < qtdParticles; i++) {
        particles[i].x = 1 + rand() % cols;
        particles[i].y = 1 + rand() % lines;
        particles[i].vx = 1 + rand() % 2;
        particles[i].vy = 1 + rand() % 2;
    }

    while (1) {
        system("clear");

        for (i = 0; i < qtdParticles; i++) {
            particle(particles[i].x, particles[i].y);
        }

        for (i = 0; i < qtdParticles; i++) {
            particles[i].x += particles[i].vx;
            particles[i].y += particles[i].vy;
        }

        for (i = 0; i < qtdParticles; i++) {
            if (particles[i].x >= cols || particles[i].x <= 0) {
                particles[i].vx *= -1;
            }
            if (particles[i].y >= lines || particles[i].y <= 0) {
                particles[i].vy *= -1;
            }
        }
        usleep(40000);
    }
    return 0;
}
