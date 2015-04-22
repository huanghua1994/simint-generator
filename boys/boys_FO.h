/*
------------------------------------
 Generated with:
   dat/generate_FO.py boys_FO

Dat files:
    Boys_0_13_13.dat
    Boys_1_13_13.dat
    Boys_2_13_13.dat
------------------------------------
*/

#ifndef BOYS_FO_H
#define BOYS_FO_H

#define BOYS_FO_MAXN 2

inline void Boys_F_FO(double * const restrict F, int n, double x)
{
    int idx = n;
    switch(n)
    {
        case 2:
        {
            const double num = 0.525305560880753447
                       + x * ( 0.110492812543561698
                       + x * ( 0.0191075521270522133
                       + x * ( 0.00308864958825646759
                       + x * ( 0.000365092211441395786
                       + x * ( 0.0000386927386117543446
                       + x * ( 3.43285176619925111e-6
                       + x * ( 2.60432969408429629e-7
                       + x * ( 1.81615413272499949e-8
                       + x * ( 8.79574269616801187e-10
                       + x * ( 8.17788745331821633e-11
                       + x * ( 9.41377749237483758e-13
                       + x * ( 1.10425964672642921e-13
                       + x * ( 6.7330075025747763e-15
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.496054363546458276
                       + x * ( 0.128217363190316964
                       + x * ( 0.0237743767099492677
                       + x * ( 0.00352539772392101481
                       + x * ( 0.00043510113976810022
                       + x * ( 0.0000454073941207125778
                       + x * ( 4.04510802860155619e-6
                       + x * ( 3.06619642129059298e-7
                       + x * ( 2.13853590636569169e-8
                       + x * ( 1.03568903196894899e-9
                       + x * ( 9.62938758302946861e-11
                       + x * ( 1.10846362277666573e-12
                       + x * ( 1.3002555622660695e-13
                       + x * ( 7.92805431387221855e-15
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 2.5);
        }
        case 1:
        {
            const double num = 0.480749856769136127
                       + x * ( 0.0757107453935371611
                       + x * ( 0.0207544733443622468
                       + x * ( 0.00296686757159093428
                       + x * ( 0.000385086850988198076
                       + x * ( 0.0000396245291118678106
                       + x * ( 3.44653527568129186e-6
                       + x * ( 2.60728584781887378e-7
                       + x * ( 1.64651276793705422e-8
                       + x * ( 1.24924114646889903e-9
                       + x * ( -4.06609033385506782e-13
                       + x * ( 6.69244577908522819e-12
                       + x * ( -1.74969643368118421e-13
                       + x * ( 9.69901476816967128e-15
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.557484696706444012
                       + x * ( 0.16330778039059299
                       + x * ( 0.0332854355906960737
                       + x * ( 0.00522222434942978777
                       + x * ( 0.000658578219691024581
                       + x * ( 0.0000682687148667475058
                       + x * ( 5.92820704830126442e-6
                       + x * ( 4.486040686836368e-7
                       + x * ( 2.83282406028920981e-8
                       + x * ( 2.14933012694134515e-9
                       + x * ( -6.99576077110757546e-13
                       + x * ( 1.15144066901510615e-11
                       + x * ( -3.01036676011995688e-13
                       + x * ( 1.66872327689919498e-14
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 1.5);
        }
        case 0:
        {
            const double num = 1.
                       + x * ( 0.414016243000866299
                       + x * ( 0.130448682735044324
                       + x * ( 0.0281490811816026161
                       + x * ( 0.00462868463720416281
                       + x * ( 0.00062025147610678493
                       + x * ( 0.0000686770885390617984
                       + x * ( 6.28488230669978749e-6
                       + x * ( 5.01986197619830788e-7
                       + x * ( 3.96915046153987083e-8
                       + x * ( 1.14619057438675389e-9
                       + x * ( 2.21422857239286206e-10
                       + x * ( -3.47087628137958658e-12
                       + x * ( 5.26907054399378694e-13
                       )))))))))))));

            const double den = 1.0
                       + x * ( 1.08068290966581548
                       + x * ( 0.539792844780494916
                       + x * ( 0.166084230769033217
                       + x * ( 0.035790298646556066
                       + x * ( 0.00589703243578234382
                       + x * ( 0.000789592116312117277
                       + x * ( 0.0000874456178357265776
                       + x * ( 8.00211107603171383e-6
                       + x * ( 6.39149165582055646e-7
                       + x * ( 5.05367903369666356e-8
                       + x * ( 1.45937517486452486e-9
                       + x * ( 2.81924337930412797e-10
                       + x * ( -4.4192569363292127e-12
                       + x * ( 6.70878898061210528e-13
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 0.5);
        }
    }
}


inline double Boys_F0_FO(double x)
{
    const double num = 1.
               + x * ( 0.414016243000866299
               + x * ( 0.130448682735044324
               + x * ( 0.0281490811816026161
               + x * ( 0.00462868463720416281
               + x * ( 0.00062025147610678493
               + x * ( 0.0000686770885390617984
               + x * ( 6.28488230669978749e-6
               + x * ( 5.01986197619830788e-7
               + x * ( 3.96915046153987083e-8
               + x * ( 1.14619057438675389e-9
               + x * ( 2.21422857239286206e-10
               + x * ( -3.47087628137958658e-12
               + x * ( 5.26907054399378694e-13
               )))))))))))));

    const double den = 1.0
               + x * ( 1.08068290966581548
               + x * ( 0.539792844780494916
               + x * ( 0.166084230769033217
               + x * ( 0.035790298646556066
               + x * ( 0.00589703243578234382
               + x * ( 0.000789592116312117277
               + x * ( 0.0000874456178357265776
               + x * ( 8.00211107603171383e-6
               + x * ( 6.39149165582055646e-7
               + x * ( 5.05367903369666356e-8
               + x * ( 1.45937517486452486e-9
               + x * ( 2.81924337930412797e-10
               + x * ( -4.4192569363292127e-12
               + x * ( 6.70878898061210528e-13
               ))))))))))))));

    const double frac = num / den;
    return sqrt(frac);
}

#endif