// This #include statement was automatically added by the Particle IDE.
#include <LiquidCrystal.h>

// This #include statement was automatically added by the Particle IDE.
#include <InternetButton.h>

String toppings = "";
String order = "CHEEEEEEEEEEEEEESE";
InternetButton b = InternetButton();

void setup() {
    
    b.begin();
}

int t_c_r[13] = {149,   232,    242,    229,    255,    255,    235,    255,    194,    0,      204,    183,     153};
int t_c_g[13] = {22 ,   108,    142,    114,    202,    0,      207,    255,    246,    204,    0,      183,     0};
int t_c_b[13] = {22 ,   170,    142,    0,      148,    0,      180,    0,      23,     0,      0,      0,     153};
String topps[] = {"pepperoni","ham","bacon","italiansausage","chicken","tomatoes","mushrooms","pineapple","bananapeppers","greenpeppers","redpeppers","blackolives","onion"};

int i = 0;
void loop() {
    
    Particle.function("cheese",cheese);
    Particle.function("veggie",veggie);
    Particle.function("pepperoni",pepperoni);
    Particle.function("regorder",regorder);
    Particle.function("pizza",pizza);
    Particle.function("pizzaPrice",pizzaPrice);
    String toppings = "";
    if(b.buttonOn(1)){
        Particle.publish("default","13.55");
        b.ledOn(1, 0, 0, 255);
        b.ledOn(11, 0, 0, 255);
        delay(3000);
        b.ledOff(1);
        b.ledOff(11);
    }
    if(b.buttonOn(2)){
        Particle.publish("pepperoni","6.22");
        b.ledOn(3, 255, 0, 0);
        delay(3000);
        b.ledOff(3);
    }
    if(b.buttonOn(3)){
        Particle.publish("cheese","5.65");
        b.ledOn(7, 255, 255, 0);
        delay(3000);
        b.ledOff(7);
    }
    if(b.buttonOn(4)){
        Particle.publish("veggie","6.78");
        b.ledOn(9, 0, 255, 0);
        delay(3000);
        b.ledOff(9);

    }


}

int cheese(String i){
    Particle.publish("cheese","5.65");
    b.ledOn(7, 255, 255, 0);
    delay(3000);
    b.ledOff(7);
    return 1;
}

int veggie(String i){
    Particle.publish("veggie","6.78");
    b.ledOn(9, 0, 255, 0);
    delay(3000);
    b.ledOff(9);
    return 2;
}

int pepperoni(String i){
    Particle.publish("pepperoni","6.22");
    b.ledOn(3, 255, 0, 0);
    delay(3000);
    b.ledOff(3);
    return 3;
}

int regorder(String i){
    Particle.publish("default","13.55");
    b.ledOn(1, 0, 0, 255);
    b.ledOn(11, 0, 0, 255);
    delay(3000);
    b.ledOff(1);
    b.ledOff(11);
    return 4;
}

int pizza(String toppings) {
        Particle.publish(toppings);
        int dashIndex = toppings.indexOf('-');
        String firstTopping = toppings.substring(0,dashIndex);
        toppings = toppings.substring(dashIndex+1);
        dashIndex = toppings.indexOf('-');
        String secondTopping = toppings.substring(0,dashIndex);
        toppings = toppings.substring(dashIndex+1);
        dashIndex = toppings.indexOf('-');
        String thirdTopping = toppings.substring(0,dashIndex);
        toppings = toppings.substring(dashIndex+1);
        String fourthTopping = toppings;
        
        Particle.publish("String", firstTopping + "/" + secondTopping + "/" + thirdTopping + "/" + fourthTopping);
        
        int l1 = search(topps,firstTopping);
        int l2 = search(topps,secondTopping);
        int l3 = search(topps,thirdTopping);
        int l4 = search(topps,fourthTopping);
        
        Particle.publish("Found",""+String(l1)+" "+String(l2)+" "+String(l3)+" "+String(l4));
        
        for(int i = 0; i<3; i++) {
            b.ledOn(1,t_c_r[l1],t_c_g[l1],t_c_b[l1]);
            b.ledOn(11,t_c_r[l1],t_c_g[l1],t_c_b[l1]);
            b.ledOn(2,t_c_r[l2],t_c_g[l2],t_c_b[l2]);
            b.ledOn(4,t_c_r[l2],t_c_g[l2],t_c_b[l2]);
            b.ledOn(5,t_c_r[l3],t_c_g[l3],t_c_b[l3]);
            b.ledOn(7,t_c_r[l3],t_c_g[l3],t_c_b[l3]);
            b.ledOn(8,t_c_r[l4],t_c_g[l4],t_c_b[l4]);
            b.ledOn(10,t_c_r[l4],t_c_g[l4],t_c_b[l4]);
            delay(5000);
            b.ledOff(1);
            b.ledOff(11);
            b.ledOff(2);
            b.ledOff(4);
            b.ledOff(5);
            b.ledOff(7);
            b.ledOff(8);
            b.ledOff(10);
            delay(100);
        }
        return 1;
}
int search(String topps[], String topping) {
    for(int i = 0; i < 13; i++) {
        if(topps[i] == topping) {
            return i;
        }
    }
    return -1;
    
}

int pizzaPrice(String price){
    Particle.publish(price);
    
    return 1;
}
