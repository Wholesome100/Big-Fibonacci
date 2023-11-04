//Name:Matthew Russo, ID:6605
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

HugeInteger *parseInt(unsigned int n)
{
    HugeInteger *ip=malloc(sizeof(HugeInteger));

    if(ip==NULL)//Guard in case malloc fails for ip
    {
        return NULL;
    }

    int digit, ext=0;
    unsigned int temp;

    temp=n;

    if(n==0)//Case when n=0
    {
        digit=1;
    }
    else
    {
        for(digit=0;temp!=0;digit++)//For loop to get how many digits are in n
        {
            temp/=10;
        }
    }

    ip->length=digit;//Set length equal to the number of n digits

    ip->digits=malloc(sizeof(int) * ip->length);//Allocate memory
    if(ip->digits==NULL)//Guard in case malloc fails
    {
        return NULL;
    }


    for(unsigned int i=0;i<ip->length;i++)//For loop extracts the digits from n
    {
        ext=n%10;//Extract digit and store it in ext
        ip->digits[i]=ext;//Assign position at i to value in ext
        n/=10;//Advance the integer
    }

    return ip;//Return struct when assignment is finished
}



HugeInteger *parseString(char *str)
{
    HugeInteger *sp=malloc(sizeof(HugeInteger));

    if(str==NULL || sp==NULL)//Guard for str and sp
    {
        return NULL;
    }

    if(strcmp(str,"")==0)//Special case if str is empty
    {
        sp->length=1;
        sp->digits=malloc(sizeof(int)*sp->length);
        if(sp->digits==NULL)//Guard if sp->digits is NULL
        {
            return NULL;
        }
        sp->digits[0]=0;
        return sp;
    }

    sp->length=strlen(str);//Assign length to the length of the string

    sp->digits=malloc(sizeof(int) * sp->length);//Allocate memory

    if(sp->digits==NULL)//Guard if malloc call fails
    {
        return NULL;
    }

    for(int i=0;i<sp->length;i++)//Convert integer characters and assign them to positions in digits
    {
        sp->digits[i]=str[sp->length-1-i]-'0';

    }

    return sp;//Return struct when assignment is finished
}



HugeInteger *hugeDestroyer(HugeInteger *p)
{
    if(p==NULL)//Guard for p being NULL
    {
        return NULL;
    }

        free(p->digits);//Free memory associated with p->digits
        free(p);//Free memory associated with p


    return NULL;//Return NULL for safety
}



unsigned int *toUnsignedInt(HugeInteger *p)
{
    if(p==NULL)//Return NULL if p is NULL
    {
        return NULL;
    }

    unsigned long long int total=0;//Total is long long because it needs to be determined if it's value greater than UINT_MAX

    unsigned int* ret=malloc(sizeof(unsigned int*));//Dynamically allocated unsigned int

    if(ret==NULL)//Guard if malloc fails
    {
        return NULL;
    }

    for(int i=p->length-1;i>=0;i--)//Backwards loop extracts MSD first and gradually builds to represented int
    {
        total=10*total+p->digits[i];

    }

    if(total>UINT_MAX)//Return NULL if total > UINT_MAX
    {
        return NULL;
    }

    ret[0]=total;//Cast total and return value equal to the total

    return ret;
}



HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q)
{

    if(p==NULL || q==NULL)//Null guards for the inputs
    {
        return NULL;
    }

    HugeInteger *sum=malloc(sizeof(HugeInteger));//Allocate memory
    if(sum==NULL)//Guard if malloc fails
    {
        return NULL;
    }

    int add1, add2, carry=0, temp;

    if(p->length >= q->length)//length is set to which is larger, p or q, and +1 for an extra value
    {
        sum->length=p->length+1;
    }
    else
    {
        sum->length=q->length+1;
    }

    sum->digits=malloc(sizeof(int)*sum->length);//Allocate for sum->digits
    if(sum->digits==NULL)//Guard if malloc fails
    {
        return NULL;
    }

    for(int i=0;i<sum->length;i++)//for loop, goes for the full length of sum->length
    {
        if(i<p->length)//Check if i is in bounds for p
        {
            add1=p->digits[i];//If i is in bounds add1 = value at element i
        }
        else
        {
            add1=0;//If i is out of bounds add1 = 0 to prevent weird values
        }


        if(i<q->length)//Same mechanics as above, but used for q
        {
            add2=q->digits[i];

        }
        else
        {
            add2=0;
        }

        temp=add1+add2+carry;//Addition of add1, add2, and carry

        carry=0;//Carry is reset to 0 after the addition

        if(temp>9)//Extract digit and carry the one if temp>9
        {
            temp=temp%10;
            carry=1;
        }

        sum->digits[i]=temp;//Assign value at sum->digits[i] to temp value

    }

    if(sum->digits[sum->length-1]==0)
    {
        sum->length-=1;//Dock the length if the extra digit isn't meaningful, preventing it from being printed
    }

    return sum;//Return sum when all addition is completed
}



HugeInteger *fib(int n)
{

HugeInteger *p=parseInt(0), *q=parseInt(1), *r=NULL;//p is the n-2 term and q is the n-1 term

if(p==NULL || q==NULL)//Guards in case p or q are NULL
{
    return NULL;
}

if(n<2)//Base cases for F(0) and F(1)
{
    return parseInt(n);//Base cases
}


for(int i=2;i<=n;i++)//For loop calculates up to F(n) while only having a few fibonacci numbers in memory
{
    r=hugeAdd(p,q);//F(n)=F(n-2)+F(n-1)

    if(r==NULL)//Guard in case r is NULL
    {
        return NULL;
    }

    p=q;//p becomes the F(n-2) term for the next value of n
    q=r;//q becomes the F(n-1) term for the next value of n
}

return q;//Return q when specified F(n) is reached
}



double hoursSpent(void)
{
    double time=5.5;//Took around 5 1/2 hours to complete
    return time;
}



double difficultyRating(void)
{
    double hard=4.0;//Difficult, it took me a while to finish
    return hard;
}
