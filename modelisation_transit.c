#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _USE_MATH_DEFINES // Pour pouvoir utiliser la constante M_PI
#include <math.h>


// Modélisation du transit

/* 
Modèle défini par paramètres :
t : Temps, date actuelle
A : Profondeur du transit, mesure la diminution de luminosité
P : Période, durée entre 2 transits successifs
D : Durée d'un transit
T0 : Temps de référence, date du premier transit observé

F(t, A, P, D, T0) = (1-A) si [(t-T0) % P] < D  (Si transit en cours)
                  = 1 sinon  (Si transit pas en cours)
*/

// Fonction modèle du transit
double F_mod(double, double, double, double, double);

// Bruit gaussien
double gaussian_noise(double, double);


#define N 100 // Nombre de points de données

// Début de la fonction main
int main(){
    // On définit une seed pour les nombres aléatoires
    srand(10); // TEMPORAIRE : On prend une seed fixée (donne les mêmes résultats à chaque fois) pour debug si nécessaire
    //srand(time(NULL)) // Seed générée à partir de la date à laquelle tourne le code

    double A, P, D, T0=0; // Pour modèle de transit
    double t[N];
    double mean, stdev; // Pour bruit gaussien

    double lum_mod_noisy[N]; // Luminosité basée sur le modèle + bruit gaussien

    long k=0;
    for (k=0; k<N; k++){
        t[k] = T0 + k*0.4; // Pas de temps arbitraire, afin de définir un array de temps t
        lum_mod_noisy[k] = F_mod(t[k], A=0.2, P=10, D=2, T0=0) + gaussian_noise(mean=0, stdev=0.05);
           printf("Noisy lum pour t=%lf (k=%ld) est : \n %lf \n", t[k], k, lum_mod_noisy[k]);
    }

}
// Fin de la fonction main



double F_mod(double t, double A, double P, double D, double T0){
    double lum;
    if (fmod((t-T0), P) < D) {
        lum = (1-A);
    }
    else lum = 1;

    return lum;
}

// Bruit gaussien : Méthode de Box-Muller 
// Provient de la correction de l'exercice du recuit simulé : "simulated_annealing.c", lignes 62-67)
double gaussian_noise(double mean, double stdev){
    double u1 = rand() / (double) RAND_MAX;
    double u2 = rand() / (double) RAND_MAX;
    double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
    return mean + z0 * stdev;
}
