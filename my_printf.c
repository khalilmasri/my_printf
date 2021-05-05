#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int my_putchar(char *c){
    return write(sizeof(char), &c, 1);
}

int my_putstr(char *str){
    int index = 0;
    if(str == NULL) return my_putstr("(NULL)");
    while(str[index]!= '\0'){
        write(sizeof(char), &str[index], 1);
        index++;
    }
    return index;
}

char* return_converted(int num, int base){
    char number[] = "0123456789";
    char *converted = malloc(100*sizeof(int));
    int printNumber, index = 0;
    while(num > 0){
        printNumber = num % base;
        for(int i =0; i < base; i++)
            if(printNumber == i){
                converted[index] = number[i];
                index++;
            }
        num /= base;
    }
    return converted;
}
int my_putint(int num, int base){
    int ret = 0;
    char minus = '-', zero = '0';
    char *converted = malloc(100*sizeof(int));
    if(num == 0){
        ret += write(sizeof(char), &zero, 1);
        return ret;
    } 
    else if(num < 0){
        ret+=write(sizeof(char), &minus, 1);
        num *= -1;
    } 
    converted = return_converted(num, base);
    int index = strlen(converted);
    while(index >= 0){
        ret+= write(sizeof(char), &converted[index], 1);
        index--;
    }
    free(converted);
    return ret-1;
}

int my_puthex(int hex){
    int temp, index = 0, ret = 0;
    char convertedHex[100];
    while(hex != 0){
        temp = hex % 16;
        if(temp < 10)
            temp += 48;
        else temp += 55;
        convertedHex[index] = temp;
        index++; 
        hex /= 16;
    }
    convertedHex[index] = '\0';
    while (index >= 0){
        ret += write(sizeof(char), &convertedHex[index], 1);
        index--;
    }
    return ret-1;
}

int my_putaddress(long address){
    int temp, index = 0, ret = 0;
    char convertedAddress[17], addressStart[2] = "0x";
    while(address!= '\0'){
        temp = address % 16;
        if(temp < 10)
        temp += 48;
        else temp += 55;
        convertedAddress[index] = temp;
        index++;
        address /= 16;
    }
    convertedAddress[index] = '\0';
    index = 0;
    while(convertedAddress[index] != '\0'){
        if(index == 0) ret+=write(sizeof(char),addressStart, 2);
        ret+= write(sizeof(char), &convertedAddress[index],1);
        index++;
    }
    return ret;
}

int my_printf(char* format, ...){
    va_list args;
    char *outputString, *s; //, enter = '\n', *newline =&enter
    int i, ret = 0;
    long l;
    va_start(args, format);

    for(outputString = format; *outputString != '\0'; outputString++){
        if(*outputString == '%'){
            outputString++;
             switch(*outputString){
                case 'c' : s = va_arg(args, char *);
                    ret += my_putchar(s); 
                    break;
                case 'd': i = va_arg(args, int);
                    ret += my_putint(i, 10);
                    break;
                case 's': s = va_arg(args, char*);
                    ret+= my_putstr(s);
                    break;
                case 'o': i = va_arg(args, int);
                    ret += my_putint(i, 8);
                    break;
                case 'u': i = va_arg(args, int);
                    ret += my_putint(i, 10);
                    break;
                case 'x': i = va_arg(args, int);
                    ret += my_puthex(i);
                    break;
                case 'p': l = va_arg(args, long);
                    ret+= my_putaddress(l);
                    break;
            }
        }
        else ret += write(1,outputString, 1);
    }    
    va_end(args);
    
    return ret;
}

