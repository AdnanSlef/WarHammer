#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MAX_NUM_MODELS 15
#define CLOSE_ENOUGH 0.1
#define DEBUG 1

struct Unit {
    struct Model *models[MAX_NUM_MODELS];
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

void setPoint(struct Point *p, double x, double y, double z) {
    p->x=x;
    p->y=y;
    p->z=z;
}

double calcDistance(struct Point *c1, float r1, struct Point *c2, float r2) { //ignores vertical distance
    double dx = fabs(c1->x - c2->x);
    double dy = fabs(c1->y - c2->y);
    double dc = sqrt(dx*dx + dy*dy);
    if (DEBUG) {
        printf("dx %f,  dy %f, dc %f\n", dx, dy, dc);
        if(dc < r1 + r2) {
            puts("ERROR: Negative distance; are the models overlapping?");
        }
    }
    //assert(dc - r1 - r2 >= -CLOSE_ENOUGH); //doesn't seem to work in g++
    return dc - r1 - r2;
}

int countBlast(struct Unit *unit, struct Point *center, double radius) {
    int hits = 0;
    struct Point *modelpos;
    double dx, dy, modeldist;
    for(int i=0; i < unit->num_models; i++) {
        modeldist = calcDistance( unit->models[i]->pos, 0, center, 0 );
        hits += fabs(modeldist) - radius < CLOSE_ENOUGH;
    }
    return hits;
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
    //currently this makes no sense as initialize model, since it just sets ModelStats stats.
}

void testBlastFunc() {
    struct Unit squad;
    struct Model troopers[4];
    struct ModelStats trooper_stats;
    struct Point blast, trooper_poses[4];
    double blastsize;
    
    for(int i=0; i<4; i++){
        troopers[i].stats = &trooper_stats;
        troopers[i].pos = trooper_poses+i; // &trooper_poses[i]
    }
    initializeModel(&troopers[0], 1, 2, 3, 4, 5, 6, 7, 8, 9);

    blastsize = 3;
    setPoint(&blast, 1.2, 3.4, 0);

    setPoint(troopers[0].pos, 1.2, 3.4, 0);
    setPoint(troopers[1].pos, 2.8, 3.4, 0);
    setPoint(troopers[2].pos, 1.2, 6.5, 0);
    setPoint(troopers[3].pos, 0.4, 4.2, 0);

    squad.num_models = 4;
    for(int i=0; i<squad.num_models; i++) {
        squad.models[i] = &troopers[i];
    }

    printf("Blast hits: %d\n", countBlast(&squad, &blast, blastsize));
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

    setPoint(vader.pos,12.5,45,0);
    setPoint(obi.pos,15,50,0);

    printf("Distance %f\n",calcDistance(vader.pos, vader.radius, obi.pos, obi.radius));

    testBlastFunc();

    return 0;
}