#include <stdio.h>
#include <cs50.h>

int calculateCoins(float money){
    int coins[] = {25, 10, 5, 1};
    int coinsQuanitity[4] = {};
    int numberOfCoins = 0;
    money = money * 100;
    for(int i = 0; i < 4; i++){
        coinsQuanitity[i] = money / coins[i];
        numberOfCoins += coinsQuanitity[i];
        money = money - coins[i]*coinsQuanitity[i];
    }
    return numberOfCoins;
}

bool validateInput(float input){
    if(input >= 0) return true;
    else return false;
}

int main()
{
    float money;
    do{
        printf("How much money is owed?\n");
        money = GetFloat();

    }while(validateInput(money) == false);
    printf("%d\n", calculateCoins(money));

    return 0;
}