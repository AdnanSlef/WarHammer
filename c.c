#include <stdio.h>

struct Unit {
    char ws;
};

struct ModelStats { 
    char ws; //
    char bs; //
    char s;  //
    char t;  //
    char w;  //
    char i;  //
    char a;  //
    char ld; //Leadership
    char sv; //Armour Save (n+)
};

struct Model {
    struct ModelStats *stats;
};

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

    vader.stats = &vaderstats;

    initializeModel(&vader, 1, 2, 3, 4, 5, 6, 7, 8, 9);

    showModel(&vader);

    return 0;
}