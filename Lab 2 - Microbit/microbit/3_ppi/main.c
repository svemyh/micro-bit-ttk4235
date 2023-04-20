#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){
    gpio_init();
    init_GPIOTE();
    init_PPI();


    while(1){
        // Do nothing.
    }
    return 0;
}