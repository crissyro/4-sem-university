#include <stdio.h>
#include <math.h>

int main() {

    double a = 1007e13; 
    double b = 103e10;  
    double c = 1.00731;  
    
    double difference = 0;
    double direct_res_target = 0;
    double improved_res_target = 0;
    for (int i = 0; i < 100; i++) {
        a = a/100;
        for (size_t j = 0; j < 100; j++) {
            b = b/10;
            for (size_t k = 0; k < 100; k++) {
                c=c+7;

                double direct_res = log(a * b / c);
                double improved_res = log(a) + log(b) - log(c);

                if (difference < fabs(direct_res - improved_res)) {
                    direct_res_target = direct_res;
                    improved_res_target = improved_res;
                    difference = fabs(direct_res - improved_res);
                }
                
            }
        }
        
    }

    printf("Прямой метод: log(a * b / c) = %e\n", direct_res_target);
    printf("Улучшенный метод: log(a) + log(b) - log(c) = %e\n", improved_res_target);
    
    printf("Разница между методами: %e\n", difference);

    return 0;
}