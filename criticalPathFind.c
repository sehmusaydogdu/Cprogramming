#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct{
	int id,es,ef,ls,lf,duration;
	int *sonraki,*onceki;

}Dugumler;

Dugumler *dugumler;


//Critical path
int n,i,j,sonrasi,oncesi,max=-1,min=1000;

void ustudoldur()
{
	dugumler[0].es=0;
	dugumler[0].ef=dugumler[0].duration+dugumler[0].es;
	for(i=1;i<n;i++) // Dugum
	{
		
		for(j=0;dugumler[i].onceki[j]!=0;j++) /// Baðlantýlar
		{
			int yer=dugumler[i].onceki[j];
			if(dugumler[yer-1].ef>max)
			   max=dugumler[yer-1].ef;
			dugumler[i].es=max;
			dugumler[i].ef=dugumler[i].duration+dugumler[i].es;
		}
		max=0;
	}
}

void altidoldur()
{
	dugumler[n-1].ls=dugumler[n-1].es;
	dugumler[n-1].lf=dugumler[n-1].ef;

	for(i=n-2;i>=0;i--) // Dugum
	{
		for(j=0;dugumler[i].sonraki[j]!=0;j++) /// Baðlantýlar
		{
			int yer=dugumler[i].sonraki[j];
			if(dugumler[yer-1].ls<min)
			    min=dugumler[yer-1].ls;
			dugumler[i].lf=min;
			dugumler[i].ls=dugumler[i].es+(dugumler[i].lf-dugumler[i].ef);
		}
		min=1000;
	}
}

void goster()
{
	system("CLS");
	printf("\n\nToplamda %d tane dugum var\n\n",n);
	for(i=0;i<n;i++)
	{
		printf("%d . dugumun id degeri        :  %d\n",i+1,dugumler[i].id);
		printf("%d . dugumun duration degeri  :  %d\n",i+1,dugumler[i].duration);
		printf("%d . dugumun (es %d  ---  ef  %d ) degeri  :  %d\n",i+1,dugumler[i].es,dugumler[i].ef,dugumler[i].duration);
	    printf("%d . dugumun (ls %d  ---  lf  %d ) degeri  :  %d\n",i+1,dugumler[i].ls,dugumler[i].lf,dugumler[i].duration);
	    
		printf("%d. dugumun oncesinin baglanti degerleri sunlardir...     \n",i+1);
        for(j=0;dugumler[i].onceki[j]!=0;j++)
        	printf("   -->>   %d dugumun oncesinin %d baglantisi  : %d  \n",i+1,j+1,dugumler[i].onceki[j]);
	
		printf("%d. dugumun sonrasinin baglanti degerleri sunlardir...   \n",i+1);
        
		for(j=0;dugumler[i].sonraki[j]!=0;j++)
        	printf("   -->>%d dugumun sonrasinin %d baglantisi : %d   \n",i+1,j+1,dugumler[i].sonraki[j]);
		
        printf("\n------------------------------------------------------\n");
	}
}

void bilgiGir()
{
	printf("Kac adet dugum gireceksiniz  :  ");
    scanf("%d",&n);
    dugumler=(Dugumler *)malloc(sizeof(Dugumler)*n);
    
	for(i=0;i<n;i++)
	{
		dugumler[i].id=i+1;
		printf("%d. dugumun duration degerini giriniz  :  ",i+1);
        scanf("%d",&dugumler[i].duration);
        
        printf("%d. dugumun sonrasinin kac baglantisi var  ?     :   ",i+1);
        scanf("%d",&sonrasi);
        
	    dugumler[i].sonraki=(int *)calloc(sonrasi,sizeof(int));
        for(j=0;j<sonrasi;j++)
        {
        	printf("%d dugumun sonrasinin %d baglantisini giriniz :   ",i+1,j+1);
        	scanf("%d",&dugumler[i].sonraki[j]);
		}
		printf("\n");
        
        printf("%d. dugumun oncesinin kac baglantisi var  ?     :   ",i+1);
        scanf("%d",&oncesi);
        
        dugumler[i].onceki=(int *)calloc(oncesi,sizeof(int));
        
		for(j=0;j<oncesi;j++)
        {
        	printf("%d dugumun oncesinin %d baglantisini giriniz :   ",i+1,j+1);
        	scanf("%d",&dugumler[i].onceki[j]);
		}
		printf("\n--------------------------------------------------------------\n");
	}
}

void kritikyolbul()
{
	printf("\n\nCritial Path  -->>   ");
	for(i=0;i<n;i++)
		if((dugumler[i].lf - dugumler[i].ef)==0)printf("%d  ",dugumler[i].id);
}



int main()
{
    bilgiGir();
    ustudoldur();
    altidoldur();
	goster();
    kritikyolbul();
}
