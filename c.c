#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Unit {
    char ws;
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
    char sv; //Armour Save (n+)
};

struct Model {
    struct ModelStats *stats;
};

char d(unsigned int n) {
    return rand() % n + 1;
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
    struct Model vader;
    struct ModelStats vaderstats;

    srand(time(NULL));

    vader.stats = &vaderstats;

    initializeModel(&vader, 1, 2, d(3), 4, 5, d(6), 7, 8, 9);

    showModel(&vader);

    return 0;
}