/*
------------------------------------
 Generated with:
   ./generate_standalone.py boys_FO

Dat files:
    Boys_0_13_13.dat
    Boys_1_13_13.dat
    Boys_2_13_13.dat
    Boys_3_13_13.dat
    Boys_4_13_13.dat
    Boys_5_13_13.dat
    Boys_6_13_13.dat
    Boys_7_13_13.dat
    Boys_8_13_13.dat
------------------------------------
*/

#ifndef BOYS_FO_H
#define BOYS_FO_H

#ifdef __cplusplus
extern "C" {
#endif

#define BOYS_FO_MAXN 8

inline void Boys_F_FO(double * const restrict F, int n, double x)
{
    int idx = n;
    switch(n)
    {
        case 8:
        {
            const double num = 0.716541425477415861
                       + x * ( -0.0227865381021285978
                       + x * ( 0.00327874937639033393
                       + x * ( 0.0000403548415935860227
                       + x * ( 7.20623219142052687e-6
                       + x * ( 3.35204815931659747e-7
                       + x * ( 1.81953034516476915e-8
                       + x * ( 9.63079734047417711e-10
                       + x * ( 3.0477603408067824e-11
                       + x * ( 1.86027306337646524e-12
                       + x * ( 8.2575916763448544e-14
                       + x * ( -2.74698299421027651e-15
                       + x * ( 2.33304207731975379e-16
                       + x * ( 1.42525357718615678e-19
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.0734624308314188403
                       + x * ( 0.00624088686737929902
                       + x * ( 0.000493279505191635856
                       + x * ( 0.0000341127754881867474
                       + x * ( 2.14130515950898463e-6
                       + x * ( 1.23779104344348298e-7
                       + x * ( 6.36733630634781479e-9
                       + x * ( 3.40081149242342238e-10
                       + x * ( 1.07507738550838754e-11
                       + x * ( 6.56279390971472287e-13
                       + x * ( 2.91315409332138546e-14
                       + x * ( -9.69094386987852644e-16
                       + x * ( 8.23062243600765652e-17
                       + x * ( 5.02808079780156285e-20
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 8.5);
        }
        case 7:
        {
            const double num = 0.696927869860540206
                       + x * ( -0.0245842821500016603
                       + x * ( 0.00387386297822400047
                       + x * ( 0.0000412752563901979249
                       + x * ( 9.65769105078521047e-6
                       + x * ( 4.49203187634950842e-7
                       + x * ( 2.49787490824865953e-8
                       + x * ( 1.62550093565884612e-9
                       + x * ( -1.98508260704137581e-12
                       + x * ( 8.69732290400856347e-12
                       + x * ( -3.74694362730532507e-13
                       + x * ( 1.95982392437448987e-14
                       + x * ( -2.09435870290602052e-16
                       + x * ( 3.65734649696346255e-18
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.0823718409527545019
                       + x * ( 0.0076004126659120389
                       + x * ( 0.000645052537446241508
                       + x * ( 0.0000475762669422998754
                       + x * ( 3.15794902771574117e-6
                       + x * ( 1.92103442667026871e-7
                       + x * ( 9.90117036546320523e-9
                       + x * ( 6.53907106156826984e-10
                       + x * ( -8.02520234211224998e-13
                       + x * ( 3.49333810076417267e-12
                       + x * ( -1.50497818196018023e-13
                       + x * ( 7.87172682319026514e-15
                       + x * ( -8.41209218920669405e-17
                       + x * ( 1.46899076338575765e-18
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 7.5);
        }
        case 6:
        {
            const double num = 0.673944447579473152
                       + x * ( -0.0273598561147759079
                       + x * ( 0.00463673728289017182
                       + x * ( 0.000034300910503431443
                       + x * ( 0.0000130358950567361568
                       + x * ( 5.83220590433158958e-7
                       + x * ( 3.44797426304112356e-8
                       + x * ( 2.38474353380293983e-9
                       + x * ( -4.59196255955898238e-11
                       + x * ( 1.99099603278533646e-11
                       + x * ( -1.4311498242876518e-12
                       + x * ( 8.80013303476364236e-14
                       + x * ( -2.42311703012800209e-15
                       + x * ( 3.49581150650835651e-17
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.0927367286140731619
                       + x * ( 0.00931025853766456165
                       + x * ( 0.000851628757507340205
                       + x * ( 0.0000670090595547958342
                       + x * ( 4.69316257859672114e-6
                       + x * ( 2.97608095074209198e-7
                       + x * ( 1.57040009441295436e-8
                       + x * ( 1.11345155312273823e-9
                       + x * ( -2.13981150385256463e-11
                       + x * ( 9.26925723537952145e-12
                       + x * ( -6.66278914581659246e-13
                       + x * ( 4.09694460483010635e-14
                       + x * ( -1.12809387751368198e-15
                       + x * ( 1.6274919899379346e-17
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 6.5);
        }
        case 5:
        {
            const double num = 0.646630038500837714
                       + x * ( -0.0182430126939650534
                       + x * ( 0.00543969649877461546
                       + x * ( 0.000116476317051295638
                       + x * ( 0.000021521931928403257
                       + x * ( 1.18615991212530143e-6
                       + x * ( 7.58604696784467546e-8
                       + x * ( 4.92699461286368605e-9
                       + x * ( 1.70136633738363635e-11
                       + x * ( 3.88505787621294195e-11
                       + x * ( -3.02592533985388176e-12
                       + x * ( 2.50393836693133557e-13
                       + x * ( -8.85454095669162848e-15
                       + x * ( 1.84699348446812487e-16
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.125633711312370486
                       + x * ( 0.0143284143238659723
                       + x * ( 0.00146343159568277208
                       + x * ( 0.000128918603936083915
                       + x * ( 0.000010007581130819214
                       + x * ( 6.93879268824586396e-7
                       + x * ( 4.13381482366787712e-8
                       + x * ( 2.72711915007782649e-9
                       + x * ( 9.35871296778309097e-12
                       + x * ( 2.1459232544492312e-11
                       + x * ( -1.67136625542074901e-12
                       + x * ( 1.38304703720495406e-13
                       + x * ( -4.89079394108677387e-15
                       + x * ( 1.02018439882235746e-16
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 5.5);
        }
        case 4:
        {
            const double num = 0.613685849032916035
                       + x * ( 0.00903173132995705395
                       + x * ( 0.0069284473671474595
                       + x * ( 0.000435156706530149163
                       + x * ( 0.0000488085495651258633
                       + x * ( 3.66096953726522648e-6
                       + x * ( 2.59751177273597696e-7
                       + x * ( 1.71762934556763709e-8
                       + x * ( 6.36469395210182763e-10
                       + x * ( 9.79098463143548107e-11
                       + x * ( -5.17453551995652055e-12
                       + x * ( 7.31427836739056021e-13
                       + x * ( -2.84387961377947079e-14
                       + x * ( 8.85040027079679332e-16
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.196535371894127447
                       + x * ( 0.0279517601730765951
                       + x * ( 0.00336319077005095874
                       + x * ( 0.000348115741765303429
                       + x * ( 0.0000314536554282140664
                       + x * ( 2.50784176166426963e-6
                       + x * ( 1.75165336933914539e-7
                       + x * ( 1.16200064640254918e-8
                       + x * ( 4.30354125246412109e-10
                       + x * ( 6.62084177654364664e-11
                       + x * ( -3.49910640701992041e-12
                       + x * ( 4.94603523474290392e-13
                       + x * ( -1.92307812889565772e-14
                       + x * ( 5.98478610349119398e-16
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 4.5);
        }
        case 3:
        {
            const double num = 0.573513198744647626
                       + x * ( 0.0884965100710721081
                       + x * ( 0.0125945026937261292
                       + x * ( 0.0018131346755066484
                       + x * ( 0.000185501511589852242
                       + x * ( 0.0000179665588981785096
                       + x * ( 1.4663716751615509e-6
                       + x * ( 1.07200007061958399e-7
                       + x * ( 6.13886384827129358e-9
                       + x * ( 5.0757503319816481e-10
                       + x * ( -3.89402001604364884e-12
                       + x * ( 3.54266040828850291e-12
                       + x * ( -1.30207429069121938e-13
                       + x * ( 6.46345036567436585e-15
                       )))))))))))));

            const double den = 1.0
                       + x * ( 0.376528191549264251
                       + x * ( 0.0764525025412929857
                       + x * ( 0.0117343580663816836
                       + x * ( 0.00149763967922572319
                       + x * ( 0.000163513443673380925
                       + x * ( 0.0000154572094390025412
                       + x * ( 1.26979191105616802e-6
                       + x * ( 9.27046437188452642e-8
                       + x * ( 5.30988729375523733e-9
                       + x * ( 4.39022184757595294e-10
                       + x * ( -3.36809850708008399e-12
                       + x * ( 3.06419443797353572e-12
                       + x * ( -1.12621824892382023e-13
                       + x * ( 5.59050724287616386e-15
                       ))))))))))))));

            const double frac = num / den;
            F[idx--] = pow(frac, 3.5);
        }
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

#ifdef __cplusplus
}
#endif

#endif