#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_NUM_MODELS 15

struct Unit {
    struct Model *models[MAX_NUM_MODELS];
    char ws;
    int num_models;
};

struct Point {
    double x;
    double y;
    double z; //height
};

struct ModelStats { 
    char ws; //Weapons Skill
    char bs; //Ballistics Skill
    char s;  //Strength
    char t;  //Toughness
    char w;  //Wounds
    char i;  //Initiative
    char a;  //Attacks
    char ld; //Leadership
    char sv; //Armour Save (sv+)
};

struct Model {
    struct ModelStats *stats;
    struct Point *pos; //Position
    double radius;
};

char d(unsigned int n) {   //Roll dice with uniform discrete distribution
    return rand() % n + 1;
}

float calcDistance(struct Point *c1, float r1, struct Point *c2, float r2) { //ignores vertical distance
    double dx = fabs(c1->x - c2->x);
    double dy = fabs(c1->y - c2->y);
    double dc = sqrt(dx*dx + dy*dy);
    printf("dx %f,  dy %f, dc %f\n", dx, dy, dc);
    return dc - r1 - r2;
}



void showModel(struct Model *model) {
    char *format = "%s: WS %d, BS %d, S %d, T %d, W %d, I %d, A %d, Ld %d, Sv %d+\n";
    printf(format, "Vader", model->stats->ws, model->stats->bs, model->stats->s,
                            model->stats->t,  model->stats->w,  model->stats->i,
                            model->stats->a,  model->stats->ld, model->stats->sv
    );
}

void initializeModel(struct Model *model, char WS, char BS, char S, char T, char W, char I, char A, char Ld, char Sv) {
    model->stats->ws = WS; model->stats->bs = BS; model->stats->s = S;
    model->stats->t  = T;  model->stats->w  = W;  model->stats->i = I;
    model->stats->a  = A;  model->stats->ld = Ld; model->stats->sv = Sv;
}

int main() {
    struct Model vader, obi;
    struct ModelStats vaderstats, obistats;
    struct Point vaderpos, obipos;

    srand(time(NULL));

    vader.stats = &vaderstats; vader.pos = &vaderpos;
    obi.stats = &obistats; obi.pos = &obipos;

    initializeModel(&vader, 1, 2, d(3), 4, 5, d(6), 7, 8, 9);
    initializeModel(&obi, 9, 8, 7, d(6), 5, 4, 3, 2, 1);

    showModel(&vader);
    showModel(&obi);

    vader.radius = 1.5;
    obi.radius = 1;

    vader.pos->x = 12.5; vader.pos->y = 45; vader.pos->z = 0;
    obi.pos->x = 15; obi.pos->y = 50; obi.pos->z = 0;

    printf("Distance %f\n",calcDistance(vader.pos, vader.radius, obi.pos, obi.radius));

    return 0;
}